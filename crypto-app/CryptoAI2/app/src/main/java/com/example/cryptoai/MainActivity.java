package com.example.cryptoai;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.navigation.NavigationBarView;

public class MainActivity extends AppCompatActivity implements OnCompleteListener {
    private EditText Email;
    private EditText Password;
    private BottomNavigationView bottombar;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Email=findViewById(R.id.etusername);
        Password=findViewById(R.id.etpassword);
        bottombar=findViewById(R.id.bottom_navigation);
        if (!foregroundServiceRunning()) {
            Intent serviceIntent = new Intent(this, MyForegroundService.class);
            startForegroundService(serviceIntent);
        }
        AppDataBase.getDatabase(getApplicationContext()).statDao().delete();
        AppDataBase2.getDataBase2(getApplicationContext()).HistoryDao().delete();
        bottombar.setOnItemSelectedListener(new NavigationBarView.OnItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                Intent intent;
                switch (item.getItemId()){
                    case R.id.page_1:
                        intent=new Intent(getApplicationContext(),MainActivity.class);
                        break;
                    case R.id.page_2:
                        intent=new Intent(getApplicationContext(),ContentActivity.class);
                        break;
                    case R.id.page_3:
                        intent=new Intent(getApplicationContext(),GraphActivity.class);
                        break;
                    case R.id.page_4:
                        intent=new Intent(getApplicationContext(),ContentActivity.class);
                        break;
                    default:
                        return onNavigationItemSelected(item);
                }
                startActivity(intent);
                return true;
            }
        });

    }
    public boolean foregroundServiceRunning() {
        ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : activityManager.getRunningServices(Integer.MAX_VALUE)) {
            if (MyForegroundService.class.getName().equals(service.service.getClassName())) {
                return true;
            }
        }
        return false;
    }

    public void login(View view) {
        String email=Email.getText().toString();
        String password=Password.getText().toString();
        FirebaseAuthUtil.loginUser(email,password,this);
    }

    public void become_a_client(View view) {
        Intent intent=new Intent(this,Newusers.class);
        startActivity(intent);
    }

    @Override
    public void onComplete(@NonNull Task task) {
        if(task.isSuccessful()){
            Intent intent=new Intent(this,ContentActivity.class);
            startActivity(intent);
        }
    }
}