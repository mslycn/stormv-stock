package org.mokey.stormv.stock.analysis.analysis;

import java.util.ArrayList;
import java.util.List;

public class ANLStock {
	public ANLStock()
	{
		historyData = new ArrayList<ANLStockDayKData>();
	}
	 
	public String id;
	public List<ANLStockDayKData> historyData;
}
