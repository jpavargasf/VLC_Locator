package com.example.vlclocator;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.media.Image;
import android.os.Handler;
import android.os.Message;
import android.widget.Toast;

import com.example.vlclocator.SaveImageFileClass;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.sql.Array;
import java.util.Arrays;
import java.util.Calendar;

public class ImageProcessing implements Runnable{

    private final int METHOD;
    private final String mFileNameSuffix;
    private final String mFileFormat;

    private final File mImgFolder;

    private boolean mSaveImage;

    private Image mImage;

    private final Context mContext;

    private final double shutterOpenTime;

    private final double freqMultFactor;

    private final Handler mHandler;

    private String ipServerString;

    private final int PnPMode;

    /*
    private final Callback  mCallback;

    public interface Callback{
        void onProcessingComplete(Context context, double[] result);
    }
    */

    private class Images{

    }
    static {
        System.loadLibrary("native-lib");
    }
    public native int[] img2gray(int[] image, int width, int height);
    public native int[] blurImg(int[] image, int width, int height, int filterOrder);
    public native int[] imgBinarize(int[] image, int width, int height);
    public native int[] findBlobs(int[] image, int width, int height);

    public native int[] CheckFrequencies(int[] originalImg,
                                         int[] grayScaleImg,
                                         int width,
                                         int height,
                                         int[] blobCoordinates,
                                         int nBlobs,
                                         double pixelExposureTime,
                                         double freqMultFactor);
    public native int[] bwImgBoards(int[] image, int width, int height);

    public native int[] bwDilatation(int[] image, int width, int height, int filterOrder, int widthOrder);

    public native int[] CheckFrequenciesv2(int[] originalImg,
                                         int[] bwImg,
                                         int width,
                                         int height,
                                         int[] blobCoordinates,
                                         int nBlobs,
                                         double pixelExposureTime,
                                         double freqMultFactor);

    public native int[] CheckFrequenciesv3(int[] originalImg,
                                           int[] bwImg,
                                           int width,
                                           int height,
                                           int[] blobCoordinates,
                                           int nBlobs,
                                           double pixelExposureTime,
                                           double freqMultFactor);
/*
    static {
        System.loadLibrary("pnp_jni");
    }
*/
    public native double[] p4pJNI(double[] K,
                                  double[] rx,
                                  int[] sx);

    public native double[] p4pJNIXoR(double[] K,
                                  double[] rx,
                                  int[] sx);
    public native double[] p6pDLTJNI(double[] rx,
                                      int[] sx);

    public native double[] p6pDLTJNIXoRK(double[] rx,
                                     int[] sx);
    public native byte[] formatString(double[] Xo,
                                     int dia,
                                     int mes,
                                     int ano,
                                     int hora,
                                     int minuto,
                                     int segundo);
    public ImageProcessing(Image image, Context context, String fileNameSuffix, String fileFormat, File imgFolder, double shutterTimeOpen, double multFactorFreq, Handler mainHandler, String ipServer, int pnpMode, int ImgProcessingMethod){
        mImage = image;

        mContext = context;

        mFileNameSuffix = fileNameSuffix;
        mFileFormat =  fileFormat;
        mImgFolder = imgFolder;

        mSaveImage = true;

        shutterOpenTime = shutterTimeOpen;

        freqMultFactor = multFactorFreq;

        mHandler = mainHandler;

        ipServerString = ipServer;

        PnPMode = pnpMode;

        METHOD = ImgProcessingMethod;
    }

    public ImageProcessing(Image image){
        mImage = image;

        mContext = null;

        mFileNameSuffix = null;
        mFileFormat =  null;
        mImgFolder = null;

        mSaveImage = false;

        shutterOpenTime = -1;
        freqMultFactor = -1;

        mHandler = null;
        ipServerString = null;
        PnPMode = 0;//dlt
        METHOD = 0;//dilatação
    }

