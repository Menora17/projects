package com.example.cryptoai;

import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;

@Dao
public interface HistoryDao {
    @Query("SELECT * FROM history_info")
    HistoryEntity[] getHistoryAll();

    @Query("SELECT * FROM history_info ORDER BY currency_id LIMIT 1")
    HistoryEntity  getFirstPlace();
    //@Query("SELECT * FROM history_info WHERE currency_name =:a ORDER BY currency")
    //HistoryEntity[] getallcoin(String a);
    @Query("SELECT * FROM history_info WHERE currency_name =:name ORDER BY currency_week")
    HistoryEntity[] getallcoin(String name);

    @Insert
    void insert(HistoryEntity history);

    @Delete
    void delete(HistoryEntity history);
    @Query("DELETE FROM history_info")
    void delete();


}