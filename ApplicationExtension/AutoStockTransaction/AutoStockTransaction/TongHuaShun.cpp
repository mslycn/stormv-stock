#include "stdafx.h"
#include "TongHuaShun.h"
#include "Common.h"
#include "math.h"

#include "windows.h"
#include "commctrl.h"
#include "WinHandle.h"

static HWND s_hMainWin = NULL;
static HWND s_hLeftTreeView = NULL;

static HWND s_hZijinGupiaoWin = NULL;
static HWND s_hBuyWin = NULL;
static HWND s_hSellWin = NULL;

int THSAPI_TongHuaShunInit()
{
	DFileLog::GetInstance()->Clear();
	DFileLog::GetInstance()->EnableSaveLog(true);
	TESTLOG("THSAPI_TongHuaShunInit#\n");

	HWND hWnd = FindTongHuaShunMainWin();

	TESTLOG("hWnd = 0x%x\n",hWnd);
	if (NULL == hWnd)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] main win error, need 网上股票交易系统5.0!\n");
		return -10;
	}
	s_hMainWin = hWnd;
	TESTLOG("THSAPI_TongHuaShunInit# search main win ok\n");

	HWND hLeftTreeView = findLeftTreeView(hWnd);
	if (NULL == hLeftTreeView)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] LeftTreeView win error\n");
		return -20;
	}
	s_hLeftTreeView = hLeftTreeView;
	TESTLOG("THSAPI_TongHuaShunInit# search LeftTreeView ok\n");
	if (selectMasterTreeViewItem(hLeftTreeView, -1)<0)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] LeftTreeView win error 2\n");
		return -21;
	}

	HWND hZijinGupiaoWin = findZijinGupiaoWin(hWnd);
	if (NULL == hZijinGupiaoWin)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] ZijinGupiao win error\n");
		return -30;
	}
	s_hZijinGupiaoWin = hZijinGupiaoWin;
	TESTLOG("THSAPI_TongHuaShunInit# search ZijinGupiaoWin ok\n");

	HWND hBuyWin = findBuyWin(hWnd);
	if (NULL == hBuyWin)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] Buy win error\n");
		return -40;
	}
	s_hBuyWin = hBuyWin;
	TESTLOG("THSAPI_TongHuaShunInit# search BuyWin ok\n");

	HWND hSellWin = findSellWin(hWnd);
	if (NULL == hSellWin)
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] Sell win error\n");
		return -50;
	}
	s_hSellWin = hSellWin;
	TESTLOG("THSAPI_TongHuaShunInit# search SellWin ok\n");

	if (0!=CancelAllMainWin())
	{
		TESTLOG("THSAPI_TongHuaShunInit# [ERROR] CancelAllMainWin error\n");
		return -60;
	}
	
	Flush_F5();

	return 0;
}

float THSAPI_GetAvailableMoney()
{
	TESTLOG("THSAPI_GetAvailableMoney#\n");
	Flush_F5();
	if (!s_hZijinGupiaoWin)
	{
		TESTLOG("THSAPI_GetAvailableMoney# [ERROR] ZijinGupiaoWin error\n");
		return 0.0f;
	}
	HWND hChild = NULL;
	int index =0;
	for(;;) {
		hChild = FindWindowExW(s_hZijinGupiaoWin, hChild, 0, 0);
		if (hChild == NULL)
			break;
		index++;
		char szTitle[200];
		char szClass[200];
		char szWinText[200];
		GetWindowText(hChild, szTitle, sizeof(szTitle) / sizeof(char));
		GetClassName(hChild, szClass, sizeof(szClass) / sizeof(char));
		GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
		if (8 == index)
		{
			for (int i=0; i<500; i++)
			{
				GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
				if (0 != strcmp(szWinText, ""))
				{
					TESTLOG("THSAPI_GetAvailableMoney# hWnd = 0x%x szClass[%s] szWinText[%s]\n",hChild, szClass,szWinText);
					float availableMoney = 0.0f;
					sscanf(szWinText ,"%f", &availableMoney);
					return  availableMoney;
				}
				Sleep(10);
			}
			TESTLOG("THSAPI_GetAvailableMoney# [ERROR] THSAPI_GetAvailableMoney\n");
			return 0.0f;
		}
	}
	return 0.0f;
}

