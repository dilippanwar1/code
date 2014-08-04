package com.marakana.compass;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;

public class Compass extends Activity implements SensorEventListener {
	SensorManager sensorManager;
	Sensor sensor;
	Rose rose;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // set full screen view
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        		WindowManager.LayoutParams.FLAG_FULLSCREEN); 
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        // Create new instance of custom Rose and set it on the screen
        rose = new Rose(this);
        setContentView(rose);
        
        // Get sensor and sensor manager
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
        Log.d("Compass", "onCreated");
    }

    // Register to listen to sensors @Override
    public void onResume() {
    	super.onResume(); 
    	sensorManager.registerListener(this, sensor,
    			SensorManager.SENSOR_DELAY_NORMAL);
    }
    
    
    // Unregister the sensor listener @Override
    public void onPause() {
    	super.onPause();
    	sensorManager.unregisterListener(this);
    }
    
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// We do not need this
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		int orientation = (int) event.values[0];
		Log.d("Compass", "Got sensor event: " + event.values[0]); 
		rose.setDirection(orientation);
	}
}
