package com.arm.malideveloper.openglessdk.textureanimation;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private static final String LOGTAG = "MainActivity";

    protected TutorialView graphicsView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(LOGTAG, "Creating New Tutorial View");
        graphicsView = new TutorialView(getApplication());
        setContentView(graphicsView);
    }
	
    @Override protected void onPause()
    {
        super.onPause();
        graphicsView.onPause();
    }
	
    @Override protected void onResume()
    {
        super.onResume();
        graphicsView.onResume();
    }

}