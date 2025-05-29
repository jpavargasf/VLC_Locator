package com.example.vlclocator;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.graphics.ImageFormat;
import android.graphics.Matrix;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.ImageReader;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.text.Editable;
import android.text.InputType;
import android.text.TextWatcher;
import android.util.Log;
import android.util.Size;
import android.util.SparseIntArray;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Surface;
import android.view.TextureView;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class CameraActivity extends AppCompatActivity {

    public static final int PERMISSION_CODE_CAMERA = 0;
    public static final int PERMISSION_CODE_STORAGE = 1;

    private static final String TAG = "CameraActivity";

    //se falso, salva textureview, se verdadeiro, salva a imagem pela captura da câmera
    private final boolean mFlagSaveImage = true;

    //private final Long mShutterFrequency = Long.valueOf(10000);
    //private Long mShutterFrequency;
    private Long mShutterNanoSecOpen;

    private double mFreqMultFactor;
    private CameraDevice mCameraDevice;
    private CameraDevice.StateCallback mCameraDeviceStateCallback;

    private TextureView mTextureView;
    private TextureView.SurfaceTextureListener mSurfaceTextureListener;

    private CaptureRequest.Builder mCaptureRequestBuilder;

    private ImageReader mImageReader;

    private ImageReader.OnImageAvailableListener mOnImageAvailableListener;

    private CameraCaptureSession mCameraCaptureSession;
    private CameraCaptureSession.CaptureCallback mCaptureCallback;

    private HandlerThread mBackgroundHandlerThread;
    private Handler mBackgroundHandler;

    private String mCameraId;
    private String mBackgroundThreadName;

    private Size mTextureViewPreviewSize;
    private Size mCameraSize;
    private Size mSavableImageSize;

    private double[] mBestRatios;
    private int mLensFacing;
    private int mImageFormat;
    private String mFileFormat = ".jpg";
    private String mFileNameSuffix = "IMG";

    private String ipServerString;

    //0 - DLT
    //1 - P4P
    private int PnPMode;

    //0 - Dilatação
    //1 - Filtro passa baixa
    private int ImageProcessingMethod;
    private File mImgFolder;

    //private boolean fullSupport;

    //private MenuItem mMenuItemCaptureCamera;
    private boolean mEstaProcessando;

    private String mDesiredCameraId;
    private static SparseIntArray ORIENTATIONS = new SparseIntArray();
    static{
        ORIENTATIONS.append(Surface.ROTATION_0,0);
        ORIENTATIONS.append(Surface.ROTATION_90,90);
        ORIENTATIONS.append(Surface.ROTATION_180,180);
        ORIENTATIONS.append(Surface.ROTATION_270,270);
    }

    CameraCharacteristicsHolder mCameraCharacteristicsHolder;

    AlertDialog mAlertDialog;

    // Load the native library
    static {
        System.loadLibrary("native-lib");
    }

    // Declare the native method
    public native String stringFromJNI();
    //public native Array img2gray(Array image, int width, int height);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);

        checkWriteStoragePermission();

        findLayoutComponents();
        initializeConstants();
        setupListeners();




    }

    @Override
    protected void onResume(){
        super.onResume();

        startBackgroundThread();
        if(mTextureView.isAvailable()){
            openCamera();
        }else{
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
    }

    @Override
    protected void onPause(){

        closeCamera();
        stopBackgroundThread();

        super.onPause();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.camera_menu,menu);
        //mMenuItemCaptureCamera = menu.findItem(R.id.menu_main_capture_photo);
        return true;
    }

    //da para melhorar o codigo abaixo, mas vai dar um pouco de trabalho...
    @Override
    public boolean onOptionsItemSelected(MenuItem menuItem){
        AlertDialog.Builder adBuilder;
        int itemId = menuItem.getItemId();
        switch(itemId){
/*            case R.id.menu_main_settings:
                Intent settings_intent  = new Intent(this, CameraListActivity.class);
                //settings_intent.putExtra("camera_characteristics_holder", mCameraCharacteristicsHolder);
                startActivity(settings_intent);
                break;*/
            case R.id.menu_main_capture_photo:
                //desativa o menu de tirar foto para impedir que haja clique duplo
                //mMenuItemCaptureCamera.setEnabled(false);
                if(mEstaProcessando == true){
                    break;
                }
                mEstaProcessando = true;
                captureImage();
                break;

            case R.id.menu_main_change_mode_pnp:

                //AlertDialog alertDialog = null;
                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.change_mode_pnp);
                String auxString2 = getApplicationContext().getString(R.string.change_mode_pnp_description);

                if(PnPMode == 0){
                    auxString2 += "P6P - DLT";
                }else{
                    auxString2 += "P4P - Grunert";
                }

                adBuilder.setMessage(auxString2);

                adBuilder.setPositiveButton("DLT", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        PnPMode = 0;
                        mAlertDialog.dismiss();
                    }
                });
                adBuilder.setNeutralButton("P4P", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        PnPMode = 1;
                        mAlertDialog.dismiss();
                    }
                });
                adBuilder.setNegativeButton("Fechar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        mAlertDialog.dismiss();
                    }
                });

                mAlertDialog = adBuilder.create();
                mAlertDialog.show();

                break;
            case R.id.menu_main_change_image_processing_method:

                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.change_image_processing_method);
                String auxString3 = getApplicationContext().getString(R.string.change_image_processing_method_description);

                if(ImageProcessingMethod == 0){
                    auxString3 += "Dilatação";
                }else{
                    auxString3 += "Filtro Passa Baixa";
                }

                adBuilder.setMessage(auxString3);

                adBuilder.setPositiveButton("Dilatação", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        ImageProcessingMethod = 0;
                        mAlertDialog.dismiss();
                    }
                });
                adBuilder.setNeutralButton("Filtro Passa Baixa", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        ImageProcessingMethod = 1;
                        mAlertDialog.dismiss();
                    }
                });
                adBuilder.setNegativeButton("Fechar", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        mAlertDialog.dismiss();
                    }
                });

                mAlertDialog = adBuilder.create();
                mAlertDialog.show();

                break;
            case R.id.menu_main_specifications:
                //AlertDialog alertDialog = null;
                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.specifications);
                adBuilder.setMessage(mCameraCharacteristicsHolder.toString());
                adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        mAlertDialog.dismiss();
                    }
                });
                mAlertDialog = adBuilder.create();
                mAlertDialog.show();
                break;
            case R.id.menu_main_next_camera:
                //meio burro essa maneira de passar o id da camera mas fazer o que
                CameraManager cameraManager = (CameraManager) this.getSystemService(Context.CAMERA_SERVICE);
                //String newCameraId = null;
                boolean b = false;
                try {
                    for (String id : cameraManager.getCameraIdList()) {
                        if(b){
                            mDesiredCameraId = id;
                            b = false;
                            break;
                        }
                        if(id.equals(mCameraId)){
                            b = true;
                        }
                    }
                    if(b){
                        mDesiredCameraId = cameraManager.getCameraIdList()[0];
                    }
                } catch (CameraAccessException e) {
                    throw new RuntimeException(e);
                }
                closeCamera();
                openCamera();
                break;
            case R.id.menu_main_shutter_speed:



                final EditText editText = new EditText(this);
                editText.setInputType(InputType.TYPE_CLASS_NUMBER);
                LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
                editText.setLayoutParams(layoutParams);

                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.change_shutter_speed);
                String auxString;
                if(mShutterNanoSecOpen == Long.valueOf(0)){
                    auxString = getResources().getString(R.string.default_string);
                }else{
                    auxString = mShutterNanoSecOpen.toString();
                }
                String messageString = getApplicationContext().getString(R.string.current) + " " + auxString + "\n" +
                        getApplicationContext().getString(R.string.range) + " " + mCameraCharacteristicsHolder.getExposureTimeRange().toString() + "\n" +
                        getApplicationContext().getString(R.string.shutter_zero_value);
                adBuilder.setMessage(messageString);
                adBuilder.setPositiveButton(R.string.save, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        String etString = editText.getText().toString();
                        if(!etString.isEmpty()){
                            Long newValueOfNanoSeconds = Long.parseLong(etString);

                            if(newValueOfNanoSeconds == Long.valueOf(0) || mCameraCharacteristicsHolder.getExposureTimeRange().contains(newValueOfNanoSeconds)){
                                //Toast.makeText(getApplicationContext(),"Yes", Toast.LENGTH_LONG).show();
                                mShutterNanoSecOpen = newValueOfNanoSeconds;
                                startPreview();
                            }else{
                                Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();
                            }
                        }else{
                            Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();
                        }
                        //Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();

                        mAlertDialog.dismiss();
                    }
                });
                mAlertDialog = adBuilder.create();


                mAlertDialog.setView(editText);
                mAlertDialog.show();

                break;

            case R.id.menu_main_mult_factor:




                final EditText editText2 = new EditText(this);
                editText2.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL);
                LinearLayout.LayoutParams layoutParams2 = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
                editText2.setLayoutParams(layoutParams2);

                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.multiplication_factor);

                String stringMessage = getApplicationContext().getString(R.string.multiplication_factor_description) +
                        String.valueOf(mFreqMultFactor);

                adBuilder.setMessage(stringMessage);
                adBuilder.setPositiveButton(R.string.save, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        String etString = editText2.getText().toString();
                        if(!etString.isEmpty()){
                            double newMultFactor = Double.parseDouble(etString);

                            if(newMultFactor != 0){
                                //Toast.makeText(getApplicationContext(),"Yes", Toast.LENGTH_LONG).show();
                                mFreqMultFactor = newMultFactor;
                                //startPreview();
                            }else{
                                Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();
                            }
                        }else{
                            Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();
                        }
                        //Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();

                        mAlertDialog.dismiss();
                    }
                });
                mAlertDialog = adBuilder.create();


                mAlertDialog.setView(editText2);
                mAlertDialog.show();

                break;

            //case R.id.menu_main_display_resolution:
                //resolutionPopupMenu(View view, int id);
            //    break;
            case R.id.menu_main_ip_server:

                final EditText editText3 = new EditText(this);
                //editText3.setInputType(InputType.TYPE_CLASS_NUMBER);
                editText3.setInputType(InputType.TYPE_CLASS_TEXT);
                //editText3.set
                LinearLayout.LayoutParams layoutParams3 = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
                editText3.setLayoutParams(layoutParams3);
