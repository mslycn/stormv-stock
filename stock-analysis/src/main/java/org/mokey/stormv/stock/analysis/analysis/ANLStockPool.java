package org.mokey.stormv.stock.analysis.analysis;


import org.mokey.stormv.stock.analysis.data.DataEngine;
import org.mokey.stormv.stock.analysis.data.StockKData;

import java.util.ArrayList;
import java.util.List;

public class ANLStockPool {
	public static ANLStock getANLStock(String id)
	{
		List<StockKData> listStockKData =  DataEngine.getStock(id);
		if(null == listStockKData)
		{
			return null;
		}
		
		ANLStock cANLStock = new ANLStock();
		cANLStock.id = id;
		
		List<StockKData> tmpLisStockKData =new ArrayList<StockKData>();
		
		for(int iIndex = 0; iIndex < listStockKData.size(); iIndex++)  
		{  
			StockKData cStockKData = listStockKData.get(iIndex);  
			String currentdate = cStockKData.datetime.split(" ")[0].replace("-","");
			tmpLisStockKData.add(cStockKData);
			if(iIndex != listStockKData.size()-1)
			{
				StockKData cStockKDataNext = listStockKData.get(iIndex+1); 
				String nextlinedate = cStockKDataNext.datetime.split(" ")[0].replace("-","");
				if(!currentdate.equals(nextlinedate))
				{
					ANLStockDayKData cANLStockDayKData = getANLStockDayKDataFromSession(tmpLisStockKData);
					cANLStock.historyData.add(cANLStockDayKData);
					tmpLisStockKData.clear();
				}
			}
			else
			{
				ANLStockDayKData cANLStockDayKData = getANLStockDayKDataFromSession(tmpLisStockKData);
				cANLStock.historyData.add(cANLStockDayKData);
				tmpLisStockKData.clear();
			} 
		}  
		
		return cANLStock;
	}
	private static ANLStockDayKData getANLStockDayKDataFromSession(List<StockKData> listStockKData)
	{
		
		ANLStockDayKData cANLStockDayKData = new ANLStockDayKData();
		float curVolume = 0;
		for(int iIndex = 0; iIndex < listStockKData.size(); iIndex++)  
		{
			StockKData cStockKData = listStockKData.get(iIndex);  
			if(0 == iIndex)
			{
				cANLStockDayKData.date = cStockKData.datetime.split(" ")[0].replace("-","");
				cANLStockDayKData.open = cStockKData.open;
				cANLStockDayKData.low = cStockKData.open;
				cANLStockDayKData.high = cStockKData.open;
			}
			if(listStockKData.size() - 1 == iIndex)
			{
				cANLStockDayKData.close = cStockKData.close;
			}
			curVolume = curVolume + cStockKData.volume;
			
			if(cStockKData.low < cANLStockDayKData.low)
			{
				cANLStockDayKData.low = cStockKData.low;
			}
			if(cStockKData.high > cANLStockDayKData.high)
			{
				cANLStockDayKData.high = cStockKData.high;
			}	
			cANLStockDayKData.priceList.add(cStockKData.close);
			cANLStockDayKData.volumeList.add(cStockKData.volume);
		}
		cANLStockDayKData.volume = curVolume;
		return cANLStockDayKData;
	}
}