    @Override
    public void run(){
        double[] Xo = null;
        double[] XoRK = null;
        double[] XoR = null;
        int n1s = 0;

        //saveImage(mImage);
        int[] imgArray = img2array(mImage);
        saveImage(imgArray, mImage.getWidth(), mImage.getHeight());
        int[] grayImage = img2gray(imgArray, mImage.getWidth(), mImage.getHeight());
        //Image image = new Image()
        saveImage(grayImage, mImage.getWidth(), mImage.getHeight());
        //SaveImageFileClass.saveImageToFile(grayImage, SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder).getAbsolutePath(), mContext);

        //sqr(sqr(1080 * 1920)) =~ 38
        ///int filterOrder = 39;
        int filterOrder = (int) Math.pow(Math.pow(mImage.getWidth() * mImage.getHeight(), 0.5), 0.5);
        if(filterOrder % 2 == 0){
            filterOrder++;
        }


        if(METHOD == 1) {//BLUR


            int[] blurrImage = blurImg(grayImage, mImage.getWidth(), mImage.getHeight(), filterOrder);
            saveImage(blurrImage, mImage.getWidth(), mImage.getHeight());

            //grayImage = null;

            int[] bwImg = imgBinarize(blurrImage, mImage.getWidth(), mImage.getHeight());
            saveImage(bwImg, mImage.getWidth(), mImage.getHeight());

            blurrImage = null;

            n1s = numberOf1sInImage(bwImg, mImage.getWidth() * mImage.getHeight());
            if(n1s < (int)(0.15 * mImage.getWidth() * mImage.getHeight())){
                int[] boardImg = bwImgBoards(bwImg, mImage.getWidth(), mImage.getHeight());
                saveImage(boardImg, mImage.getWidth(), mImage.getHeight());

                int[] blobCoordinates = findBlobs(boardImg, mImage.getWidth(), mImage.getHeight());

                boardImg = null;

                //atualiza bwImg para ser compativel com os metodos desenvolvidos para a dilatação
                bwImg = null;
                bwImg = imgBinarize(grayImage, mImage.getWidth(), mImage.getHeight());

                grayImage = null;

                if(PnPMode == 0){
                    int[] imgWithCountoursAndMapping = CheckFrequenciesv3(imgArray, bwImg, mImage.getWidth(), mImage.getHeight(), blobCoordinates, blobCoordinates.length / 4, shutterOpenTime, freqMultFactor);
                    imgArray = null;
                    bwImg = null;

                    int[] imgWithCountours = Arrays.copyOfRange(imgWithCountoursAndMapping, 0, mImage.getWidth() * mImage.getHeight());
                    int[] mapping = Arrays.copyOfRange(imgWithCountoursAndMapping, mImage.getWidth() * mImage.getHeight(), mImage.getWidth() * mImage.getHeight() + blobCoordinates.length / 4);

                    saveImage(imgWithCountours, mImage.getWidth(), mImage.getHeight());

                    imgWithCountours = null;

                    //pontos        DCA     DCB     F1      F2      F3      F4
                    double[] rx = {-0.15,   0.45,   0,      0,      0.3,    0.3,
                            0.15,   0.15,   0.3,    0,      0,      0.3,
                            0.08,   0.08,   0.01,   0.01,   0.01,   0.01,
                            1,      1,      1,      1,      1,      1};

                    int[] sx = getCenterOfBlobs(blobCoordinates, mapping, 6);
                    //para teste vou usar pontos que eu já sei a posição.


                    //int[] sx = {1834, 1596, 1036, 1031,
                    //        1105, 2143, 1960, 1295,
                    //        1, 1, 1, 1};
                    //int[] sx = getCenterOfBlobs(blobCoordinates, mapping);



                    //colocar p6pdlt aqui
                    //Xo = p6pDLTJNI(rx, sx);

                    XoRK = p6pDLTJNIXoRK(rx, sx);
                    Xo = Arrays.copyOfRange(XoRK, 0, 3);
                    System.out.println("Xo: " + Arrays.toString(Xo));

                }else {
                    int[] imgWithCountoursAndMapping = CheckFrequenciesv2(imgArray, bwImg, mImage.getWidth(), mImage.getHeight(), blobCoordinates, blobCoordinates.length / 4, shutterOpenTime, freqMultFactor);
                    imgArray = null;
                    bwImg = null;

                    int[] imgWithCountours = Arrays.copyOfRange(imgWithCountoursAndMapping, 0, mImage.getWidth() * mImage.getHeight());
                    int[] mapping = Arrays.copyOfRange(imgWithCountoursAndMapping, mImage.getWidth() * mImage.getHeight(), mImage.getWidth() * mImage.getHeight() + blobCoordinates.length / 4);

                    saveImage(imgWithCountours, mImage.getWidth(), mImage.getHeight());

                    imgWithCountours = null;

                    //System.out.println("Mapeamento: " + Arrays.toString(mapping));

                /*
                double[] K = {2988.603737, 40.688782, 2175.006015,
                        0, 2977.833129, 1344.845743,
                        0, 0, 1};

                 */
                /*
                double[] K = {3000, 0, 2000,
                        0, 3000, 1500,
                        0, 0, 1};
                */
                    //checkered board K
                /*
                2997.26561678079	0	1969.05834609630
                0	2995.58260131049	1478.29861618836
                0	0	1
                    */
                    double[] K = {2997.26561678079, 0, 1969.05834609630,
                            0, 2995.58260131049, 1478.29861618836,
                            0, 0, 1};

                    double[] rx = {0, 0, 0.3, 0.3,
                            0.3, 0, 0, 0.3,
                            0, 0, 0, 0,
                            1, 1, 1, 1};
                    //double[] rx = {0.227, 0.237, 0.459, 0.507,
                    //        -0.015, 0.315, 0.328, 0.11,
                    //        0.15, 0.15, 0.15, 0.15,
                    //        1, 1, 1, 1};
                    int[] sx = getCenterOfBlobs(blobCoordinates, mapping, 4);
                    //para teste vou usar pontos que eu já sei a posição.


                    //int[] sx = {1834, 1596, 1036, 1031,
                    //        1105, 2143, 1960, 1295,
                    //        1, 1, 1, 1};
                    //int[] sx = getCenterOfBlobs(blobCoordinates, mapping);
                    //Xo = p4pJNI(K, rx, sx);
                    XoR = p4pJNIXoR(K, rx, sx);
                    Xo = Arrays.copyOfRange(XoR, 0, 3);
                    System.out.println("Xo: " + Arrays.toString(Xo));
                }
            }

            //int[] boardImg = bwImgBoards(bwImg, mImage.getWidth(), mImage.getHeight());
            //saveImage(boardImg, mImage.getWidth(), mImage.getHeight());

            //para a versao anterior
            //int[] blobImg = findBlobs(boardImg, mImage.getWidth(), mImage.getHeight());
            //saveImage(blobImg, mImage.getWidth(), mImage.getHeight());

            //nova versão de findBLobs, retorna as coordenadas dos blobs
            //int[] blobCoordinates = findBlobs(boardImg, mImage.getWidth(), mImage.getHeight());

            //int[] imgWithCountours = CheckFrequencies(imgArray, grayImage, mImage.getWidth(), mImage.getHeight(), blobCoordinates, blobCoordinates.length / 4, shutterOpenTime, freqMultFactor);
            //saveImage(imgWithCountours, mImage.getWidth(), mImage.getHeight());
        }else{//DILATAÇÃO
            int[] bwImg = imgBinarize(grayImage, mImage.getWidth(), mImage.getHeight());
            //int[] bwImgNPixels = imgBinarize(grayImage, mImage.getWidth(), mImage.getHeight());
            //int[] bwImg = Arrays.copyOfRange(bwImgNPixels, 0, mImage.getWidth() * mImage.getHeight());
            saveImage(bwImg, mImage.getWidth(), mImage.getHeight());
            //int nPixelsF = bwImgNPixels[mImage.getWidth() * mImage.getHeight()];
            //bwImgNPixels = null;

            //if(nPixelsF < (int)(0.125 * mImage.getWidth() * mImage.getHeight())) {

            grayImage = null;

            int[] dImg = bwDilatation(bwImg, mImage.getWidth(), mImage.getHeight(), filterOrder, (int) (5 + Math.pow(filterOrder, 0.5)));
            saveImage(dImg, mImage.getWidth(), mImage.getHeight());

            n1s = numberOf1sInImage(dImg, mImage.getWidth() * mImage.getHeight());
            if(n1s < (int)(0.15 * mImage.getWidth() * mImage.getHeight())) {


                int[] boardImg = bwImgBoards(dImg, mImage.getWidth(), mImage.getHeight());
                saveImage(boardImg, mImage.getWidth(), mImage.getHeight());

                dImg = null;

                int[] blobCoordinates = findBlobs(boardImg, mImage.getWidth(), mImage.getHeight());

                boardImg = null;

                if(PnPMode == 0){
                    int[] imgWithCountoursAndMapping = CheckFrequenciesv3(imgArray, bwImg, mImage.getWidth(), mImage.getHeight(), blobCoordinates, blobCoordinates.length / 4, shutterOpenTime, freqMultFactor);
                    imgArray = null;
                    bwImg = null;

                    int[] imgWithCountours = Arrays.copyOfRange(imgWithCountoursAndMapping, 0, mImage.getWidth() * mImage.getHeight());
                    int[] mapping = Arrays.copyOfRange(imgWithCountoursAndMapping, mImage.getWidth() * mImage.getHeight(), mImage.getWidth() * mImage.getHeight() + blobCoordinates.length / 4);

                    saveImage(imgWithCountours, mImage.getWidth(), mImage.getHeight());

                    imgWithCountours = null;

                    //pontos        DCA     DCB     F1      F2      F3      F4
                    double[] rx = {-0.15,   0.45,   0,      0,      0.3,    0.3,
                                    0.15,   0.15,   0.3,    0,      0,      0.3,
                                    0.083,   0.083,   0.013,   0.013,   0.013,   0.013,
                                    1,      1,      1,      1,      1,      1};

                    int[] sx = getCenterOfBlobs(blobCoordinates, mapping, 6);
                    //para teste vou usar pontos que eu já sei a posição.


                    //int[] sx = {1834, 1596, 1036, 1031,
                    //        1105, 2143, 1960, 1295,
                    //        1, 1, 1, 1};
                    //int[] sx = getCenterOfBlobs(blobCoordinates, mapping);



                    //colocar p6pdlt aqui
                    //Xo = p6pDLTJNI(rx, sx);

                    XoRK = p6pDLTJNIXoRK(rx, sx);
                    Xo = Arrays.copyOfRange(XoRK, 0, 3);
                    System.out.println("Xo: " + Arrays.toString(Xo));

                }else {
                    int[] imgWithCountoursAndMapping = CheckFrequenciesv2(imgArray, bwImg, mImage.getWidth(), mImage.getHeight(), blobCoordinates, blobCoordinates.length / 4, shutterOpenTime, freqMultFactor);
                    imgArray = null;
                    bwImg = null;

                    int[] imgWithCountours = Arrays.copyOfRange(imgWithCountoursAndMapping, 0, mImage.getWidth() * mImage.getHeight());
                    int[] mapping = Arrays.copyOfRange(imgWithCountoursAndMapping, mImage.getWidth() * mImage.getHeight(), mImage.getWidth() * mImage.getHeight() + blobCoordinates.length / 4);

                    saveImage(imgWithCountours, mImage.getWidth(), mImage.getHeight());

                    imgWithCountours = null;

                    //System.out.println("Mapeamento: " + Arrays.toString(mapping));

                /*
                double[] K = {2988.603737, 40.688782, 2175.006015,
                        0, 2977.833129, 1344.845743,
                        0, 0, 1};

                 */
                /*
                double[] K = {3000, 0, 2000,
                        0, 3000, 1500,
                        0, 0, 1};
                */
                    //checkered board K
                /*
                2997.26561678079	0	1969.05834609630
                0	2995.58260131049	1478.29861618836
                0	0	1
                    */
                    double[] K = {2997.26561678079, 0, 1969.05834609630,
                            0, 2995.58260131049, 1478.29861618836,
                            0, 0, 1};

                    double[] rx = {0, 0, 0.3, 0.3,
                            0.3, 0, 0, 0.3,
                            0.013, 0.013, 0.013, 0.013,
                            1, 1, 1, 1};
                    //double[] rx = {0.227, 0.237, 0.459, 0.507,
                    //        -0.015, 0.315, 0.328, 0.11,
                    //        0.15, 0.15, 0.15, 0.15,
                    //        1, 1, 1, 1};
                    int[] sx = getCenterOfBlobs(blobCoordinates, mapping, 4);
                    //para teste vou usar pontos que eu já sei a posição.


                    //int[] sx = {1834, 1596, 1036, 1031,
                    //        1105, 2143, 1960, 1295,
                    //        1, 1, 1, 1};
                    //int[] sx = getCenterOfBlobs(blobCoordinates, mapping);
                    //Xo = p4pJNI(K, rx, sx);
                    XoR = p4pJNIXoR(K, rx, sx);
                    Xo = Arrays.copyOfRange(XoR, 0, 3);
                    System.out.println("Xo: " + Arrays.toString(Xo));
                }

                //}
            }
        }
        if(Xo == null){
            Xo = new double[3];
            Xo[0] = 0;Xo[1] = 0;Xo[2] = 0;
        }
        mImage.close();
        sendPositionToTCP(Xo);
        if(mHandler != null){
            // 🔹 Chama o callback para enviar os dados para a UI thread
            Message msg;
            if(XoRK == null && XoR == null){
                msg = mHandler.obtainMessage(1, Xo);
            }else{
                if(PnPMode == 0){
                    if(XoRK == null){
                        XoRK = new double[21];
                        for(int i = 0; i < 21; i++){
                            XoRK[i] = 0;
                        }
                    }
                    msg = mHandler.obtainMessage(4, XoRK);
                }else{
                    if(XoR == null){
                        XoR = new double[21];
                        for(int i = 0; i < 12; i++){
                            XoR[i] = 0;
                        }
                    }
                    msg = mHandler.obtainMessage(3, XoR);
                }
            }
            mHandler.sendMessage(msg);
        }

    }

