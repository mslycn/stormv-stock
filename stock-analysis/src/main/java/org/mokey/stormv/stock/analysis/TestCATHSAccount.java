package org.mokey.stormv.stock.analysis;

import org.mokey.stormv.stock.analysis.capi.CATHSAccount;

import java.util.Formatter;

public class TestCATHSAccount {

	// for test: please be carefull
	public static void main(String[] args) {
        // TODO Auto-generated method stub
        //System.getProperty("java.library.path");
		Formatter fmt = new Formatter(System.out);
		fmt.format("### main begin\n");
		
        int iInitRet = CATHSAccount.initialize();
        fmt.format("CATHSAccount.initialize = %d\n", iInitRet);

        float avalableMoney = CATHSAccount.getAvailableMoney();
        fmt.format("CATHSAccount.getAvailableMoney = %.2f\n", avalableMoney);
        
        float allMoney = CATHSAccount.getAllMoney();
        fmt.format("CATHSAccount.getAllMoney = %.2f\n", allMoney);
        
        float allStockMarketValue = CATHSAccount.getAllStockMarketValue();
        fmt.format("CATHSAccount.getAllStockMarketValue = %.2f\n", allStockMarketValue);
        
        int iBuyRet = CATHSAccount.buyStock("601988", 100, 1.0f);
        fmt.format("CATHSAccount.buyStock = %d\n", iBuyRet);
        
        int iSellRet = CATHSAccount.sellStock("601988", 100, 3.99f);
        fmt.format("CATHSAccount.sellStock = %d\n", iSellRet);
        
        fmt.format("### main end\n");
    }

}