/*
                editText3.addTextChangedListener(new TextWatcher() {
                    private String currentText = "";
                    private boolean isUpdating = false;

                    @Override
                    public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

                    }

                    @Override
                    public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {

                    }

                    @Override
                    public void afterTextChanged(Editable editable) {
                        if(isUpdating){
                            return;
                        }

                        isUpdating = true;

                        String digitsOnly = editable.toString().replaceAll("[^\\d]", "");
                        StringBuilder ip = new StringBuilder();

                        int maxLength = Math.min(digitsOnly.length(), 12); // no máximo 12 dígitos

                        for (int i = 0; i < maxLength; i++) {
                            ip.append(digitsOnly.charAt(i));
                            if ((i == 2 || i == 5 || i == 8) && i != maxLength - 1) {
                                ip.append('.');
                            }
                        }
                        /*

                        StringBuilder ip = new StringBuilder();
                        String a = editable.toString();
                        int n  = 0;
                        int n_desde_ponto = 0;
                        //StringBuilder ip = new StringBuilder();
                        for(int i = 0; i < a.length(); i++){
                            n_desde_ponto++;
                            char c = a.charAt(i);
                            ip.append(c);
                            if(c == '.'){
                                n_desde_ponto = 0;
                                n++;
                            }else if(n_desde_ponto == 3){
                                if(n != 3){
                                    ip.append('.');
                                    n_desde_ponto = 0;
                                }else{
                                    break;
                                }
                            }
                        }

*//*
                        currentText = ip.toString();
                        editText3.setText(currentText);
                        editText3.setSelection(currentText.length());

                        isUpdating = false;
                    }
                });
*/
                adBuilder = new AlertDialog.Builder(this);
                adBuilder.setTitle(R.string.ip_server);

                String stringMessage2 = getApplicationContext().getString(R.string.ip_server_description);
                if(ipServerString == null){
                    stringMessage2 += "Automática";
                }else{
                    stringMessage2 += ipServerString;
                }

                adBuilder.setMessage(stringMessage2);
                adBuilder.setPositiveButton(R.string.save, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        String etString = editText3.getText().toString();
                        boolean validInput = true;
                        if(!etString.isEmpty()){
                            //contar quantos pontos tem
                            int n = 0;
                            for(int index = 0; index < etString.length(); index++){
                                char c = etString.charAt(index);
                                if(c == '.'){
                                    n++;
                                }
                            }
                            if(n != 3){
                                validInput = false;
                            }else {
                                String[] parts = etString.split("\\.");
                                if (parts.length == 4) {
                                    for (String part : parts) {
                                        for (int index = 0; index < part.length(); index++) {
                                            char c = part.charAt(index);
                                            if (c < '0' || c > '9') {
                                                validInput = false;
                                                break;
                                            }
                                        }
                                        if (validInput) {
                                            int val = Integer.parseInt(part);
                                            if (val <= 0 || val >= 255) {
                                                validInput = false;
                                                break;
                                            }
                                        } else {
                                            break;
                                        }
                                    }
                                } else {
                                    validInput = false;
                                }
                            }
                        }else{
                            validInput = false;
                        }
                        if(validInput){
                            //Toast.makeText(getApplicationContext(),R.string., Toast.LENGTH_LONG).show();
                            ipServerString = etString;
                            Toast.makeText(getApplicationContext(),ipServerString, Toast.LENGTH_LONG).show();
                        }else{
                            Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();
                            ipServerString = null;
                        }
                        //Toast.makeText(getApplicationContext(),R.string.invalid_value, Toast.LENGTH_LONG).show();

                        mAlertDialog.dismiss();
                    }
                });
                mAlertDialog = adBuilder.create();


                mAlertDialog.setView(editText3);
                mAlertDialog.show();


                break;
                /*
            case R.id.cpptest:
                adBuilder = new AlertDialog.Builder(this);
                String a = stringFromJNI();
                adBuilder.setTitle(a);
                adBuilder.setMessage(a);
                adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        mAlertDialog.dismiss();
                    }
                });
                mAlertDialog = adBuilder.create();
                mAlertDialog.show();
                break;
*/
            default:


        }

        return true;
    }

    //private void resolutionPopupMenu(View view, int id){
        //if()//
    //}
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults){
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch(requestCode){
            case PERMISSION_CODE_CAMERA:
                if(grantResults[0] == PackageManager.PERMISSION_DENIED){
                    Toast.makeText(this,getResources().getString(R.string.camera_permission_denied),
                            Toast.LENGTH_SHORT).show();
                }
                break;
            case PERMISSION_CODE_STORAGE:
                if(grantResults[0] == PackageManager.PERMISSION_DENIED){
                    Toast.makeText(this,getResources().getString(R.string.storage_permission_denied),
                            Toast.LENGTH_SHORT).show();
                }
                break;
            default:
                break;
        }
    }

    private void checkWriteStoragePermission(){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    == PackageManager.PERMISSION_DENIED) {
                if(shouldShowRequestPermissionRationale(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                    Toast.makeText(this, getResources().getString(R.string.storage_permission_needed), Toast.LENGTH_SHORT).show();
                }
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, PERMISSION_CODE_STORAGE);
            }
        }
    }

    private void findLayoutComponents(){
        mTextureView = (TextureView) findViewById(R.id.camera_textureView);
    }

    private void initializeConstants(){
        mBestRatios = new double[]{(double) 16 / (double) 9, (double) 4 / (double) 3};

        mLensFacing = CameraMetadata.LENS_FACING_BACK;
        mImageFormat = ImageFormat.JPEG;

        mBackgroundThreadName = "CameraActivity_backgroundThread";

        String folderName = getResources().getString(R.string.app_name);
        mImgFolder = SaveImageFileClass.createFolder(Environment.DIRECTORY_PICTURES, folderName);


        mDesiredCameraId = null;
        mAlertDialog = null;
        //mShutterFrequency = Long.valueOf(0);
        mShutterNanoSecOpen = Long.valueOf(61000);

        mFreqMultFactor = 4;
        //mFreqMultFactor = 3;
        //5.8 quando full hd
        //2 quando 4000x3000

        ipServerString = null;
        PnPMode = 0;
        ImageProcessingMethod = 0;
        mEstaProcessando = false;
    }


    private void openCamera(){
        setupCamera();
        connectCamera();
    }

    private void closeCamera(){
        if(mCameraDevice != null){
            mCameraDevice.close();
            mCameraDevice = null;
        }
    }



    private void captureImage(){
        if(mFlagSaveImage){//salva imagem da camera
            try {
                mCameraCaptureSession.capture(mCaptureRequestBuilder.build(),
                        mCaptureCallback, mBackgroundHandler);
            } catch (CameraAccessException e) {
                throw new RuntimeException(e);
            }
        }else{
            try {//salva imagem do preview
                File imgFile = SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder);
                mBackgroundHandler.post(new SaveImageFileClass(mTextureView, imgFile.getAbsolutePath(), getApplicationContext()));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

    }

    /*
    /startBackgroundThread
    /Descrição: Inicia a thread que cuidará de tarefas de processamento em background
    /           Chamada a partir de resume()
     */
    private void startBackgroundThread(){
        mBackgroundHandlerThread = new HandlerThread(mBackgroundThreadName);
        mBackgroundHandlerThread.start();
        mBackgroundHandler = new Handler(mBackgroundHandlerThread.getLooper());
    }

    /*
    /stopBackgroundThread
    /Descrição: Mata a thread que cuidará de tarefas de processamento em background
    /           Chamada a partir de pause()
     */
    private void stopBackgroundThread(){
        //sai assim que terminar as tarefas
        mBackgroundHandlerThread.quitSafely();
        try{
            //limpar recursos
            mBackgroundHandlerThread.join();
            mBackgroundHandlerThread = null;
            mBackgroundHandler = null;
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }

    /*
    /setupListeners
    /Descrição: Define os listener de
    /               CameraDevice.StateCallback
    /               TextureView.SurfaceTextureListener
    /               ImageReader.OnImageAvailableListener
    /               CameraCaptureSession.CaptureCallback
    */
    private void setupListeners() {
        mCameraDeviceStateCallback = new CameraDevice.StateCallback() {
            @Override
            public void onOpened(@NonNull CameraDevice cameraDevice) {
                mCameraDevice = cameraDevice;
                startPreview();
            }

            @Override
            public void onDisconnected(@NonNull CameraDevice cameraDevice) {
                cameraDevice.close();
                mCameraDevice = null;
            }

            @Override
            public void onError(@NonNull CameraDevice cameraDevice, int i) {
                cameraDevice.close();
                mCameraDevice = null;
            }
        };

        mSurfaceTextureListener = new TextureView.SurfaceTextureListener() {
            @Override
            public void onSurfaceTextureAvailable(@NonNull SurfaceTexture surfaceTexture, int width, int height) {
                mCameraSize = new Size(width, height);
                openCamera();
            }

            @Override
            public void onSurfaceTextureSizeChanged(@NonNull SurfaceTexture surfaceTexture, int width, int height) {

            }

            @Override
            public boolean onSurfaceTextureDestroyed(@NonNull SurfaceTexture surfaceTexture) {
                return false;
            }

            @Override
            public void onSurfaceTextureUpdated(@NonNull SurfaceTexture surfaceTexture) {

            }
        };

        /*
        if(!mTextureView.isAvailable()){
            mTextureView.setSurfaceTextureListener(mSurfaceTextureListener);
        }
        */
        mOnImageAvailableListener = new ImageReader.OnImageAvailableListener() {
            @Override
            public void onImageAvailable(ImageReader imageReader) {
                Log.d(TAG,"onImageAvailable");

                /*
                //para pegar resultado dda backgroundthread
                Handler mainHandler = new Handler(Looper.getMainLooper());


                //para processar imagem
                mBackgroundHandler.post(new ImageProcessing(imageReader.acquireLatestImage(),
                        getApplicationContext(),
                        mFileNameSuffix, mFileFormat, mImgFolder,
                        (double) mShutterNanoSecOpen / (1000000000), mFreqMultFactor,
                        new ImageProcessing.Callback(){
                            @Override
                            public void onProcessingComplete(Context context, double[] result){
                                mainHandler.post(new Runnable() {
                                    @Override
                                    public void run() {
                                        if(context == null){
                                            return;
                                        }
                                        AlertDialog.Builder adBuilder;
                                        adBuilder = new AlertDialog.Builder(context);
                                        adBuilder.setTitle(R.string.camera_position);
                                        String message;
                                        if(result != null){
                                            message = Arrays.toString(result);
                                        }else{
                                            message = "null";
                                        }
                                        adBuilder.setMessage(message);
                                        adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                                            @Override
                                            public void onClick(DialogInterface dialogInterface, int i) {
                                                if(mAlertDialog != null){
                                                    mAlertDialog.dismiss();
                                                }
                                            }
                                        });
                                        mAlertDialog = adBuilder.create();
                                        mAlertDialog.show();
                                    }
                                });
                            }
                        }));
                */

                //para pegar resultado dda backgroundthread
                Handler mainHandler = new Handler(Looper.getMainLooper(), new Handler.Callback() {
                    @Override
                    public boolean handleMessage(Message msg) {
                        AlertDialog.Builder adBuilder;
                        double[] result;
                        double[] Xo;
                        double[][] R_matrix;
                        double[][] K_matrix;

                        switch(msg.what){
                            case 1://apenas  aposição
                                //double[] result = (double[]) msg.obj; // Recuperar os dados
                                result = (double[]) msg.obj; // Recuperar os dados

                                //AlertDialog.Builder adBuilder = new AlertDialog.Builder(CameraActivity.this);
                                adBuilder = new AlertDialog.Builder(CameraActivity.this);
                                adBuilder.setTitle(R.string.camera_position);
                                adBuilder.setMessage(Arrays.toString(result));
                                adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {
                                        dialog.dismiss();
                                    }
                                });
                                adBuilder.create().show();
                                break;
                            case 2:
                                ipServerString = (String) msg.obj;
                                break;
                            default:
                                //3 para XoR e 4 para XoRK
                                if(msg.what != 3 && msg.what!= 4){
                                    break;
                                }

                                result = (double[]) msg.obj;
                                Xo = new double[3];
                                R_matrix = new double[3][3];
                                K_matrix = new double[3][3];

                                for(int i = 0; i < 3; i++){
                                    Xo[i] = result[i];
                                    for(int j = 0; j < 3; j++){
                                        R_matrix[i][j] = result[3 + 3 * i + j];
                                        if(msg.what == 4) {
                                            K_matrix[i][j] = result[12 + 3 * i + j];
                                        }
                                    }
                                }

                                String message =    "Xo = " + Arrays.toString(Xo);
                                message += "\nR = ";

                                for(int i = 0; i < 3; i++){
                                    message += Arrays.toString(R_matrix[i]);
                                }

                                if(msg.what == 4){
                                    message += "\nK = ";
                                    for(int i = 0; i < 3; i++){
                                        message += Arrays.toString(K_matrix[i]);
                                    }
                                }

                                adBuilder = new AlertDialog.Builder(CameraActivity.this);
                                adBuilder.setTitle(R.string.camera_position);
                                adBuilder.setMessage(message);
                                adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {
                                        dialog.dismiss();
                                    }
                                });
                                adBuilder.create().show();

                                Xo = null;
                                result = null;
                                R_matrix = null;
                                K_matrix = null;

                                break;
                        }
                        /*
                        if (msg.what == 1) { // Identificador da mensagem

                            double[] result = (double[]) msg.obj; // Recuperar os dados

                            AlertDialog.Builder adBuilder = new AlertDialog.Builder(CameraActivity.this);
                            adBuilder.setTitle(R.string.camera_position);
                            adBuilder.setMessage(Arrays.toString(result));
                            adBuilder.setPositiveButton(R.string.close, new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    dialog.dismiss();
                                }
                            });
                            adBuilder.create().show();
                        }
                        */

                        //habilita o botão de tirar foto novamente
                        //mMenuItemCaptureCamera.setEnabled(true);
                        mEstaProcessando = false;

                        return true;
                    }
                });


                //para processar imagem
                mBackgroundHandler.post(new ImageProcessing(imageReader.acquireLatestImage(),
                        getApplicationContext(),
                        mFileNameSuffix, mFileFormat, mImgFolder,
                        (double) mShutterNanoSecOpen / (1000000000), mFreqMultFactor,
                        mainHandler, ipServerString, PnPMode, ImageProcessingMethod));
                //5.8 quando full hd
                //2 quando 4000x3000

                //codigo abaixo para apenas salvar imagem
                /*
                File imgFile = null;
                try {
                    //imgFile = SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder);
                    //mBackgroundHandler.post(new SaveImageFileClass(imageReader.acquireLatestImage(), imgFile.getAbsolutePath(), getApplicationContext()));
                    mBackgroundHandler.post(new ImageProcessing(imageReader.acquireLatestImage(),getApplicationContext(),mFileNameSuffix, mFileFormat, mImgFolder));

                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                */
            }
        };


        mCaptureCallback = new CameraCaptureSession.CaptureCallback() {
            @Override
            public void onCaptureStarted(@NonNull CameraCaptureSession session, @NonNull CaptureRequest request, long timestamp, long frameNumber) {
                super.onCaptureStarted(session, request, timestamp, frameNumber);

                startStillCaptureRequest();
            }
        };

    }

    private void setupCamera(){
        CameraManager cameraManager = (CameraManager) this.getSystemService(Context.CAMERA_SERVICE);
        String newCameraId = null;
        try {
            if(BuildConfig.DEBUG) {
                for (String id : cameraManager.getCameraIdList()) {
                    CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(id);
                    CameraCharacteristicsHolder  cch= new CameraCharacteristicsHolder(cameraCharacteristics, id);
                    Log.d(TAG, cch.toString());
                }
            }
            if(mDesiredCameraId != null){
                for(String id : cameraManager.getCameraIdList()){
                    if(mDesiredCameraId.equals(id)){
                        newCameraId = id;
                        break;
                    }
                }
            }
            if(newCameraId == null){
                for(String id : cameraManager.getCameraIdList()){
                    CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(id);
                    if(cameraCharacteristics.get(CameraCharacteristics.LENS_FACING) == mLensFacing) {
                        newCameraId = id;
                        break;
                    }
                }
            }
            if(newCameraId != null){
                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(newCameraId);

                mCameraId = newCameraId;

                mCameraCharacteristicsHolder = new CameraCharacteristicsHolder(cameraCharacteristics, mCameraId);


                //Range<Long> exposure_time_range = cameraCharacteristics.get(CameraCharacteristics.SENSOR_INFO_EXPOSURE_TIME_RANGE);
                //long freq = 1000;
/*                if(exposure_time_range != null && exposure_time_range.contains(1000000000/mShutterFrequency)){
                    //set shutter speed
                    fullSupport = true;
                }else{
                    fullSupport = false;
                }*/



                //pegar todas as resoluções da câmera
                StreamConfigurationMap streamConfigurationMap = cameraCharacteristics.get(
                        CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
                mTextureViewPreviewSize = chooseOptimalSize(streamConfigurationMap.getOutputSizes(
                        SurfaceTexture.class));

                calculateTextureViewTransform();

                //mSavableImageSize = chooseOptimalSize(streamConfigurationMap.getOutputSizes(
                //        mImageFormat));

                mSavableImageSize = streamConfigurationMap.getOutputSizes(
                        mImageFormat)[0];

                //max images deve ser no mínimo 2 para usar o método ImageReader.acquireLatestImage();
                mImageReader = ImageReader.newInstance(mSavableImageSize.getWidth(), mSavableImageSize.getHeight(), mImageFormat, 2);
                mImageReader.setOnImageAvailableListener(mOnImageAvailableListener, mBackgroundHandler);
            }
/*            for(String id : cameraManager.getCameraIdList()){
                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(id);
                if(cameraCharacteristics.get(CameraCharacteristics.LENS_FACING) == mLensFacing){
*//*
                    Range<Long> exposure_time_range = cameraCharacteristics.get(CameraCharacteristics.SENSOR_INFO_EXPOSURE_TIME_RANGE);
                    if(isHardwareLevelSupported(cameraCharacteristics,CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_FULL)){
                        Log.d(TAG, "Hardware Support Level = FULL");
                    }else{
                        Log.d(TAG, "Hardware Support Level = NOT FULL");
                    }
*//*

                    Range<Long> exposure_time_range = cameraCharacteristics.get(CameraCharacteristics.SENSOR_INFO_EXPOSURE_TIME_RANGE);
                    //long freq = 1000;
                    if(exposure_time_range != null && exposure_time_range.contains(1000000000/mShutterFrequency)){
                        //set shutter speed
                        fullSupport = true;
                    }else{
                        fullSupport = false;
                    }

                    mCameraId = id;

                    //pegar todas as resoluções da câmera
                    StreamConfigurationMap streamConfigurationMap = cameraCharacteristics.get(
                            CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
                    mTextureViewPreviewSize = chooseOptimalSize(streamConfigurationMap.getOutputSizes(
                            SurfaceTexture.class));

                    calculateTextureViewTransform();

                    mSavableImageSize = chooseOptimalSize(streamConfigurationMap.getOutputSizes(
                            mImageFormat));
                    //max images deve ser no mínimo 2 para usar o método ImageReader.acquireLatestImage();
                    mImageReader = ImageReader.newInstance(mSavableImageSize.getWidth(), mSavableImageSize.getHeight(), mImageFormat, 2);
                    mImageReader.setOnImageAvailableListener(mOnImageAvailableListener, mBackgroundHandler);

                    return;
                }
            }*/


        }catch (CameraAccessException e){
            e.printStackTrace();
        }
    }

    /*
    /connectCamera
    /Descrição: Conecta à câmera, ou simplesmente a abre, após setupCamera
    /
     */

    private void connectCamera(){
        CameraManager cameraManager = (CameraManager) this.getSystemService(Context.CAMERA_SERVICE);
        try {
            //versão marshmallow ou acima do android requer que cheque permissão
            if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){

                if(ContextCompat.checkSelfPermission(this, android.Manifest.permission.CAMERA) ==
                        PackageManager.PERMISSION_GRANTED){
                    cameraManager.openCamera(mCameraId, mCameraDeviceStateCallback, mBackgroundHandler);
                }else{
                    //checa se já foi recusada a permissão
                    if(shouldShowRequestPermissionRationale(android.Manifest.permission.CAMERA)){
                        Toast.makeText(this, getResources().getString(R.string.camera_permission_denied),
                                Toast.LENGTH_LONG).show();
                    }
                    //requisita permissão novamente, que retornará com resultado com código PERMISSION_CODE_CAMERA
                    requestPermissions(new String[] {Manifest.permission.CAMERA}, PERMISSION_CODE_CAMERA);
                }

            }else{
                cameraManager.openCamera(mCameraId, mCameraDeviceStateCallback, mBackgroundHandler);
            }
        } catch (CameraAccessException e) {
            throw new RuntimeException(e);
        }
    }

    private void startPreview(){
        SurfaceTexture surfaceTexture = mTextureView.getSurfaceTexture();
        surfaceTexture.setDefaultBufferSize(mTextureViewPreviewSize.getWidth(), mTextureViewPreviewSize.getHeight());

        Surface previewSurface = new Surface(surfaceTexture);

        try{
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            mCaptureRequestBuilder.addTarget(previewSurface);

            configureCaptureRequestBuilder();

            mCameraDevice.createCaptureSession(
                    Arrays.asList(previewSurface, mImageReader.getSurface()),
                    new CameraCaptureSession.StateCallback() {
                        @Override
                        public void onConfigured(@NonNull CameraCaptureSession session) {
                            mCameraCaptureSession = session;
                            //caso dê certo
                            try{
                                //para fazer algo com os dados, é necessário ter um captureCallback, pelo
                                //que parece, no lugar do null
                                mCameraCaptureSession.setRepeatingRequest(mCaptureRequestBuilder.build(),
                                        null,mBackgroundHandler);
                            }catch(CameraAccessException e){
                                e.printStackTrace();
                            }

                        }

                        @Override
                        public void onConfigureFailed(@NonNull CameraCaptureSession cameraCaptureSession) {
                            //caso dê errado
                            Toast.makeText(getApplicationContext(),
                                    "Capture Session Configuration Failed",
                                    Toast.LENGTH_LONG).show();

                        }
                    },
                    null);
        }catch(CameraAccessException e){
            e.printStackTrace();
        }

    }

    private void startStillCaptureRequest(){
        Log.d(TAG, "startStillCaptureRequest");
        if(mCameraDevice == null){
            closeCamera();
            openCamera();
            Log.d(TAG, "mCameraDevice == null");
            return;
        }
        try {
            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
            mCaptureRequestBuilder.addTarget(mImageReader.getSurface());

            configureCaptureRequestBuilder();

            //para a rotação
            //captureRequestBuilder.set(CaptureRequest.JPEG_ORIENTATION, totalRotation);

            CameraCaptureSession.CaptureCallback stillCaptureCallback = new CameraCaptureSession.CaptureCallback() {
                @Override
                public void onCaptureStarted(@NonNull CameraCaptureSession session, @NonNull CaptureRequest request, long timestamp, long frameNumber) {
                    super.onCaptureStarted(session, request, timestamp, frameNumber);
/*
                    try {
                        //File imageFile = createImageFileName();
                        createImageFileName();

                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
*/
                }



            };

            //null porque já está na thread em background
            mCameraCaptureSession.capture(mCaptureRequestBuilder.build(), stillCaptureCallback, null);
        } catch (CameraAccessException e) {
            throw new RuntimeException(e);
        }
    }

    private void configureCaptureRequestBuilder(){
        //if(mShutterFrequency == Long.valueOf(0))  return;
        if(mShutterNanoSecOpen == Long.valueOf(0))  return;

        //checa se esta dentro do intervalo
        //Long nanoSecondsOpen = 1000000000 / mShutterFrequency;

        if(mCameraCharacteristicsHolder.getExposureTimeRange().contains(mShutterNanoSecOpen)){
            //autofocus off
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AF_MODE, CaptureRequest.CONTROL_AF_MODE_OFF);


            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_OFF);
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_MODE,CaptureRequest.CONTROL_MODE_OFF);
            //mCaptureRequestBuilder.set(CaptureRequest.SENSOR_EXPOSURE_TIME,Long.valueOf(1000000000)/mShutterFrequency);
            mCaptureRequestBuilder.set(CaptureRequest.SENSOR_EXPOSURE_TIME,mShutterNanoSecOpen);

            //mCaptureRequestBuilder.set(CaptureRequest.SENSOR_FRAME_DURATION, (long)500000000);
            //18/03/2025
            long frame_duration = mSavableImageSize.getHeight() * mShutterNanoSecOpen;
            mCaptureRequestBuilder.set(CaptureRequest.SENSOR_FRAME_DURATION, frame_duration);

            //para nao pegar outras fontes de luz
            //ISO 50
            mCaptureRequestBuilder.set(CaptureRequest.SENSOR_SENSITIVITY, 50);
            //mCaptureRequestBuilder.set(CaptureRequest.SENSOR_SENSITIVITY, mCameraCharacteristicsHolder.getISORange().getUpper());
            //long a = mCaptureRequestBuilder.get(CaptureRequest.SENSOR_SENSITIVITY);
            //mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AE_EXPOSURE_COMPENSATION, -2);

            //focus 10.0f

            //mCaptureRequestBuilder.set(CaptureRequest.LENS_FOCUS_DISTANCE, mCameraCharacteristicsHolder.getHyperfocalDistance());
            //mCaptureRequestBuilder.set(CaptureRequest.LENS_FOCUS_DISTANCE, (float) 1.0 );
            mCaptureRequestBuilder.set(CaptureRequest.LENS_FOCUS_DISTANCE, mCameraCharacteristicsHolder.getMinimumFocusDistance());
            //mCaptureRequestBuilder.set(CaptureRequest.LENS_FOCUS_DISTANCE, 9.9f);


        }

        /*if(fullSupport){
            //control ae mode off, para que não seja sobrescito o valor em sensor exposure time
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AE_MODE, CaptureRequest.CONTROL_AE_MODE_OFF);
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_MODE,CaptureRequest.CONTROL_MODE_OFF);
            mCaptureRequestBuilder.set(CaptureRequest.SENSOR_EXPOSURE_TIME,Long.valueOf(1000000000)/mShutterFrequency);//1ms = 1khz
        }
*/
        if(BuildConfig.DEBUG){
            Long j = mCaptureRequestBuilder.get(CaptureRequest.SENSOR_EXPOSURE_TIME);
            if(j != null){
                Log.d(TAG, j.toString());
                Log.d(TAG, mCaptureRequestBuilder.get(CaptureRequest.SENSOR_SENSITIVITY).toString());
            }
        }
    }



    /*
    /chooseOptimalSize
    /Descrição: Escolhe melhor tamanho.
    /           Usada para escolher o tamanho de preview de TextureView ou o tamanho da imagem salva.
    /           É escolhida de acordo com a razão de câmera ou com razões definidas em bestRatios.
     */
    private Size chooseOptimalSize(Size[] sizes){

        class CompareSizeByArea implements Comparator<Size> {

            //compara dois objetos
            //se size1>size2 retorna 1
            //se size1<size2 retorna -1
            //se size1==size2 retorna 0
            @Override
            public int compare(Size size1,Size size2){
                int result = size1.getWidth() * size1.getHeight() -
                        size2.getWidth() * size2.getHeight();

                if(result<0){
                    result = -1;
                } else if (result>0) {
                    result = 1;
                }

                return result;
            }

        }

        Size returnSize;

        //armazenar possíveis tamanhos
        List<Size> possibleSizeList = new ArrayList<Size>();
        List<Size> croppableSizeList = new ArrayList<Size>();

        double mainRatio = (double) mCameraSize.getWidth() / (double) mCameraSize.getHeight();

        Size displaySize = new Size(Resources.getSystem().getDisplayMetrics().widthPixels,
                Resources.getSystem().getDisplayMetrics().heightPixels);


        double actualRatio;
        double errorPercentage = 0.01;

        CompareSizeByArea compareSizeByArea = new CompareSizeByArea();

        for(Size size : sizes){
            actualRatio = (double) size.getWidth() / (double) size.getHeight();

            if(mainRatio <= actualRatio * (1 + errorPercentage) &&
                    mainRatio >= actualRatio * (1 - errorPercentage)){
                possibleSizeList.add(size);
            }else if(compareSizeByArea.compare(displaySize,size) == 1){
                for(int i = 0; i < mBestRatios.length; i++){
                    if(actualRatio <= mBestRatios[i] * (1 + errorPercentage) &&
                            actualRatio >= mBestRatios[i] * (1 - errorPercentage)){
                        croppableSizeList.add(size);
                    }
                }
            }
        }
        //achou tamanho na mesma proporção
        if(possibleSizeList.size() > 0){
            returnSize =  Collections.max(possibleSizeList, compareSizeByArea);
        }else {
            if (croppableSizeList.size() > 0) {
                //provavelmente eu pegue o de maior tamanho, que deve estar inicialmente na lista,
                //e encontre os valores de cropp
                returnSize = croppableSizeList.get(0);
            }else{
                returnSize =  sizes[0];
            }
        }
        return returnSize;
    }

    /*
    /calculateTextureViewTransform
    /Descrição: Calcula as razões do tamanho da câmera e textureView para que a imagem não fique
    /           esticada.
     */
    private void calculateTextureViewTransform(){

        Matrix transformMatrix;

        double imageRatio = (double) mCameraSize.getWidth() / (double) mCameraSize.getHeight();
        double previewRatio = (double) mTextureViewPreviewSize.getWidth() / (double) mTextureViewPreviewSize.getHeight();

        double rotation = ORIENTATIONS.get(mTextureView.getDisplay().getRotation());

        double scaleX;
        double scaleY;
        if(previewRatio < imageRatio){
            scaleX = 1 / (imageRatio * previewRatio);
            scaleY = 1;
        }else{
            scaleX = 1;
            scaleY = (imageRatio * previewRatio);
        }

        transformMatrix = new Matrix();
        transformMatrix.setScale( (float) scaleX, (float) scaleY, mTextureViewPreviewSize.getWidth() / 2, mTextureViewPreviewSize.getHeight() / 2);
        transformMatrix.postRotate((float) - rotation, mTextureViewPreviewSize.getWidth() / 2, mTextureViewPreviewSize.getHeight() / 2);

        mTextureView.setTransform(transformMatrix);
    }

}