package org.mokey.stormv.stock.analysis.analysis;

import java.util.ArrayList;
import java.util.List;

public class ANLPolicy {
	 
	public static boolean enterCheck(List<ANLStockDayKData> cListANLStockDayKData) {
        int lenlist = cListANLStockDayKData.size();
        if(lenlist < 60)
        {
        	return false;
        }
        int iCheckDay = lenlist-1;
        ANLStockDayKData cCheckDayKData = cListANLStockDayKData.get(iCheckDay);

        List<ANLStockDayKData> cTmpCheckListX = cListANLStockDayKData.subList(iCheckDay-8, iCheckDay+1);
        List<ANLStockDayKData> cTmpCheckListY = cListANLStockDayKData.subList(iCheckDay-8, iCheckDay);
        
        for(int i=0; i<1; i++)
        {
        	RetPriceTuPo cRetPriceTuPo = ANLPolicy.paramPriceTuPo(cTmpCheckListX);
            if(cRetPriceTuPo.yangShiTi > 0.03 && cRetPriceTuPo.yangShiTi < 0.08
        			&& cRetPriceTuPo.zhangFu > 0.03 && cRetPriceTuPo.zhangFu < 0.09)
            {
            	boolean paramLiangTuPo = ANLPolicy.paramLiangTuPo(cTmpCheckListX);
        		float paramGaoZhiInDay = ANLPolicy.paramGaoZhiInDay(cCheckDayKData);
        		int paramWeiQuShi = ANLPolicy.paramWeiQuShi(cTmpCheckListY);
        		RetZhenDang cRetZhenDang = ANLPolicy.paramZhenDang(cTmpCheckListY);
        		if(!paramLiangTuPo)
        		{
        			break;
        		}
        		if(paramGaoZhiInDay<0.6)
        		{
        			continue;
        		}
        		if(paramWeiQuShi>0)
        		{
        			continue;
        		}
        		if(cRetZhenDang.fangCha<0.3 && Math.abs(paramWeiQuShi) <=2)
        		{
        			continue;
        		}
            	//System.out.println(cCheckDayKData.date);
            	return true;
            }	
        }
        return false;
	}
	
	/////////////////////////////////////////////////////////////
	
	private static class RetPriceTuPo
	{
		public RetPriceTuPo(float paramYangShiTi, float paramZhangFu)
		{
			yangShiTi = paramYangShiTi;
			zhangFu = paramZhangFu;
		}
		public float yangShiTi;
		public float zhangFu;
	}
	private static RetPriceTuPo paramPriceTuPo(List<ANLStockDayKData> cListANLStockDayKData) {
		int indexBegin = 0;
		int indexEnd = cListANLStockDayKData.size()-1;
		ANLStockDayKData cCheckKData = cListANLStockDayKData.get(indexEnd);
		ANLStockDayKData cCheckKDataPre = cListANLStockDayKData.get(indexEnd-1);
		
		float zhangFu = (cCheckKData.close - cCheckKDataPre.close)/cCheckKDataPre.close;
		float yangShiTi = (cCheckKData.close - cCheckKData.open)/cCheckKData.open;
		float highPriceBefore = cListANLStockDayKData.get(indexBegin).open;
		for(int iIndex = indexBegin; iIndex < indexEnd; iIndex++)  
		{  
			ANLStockDayKData cTmpCheckKData = cListANLStockDayKData.get(iIndex);
			if(cTmpCheckKData.close > highPriceBefore)
			{
				highPriceBefore = cTmpCheckKData.close;
			}
		} 
		
		if (cCheckKData.close > highPriceBefore)
		{
			return new RetPriceTuPo(yangShiTi, zhangFu);
		}
		else
		{
			return new RetPriceTuPo(0, 0);
		}
	}
	
	private static boolean paramLiangTuPo(List<ANLStockDayKData> cListANLStockDayKData) {
		boolean bLiangTuPo = false;
		int indexBegin = 0;
		int indexEnd = cListANLStockDayKData.size()-1;
		int numdays = indexEnd-indexBegin;
		
		ANLStockDayKData checkDayKData = cListANLStockDayKData.get(indexEnd);
		
		float aveVolume = 0;
		for(int iIndex = indexBegin; iIndex < indexEnd; iIndex++)  
		{  
			aveVolume = aveVolume + cListANLStockDayKData.get(iIndex).volume;
		}
		aveVolume = aveVolume/numdays;
		
		boolean check1 = (checkDayKData.volume/aveVolume) > 2;
		
		boolean check2 = true;
		int fromIndex2 = indexEnd - numdays/2;
		for(int iIndex = fromIndex2; iIndex < indexEnd; iIndex++)  
		{  
			if(cListANLStockDayKData.get(iIndex).volume > checkDayKData.volume)
			{
				check2 = false;
			}
		}
		
		boolean check3 = false;
		int fromIndex3 = indexEnd - (numdays/4)*4;
		int fromIndex4 = indexEnd - (numdays/4);
		float aveVolMid = 0;
		for(int iIndex = fromIndex3; iIndex < fromIndex4; iIndex++)  
		{  
			aveVolMid = aveVolMid + cListANLStockDayKData.get(iIndex).volume;
		}
		aveVolMid = aveVolMid/(fromIndex4-fromIndex3);
		float aveVolLast = 0;
		for(int iIndex = fromIndex4+1; iIndex < indexEnd+1; iIndex++)  
		{  
			aveVolLast = aveVolLast + cListANLStockDayKData.get(iIndex).volume;
		}
		aveVolLast = aveVolLast/(indexEnd-fromIndex4);
		if(aveVolLast > aveVolMid*2)
		{
			check3 = true;
		}
		
		if(check1 && check2 && check3)
		{
			bLiangTuPo = true;
		}
		
		return bLiangTuPo;
	}
	
