package org.mokey.stormv.stock.analysis;

import org.mokey.stormv.stock.analysis.analysis.ANLPolicy;
import org.mokey.stormv.stock.analysis.analysis.ANLStock;
import org.mokey.stormv.stock.analysis.analysis.ANLStockDayKData;
import org.mokey.stormv.stock.analysis.analysis.ANLStockPool;

import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;

public class TestSuccRate {
	public static class ProfitResult
	{
		public ProfitResult()
		{
			id = "000000";
			succCnt = 0;
			failCnt = 0;
		}
		public String id;
		public int succCnt;
		public int failCnt;
	}
	public static boolean CheckProfit(ANLStock cANLStock, int iEnter, ProfitResult cProfitResult)
	{
		int iCheckDayBegin = iEnter;
		int iCheckDayEnd = iEnter+40;
		float currentPrice = cANLStock.historyData.get(iCheckDayBegin).close;
		for(int iCheckDay = iCheckDayBegin; iCheckDay <iCheckDayEnd; iCheckDay++)
		{
			ANLStockDayKData checkDayKData = cANLStock.historyData.get(iCheckDay);
			float highDay = checkDayKData.high;
			float lowDay = checkDayKData.low;
			float midDay = (highDay + lowDay)/2;
			float profit = (midDay-currentPrice)/currentPrice;
			if(profit>0.1)
			{
				cProfitResult.succCnt = cProfitResult.succCnt + 1;
				return true;
			}
			if(profit<-0.1)
			{
				cProfitResult.failCnt = cProfitResult.failCnt + 1;
				return false;
			}   	
		}
		cProfitResult.failCnt = cProfitResult.failCnt + 1;
		return false;
	}
	public static void Check()
	{
		Formatter fmt = new Formatter(System.out);
		
		List<String> stockIdList = new ArrayList<String>();
		stockIdList.add("000421");
		stockIdList.add("002118");
		stockIdList.add("600030");
		stockIdList.add("600818");
		stockIdList.add("601766");
		
		List<ProfitResult> cListProfitResult = new ArrayList<ProfitResult>();
		
		for(int i=0; i<stockIdList.size();i++)
		{
			ProfitResult cProfitResult = new ProfitResult();
			
			String stockId = stockIdList.get(i);
			fmt.format("--->Stock Checking: %s\n", stockId);
			
			ANLStock cANLStock = ANLStockPool.getANLStock(stockId);
			cProfitResult.id = stockId;
			int lenlist = cANLStock.historyData.size();
			if(lenlist < 200)
			    continue;
			int iCheckDayBegin = 100;
			int iCheckDayEnd = lenlist-60;
			for(int iIndex = iCheckDayBegin; iIndex < iCheckDayEnd; iIndex++) 
			{
				List<ANLStockDayKData> cTmpCheckList = cANLStock.historyData.subList(iIndex-60, iIndex+1);
				ANLStockDayKData checkday = cTmpCheckList.get(cTmpCheckList.size()-1);
				if(ANLPolicy.enterCheck(cTmpCheckList))
				{
					//System.out.println(checkday.date);
					fmt.format("    EnterDate: %s", checkday.date);
					if(CheckProfit(cANLStock, iIndex, cProfitResult))
					{
						fmt.format(" OK!\n");
					}
					else
					{
						fmt.format(" NG!\n");
					}
				}
			}
			
			cListProfitResult.add(cProfitResult);
		}
		
		fmt.format("======================================================\n");
		int allSucc = 0;
		int allFail = 0;
		for(int iIndex = 0; iIndex < cListProfitResult.size(); iIndex++) 
		{
			ProfitResult cProfitResult = cListProfitResult.get(iIndex);
			fmt.format("StockId:%s succCnt:%d failCnt:%d\n", cProfitResult.id, cProfitResult.succCnt, cProfitResult.failCnt); 
			allSucc = allSucc + cProfitResult.succCnt;
			allFail = allFail + cProfitResult.failCnt;
		}
		float succRate = 0.0f;
		if((allSucc+allFail)!=0)
		{
			succRate = (float)allSucc/(float)(allSucc+allFail)*100;
		}
		fmt.format("succRate:%.3f%%\n", succRate);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("### Main Begin");
		
		Check();

		System.out.println("### Main End");
	}
}
