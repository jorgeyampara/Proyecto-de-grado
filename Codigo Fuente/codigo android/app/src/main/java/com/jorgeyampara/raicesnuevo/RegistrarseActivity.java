package com.jorgeyampara.raicesnuevo;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;
import java.util.Map;

public class RegistrarseActivity extends AppCompatActivity {

    private EditText nombreUsuario;
    private EditText correoElectronico;
    private EditText contraseña;
    private Button botonRegistrarse;

    //variables de los datos del usuario

    private String name;
    private String email;
    private String password;


    FirebaseAuth firebaseAuth;
    DatabaseReference databaseReference;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.acitivity_registrarse);

        firebaseAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference();



        nombreUsuario = (EditText) findViewById(R.id.usuario);
        correoElectronico = (EditText) findViewById(R.id.correo);
        contraseña = (EditText) findViewById(R.id.contraseña);

        botonRegistrarse = (Button) findViewById(R.id.registrarse);
        botonRegistrarse.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                name = nombreUsuario.getText().toString();
                email = correoElectronico.getText().toString();
                password = contraseña.getText().toString();

                if (!name.isEmpty() && !email.isEmpty() && !password.isEmpty()){

                    if (password.length() >=6){
                        Toast.makeText(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, "Registro exitoso",Toast.LENGTH_SHORT).show();
                        registarUsuario();
                    }
                    else {
                        Toast.makeText(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, "La contarseña debe tener al menos 6 caracteres", Toast.LENGTH_SHORT).show();
                    }

                }
                else {
                    Toast.makeText(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, "Debe completar todos los datos",Toast.LENGTH_SHORT).show();
                }

            }
        });

   }

   private void registarUsuario(){
        firebaseAuth.createUserWithEmailAndPassword(email,password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if (task.isSuccessful()){
                    Map<String, Object> map = new HashMap<>();
                    map.put("name",name);
                    map.put("email", email);
                    map.put("paswword", password);
                    map.put("temperatura",0);
                    map.put("pH", 0);
                    map.put("electroconductividad", 0);
                    map.put("bomba", 0);
                    map.put("mezcla", 0);
                    map.put("luz1", 0);
                    map.put("luz2", 0);
                    map.put("luz3", 0);

                    String id = firebaseAuth.getCurrentUser().getUid();

                    databaseReference.child("Users").child(id).setValue(map).addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(@NonNull Task<Void> task2) {
                            if (task2.isSuccessful()){

                                FirebaseUser user = firebaseAuth.getCurrentUser();
                                user.sendEmailVerification();

                                startActivity(new Intent(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, com.jorgeyampara.raicesnuevo.LoginActivity.class));
                                finish();
                            }
                            else {
                                Toast.makeText(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, "No se pudo registrar ",Toast.LENGTH_SHORT).show();
                            }

                        }
                    });
                }
                else {
                    Toast.makeText(com.jorgeyampara.raicesnuevo.RegistrarseActivity.this, "No se pudo registrar ",Toast.LENGTH_SHORT).show();
                }
            }
        });
   }
}


