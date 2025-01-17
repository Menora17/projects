package com.example.cryptoai;

import android.content.Context;

import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;

@Database(entities = {StatEntity.class}, version = 1)
public abstract class AppDataBase extends RoomDatabase {
    public abstract StatDao statDao();

    private static volatile AppDataBase INSTANCE;

    public static AppDataBase getDatabase(final Context context) {
        if (INSTANCE == null) {
            synchronized (AppDataBase.class) {
                if (INSTANCE == null) {
                    // Create database here
                    INSTANCE = Room.databaseBuilder(context.getApplicationContext(),
                                    AppDataBase.class, "app_database")
                            .allowMainThreadQueries()
                            .build();
                }
            }
        }
        return INSTANCE;
    }
}
