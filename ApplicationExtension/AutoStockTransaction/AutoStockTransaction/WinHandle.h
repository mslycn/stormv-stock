#include "Common.h"
#include "windows.h"
#include "commctrl.h"

//////////////////////////////////////////////////////////////////////////
// Sub windows in TongHuaShun

HWND findLeftTreeView(HWND hWnd);
int selectMasterTreeViewItem(HWND hTreeView, int index);
HWND findZijinGupiaoWin(HWND hWnd);
HWND findBuyWin(HWND hWnd);
HWND findSellWin(HWND hWnd);

//////////////////////////////////////////////////////////////////////////
//  main win in desktop

HWND FindTongHuaShunMainWin();

int CancelAllMainWin();

// ZhangDieXianZhi
HWND Find_ZhangDieXianZhi();
int CloseZhangDieXianZhi_Cancel();

// WeiTuoQueRen
// iflag=0 buy,iflag=1 sell,
// id QueRen
// amount QueRen
// price QueRen
HWND Find_WeiTuoQueRen(int& iflag,string& id, int& amount, float& price); 
int CloseWeiTuoQueRen_OK();
int CloseWeiTuoQueRen_Cancel();

// TiJiaoShiBai
HWND Find_TijiaoShiBai();
int CloseTijiaoShiBai();

// TijiaoChengGong
HWND Find_TijiaoChengGong();
int CloseTijiaoChengGong();

// flush
int Flush_F5();


