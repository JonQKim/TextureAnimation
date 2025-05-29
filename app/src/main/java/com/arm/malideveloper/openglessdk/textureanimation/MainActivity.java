package com.arm.malideveloper.openglessdk.textureanimation;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import java.io.File;
import java.io.InputStream;
import java.io.RandomAccessFile;

public class MainActivity extends AppCompatActivity {
    private static final String LOGTAG = "MainActivity";

    protected TutorialView graphicsView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(LOGTAG, "Creating New Tutorial View");

        /* [publicPrivateCacheFileLocations] */
        String privateAssetDirectory = getFilesDir().getAbsolutePath();
        Log.i(LOGTAG, "privateAssetDirectory's path is equal to: " + privateAssetDirectory);
        /* [publicPrivateCacheFileLocations] */

        /* [callExtractAssets] */
        String[] privateApplicationFileNames = {
                "1.raw", "2.raw", "3.raw",
                "4.raw", "5.raw", "6.raw",
                "7.raw", "8.raw", "9.raw"
        };
        for(String privateApplicationFileName : privateApplicationFileNames) {
            extractAsset(privateApplicationFileName, privateAssetDirectory);
        }
        /* [callExtractAssets] */

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

    /* [extractAssetBeginning] */
    private void extractAsset(String assetName, String assetPath) {
        File fileTest = new File(assetPath, assetName);

        if (fileTest.exists()) {
            Log.d(LOGTAG, assetName + " already exists no extraction needed\n");
        } else {
            Log.d(LOGTAG, assetName + " doesn't exist extraction needed \n");
            /* [extractAssetBeginning] */
            /* [extractAssets] */
            try {
                RandomAccessFile out = new RandomAccessFile(fileTest, "rw");
                AssetManager am = getResources().getAssets();

                InputStream inputStream = am.open(assetName);
                byte buffer[] = new byte[1024];
                int count = inputStream.read(buffer, 0, 1024);

                while (count > 0) {
                    out.write(buffer, 0, count);
                    count = inputStream.read(buffer, 0, 1024);
                }
                out.close();
                inputStream.close();
            }
            /* [extractAssets] */
            /*  [extractAssetsErrorChecking] */ catch (Exception e) {
                Log.e(LOGTAG, "Failure in extractAssets(): " + e.toString() + " " + assetPath + assetName);
            }
            if (fileTest.exists()) {
                Log.d(LOGTAG, "File Extracted successfully");
            }
            /*  [extractAssetsErrorChecking] */
        }
    }
}