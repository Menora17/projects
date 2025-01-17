package com.example.cryptoai;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class coinAdapter extends RecyclerView.Adapter<coinAdapter.CoinVH> {
    private static final String TAG = "CoinAdapter";
    List<Coin> coinList;

    public coinAdapter(List<Coin> coinList) {
        this.coinList = coinList;
    }

    @NonNull
    @Override
    public CoinVH onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.coin_row, parent, false);
        return new CoinVH(view);
    }

    @Override
    public void onBindViewHolder(@NonNull CoinVH holder, int position) {

        Coin coin = coinList.get(position);
        holder.titleTextView.setText(coin.getTitle());
        holder.ratingTextView.setText(Double.toString(coin.getPrice()));


        boolean isExpanded = coinList.get(position).isExpanded();
        holder.expandableLayout.setVisibility(isExpanded ? View.VISIBLE : View.GONE);

    }

    @Override
    public int getItemCount() {
        return coinList.size();
    }

    class CoinVH extends RecyclerView.ViewHolder {

        private static final String TAG = "CoinVH";

        ConstraintLayout expandableLayout;
        TextView titleTextView, yearTextView, ratingTextView;

        public CoinVH(@NonNull final View itemView) {
            super(itemView);

            titleTextView = itemView.findViewById(R.id.titleTextView);
            yearTextView = itemView.findViewById(R.id.yearTextView);
            ratingTextView = itemView.findViewById(R.id.ratingTextView);

            expandableLayout = itemView.findViewById(R.id.expandableLayout);


            titleTextView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {

                    Coin coin = coinList.get(getAdapterPosition());
                    coin.setExpanded(!coin.isExpanded());
                    notifyItemChanged(getAdapterPosition());

                }
            });
        }
    }
}
