package com.example.cryptoai;

public class Coin {
    private String title;
    private double price;
    private boolean expanded;

    public Coin(String title, double price) {
        this.title = title;
        this.price = price;
        this.expanded = true;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(String rating) {
        this.price = price;
    }



    public boolean isExpanded() {
        return expanded;
    }

    public void setExpanded(boolean expanded) {
        this.expanded = expanded;
    }

    @Override
    public String toString() {
        return "Coin{" +
                "title='" + title + '\'' +
                ", rating='" + price + '\'' +
                ", expanded=" + expanded +
                '}';
    }
}
