package org.mokey.stormv.stock.data.entities;

import java.util.Date;

/**
 * Created by enousei on 9/29/15.
 */
public class YahooEntity {
    private Date date;
    private float open;
    private float high;
    private float low;
    private float close;
    private double volume;
    private float adjClose;

    public float getAdjClose() {
        return adjClose;
    }

    public void setAdjClose(float adjClose) {
        this.adjClose = adjClose;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public float getOpen() {
        return open;
    }

    public void setOpen(float open) {
        this.open = open;
    }

    public float getHigh() {
        return high;
    }

    public void setHigh(float high) {
        this.high = high;
    }

    public float getLow() {
        return low;
    }

    public void setLow(float low) {
        this.low = low;
    }

    public float getClose() {
        return close;
    }

    public void setClose(float close) {
        this.close = close;
    }

    public double getVolume() {
        return volume;
    }

    public void setVolume(double volume) {
        this.volume = volume;
    }
}
