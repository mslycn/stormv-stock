package org.mokey.stormv.stock.data.core;

import com.csvreader.CsvReader;
import org.springframework.beans.factory.annotation.Value;

import java.io.File;
import java.nio.charset.Charset;

/**
 * 下载新浪交易明细
 * Created by enousei on 9/27/15.
 */
public class SinaTradePull implements Runnable{
    @Value("${data.dir}")
    private String datDir;

    @Value("${sina.download.url}")
    private String sinaUrl;

    private String code;

    public void setCode(String code) {
        this.code = code;
    }

    public void run() {
        File yahoo = new File(this.datDir + "/yahoo/" + this.code + ".csv");
        if(!yahoo.exists()){
            return;
        }

        CsvReader reader = null;
        try{
            reader = new CsvReader(yahoo.getPath(), ',', Charset.forName("UTF-8"));
            reader.readRecord();
        }catch (Exception e){

        }finally {
            if(reader != null){
                reader.close();
            }
        }
    }
}
