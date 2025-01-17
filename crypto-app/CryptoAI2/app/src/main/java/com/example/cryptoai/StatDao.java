package com.example.cryptoai;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;

@Dao
public interface StatDao {
    @Query("SELECT * FROM currency_info")
    StatEntity[] getAll();

    @Query("SELECT * FROM currency_info ORDER BY currency_id LIMIT 1")
    StatEntity getFirstPlace();

    @Query("SELECT * FROM currency_info ORDER BY currency_date LIMIT 1")
    StatEntity getFirstHour();
    @Query("SELECT * FROM currency_info WHERE currency_name =:name ORDER BY currency_date")
    StatEntity[] getallcoin(String name);

    @Insert
    void insert(StatEntity stat);

    @Delete
    void delete(StatEntity stat);
    @Query("DELETE FROM currency_info")
    void delete();


}