    private void sendPositionToTCP(double[] Xo){
        Calendar calendar = Calendar.getInstance();
        int ano = calendar.get(Calendar.YEAR);
        int mes = calendar.get(Calendar.MONTH) + 1;  // Janeiro é 0, então somamos 1
        int dia = calendar.get(Calendar.DAY_OF_MONTH);
        int hora = calendar.get(Calendar.HOUR_OF_DAY);  // Hora no formato 24 horas
        int minuto = calendar.get(Calendar.MINUTE);
        int segundo = calendar.get(Calendar.SECOND);

        byte[] mensagem = formatString(Xo, dia, mes, ano, hora, minuto, segundo);

        if(ipServerString == null){
            //descobrir o servidor
            try {
                DatagramSocket dsocket = new DatagramSocket();
                InetAddress endereco = InetAddress.getByName("255.255.255.255");
                byte[] byte_data = new byte[4];
                byte_data[0] = 'v';
                byte_data[1] = 'l';
                byte_data[2] = 'c';
                byte_data[3] = 'c';
                DatagramPacket pacote = new DatagramPacket(byte_data, byte_data.length, endereco, 8235);


                //DatagramSocket rxsocket = new DatagramSocket(8235);
                //rxsocket.setSoTimeout(3000);
                //dsocket.setSoTimeout(3000);
                byte[] buffer = new byte[1024];
                DatagramPacket pacote_rx = new DatagramPacket(buffer, buffer.length);
                boolean recebido = false;
                while(!recebido){
                    //DatagramSocket dsocket = new DatagramSocket();
                    dsocket.send(pacote);
                    //dsocket.close();

                    //DatagramSocket rxsocket = new DatagramSocket(8235);
                    //rxsocket.setSoTimeout(3000);
                    //DatagramPacket pacote_rx = new DatagramPacket(buffer, buffer.length);
                    //rxsocket.receive(pacote_rx);
                    dsocket.receive(pacote_rx);
                    String msg_rx = new String(pacote_rx.getData(), 0, pacote_rx.getLength());
                    if(msg_rx.length() == 4 && msg_rx.equals("vlcs")){
                        recebido = true;
                        ipServerString = pacote_rx.getAddress().getHostAddress();

                        //enviar para a thread principal
                        if(mHandler != null){
                            Message msg = mHandler.obtainMessage(2, ipServerString);
                            mHandler.sendMessage(msg);
                        }
                    }
                }


                //dsocket.send(pacote);
                dsocket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }



            //return;
        }

        try {
            Socket socket = new Socket(ipServerString, 8234); // IP e porta do servidor
/*//estava enviando 1 byte primeiro para depois enviar o restante
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

            for(int i = 0; i < 8; i++){
                dos.writeInt(mensagem[i]);
            }
            dos.close();

 */
            OutputStream os = socket.getOutputStream();
            os.write(mensagem); // ✅ envia os 32 bytes de uma vez
            os.flush();
            os.close();



            //OutputStream output = socket.getOutputStream();
            //PrintWriter writer = new PrintWriter(output, true);

            //writer.println("Olá servidor!");

            //BufferedReader reader = new BufferedReader(
            //        new InputStreamReader(socket.getInputStream(), "UTF-8"));

            //OutputStream out = socket.getOutputStream();
            //out.write("This is my message".getBytes("UTF-8"));
            //final String response = reader.readLine();

            // Para atualizar a UI, use runOnUiThread
            //((Activity) context).runOnUiThread(() -> {
            //    Toast.makeText(context, "Resposta: " + response, Toast.LENGTH_LONG).show();
            //});

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    //w - x
    //h - y
    //1 - 1
    private int[] getCenterOfBlobs(int[] blobCoordinates, int[] mapping, int nPontos){
        int nBLobs = mapping.length;
        if(blobCoordinates == null || mapping == null || nBLobs != (blobCoordinates.length / 4)){
            return null;
        }
        int[] center = new int[nPontos * 3];
        int numberOfPoints = 0;
        for(int i = 0; i < nBLobs; i++){
            if(mapping[i] != -1){
                numberOfPoints++;

                //faço o menos porque a calibração foi feita assim?
                //acho que tem mais a ver com o salvamento de imagens
                //center[mapping[i]] = 4000 - ((blobCoordinates[4 * i] + blobCoordinates[4 * i + 1]) / 2);
                //center[4 + mapping[i]] = 3000 - ((blobCoordinates[4 * i + 2] + blobCoordinates[4 * i + 3]) / 2);
                center[mapping[i]] = ((blobCoordinates[4 * i] + blobCoordinates[4 * i + 1]) / 2);
                center[nPontos + mapping[i]] = ((blobCoordinates[4 * i + 2] + blobCoordinates[4 * i + 3]) / 2);
                center[2 * nPontos + mapping[i]] = 1;
            }
        }
        if(numberOfPoints < nPontos){
            center = null;
        }
        System.out.println("center java: " + Arrays.toString(center));
        return center;
    }

    public static int numberOf1sInImage(int[] img, int nPixels){
        int n = 0;
        for(int i = 0; i < nPixels; i++){
            if((img[i] & 0x00FFFFFF) == 0x00FFFFFF){
                n++;
            }
        }
        return n;
    }
    public static int[] img2array(Image image) {
        if (image.getFormat() == ImageFormat.JPEG) {
            ByteBuffer buffer = image.getPlanes()[0].getBuffer();
            byte[] bytes = new byte[buffer.remaining()];
            buffer.get(bytes);

            Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
            int width = image.getWidth();
            int height = image.getHeight();
            int[] pixelArray = new int[width * height];
            bitmap.getPixels(pixelArray, 0, width, 0, 0, width, height);

            return pixelArray;
        } else {
            throw new UnsupportedOperationException("Unsupported image format: " + image.getFormat());
        }
    }

    private void saveImage(Image image){
        if(!mSaveImage) return;
        try {
            //SaveImageFileClass sifc = new SaveImageFileClass(image, SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder).getAbsolutePath(), mContext);
            SaveImageFileClass.saveImageToFile(image, SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder).getAbsolutePath(), mContext);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void saveImage(int[] image, int width, int height){
        if(!mSaveImage) return;


        // Create a bitmap with the specified width and height, and with ARGB_8888 format
        Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);

        // Set the pixels in the bitmap from the int array
        bitmap.setPixels(image, 0, width, 0, 0, width, height);

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();

        // Compress the bitmap to JPEG format with the specified quality
        bitmap.compress(Bitmap.CompressFormat.JPEG, 100, outputStream);

        // Convert the output stream to a byte array
        byte[] jpegData = outputStream.toByteArray();


        try {
            //SaveImageFileClass sifc = new SaveImageFileClass(image, SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder).getAbsolutePath(), mContext);
            SaveImageFileClass.saveImageToFile(jpegData, SaveImageFileClass.createFileName(mFileNameSuffix, mFileFormat, mImgFolder).getAbsolutePath(), mContext);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
