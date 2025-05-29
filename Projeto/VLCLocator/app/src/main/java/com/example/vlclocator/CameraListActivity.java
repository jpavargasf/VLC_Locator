package com.example.vlclocator;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraManager;
import android.os.Bundle;
import android.view.Menu;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

//está crashando e n sei pq
public class CameraListActivity extends AppCompatActivity {

    private ListView mListView;

    private List<CameraCharacteristicsHolder> mCameraCharacteristicsHolderList;

    ArrayAdapter<CameraCharacteristicsHolder> mArrayAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_list);

        mCameraCharacteristicsHolderList = new ArrayList<CameraCharacteristicsHolder>();

        CameraManager cameraManager = (CameraManager) this.getSystemService(Context.CAMERA_SERVICE);
        try {
            for(String id : cameraManager.getCameraIdList()) {
                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(id);
                CameraCharacteristicsHolder cch = new CameraCharacteristicsHolder(cameraCharacteristics,id);
                mCameraCharacteristicsHolderList.add(cch);
            }
        } catch (CameraAccessException e) {
            throw new RuntimeException(e);
        }


        mListView = (ListView) findViewById(R.id.camera_list_activity_listview);
        mArrayAdapter = new ArrayAdapter<CameraCharacteristicsHolder>(this, R.layout.activity_camera_list, mCameraCharacteristicsHolderList);
        mListView.setAdapter(mArrayAdapter);

    }

    public boolean onCreateOptionsMenu(Menu menu) {
        //getMenuInflater().inflate(R.menu.camera_menu, menu);
        return true;
    }

    @Override
    protected void onResume(){
        super.onResume();
        //mListView.setAdapter(mArrayAdapter);
    }
    @Override
    protected void onPause(){
        super.onPause();
    }

}