float THSAPI_GetAllMoney()
{
	TESTLOG("THSAPI_GetAllMoney#\n");
	Flush_F5();
	if (!s_hZijinGupiaoWin)
	{
		TESTLOG("THSAPI_GetAllMoney# [ERROR] ZijinGupiaoWin error\n");
		return 0.0f;
	}
	HWND hChild = NULL;
	int index =0;
	for(;;) {
		hChild = FindWindowExW(s_hZijinGupiaoWin, hChild, 0, 0);
		if (hChild == NULL)
			break;
		index++;
		char szTitle[200];
		char szClass[200];
		char szWinText[200];
		GetWindowText(hChild, szTitle, sizeof(szTitle) / sizeof(char));
		GetClassName(hChild, szClass, sizeof(szClass) / sizeof(char));
		GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
		if (14 == index)
		{
			for (int i=0; i<500; i++)
			{
				GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
				if (0 != strcmp(szWinText, ""))
				{
					TESTLOG("THSAPI_GetAllMoney# hWnd = 0x%x szClass[%s] szWinText[%s]\n",hChild, szClass,szWinText);
					float allMoney = 0.0f;
					sscanf(szWinText ,"%f", &allMoney);
					return  allMoney;
				}
				Sleep(10);
			}
			TESTLOG("THSAPI_GetAllMoney# [ERROR] THSAPI_GetAllMoney\n");
			return 0.0f;
		}
	}
	return 0.0f;
}

float THSAPI_GetAllStockMarketValue()
{
	TESTLOG("THSAPI_GetStockMarketValue#\n");
	Flush_F5();
	if (!s_hZijinGupiaoWin)
	{
		TESTLOG("THSAPI_GetStockMarketValue# [ERROR] ZijinGupiaoWin error\n");
		return 0.0f;
	}
	HWND hChild = NULL;
	int index =0;
	for(;;) {
		hChild = FindWindowExW(s_hZijinGupiaoWin, hChild, 0, 0);
		if (hChild == NULL)
			break;
		index++;
		char szTitle[200];
		char szClass[200];
		char szWinText[200];
		GetWindowText(hChild, szTitle, sizeof(szTitle) / sizeof(char));
		GetClassName(hChild, szClass, sizeof(szClass) / sizeof(char));
		GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
		if (13 == index)
		{
			for (int i=0; i<500; i++)
			{
				GetWindowText(hChild, szWinText, sizeof(szWinText) / sizeof(char));
				if (0 != strcmp(szWinText, ""))
				{
					TESTLOG("THSAPI_GetStockMarketValue# hWnd = 0x%x szClass[%s] szWinText[%s]\n",hChild, szClass,szWinText);
					float stockMarketValue = 0.0f;
					sscanf(szWinText ,"%f", &stockMarketValue);
					return  stockMarketValue;
				}
				Sleep(10);
			}
			TESTLOG("THSAPI_GetStockMarketValue# [ERROR] THSAPI_GetStockMarketValue\n");
			return 0.0f;
		}
	}
	return 0.0f;
}

