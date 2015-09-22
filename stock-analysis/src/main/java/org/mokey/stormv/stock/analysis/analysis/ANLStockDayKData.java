package org.mokey.stormv.stock.analysis.analysis;

import java.util.ArrayList;
import java.util.List;
 
public class ANLStockDayKData {
	public ANLStockDayKData()
	{
		priceList = new ArrayList<Float>();
		volumeList = new ArrayList<Float>();
	} 
	public String date;
	public float open;
	public float close;
	public float high;
	public float low;
	public float volume;
	public List<Float> priceList;
	public List<Float> volumeList;
}