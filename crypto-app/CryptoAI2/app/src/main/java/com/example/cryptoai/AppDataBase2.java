package com.example.cryptoai;

import android.content.Context;

import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;


@Database(entities = {HistoryEntity.class}, version = 1)
public abstract class AppDataBase2 extends RoomDatabase {
    public abstract HistoryDao HistoryDao();

    private static volatile AppDataBase2 INSTANCE;

    public static AppDataBase2 getDataBase2(final Context context) {
        if (INSTANCE == null) {
            synchronized (AppDataBase2.class) {
                if (INSTANCE == null) {
                    // Create database here
                    INSTANCE = Room.databaseBuilder(context.getApplicationContext(),
                                    AppDataBase2.class, "app_databaseh")
                            .allowMainThreadQueries()
                            .build();
                }
            }
        }
        return INSTANCE;
    }
}

