package com.example.cryptoai;
import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity(tableName = "currency_info")
public class StatEntity {
    @PrimaryKey(autoGenerate = true)
    @ColumnInfo(name = "currency_id")
    private int id;

    @ColumnInfo(name = "currency_name")
    private String currencyName;


    @ColumnInfo(name = "currency_date")
    private String currencyDate;

    @ColumnInfo(name = "currency_value")
    private double currencyValue;

    public StatEntity(String currencyName,String currencyDate, double currencyValue){
        this.id = 0;
        this.currencyDate=currencyDate;
        this.currencyName = currencyName;
        this.currencyValue = currencyValue;
    }
    public StatEntity(){

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getCurrencyDate() {
        return currencyDate;
    }

    public void setCurrencyDate(String currencyDate) {
        this.currencyDate = currencyDate;
    }

    public String getCurrencyName() {
        return currencyName;
    }

    public void setCurrencyName(String currencyName) {
        this.currencyName = currencyName;
    }

    public double getCurrencyValue() {
        return currencyValue;
    }

    public void setCurrencyValue(double currencyValue) {
        this.currencyValue = currencyValue;
    }
}
