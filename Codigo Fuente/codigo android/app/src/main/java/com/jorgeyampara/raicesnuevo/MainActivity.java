package com.jorgeyampara.raicesnuevo;


import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private Button botonLuces;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        botonLuces = (Button) findViewById(R.id.luces);
        botonLuces.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(com.jorgeyampara.raicesnuevo.MainActivity.this, LucesActivity.class));
            }
        });
    }
}