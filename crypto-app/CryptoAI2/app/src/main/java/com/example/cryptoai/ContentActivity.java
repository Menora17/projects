package com.example.cryptoai;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;

import androidx.appcompat.app.AppCompatActivity;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.GridLabelRenderer;
import com.jjoe64.graphview.LegendRenderer;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;
import android.view.ViewGroup.LayoutParams;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class ContentActivity extends AppCompatActivity {

    private RecyclerView currencyRV;
    RecyclerView recyclerView;
    List<Coin> coinList;
    private EditText searchEdt;
    private ArrayList<CurrencyModal> currencyModalArrayList;
    private CurrencyRVAdapter currencyRVAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.contextpage);
        recyclerView = findViewById(R.id.recyclerView);

        searchEdt = findViewById(R.id.idEdtCurrency);
        currencyRV = findViewById(R.id.idRVcurrency);
        currencyModalArrayList = new ArrayList<>();
        // initializing our adapter class.
        currencyRVAdapter = new CurrencyRVAdapter(currencyModalArrayList, this);
        // setting layout manager to recycler view.
        currencyRV.setLayoutManager(new LinearLayoutManager(this));
        // setting adapter to recycler view.
        currencyRV.setAdapter(currencyRVAdapter);


        testing();
        run();
        initData();
        initRecyclerView();

    }
    private void initRecyclerView() {
        coinAdapter CoinAdapter = new coinAdapter(coinList);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(CoinAdapter);
    }
    private void initData() {
        coinList = new ArrayList<>();
        for (CurrencyModal item : currencyModalArrayList) {
            coinList.add(new Coin(item.getName(),item.getPrice()));
        }
    }
    public void run() {



        AppDataBase dataBase = AppDataBase.getDatabase(getApplicationContext());
        StatEntity[] stats = dataBase.statDao().getAll();
        currencyModalArrayList.clear();
        currencyRVAdapter.notifyDataSetChanged();
        // calling get data method to get data from API.
        if(stats!=null){
            for (int i = 0; i <stats.length; i++) {
                currencyModalArrayList.add(new CurrencyModal(stats[i].getCurrencyName(), "$", stats[i].getCurrencyValue()));
            }
            currencyRVAdapter.notifyDataSetChanged();
        }




    }

    public void testing(){
        // on below line we are adding text watcher for our
        // edit text to check the data entered in edittext.

        searchEdt.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                // on below line calling a
                // method to filter our array list
                filter(s.toString());
            }
        });
    }
    private void filter(String filter) {
        // on below line we are creating a new array list
        // for storing our filtered data.
        ArrayList<CurrencyModal> filteredlist = new ArrayList<>();
        // running a for loop to search the data from our array list.

        for (CurrencyModal item : currencyModalArrayList) {
            // on below line we are getting the item which are
            // filtered and adding it to filtered list.
            if (item.getName().toLowerCase().contains(filter.toLowerCase())) {
                filteredlist.add(item);
            }
        }
        // on below line we are checking
        // weather the list is empty or not.
        if (filteredlist.isEmpty()) {
            // if list is empty we are displaying a toast message.
            //Toast.makeText(this, "No currency found..", Toast.LENGTH_SHORT).show();
        } else {
            // on below line we are calling a filter
            // list method to filter our list.
            currencyRVAdapter.filterList(filteredlist);
        }
    }


    public void test(View view) {
        Intent intent=new Intent(this,MainActivity.class);
        startActivity(intent);
    }
    public void become_a_client(View view) {
        Intent intent=new Intent(this,Newusers.class);
        startActivity(intent);
    }


}
