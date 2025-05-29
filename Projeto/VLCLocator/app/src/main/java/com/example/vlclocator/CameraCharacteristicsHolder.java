package com.example.vlclocator;

import android.graphics.Camera;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraMetadata;
import android.util.Range;
import android.util.Size;
import android.view.Surface;

import java.io.Serializable;
import java.util.List;

public class CameraCharacteristicsHolder implements Serializable {

    private String mId;
    private int mLensFacing;
    private int mHardwareSupportLevel;

/*    private Long mExposureTime;*/
    private Range<Long> mExposureTimeRange;
    private Size[] mDisplaySizes;

    private Integer mFocusCalibration;

    private float mMinimumFocusDistance;
    private float mHyperfocalDistance;

    private Range<Integer> mISORange;



    public CameraCharacteristicsHolder(CameraCharacteristics cameraCharacteristics, String id){
        mId = id;
        setupCameraCharacteristics(cameraCharacteristics);
       /* mExposureTime = Long.valueOf(0);*/
    }

/*
    public CameraCharacteristicsHolder(CameraCharacteristics cameraCharacteristics, String id, Long ExposureTime){
        mId = id;
        setupCameraCharacteristics(cameraCharacteristics);
        mExposureTime = ExposureTime;
    }
*/

    public void setupCameraCharacteristics(CameraCharacteristics cameraCharacteristics){
        mHardwareSupportLevel = cameraCharacteristics.get(CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL);
        mLensFacing = cameraCharacteristics.get(CameraCharacteristics.LENS_FACING);
        mExposureTimeRange = cameraCharacteristics.get(CameraCharacteristics.SENSOR_INFO_EXPOSURE_TIME_RANGE);
        mDisplaySizes = cameraCharacteristics.get(
                CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP).getOutputSizes(
                        SurfaceTexture.class);

        mFocusCalibration = cameraCharacteristics.get(CameraCharacteristics.LENS_INFO_FOCUS_DISTANCE_CALIBRATION);
        mMinimumFocusDistance = cameraCharacteristics.get(CameraCharacteristics.LENS_INFO_MINIMUM_FOCUS_DISTANCE);
        mHyperfocalDistance = cameraCharacteristics.get(CameraCharacteristics.LENS_INFO_HYPERFOCAL_DISTANCE);
        mISORange = cameraCharacteristics.get(CameraCharacteristics.SENSOR_INFO_SENSITIVITY_RANGE);
    }
/*
    public void setExposureTime(Long exposureTime){
        mExposureTime = exposureTime;
    }

    public Long getExposureTime(){
        return mExposureTime;
    }*/
    public String getId(){
        return mId;
    }

    public int getLensFacing(){
        return mLensFacing;
    }

    public int getHardwareSupportLevel(){
        return mHardwareSupportLevel;
    }

    public Range<Long> getExposureTimeRange(){
        return mExposureTimeRange;
    }

    public Size[] getDisplaySizes(){
        return mDisplaySizes;
    }

    public float getMinimumFocusDistance(){
        return mMinimumFocusDistance;
    }

    public float getHyperfocalDistance(){
        return mHyperfocalDistance;
    }

    public Range<Integer> getISORange(){
        return mISORange;
    }
    @Override
    public String toString(){
        return "Id = " + mId + "\n" +
                "LensFacing = " + lensFacingToString(mLensFacing) + "\n" +
                "HardwareSupportLevel = " + hardwareSupportLevelToString(mHardwareSupportLevel) + "\n" +
                "ExposureTimeRange = " + exposureTimeRangeToString(mExposureTimeRange) + "\n" +
                "DisplaySizes = " + displaySizesToString(mDisplaySizes) + "\n" +
                "FocusCalibration = " + focusCalibrationToString(mFocusCalibration) + "\n" +
                "MinimumFocusDistance = " + Float.toString(mMinimumFocusDistance) + "\n" +
                "HyperfocalDistance = " + Float.toString(mHyperfocalDistance) + "\n" +
                "ISORange = " + isoRangeToString(mISORange);

    }

    public static boolean isHardwareLevelSupported(CameraCharacteristics c, int requiredLevel) {
        final int[] sortedHwLevels = {
                CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY,
                CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_EXTERNAL,
                CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LIMITED,
                CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_FULL,
                CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_3
        };
        int deviceLevel = c.get(CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL);
        if (requiredLevel == deviceLevel) {
            return true;
        }

        for (int sortedlevel : sortedHwLevels) {
            if (sortedlevel == requiredLevel) {
                return true;
            } else if (sortedlevel == deviceLevel) {
                return false;
            }
        }
        return false; // Should never reach here
    }
    private static String hardwareSupportLevelToString(int hardwareSupportLevel){
        switch(hardwareSupportLevel){
            case CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY:
                return "LEGACY";
            case CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_EXTERNAL:
                return "EXTERNAL";
            case CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LIMITED:
                return "LIMITED";
            case CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_FULL:
                return "FULL";
            case CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_3:
                return "LEVEL 3";
            default:
                return "null";
        }
    }

    private static String lensFacingToString(int lensFacing){
        switch(lensFacing){
            case CameraCharacteristics.LENS_FACING_BACK:
                return "BACK";
            case CameraCharacteristics.LENS_FACING_FRONT:
                return "FRONT";
            case CameraCharacteristics.LENS_FACING_EXTERNAL:
                return "EXTERNAL";
            default:
                return "null";
        }
    }

    private static String exposureTimeRangeToString(Range<Long> exposureTimeRange){
        if(exposureTimeRange == null){
            return "null";
        }
        return exposureTimeRange.toString();
    }

    private static String displaySizesToString(Size[] displaySizes){
        if(displaySizes == null){
            return "null";
        }
        String returnString = "";
        for(Size size:displaySizes){
            //acho q n é o melhor método, mas fazer o q
            returnString += "[" + size.toString() + "]";
        }
        return returnString;
    }

    private static String focusCalibrationToString(Integer focusCalibration){
        if(focusCalibration == null){
            return "null";
        }
        String returnValue;
        switch (focusCalibration) {
            case CameraCharacteristics.LENS_INFO_FOCUS_DISTANCE_CALIBRATION_UNCALIBRATED:
                returnValue = "Uncalibrated";
                break;
            case CameraCharacteristics.LENS_INFO_FOCUS_DISTANCE_CALIBRATION_APPROXIMATE:
                returnValue = "Approximate";
                break;
            case CameraCharacteristics.LENS_INFO_FOCUS_DISTANCE_CALIBRATION_CALIBRATED:
                returnValue = "Calibrated";
                break;
            default:
                returnValue = "Unknown";
                break;
        }
        return returnValue;
    }

    private static String isoRangeToString(Range<Integer> isoRange){
        if(isoRange == null){
            return "null";
        }
        return isoRange.toString();
    }
}