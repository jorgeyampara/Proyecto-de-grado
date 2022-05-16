package com.jorgeyampara.raicesnuevo;

import android.os.Bundle;
import android.view.View;
import android.widget.Switch;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class LucesActivity extends AppCompatActivity {
    private int encendido=1;
    private Switch luz2;
    private DatabaseReference mDatabase;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_luces);
        mDatabase=FirebaseDatabase.getInstance().getReference();

        luz2 = (Switch) findViewById(R.id.luces2);
        luz2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(luz2.isChecked()){
                    mDatabase.child("Users").child("luz").setValue(1);
                    //Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"funciona",Toast.LENGTH_LONG).show();

                }
                else{
                    mDatabase.child("Users").child("luz").setValue(0);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"desactivado",Toast.LENGTH_LONG).show();
                }

            }
        });
    }
}