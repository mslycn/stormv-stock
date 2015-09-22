#include "stdafx.h"
#include "WinHandle.h"
#include "TongHuaShun.h"
#include "Common.h"
#include "windows.h"
#include "commctrl.h"


//////////////////////////////////////////////////////////////////////////
// find sub windows in tonghuashun

HWND findLeftTreeView(HWND hWnd) // and select expend 
{
	TESTLOG("findLeftTreeView#\n");
	HWND hLeftTreeView = NULL;
	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findLeftTreeView# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				if (0 == strcmp(szClassL2, "AfxWnd42s"))
				{
					TESTLOG("findLeftTreeView# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

					HWND hChildL3 = NULL;
					int iTimesHexinScrollWnd = 0;
					for(;;) {
						hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
						if (hChildL3 == NULL)
							break;
						char szTitleL3[200];
						char szClassL3[200];
						char szWinTextL3[200];
						GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
						GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
						GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
						if (0 == strcmp(szWinTextL3, "HexinScrollWnd"))
						{
							iTimesHexinScrollWnd++;
							//if (iTimesHexinScrollWnd == 2)  find all
							{
								TESTLOG("findLeftTreeView# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);

								HWND hChildL4 = NULL;
								for(;;) {
									hChildL4 = FindWindowExW(hChildL3, hChildL4, 0, 0);
									if (hChildL4 == NULL)
										break;
									char szTitleL4[200];
									char szClassL4[200];
									char szWinTextL4[200];
									GetWindowText(hChildL4, szTitleL4, sizeof(szTitleL4) / sizeof(char)); 
									GetClassName(hChildL4, szClassL4, sizeof(szClassL4) / sizeof(char));
									GetWindowText(hChildL4, szWinTextL4, sizeof(szWinTextL4) / sizeof(char));

									if (0 == strcmp(szWinTextL4, "HexinScrollWnd2"))
									{
										TESTLOG("findLeftTreeView# hWndL4 = 0x%x szClassL4[%s] szWinTextL4[%s]\n",hChildL4, szClassL4,szWinTextL4);

										HWND hChildL5 = NULL;
										for(;;) {
											hChildL5 = FindWindowExW(hChildL4, hChildL5, 0, 0);
											if (hChildL5 == NULL)
												break;
											char szTitleL5[200];
											char szClassL5[200];
											char szWinTextL5[200];
											GetWindowText(hChildL5, szTitleL5, sizeof(szTitleL5) / sizeof(char)); 
											GetClassName(hChildL5, szClassL5, sizeof(szClassL5) / sizeof(char));
											GetWindowText(hChildL5, szWinTextL5, sizeof(szWinTextL5) / sizeof(char));

											TESTLOG("findLeftTreeView# hWndL5 = 0x%x szClassL5[%s] szWinTextL5[%s]\n",hChildL5, szClassL5,szWinTextL5);
											if (0 == strcmp(szClassL5, "SysTreeView32"))
											{
												if (0 == selectMasterTreeViewItem(hChildL5,-1))
												{
													return hChildL5;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return hLeftTreeView;
}

int selectMasterTreeViewItem(HWND hTreeView, int index = -1)
{
	TESTLOG("selectMasterTreeViewItem#\n");
	if (-1 == index)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// 买入选择
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		// 卖出选择
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		// 撤单
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// 双向
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// 市价
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// 查询
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		for (int i = 0; i<10 ;i++)
		{
			if (TreeView_Expand(hTreeView, tvItem.hItem, TVE_EXPAND))
			{
				// 资金股票选择
				tvItem.hItem = TreeView_GetChild(hTreeView, tvItem.hItem);
				if (!tvItem.hItem)
					continue;
				TreeView_SelectItem(hTreeView, tvItem.hItem);

				// 选会买入
				tvItem.hItem = TreeView_GetRoot(hTreeView);
				// 买入选择
				TreeView_SelectItem(hTreeView, tvItem.hItem);
				return 0;
			}
		}
		return -1;
	}
	else if (0 == index)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// 买入选择
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		return 0;
	}
	else if (1 == index)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// 卖出选择
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		return 0;
	}

	return -1;
}

HWND findZijinGupiaoWin(HWND hWnd)
{
	TESTLOG("findZijinGupiaoWin#\n");
	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findZijinGupiaoWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findZijinGupiaoWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iTimesCheck = 0;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (0 == strcmp(szWinTextL3, "资金余额"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "冻结金额"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "可用金额"))
					{
						iTimesCheck++;
					}
					if (3 == iTimesCheck)
					{
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

HWND findBuyWin(HWND hWnd)
{
	TESTLOG("findBuyWin#\n");

	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findBuyWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findBuyWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (20 == iFIndex && 0 == strcmp(szWinTextL3, "买入股票"))
					{
						TESTLOG("findBuyWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

HWND findSellWin(HWND hWnd)
{
	TESTLOG("findSellWin#\n");

	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findSellWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findSellWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (18 == iFIndex && 0 == strcmp(szWinTextL3, "卖出股票"))
					{
						TESTLOG("findSellWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// find main win in desktop

HWND FindTongHuaShunMainWin()
{
	return FindWindowW(0, L"网上股票交易系统5.0");
}

int CancelAllMainWin()
{
	int iCloseZhangDieXianZhi =  CloseZhangDieXianZhi_Cancel();
	int iCloseWeiTuoQueRen = CloseWeiTuoQueRen_Cancel();
	int iCloseTijiaoShiBai = CloseTijiaoShiBai();
	int iCloseTijiaoChengGong = CloseTijiaoChengGong();
	if (0 == iCloseZhangDieXianZhi &&
		0 == iCloseWeiTuoQueRen &&
		0 == iCloseTijiaoShiBai &&
		0 ==iCloseTijiaoChengGong
		)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

// zhangdiexianzhi
HWND Find_ZhangDieXianZhi()
{
	HWND hZhangDieXianZhiTishi = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (1 == index && 0 == strcmp("Static", szClassL1))
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("提示信息", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 2)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hZhangDieXianZhiTishi = hMainWin;
				return hZhangDieXianZhiTishi;
			}
		}
	}
	return hZhangDieXianZhiTishi;
}
HWND FindZhangDieXianZhiCloseBtn(HWND hZhangDieXianZhi)
{
	HWND hCloseBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hZhangDieXianZhi, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (3 == index)
		{
			hCloseBtn = hChildL1;
			break;
		}
	}
	return hCloseBtn;
}

int CloseZhangDieXianZhi_Cancel()
{
	for (int i=0; i<500; i++)
	{
		HWND hZhangDieXianZhi = Find_ZhangDieXianZhi();
		if (NULL != hZhangDieXianZhi)
		{
			HWND hCloseBtn = FindZhangDieXianZhiCloseBtn(hZhangDieXianZhi);
			if (NULL != hCloseBtn)
			{
				PostMessage(hCloseBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hCloseBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// WeiTuoQueRen
HWND Find_WeiTuoQueRen(int& iflag,string& id, int& amount, float& price)
{
	HWND hWeiTuoQueRen = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			char szWinText10Caption[200];
			//printf("Find_WeiTuoQueRen# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (10 == index && 0 == strcmp("Static", szClassL1))
			{
				strcpy(szWinText10Caption,szWinTextL1);
				iCheckCount++;
			}
			if (12 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("委托确认", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 2)
			{
				char szId[200];
				char szAmount[200];
				char szPrice[200];
				DWORD isize = 200;
				if (DStr::InstrA(szWinText10Caption,"买入价格")>0)
				{
					iflag = 0;
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"证券代码：","买入价格",szId,isize);
					DStr::TrimA(szId);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"买入数量：","预估金额",szAmount,isize);
					DStr::TrimA(szAmount);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"买入价格：","买入数量",szPrice,isize);
					DStr::TrimA(szPrice);
				}
				if (DStr::InstrA(szWinText10Caption,"卖出价格")>0)
				{
					// 股东帐号：A375867637证券代码：601988卖出价格：4.020卖出数量：100预估金额：396.000您是否确定以上卖出委托？
					iflag = 1;
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"证券代码：","卖出价格",szId,isize);
					DStr::TrimA(szId);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"卖出数量：","预估金额",szAmount,isize);
					DStr::TrimA(szAmount);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"卖出价格：","卖出数量",szPrice,isize);
					DStr::TrimA(szPrice);
				}
				id = string(szId);
				int iamount = 0;
				sscanf(szAmount ,"%d", &iamount);	
				amount = iamount;
				float fprice = 0.0f;
				sscanf(szPrice ,"%f", &fprice);
				price = fprice;

				//printf("Find_WeiTuoQueRen# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hWeiTuoQueRen = hMainWin;
				return hWeiTuoQueRen;
			}
		}
	}
	return hWeiTuoQueRen;
}
HWND FindWeiTuoQueRenOKBtn(HWND hWeiTuoQueRen)
{
	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hWeiTuoQueRen, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
HWND FindWeiTuoQueRenCancelBtn(HWND hWeiTuoQueRen)
{
	HWND hCancelBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hWeiTuoQueRen, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (2 == index)
		{
			hCancelBtn = hChildL1;
			break;
		}
	}
	return hCancelBtn;
}
int CloseWeiTuoQueRen_OK()
{
	for (int i=0; i<500; i++)
	{
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId, iAmount,fPrice);
		if (NULL != hWeiTuoQueRen)
		{
			HWND hOKBtn = FindWeiTuoQueRenOKBtn(hWeiTuoQueRen);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}
int CloseWeiTuoQueRen_Cancel()
{
	for (int i=0; i<500; i++)
	{
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId, iAmount,fPrice);
		if (NULL != hWeiTuoQueRen)
		{
			HWND hCancelBtn = FindWeiTuoQueRenCancelBtn(hWeiTuoQueRen);
			if (NULL != hCancelBtn)
			{
				PostMessage(hCancelBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hCancelBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// TiJiaoShiBai
HWND Find_TijiaoShiBai()
{
	HWND hTijiaoShiBai = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (2 == index && 0 == strcmp("Button", szClassL1) && 0 == strcmp("查询当前委托", szWinTextL1))
			{
				iCheckCount++;
			}
			if (3 == index && 0 == strcmp("Static", szClassL1) && DStr::InstrA(szWinTextL1,"成功提交")<0)
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("提示", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 3)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hTijiaoShiBai = hMainWin;
				return hTijiaoShiBai;
			}
		}
	}
	return hTijiaoShiBai;
}
HWND FindTijiaoShiBaiOKBtn(HWND hTijiaoShiBai)
{
	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hTijiaoShiBai, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
int CloseTijiaoShiBai()
{
	for (int i=0; i<500; i++)
	{
		HWND hTijiaoShiBai = Find_TijiaoShiBai();
		if (NULL != hTijiaoShiBai)
		{
			HWND hOKBtn = FindTijiaoShiBaiOKBtn(hTijiaoShiBai);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// TijiaoChengGong
HWND Find_TijiaoChengGong()
{
	HWND hTijiaoChengGong = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (2 == index && 0 == strcmp("Button", szClassL1) && 0 == strcmp("查询当前委托", szWinTextL1))
			{
				iCheckCount++;
			}
			if (3 == index && 0 == strcmp("Static", szClassL1) && DStr::InstrA(szWinTextL1,"成功提交")>=0)
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("提示", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 3)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hTijiaoChengGong = hMainWin;
				return hTijiaoChengGong;
			}
		}
	}
	return hTijiaoChengGong;
}
HWND FindTijiaoChengGongOKBtn(HWND hTijiaoChengGong)
{
	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hTijiaoChengGong, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
int CloseTijiaoChengGong(){
	for (int i=0; i<500; i++)
	{
		HWND hTijiaoChengGong = Find_TijiaoChengGong();
		if (NULL != hTijiaoChengGong)
		{
			HWND hOKBtn = FindTijiaoChengGongOKBtn(hTijiaoChengGong);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

int Flush_F5()
{
	HWND hWnd = FindTongHuaShunMainWin();
	::PostMessage(hWnd, WM_KEYDOWN, VK_F5, 0);
	::PostMessage(hWnd, WM_KEYUP, VK_F5, 0);
	Sleep(50);
	return 0;
}