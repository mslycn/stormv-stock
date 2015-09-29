package org.mokey.stormv.stock.data.utils;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * Created by enousei on 9/27/15.
 */
public class DateUtil {
    private static Logger logger = LoggerFactory.getLogger(DateUtil.class);

    private static SimpleDateFormat sdff = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    private static SimpleDateFormat sdf_s = new SimpleDateFormat("yyyy-MM-dd");

    public static Date getTime(String source){
        try {
            return sdff.parse(source);
        }catch (Exception e){
            logger.error(source, e);
        }

        return null;
    }

    public static Date getNextDay(Date date){
        Calendar rightNow = Calendar.getInstance();
        rightNow.setTime(date);
        rightNow.add(Calendar.DAY_OF_YEAR, 1);
        return  rightNow.getTime();
    }

    public static String format(Date date){
        return sdff.format(date);
    }

    public static String simpleFormat(Date date){
        return sdf_s.format(date);
    }

    public static Date getNext5M(Date date){
        Calendar rightNow = Calendar.getInstance();
        rightNow.setTime(date);
        rightNow.add(Calendar.MINUTE, 5);
        return  rightNow.getTime();
    }
}
