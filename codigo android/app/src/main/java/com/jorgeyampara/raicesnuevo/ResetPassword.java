package com.jorgeyampara.raicesnuevo;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;

public class ResetPassword extends AppCompatActivity {
    private EditText editTextEmail;
    private Button botonEnviar;

    private String email;

    private FirebaseAuth firebaseAuth;

    private ProgressDialog progressDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reset_password);

        firebaseAuth = FirebaseAuth.getInstance();
        progressDialog = new ProgressDialog(this);

        editTextEmail = (EditText) findViewById(R.id.correo);
        botonEnviar = (Button) findViewById(R.id.enviarcorreo);

        botonEnviar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                email = editTextEmail.getText().toString();
                if (!email.isEmpty()){
                    progressDialog.setMessage("Espere un momento...");
                    progressDialog.setCanceledOnTouchOutside(false);
                    progressDialog.show();
                    resetPassword();
                }
                else {
                    Toast.makeText(com.jorgeyampara.raicesnuevo.ResetPassword.this, "Debe ingresar su Email",Toast.LENGTH_SHORT).show();
                }

            }
        });
    }
    private void resetPassword(){
        firebaseAuth.setLanguageCode("es");
        firebaseAuth.sendPasswordResetEmail(email).addOnCompleteListener(new OnCompleteListener<Void>() {
            @Override
            public void onComplete(@NonNull Task<Void> task) {

                if (task.isSuccessful()){
                    Toast.makeText(com.jorgeyampara.raicesnuevo.ResetPassword.this, "Se envio un correo para restablecer su contraseña",Toast.LENGTH_SHORT).show();
                }
                else {
                    Toast.makeText(com.jorgeyampara.raicesnuevo.ResetPassword.this, "No se pudo enviar el correo",Toast.LENGTH_SHORT).show();
                }
                progressDialog.dismiss();
            }
        });

    }
}