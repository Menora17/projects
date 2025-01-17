package com.example.cryptoai;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.Nullable;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;

public class MyForegroundService extends Service {

    public Context context=this;
    int time;
    boolean check;
    @Override
    public void onCreate() {
        super.onCreate();
        time = 0;
    }
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Timer();


        final String CHANNELID = "Foreground Service ID";
        NotificationChannel channel = new NotificationChannel(
                CHANNELID,
                CHANNELID,
                NotificationManager.IMPORTANCE_LOW
        );

        getSystemService(NotificationManager.class).createNotificationChannel(channel);
        Notification.Builder notification = new Notification.Builder(this, CHANNELID)
                .setContentText("Service is running")
                .setContentTitle("Service enabled")
                .setSmallIcon(R.drawable.ic_launcher_background);

        startForeground(1001, notification.build());


        return super.onStartCommand(intent, flags, startId);
    }



    private void Timer() {
        final Handler handler = new Handler();

        handler.post(new Runnable() {


            @Override
            public void run() {
                handler.postDelayed(this, 1000);
                time++;
                int mins=0;
                if(time%60==0){
                    mins++;
                }
                if (time==1||mins%5==0&&mins!=0) {
                    Log.e("Service", "5 min");
                    getData();

                }


            }
        });
    }

    private void getData() {
        // creating a variable for storing our string.


        String url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest";
        // creating a variable for request queue.
        RequestQueue queue = Volley.newRequestQueue(context);
        // making a json object request to fetch data from API.
        JsonObjectRequest jsonObjectRequest = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                // inside on response method extracting data
                // from response and passing it to array list
                // on below line we are making our progress
                // bar visibility to gone.

                AppDataBase dataBase = AppDataBase.getDatabase(context);
                AppDataBase2 dataBaseH = AppDataBase2.getDataBase2(context);
                Calendar calendar = Calendar.getInstance();
                SimpleDateFormat days = new SimpleDateFormat("dd");
                SimpleDateFormat dates = new SimpleDateFormat("HHmm");
                SimpleDateFormat mins = new SimpleDateFormat("mm");
                SimpleDateFormat weeks = new SimpleDateFormat("WWdd");
                //int week=0;
                try {
                    // extracting data from json.
                    JSONArray dataArray = response.getJSONArray("data");
                    for (int i = 0;dataArray.length()>i ; i++) {
                        JSONObject dataObj = dataArray.getJSONObject(i);
                        String symbol = dataObj.getString("symbol");
                        Log.e("Service", "test");
                        String name = dataObj.getString("name");
                        JSONObject quote = dataObj.getJSONObject("quote");
                        JSONObject USD = quote.getJSONObject("USD");
                        double price = USD.getDouble("price");

                        // adding all data to our array list.
                        //currencyModalArrayList.add(new CurrencyModal(name, symbol, price));
                        String date =days.format(calendar.getTime());
                        String week=weeks.format(calendar.getTime());
                        StatEntity info = new StatEntity(name,date,price);
                        dataBase.statDao().insert(info);
                        if(date.equals("0000")){
                            HistoryEntity history=new HistoryEntity(name,week,price);
                            dataBaseH.HistoryDao().insert(history);
                        }
                    }


                } catch (JSONException e) {
                    // handling json exception.
                    e.printStackTrace();
                    //toast.setText("Something went amiss. Please try again later");
                    // toast.show();
                    // Toast.makeText(ContentActivity.this, "Something went amiss. Please try again later", Toast.LENGTH_SHORT).show();
                }




            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                // displaying error response when received any error.
                // toast.setText("Something went amiss. Please try again later");
                // toast.show();
                //Toast.makeText(ContentActivity.this, "Something went amiss. Please try again later", Toast.LENGTH_SHORT).show();
            }
        }) {
            @Override
            public Map<String, String> getHeaders() {
                // in this method passing headers as
                // key along with value as API keys.
                HashMap<String, String> headers = new HashMap<>();
                headers.put("X-CMC_PRO_API_KEY", "1757d359-6449-4d2d-8f1b-5fb772961581");
                // at last returning headers
                return headers;
            }
        };
        // calling a method to add our
        // json object request to our queue.
        queue.add(jsonObjectRequest);

    }



    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}