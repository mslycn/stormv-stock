package org.mokey.stormv.stock.data.core;

import org.mokey.stormv.stock.data.dao.YahooDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;

/**
 * 下载雅虎复权日K数据
 * Created by enousei on 9/27/15.
 */
public class YahooKLinePull implements Runnable {

    @Value("${data.dir}")
    private String datDir;

    @Value("${yahoo.download.url}")
    private String yahooUrl;

    @Autowired
    private YahooDao dao;

    private String yahooDir;

    public YahooKLinePull(){
        yahooDir = datDir + "/yahoo";
    }

    public void run() {

    }
}
