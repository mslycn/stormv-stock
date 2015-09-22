package org.mokey.stormv.stock.analysis.capi;
 
public class CATHSAccount {
	
	static{
		//
        System.loadLibrary("AutoStockTransaction");
    }
	
	// TongHuaShun Initialize
	// 0 : success
	public static native int initialize();
	
	public static native float getAvailableMoney();
	
	public static native float getAllMoney();
	
	public static native float getAllStockMarketValue();
	
	// 0 : success to commit buy order
	public static native int buyStock(String stockId, int amount, float price);
	
	// 0 : success to commit sell order
	public static native int sellStock(String stockId, int amount, float price);
}
