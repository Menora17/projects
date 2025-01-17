package com.example.cryptoai;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.util.ArrayList;
import java.util.List;

public class GraphActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {

    ArrayList<String> Items = new ArrayList<String>();
    private int position=3;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.graph_page);
        TextView test=findViewById(R.id.test);
        GraphView graph = (GraphView) findViewById(R.id.graph);
        Intent intent=getIntent();
        String str=intent.getStringExtra("test");
        test.setText(str);
        AppDataBase dataBase = AppDataBase.getDatabase(getApplicationContext());
        StatEntity[] stats = dataBase.statDao().getAll();
        SetItems();
        Spinner spino = findViewById(R.id.spinner_coins);
        spino.setOnItemSelectedListener(this);
        graph.setTitleColor(1548661);

        // Create the instance of ArrayAdapter
        // having the list of courses
        ArrayAdapter ad
                = new ArrayAdapter(
                this,
                android.R.layout.simple_spinner_item,
                Items);

        ad.setDropDownViewResource(
                android.R.layout
                        .simple_spinner_dropdown_item);

        // Set the ArrayAdapter (ad) data on the
        // Spinner which binds data to spinner
        spino.setAdapter(ad);

        for(int i=0;i<stats.length;i++) {

        }
//        DataPoint[] values = new DataPoint[stats.length];
//        values[0]=new DataPoint(0,0);//creating an object of type DataPoint[] of size 'n'
//        for(int i=1;i<stats.length;i++){
//            if(stats[i].getCurrencyName().toLowerCase()=="bitcoin") {
//                DataPoint v = new DataPoint(i,i);
//                values[i] = v;
//            }
//        }
//        LineGraphSeries<DataPoint> series = new LineGraphSeries<DataPoint>(values);




    }
    public void AddToGraph(String name){
        GraphView graph = (GraphView) findViewById(R.id.graph);
        graph.removeAllSeries();
        AppDataBase dataBase = AppDataBase.getDatabase(getApplicationContext());
        AppDataBase2 dataBaseH = AppDataBase2.getDataBase2(getApplicationContext());
        HistoryEntity[] allofcoinH=dataBaseH.HistoryDao().getallcoin(name);
        StatEntity[] allofcoin=dataBase.statDao().getallcoin(name);
        DataPoint[] dataPoints = new DataPoint[allofcoinH.length+1];
        // declare an array of DataPoint objects with the same size as your list
        for (int i = 0; i < allofcoinH.length+1; i++) {

            dataPoints[i] = new DataPoint(i, allofcoin[i].getCurrencyValue());
//            if(i==allofcoinH.length)
//                dataPoints[i] = new DataPoint(i, allofcoin[i].getCurrencyValue());
        }
        LineGraphSeries<DataPoint> series = new LineGraphSeries<DataPoint>(dataPoints);
        series.setDrawBackground(true);
        graph.addSeries(series);
        series.setColor(Color.GREEN);
        series.setDrawDataPoints(true);



    }

    public void Goback(View view) {
        Intent intent=new Intent(this,ContentActivity.class);
        startActivity(intent);
    }
    public void SetItems(){
        AppDataBase dataBase = AppDataBase.getDatabase(getApplicationContext());
        StatEntity[] stats = dataBase.statDao().getAll();
        for(int i=0;i<stats.length;i++){
            Items.add(stats[i].getCurrencyName());
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
        AddToGraph(Items.get(pos));
        Toast.makeText(getApplicationContext(),Items.get(pos) , Toast.LENGTH_LONG).show();
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
}
