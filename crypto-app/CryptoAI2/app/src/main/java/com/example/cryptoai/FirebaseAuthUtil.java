package com.example.cryptoai;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.firebase.auth.FirebaseAuth;

public final class FirebaseAuthUtil {
    private static final String TAG = "FirebaseAuth Util";
    private static FirebaseAuth AUTH;

    private FirebaseAuthUtil(){}

    // Static methods for Authentication

    public static FirebaseAuth getAuth() {
        if (AUTH == null)
            AUTH = FirebaseAuth.getInstance();
        return AUTH;
    }

    public static boolean isUserSignedIn() {

        return getAuth().getCurrentUser() != null;
    }

    public static void signOut() {

        if(getAuth().getCurrentUser() != null)
            getAuth().signOut();
    }

    public static String authUserEmail() {
        return getAuth().getCurrentUser().getEmail();


    }

    public static String authUserUid() {
        return getAuth().getCurrentUser().getUid();
    }

    public static void loginUser(String email, String password, OnCompleteListener listener) {

        getAuth().signInWithEmailAndPassword(email, password)
                .addOnCompleteListener(listener);
    }

    public static void createUser(String mail, String password, OnCompleteListener listener) {
        getAuth().createUserWithEmailAndPassword(mail, password)
                .addOnCompleteListener(listener);
    }
}


