package com.example.cryptoai;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

public class Newusers extends AppCompatActivity implements OnCompleteListener {
    private EditText name;
    private EditText password;
    private EditText email;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.newusers);
        name=findViewById(R.id.etnewname);
        password=findViewById(R.id.etnewpassword);
        email=findViewById(R.id.etnewemail);
    }

    public void create(View view) {
        String emails=email.getText().toString();
        String passwords=password.getText().toString();
        FirebaseAuthUtil.createUser(emails,passwords,this);

    }

    @Override
    public void onComplete(@NonNull Task task) {
        if(task.isSuccessful()){
            Intent intent=new Intent(this,MainActivity.class);
            startActivity(intent);
        }
    }
    @Override
    protected void onStop() {
        super.onStop();
        finish();
    }

}
