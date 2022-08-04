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

public class LoginActivity extends AppCompatActivity {
    private EditText Correo;
    private EditText Contraseña;
    private Button botonIniciarSecion;
    private Button botonCrearCuenta;
    private Button reestablecerContraseña;
    //variables de los datos del usuario

    FirebaseAuth firebaseAuth;

    private String name;
    private String email;
    private String password;

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        firebaseAuth = FirebaseAuth.getInstance();


        Correo = (EditText) findViewById(R.id.correoElectronico);
        Contraseña = (EditText) findViewById(R.id.contraseña);
        botonCrearCuenta = (Button) findViewById(R.id.crearCuenta);
        botonIniciarSecion = (Button) findViewById(R.id.iniciarSecion);
        reestablecerContraseña = (Button) findViewById(R.id.reestablecerPassword);


        //boton crear cuenta
        botonCrearCuenta.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(com.jorgeyampara.raicesnuevo.LoginActivity.this, RegistrarseActivity.class));
            }
        });


        //boton reestablecer contraseña
        reestablecerContraseña.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(com.jorgeyampara.raicesnuevo.LoginActivity.this, ResetPassword.class));
            }
        });

        //boton inisiar sesion
        botonIniciarSecion.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                email= Correo.getText().toString();
                password = Contraseña.getText().toString();

                if (!email.isEmpty() && !password.isEmpty()){
                    FirebaseAuth.getInstance().signInWithEmailAndPassword(email,password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {


                        @Override
                        public void onComplete(@NonNull Task<AuthResult> task) {
                            String id = firebaseAuth.getCurrentUser().getUid();

                            if (task.isSuccessful()){
                                FirebaseUser user = firebaseAuth.getCurrentUser();
                                if (!user.isEmailVerified()){
                                    Toast.makeText(com.jorgeyampara.raicesnuevo.LoginActivity.this, "Correo elctronico no verificado",Toast.LENGTH_SHORT).show();
                                }
                                else{
                                    startActivity(new Intent(com.jorgeyampara.raicesnuevo.LoginActivity.this, MainActivity.class));
                                    finish();
                                    }

                            }
                            else {
                                Toast.makeText(com.jorgeyampara.raicesnuevo.LoginActivity.this, "Usuario o contraseña incorrecto",Toast.LENGTH_SHORT).show();
                            }

                        }
                    });
                }
                else {
                    Toast.makeText(com.jorgeyampara.raicesnuevo.LoginActivity.this, "Debe completar todos los campos",Toast.LENGTH_SHORT).show();
                }
            }
        }
        );

    }
}
