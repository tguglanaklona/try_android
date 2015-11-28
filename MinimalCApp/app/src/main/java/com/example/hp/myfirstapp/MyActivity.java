package com.example.hp.myfirstapp;

import android.os.Bundle;
import android.os.Build;
import android.view.Window;
import android.view.WindowManager;
import android.view.View;
import android.widget.TextView;
import android.app.ActionBar;
import android.support.v7.app.AppCompatActivity;

public class MyActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstanceState);

        // hide the status bar
        if (Build.VERSION.SDK_INT < 16) {
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                    WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
        else if (Build.VERSION.SDK_INT < 19) {
            View decorView = getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_FULLSCREEN;
            decorView.setSystemUiVisibility(uiOptions);
            ActionBar actionBar = getActionBar();
            actionBar.hide();
        }
        else{
            View decorView = getWindow().getDecorView();
            decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_LOW_PROFILE | View.SYSTEM_UI_FLAG_FULLSCREEN);
            //(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);//(View.SYSTEM_UI_FLAG_IMMERSIVE | View.SYSTEM_UI_FLAG_FULLSCREEN);
        }

        TextView tv = new TextView(this);
        tv.setText(HelloJNI());
        setContentView(tv);

        //setContentView(R.layout.activity_my);
        //Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        //setSupportActionBar(toolbar);
    }

    public native String HelloJNI();
    static
    {
        System.loadLibrary("HelloJNI");
    }
}
