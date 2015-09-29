package org.mokey.stormv.stock.data.entities;

import org.mokey.stormv.stock.data.utils.DateUtil;

import java.text.DecimalFormat;
import java.util.Date;

/**
 * Created by enousei on 9/27/15.
 */
public class TradeDetail {

    private static DecimalFormat decimalFormat = new DecimalFormat();
    private static DecimalFormat formatDecimal = new DecimalFormat("#.00");

    private Date time;
    private float price;
    private float change;
    private long volume;
    private long amount;

    public Date getTime() {
        return time;
    }

    public void setTime(Date time) {
        this.time = time;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public float getChange() {
        return change;
    }

    public void setChange(float change) {
        this.change = change;
    }

    public long getVolume() {
        return volume;
    }

    public void setVolume(long volume) {
        this.volume = volume;
    }

    public long getAmount() {
        return amount;
    }

    public void setAmount(long amount) {
        this.amount = amount;
    }

    public static TradeDetail parse(String day, String[] tokens) throws Exception{
        if(tokens == null || tokens.length < 5){
            return null;
        }

        TradeDetail detail = new TradeDetail();
        if(tokens[0].split(" ").length == 2){
            detail.setTime(DateUtil.getTime(tokens[0]));
        }else {
            detail.setTime(DateUtil.getTime(day + " " + tokens[0]));
        }
        detail.setPrice(Float.parseFloat(tokens[1]));
        if(!tokens[2].equals("--")){
            detail.setChange(Float.parseFloat(tokens[2]));
        }
        detail.setVolume(decimalFormat.parse(tokens[3]).longValue());
        detail.setAmount(decimalFormat.parse(tokens[4]).longValue());
        return detail;
    }

    public String[] toValues(){
        String[] tokens = new String[5];
        tokens[0] = DateUtil.format(this.getTime());
        tokens[1] = formatDecimal.format(this.price);
        tokens[2] = formatDecimal.format(this.change);
        tokens[3] = formatDecimal.format(this.volume);
        tokens[4] = formatDecimal.format(this.amount);


        return tokens;
    }
}