int THSAPI_BuyStock(const char* stockId, const int buyAmount, const float price)
{
	TESTLOG("THSAPI_BuyStock#\n");
	Flush_F5();
	HWND hStockIDWin = NULL;
	HWND hStockPriceWin = NULL;
	HWND hStockAmountWin = NULL;
	HWND hStockBuyBtnWin = NULL;
	if (NULL == s_hBuyWin)
	{
		TESTLOG("THSAPI_BuyStock# [ERROR] BuyWin error\n");
		return -10;
	}
	if (0!=CancelAllMainWin())
	{
		TESTLOG("THSAPI_BuyStock# [ERROR] CancelAllMainWin error\n");
		return -11;
	}
	HWND hChildL1 = NULL;
	int index =0;
	for(;;) {
		hChildL1 = FindWindowExW(s_hBuyWin, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockIDWin = hChildL1;
			TESTLOG("THSAPI_BuyStock# THSAPI_BuyStock hStockIDWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (3 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockPriceWin = hChildL1;
			TESTLOG("THSAPI_BuyStock# THSAPI_BuyStock hStockPriceWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (5 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockAmountWin = hChildL1;
			TESTLOG("THSAPI_BuyStock# THSAPI_BuyStock hStockAmountWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (6 == index && 0 == strcmp("Button",szClassL1))
		{
			hStockBuyBtnWin = hChildL1;
			TESTLOG("THSAPI_BuyStock# THSAPI_BuyStock hStockBuyBtnWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (index > 6)
		{
			if (!hStockIDWin || !hStockPriceWin || !hStockAmountWin || !hStockBuyBtnWin )
			{
				return -20;
			}
		}
	}
	
	// 选择买入画面
	selectMasterTreeViewItem(s_hLeftTreeView, 0);

	// 填写买入股票号
	for (int i=0;i<100;i++)
	{
		SendMessageA(hStockIDWin, WM_SETTEXT, 0, (LPARAM) stockId);
		Sleep(50);
		char checkstr[200];
		SendMessage(hStockIDWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,stockId))
		{
			break;
		}
		CancelAllMainWin();
	}

	// 填写买入数量
	char szBuyAmount[200];
	sprintf(szBuyAmount, "%d", buyAmount);
	for (int i=0;i<10;i++)
	{
		SendMessageA(hStockAmountWin, WM_SETTEXT, 0, (LPARAM) szBuyAmount);
		Sleep(200);
		char checkstr[200];
		SendMessage(hStockAmountWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,szBuyAmount))
		{
			break;
		}
		CancelAllMainWin();
	}

	// 填写买入价格
	SendMessageA(hStockPriceWin, WM_SETFOCUS, 0, 0);
	Sleep(10);
	char szPrice[200];
	sprintf(szPrice, "%.2f", price);
	for (int i=0;i<100;i++)
	{
		SendMessageA(hStockPriceWin, WM_SETTEXT, 0, (LPARAM) szPrice);
		Sleep(50);
		char checkstr[200];
		SendMessage(hStockPriceWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,szPrice))
		{
			break;
		}
		CancelAllMainWin();
	}
	SendMessageA(hStockPriceWin, WM_SETFOCUS, 0, 0);

	// 点击买入按钮
	PostMessage(hStockBuyBtnWin,WM_LBUTTONDOWN,0,0);
	Sleep(10);
	PostMessage(hStockBuyBtnWin,WM_LBUTTONUP,0,0);
	for (int i=0;i<500;i++)
	{
		HWND hZhangDieXianZhiCheck = Find_ZhangDieXianZhi();
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRenCheck = Find_WeiTuoQueRen(iFlag,sId, iAmount, fPrice);
		if (NULL!=hZhangDieXianZhiCheck || NULL!=hWeiTuoQueRenCheck)
		{
			break;
		}
		Sleep(10);
	}

    // 点击确认下单按钮
	for (int i=0;i<100;i++)
	{
		// 涨跌限制关闭，交易失败
		HWND hZhangDieXianZhi = Find_ZhangDieXianZhi();
		if (hZhangDieXianZhi)
		{
			CloseZhangDieXianZhi_Cancel();
			return -30;
		}
		// 委托确认
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId, iAmount, fPrice);
		if (hWeiTuoQueRen)
		{
			if (0 == iFlag &&
				0 == strcmp(sId.c_str(),stockId) &&
				iAmount == buyAmount &&
				fabs(fPrice-price) < 0.0001)
			{
				CloseWeiTuoQueRen_OK();
			}
			else
			{
				CloseWeiTuoQueRen_Cancel();
				return -31;
			}
			
			for (int i=0;i<500;i++)
			{
				HWND hTijiaoChengGongCheck = Find_TijiaoChengGong();
				HWND hJiaoYiShiBaiCheck = Find_TijiaoShiBai();
				if (NULL!=hTijiaoChengGongCheck || NULL!=hJiaoYiShiBaiCheck)
				{
					break;
				}
				Sleep(10);
			}

			//委托成功或失败确认
			for (int i=0;i<100;i++)
			{
				//交易成功
				HWND hTijiaoChengGong = Find_TijiaoChengGong();
				if (hTijiaoChengGong)
				{
					CloseTijiaoChengGong();
					return 0;
				}
				else
				{
					//交易成功
					HWND hJiaoYiChengGong = Find_TijiaoChengGong();
					if (hJiaoYiChengGong)
					{
						CloseTijiaoChengGong();
						return 0;
					}
					//交易失败
					HWND hJiaoYiShiBai = Find_TijiaoShiBai();
					if (hJiaoYiShiBai)
					{
						CloseTijiaoShiBai();
						return -40;
					}
				}
				Sleep(10);
			}
			break;
		}
		Sleep(10);
	}

    // 未知错误
	return -100;
}


int THSAPI_SellStock(const char* stockId, const int sellAmount, const float price)
{
	TESTLOG("THSAPI_SellStock#\n");
	Flush_F5();
	HWND hStockIDWin = NULL;
	HWND hStockPriceWin = NULL;
	HWND hStockAmountWin = NULL;
	HWND hStockSellBtnWin = NULL;
	if (NULL == s_hSellWin)
	{
		TESTLOG("THSAPI_SellStock# [ERROR] SellWin error\n");
		return -10;
	}
	if (0!=CancelAllMainWin())
	{
		TESTLOG("THSAPI_SellStock# [ERROR] CancelAllMainWin error\n");
		return -11;
	}
	HWND hChildL1 = NULL;
	int index =0;
	for(;;) {
		hChildL1 = FindWindowExW(s_hSellWin, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockIDWin = hChildL1;
			TESTLOG("THSAPI_SellStock# THSAPI_BuyStock hStockIDWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (3 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockPriceWin = hChildL1;
			TESTLOG("THSAPI_SellStock# THSAPI_BuyStock hStockPriceWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (5 == index && 0 == strcmp("Edit",szClassL1))
		{
			hStockAmountWin = hChildL1;
			TESTLOG("THSAPI_SellStock# THSAPI_BuyStock hStockAmountWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (6 == index && 0 == strcmp("Button",szClassL1))
		{
			hStockSellBtnWin = hChildL1;
			TESTLOG("THSAPI_SellStock# THSAPI_BuyStock hStockSellBtnWin = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);
		}
		if (index > 6)
		{
			if (!hStockIDWin || !hStockPriceWin || !hStockAmountWin || !hStockSellBtnWin )
			{
				return -20;
			}
		}
	}

	// 选择卖出画面
	selectMasterTreeViewItem(s_hLeftTreeView, 1);

	// 填写卖出股票号
	for (int i=0;i<100;i++)
	{
		SendMessageA(hStockIDWin, WM_SETTEXT, 0, (LPARAM) stockId);
		Sleep(50);
		char checkstr[200];
		SendMessage(hStockIDWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,stockId))
		{
			break;
		}
		CancelAllMainWin();
	}

	// 填写卖出数量
	char szSellAmount[200];
	sprintf(szSellAmount, "%d", sellAmount);
	for (int i=0;i<10;i++)
	{
		SendMessageA(hStockAmountWin, WM_SETTEXT, 0, (LPARAM) szSellAmount);
		Sleep(200);
		char checkstr[200];
		SendMessage(hStockAmountWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,szSellAmount))
		{
			break;
		}
		CancelAllMainWin();
	}

	// 填写卖出价格
	SendMessageA(hStockPriceWin, WM_SETFOCUS, 0, 0);
	Sleep(10);
	char szPrice[200];
	sprintf(szPrice, "%.2f", price);
	for (int i=0;i<100;i++)
	{
		SendMessageA(hStockPriceWin, WM_SETTEXT, 0, (LPARAM) szPrice);
		Sleep(50);
		char checkstr[200];
		SendMessage(hStockPriceWin, WM_GETTEXT, 200, long(checkstr));
		if (0 == strcmp(checkstr,szPrice))
		{
			break;
		}
		CancelAllMainWin();
	}
	SendMessageA(hStockPriceWin, WM_SETFOCUS, 0, 0);

	// 点击卖出按钮
	PostMessage(hStockSellBtnWin,WM_LBUTTONDOWN,0,0);
	Sleep(10);
	PostMessage(hStockSellBtnWin,WM_LBUTTONUP,0,0);
	for (int i=0;i<500;i++)
	{
		HWND hZhangDieXianZhiCheck = Find_ZhangDieXianZhi();
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRenCheck = Find_WeiTuoQueRen(iFlag,sId, iAmount, fPrice);
		if (NULL!=hZhangDieXianZhiCheck || NULL!=hWeiTuoQueRenCheck)
		{
			break;
		}
		Sleep(10);
	}

	// 点击确认下单按钮
	for (int i=0;i<100;i++)
	{
		// 涨跌限制关闭，交易失败
		HWND hZhangDieXianZhi = Find_ZhangDieXianZhi();
		if (hZhangDieXianZhi)
		{
			CloseZhangDieXianZhi_Cancel();
			return -30;
		}

		// 委托确认
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId,iAmount, fPrice);
		if (hWeiTuoQueRen)
		{
			if (1 == iFlag && 
				0 == strcmp(sId.c_str(),stockId) && 
				iAmount == sellAmount && 
				fabs(fPrice-price) < 0.0001)
			{
				CloseWeiTuoQueRen_OK();
			}
			else
			{
				CloseWeiTuoQueRen_Cancel();
				return -31;
			}

			for (int i=0;i<500;i++)
			{
				HWND hTijiaoChengGongCheck = Find_TijiaoChengGong();
				HWND hJiaoYiShiBaiCheck = Find_TijiaoShiBai();
				if (NULL!=hTijiaoChengGongCheck || NULL!=hJiaoYiShiBaiCheck)
				{
					break;
				}
				Sleep(10);
			}

			//委托成功或失败确认
			for (int i=0;i<100;i++)
			{
				//交易成功
				HWND hTijiaoChengGong = Find_TijiaoChengGong();
				if (hTijiaoChengGong)
				{
					CloseTijiaoChengGong();
					return 0;
				}
				else
				{
					//交易成功
					HWND hJiaoYiChengGong = Find_TijiaoChengGong();
					if (hJiaoYiChengGong)
					{
						CloseTijiaoChengGong();
						return 0;
					}
					//交易失败
					HWND hJiaoYiShiBai = Find_TijiaoShiBai();
					if (hJiaoYiShiBai)
					{
						CloseTijiaoShiBai();
						return -40;
					}
				}
				Sleep(10);
			}
			break;
		}
		Sleep(10);
	}

	// 未知错误
	return -100;
}