	private static float paramGaoZhiInDay(ANLStockDayKData cANLStockDayKData) 
	{
		float midprice = (cANLStockDayKData.close + cANLStockDayKData.open)/2;
		int lenList = cANLStockDayKData.priceList.size();
		int biggerCount = 0;
		for(int iIndex = 0; iIndex < lenList; iIndex++)  
		{  
			float curPrice = cANLStockDayKData.priceList.get(iIndex);
			if(curPrice > midprice)
			{
				biggerCount = biggerCount + 1;
			}
		}
		float fBiggerCount = biggerCount;
		float retParam = fBiggerCount/lenList;
		return retParam;
	}
	
	private static int paramWeiQuShi(List<ANLStockDayKData> cListANLStockDayKData)
	{
		int iQushiParam1 = 0;
		int indexBegin = 0;
		int indexEnd = cListANLStockDayKData.size()-1;
		for(int iIndex = indexBegin; iIndex < indexEnd; iIndex++)  
		{  
			float midPrice0 = (cListANLStockDayKData.get(iIndex).open + cListANLStockDayKData.get(iIndex).close)/2;
			float midPrice1 = (cListANLStockDayKData.get(iIndex+1).open + cListANLStockDayKData.get(iIndex+1).close)/2;
			if(midPrice0 < midPrice1)
			{
				iQushiParam1 = iQushiParam1 + 1;
			}
			else
			{
				iQushiParam1 = iQushiParam1 - 1;
			}
		}
		return iQushiParam1;
	}
	
	private static class RetZhenDang
	{
		public RetZhenDang(float paramZhenfu, float paramFangCha, float paramCrosstimes)
		{
			zhenFu = paramZhenfu;
			fangCha = paramFangCha;
			crossTimes = paramCrosstimes;
		}
		public float zhenFu;
		public float fangCha;
		public float crossTimes;
	}
	private static float calFangCha(List<Float> valList)
	{
		float valSum = 0.0f;
		int lenList = valList.size();
		for(int iIndex = 0; iIndex < lenList; iIndex++)  
		{
			float val = valList.get(iIndex);
			valSum = valSum + val;
		}
		float aveVal = valSum/lenList;
		float fcSum = 0.0f;
		for(int iIndex = 0; iIndex < lenList; iIndex++)  
		{
			float val = valList.get(iIndex);
			fcSum = fcSum + (val - aveVal) * (val - aveVal);
		}
		float fangcha = fcSum/lenList;
		return fangcha;
	}
	private static RetZhenDang paramZhenDang(List<ANLStockDayKData> cListANLStockDayKData)
	{
		int indexBegin = 0;
		int indexEnd = cListANLStockDayKData.size()-1;
		
		float highPrice = cListANLStockDayKData.get(indexBegin).open;
		float lowPrice = cListANLStockDayKData.get(indexBegin).open;
		for(int iIndex = indexBegin; iIndex < indexEnd+1; iIndex++)  
		{  
			float highday = cListANLStockDayKData.get(iIndex).high;
			float lowday = cListANLStockDayKData.get(iIndex).low;
            if(highday > highPrice)
            {
            	highPrice = highday;
            }
            if(lowday < lowPrice)
            {
            	lowPrice = lowday;
            }
		}
		float curZhenfu = (highPrice - lowPrice)/lowPrice;

		List<Float> valList = new ArrayList<Float>();
		float firstActuralVal = 0.0f;
		for(int iIndex = indexBegin; iIndex < indexEnd+1; iIndex++)  
		{
			float midval = cListANLStockDayKData.get(iIndex).close;
			if(iIndex == indexBegin)
			{
				firstActuralVal = midval;
				valList.add(0.0f);
			}
			else
			{
				float calval = (midval - firstActuralVal)/firstActuralVal;
				valList.add(calval);
			}
		}
		float curfangcha = calFangCha(valList)*1000;
		
		float ave = (highPrice + lowPrice)/2;
		int crosstimes = 0;
		for(int iIndex = indexBegin; iIndex < indexEnd-1; iIndex++)  
		{
			if((cListANLStockDayKData.get(iIndex).high-ave)*(cListANLStockDayKData.get(iIndex).close-ave) < 0)
			{
				crosstimes = crosstimes + 1;
			}
		}
		return new RetZhenDang(curZhenfu,curfangcha,crosstimes);
	}
}
