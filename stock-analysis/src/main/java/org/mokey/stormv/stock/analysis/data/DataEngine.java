package org.mokey.stormv.stock.analysis.data;
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;  
import java.io.IOException;

import java.util.ArrayList;
import java.util.List;

public class DataEngine {
	public static List<StockKData> getStock(String id) {
		String dataFileName = "";
		File root = new File("data");
		File[] fs = root.listFiles();
		for(int i=0; i<fs.length; i++){
			if(!fs[i].isDirectory()){
				if(fs[i].getName().contains(id))
				{
					dataFileName = fs[i].getAbsolutePath();
				}
			}
		}
		
		List<StockKData> listStockKData =new ArrayList<StockKData>();
		
        int iposDate = -1;
        int iposOpen = -1;
        int iposClose = -1;
        int iposLow = -1;
        int iposHigh = -1;
        int iposVolume = -1;
        int iposAmount = -1;
        int iIndex = -1;
		File file = new File(dataFileName);  
        BufferedReader reader = null;  
        try {   
            reader = new BufferedReader(new FileReader(file));  
            String tempString = null;  
            while ((tempString = reader.readLine()) != null) {   
            	tempString = tempString.trim();
            	if(tempString == "")
            		continue;
            	iIndex = iIndex + 1;
            	if(iIndex == 0)
            	{
            		String[] cols = tempString.split(",");
            		for(int iCheck = 0; iCheck < cols.length; iCheck++)
            		{
            			String checkStr = cols[iCheck].trim().toLowerCase();
            			if(checkStr.contains("date") && iposDate == -1)
            			{
            				iposDate = iCheck;
            			}
            			if(checkStr.contains("open") && iposOpen == -1)
            			{
            				iposOpen = iCheck;
            			}
            			if(checkStr.contains("close") && iposClose == -1)
            			{
            				iposClose = iCheck;
            			}
            			if(checkStr.contains("low") && iposLow == -1)
            			{
            				iposLow = iCheck;
            			}
            			if(checkStr.contains("high") && iposHigh == -1)
            			{
            				iposHigh = iCheck;
            			}
            			if(checkStr.contains("volume") && iposVolume == -1)
            			{
            				iposVolume = iCheck;
            			}
            			if(checkStr.contains("amount") && iposAmount == -1)
            			{
            				iposAmount = iCheck;
            			}
            		}
            	}
            	else
            	{
                	StockKData cStockKData = new StockKData();
                    String[] cols = tempString.split(",");
                    
                    cStockKData.datetime = cols[iposDate];
                    cStockKData.open = Float.parseFloat(cols[iposOpen]);
                    cStockKData.close = Float.parseFloat(cols[iposClose]);
                    cStockKData.low = Float.parseFloat(cols[iposLow]);
                    cStockKData.high = Float.parseFloat(cols[iposHigh]);
                    cStockKData.volume = Float.parseFloat(cols[iposVolume]);
                    cStockKData.amount = Float.parseFloat(cols[iposAmount]);

                    listStockKData.add(cStockKData); 
            	}
            }  
            reader.close();  
        } catch (IOException e) {  
            e.printStackTrace();  
        } finally {  
            if (reader != null) {  
                try {  
                    reader.close();  
                } catch (IOException e1) {  
                }  
            }  
        }  
        
		return listStockKData;
	}
}
