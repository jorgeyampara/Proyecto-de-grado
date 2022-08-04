package com.jorgeyampara.raicesnuevo;

import android.os.Bundle;
import android.view.View;
import android.widget.Switch;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class LucesActivity extends AppCompatActivity {

    FirebaseAuth firebaseAuth;

    private int encendido=1;
    private Switch luz1,luz2,luz3;
    private DatabaseReference mDatabase;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_luces);
        mDatabase=FirebaseDatabase.getInstance().getReference();
        firebaseAuth = FirebaseAuth.getInstance();

        luz1 = (Switch) findViewById(R.id.luces1);
        luz2 = (Switch) findViewById(R.id.luces2);
        luz3 = (Switch) findViewById(R.id.luces3);

        luz1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String id = firebaseAuth.getCurrentUser().getUid();
                if(luz2.isChecked()){
                    mDatabase.child("Users").child(id).child("luz1").setValue(1);
                    //Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"funciona",Toast.LENGTH_LONG).show();

                }
                else{
                    mDatabase.child("Users").child(id).child("luz1").setValue(0);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"desactivado",Toast.LENGTH_LONG).show();
                }

            }
        });
        luz2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String id = firebaseAuth.getCurrentUser().getUid();
                if(luz2.isChecked()){
                    mDatabase.child("Users").child(id).child("luz2").setValue(1);
                    //Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"funciona",Toast.LENGTH_LONG).show();

                }
                else{
                    mDatabase.child("Users").child(id).child("luz2").setValue(0);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"desactivado",Toast.LENGTH_LONG).show();
                }

            }
        });
        luz3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String id = firebaseAuth.getCurrentUser().getUid();
                if(luz2.isChecked()){
                    mDatabase.child("Users").child(id).child("luz3").setValue(1);
                    //Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"funciona",Toast.LENGTH_LONG).show();

                }
                else{
                    mDatabase.child("Users").child(id).child("luz3").setValue(0);
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LucesActivity.this,"desactivado",Toast.LENGTH_LONG).show();
                }

            }
        });
    }
}