/*************************************************************************
 *	BEGIN OF FILE
 *		FileName	:	DCLib.h
 *		Version  	:	1.0.0.1
 *		Author		:	Wu Di
 *		Modify Date	:	2012.10.10
*************************************************************************/

/*
 * If you want to exports the API used for the other program, please define macro DCLIB_EXPORTS;
 * If you want to imports the API from Dll, please define macro DCLIB_IMPORTS;
 * #define DCLIB_EXPORTS
 * #define DCLIB_IMPORTS
**/

/*
 * Public include header file
**/

#include <windows.h>  
#include <stdio.h>  
#include <process.h>
#include "stdarg.h"
#include "string.h"
#include "io.h"
#include "direct.h"

#ifndef INCLUDE_DCLIB
#define INCLUDE_DCLIB

#ifdef DCLIB_EXPORTS			 /* DLL export */
#	define DCLIB_API __declspec(dllexport)
#	define DCLIB_DATA __declspec(dllexport)
#else
#	ifdef DCLIB_IMPORTS			/* DLL import */ 
#		define DCLIB_API __declspec(dllimport)
#		define DCLIB_DATA __declspec(dllimport)
#	else						/* single program */
#		define DCLIB_API
#		define DCLIB_DATA
#	endif
#endif

/*
 * DFileLog class
**/
class DCLIB_API DStr
{
public:
	/*
	 * Function description:
	 *     Find the position of sub string in the source string.
	 * Parameters description:
	 *     PSourceStr: source string.
	 *     PFindStr: the string you want to find.
	 * Return value description:
	 *     The position of find sub string, the first position is 0, return(-1)if not found
	**/
	static int InstrW(wchar_t * PSourceStr,wchar_t * PFindStr);
	static int InstrA(char * PSourceStr,char * PFindStr);

	/*
	 * Function description:
	 *     Find the position of sub string in the source string, search it from head to tail.
	 * Parameters description:
	 *     PSourceStr: source string.
	 *     PFindStr: the string you want to find.
	 * Return value description:
	 *     The position of find sub string, the first position is 0, return(-1)if not found
	**/
	static int Instr_FromHeadToTailW(wchar_t * PSourceStr,wchar_t * PFindStr);
	static int Instr_FromHeadToTailA(char * PSourceStr,char * PFindStr);

	/*
	 * Function description:
	 *     Find the position of sub string in the source string, search it tail head to head.
	 * Parameters description:
	 *     PSourceStr: source string.
	 *     PFindStr: the string you want to find.
	 * Return value description:
	 *     The position of find sub string, the first position is 0, return(-1)if not found
	**/
	static int Instr_FromTailToHeadW(wchar_t * PSourceStr,wchar_t * PFindStr);
	static int Instr_FromTailToHeadA(char * PSourceStr,char * PFindStr);

	/*
	 * Function description:
	 *     Find the position of sub string in the source string, 
	 *     ignore space in the head and tail, ignore uppercase and lowercase.
	 * Parameters description:
	 *     PSourceStr: source string.
	 *     PFindStr: the string you want to find.
	 * Return value description:
	 *     The position of find sub string, the first position is 0, return(-1)if not found
	**/
	static int InstrTrimIgnoreULW(wchar_t * PSourceStr,wchar_t * PFindStr);
	static int InstrTrimIgnoreULA(char * PSourceStr,char * PFindStr);

	/*
	 * Function description:
	 *     Compare string ignore upper and lower.
	 * Parameters description:
	 *     in_CmpStr1: the first string.
	 *     in_CmpStr2: the second string.
	 * Return value description:
	 *     The same with strcmp function.
	**/
	static int CmpStrIgnoreULW(wchar_t * in_CmpStr1,wchar_t * in_CmpStr2);
	static int CmpStrIgnoreULA(char * in_CmpStr1,char * in_CmpStr2);

	/*
	 * Function description:
	 *     Convert to the upper case character.
	 * Parameters description:
	 *     PConvertStr: the string you want to convert.
	 * Return value description:
	 *     The length of the string converted.
	 *     -1: convert failed.
	**/
	static int UCaseW(wchar_t * PConvertStr);

	/*
	 * Function description:
	 *     Convert to the lower case character.
	 * Parameters description:
	 *     PConvertStr: the string you want to convert.
	 * Return value description:
	 *     The length of the string converted.
	 *     -1: convert failed.
	**/
	static int LCaseW(wchar_t * PConvertStr);

	/*
	 * Function description:
	 *     Delete '\r' '\n' space character in the left of string.
	 * Parameters description:
	 *     PConvertStr: the string you want to convert.
	 * Return value description:
	 *     The length of the string converted.
	 *     -1: convert failed.
	**/
	static int LTrimW(wchar_t * PConvertStr);

	/*
	 * Function description:
	 *     Delete '\r' '\n' space character in the right of string.
	 * Parameters description:
	 *     PConvertStr: the string you want to convert.
	 * Return value description:
	 *     The count of space to delete.
	 *     -1: convert failed.
	**/
	static int RTrimW(wchar_t * PConvertStr);

	/*
	 * Function description:
	 *     Delete '\r' '\n' space character in the left and the right of string.
	 * Parameters description:
	 *     PConvertStr: the string you want to convert.
	 * Return value description:
	 *     The length of the string converted.
	 *     -1: convert failed.
	**/
	static int TrimW(wchar_t * PConvertStr);
	static int TrimA(char * PConvertStr);

	/*
	 * Function description:
	 *     Get the sub string, which is after special string and find it from head to tail.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     SpecialStr: special string.
	 *     SubStr: the buffer of sub string.
	 *     NeedSize: return the size of sub string that need to save(you could set the SubStr NULL to get this size).
	 * Return value description:
	 *     The size of sub string that need to save.
	 *     -1: not found SubStr in PSourceStr or get failed.
	**/
	static int GetSubStr_FormHeadToTail_AfterSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize);
	static int GetSubStr_FormHeadToTail_AfterSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize);

	/*
	 * Function description:
	 *     Get the sub string, which is before special string and find it from head to tail.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     SpecialStr: special string.
	 *     SubStr: the buffer of sub string.
	 *     NeedSize: return the size of sub string that need to save(you could set the SubStr NULL to get this size).
	 * Return value description:
	 *     The size of sub string that need to save.
	 *     -1: not found SubStr in PSourceStr or get failed.
	**/
	static int GetSubStr_FormHeadToTail_BeforeSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize);
	static int GetSubStr_FormHeadToTail_BeforeSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize);

	/*
	 * Function description:
	 *     Get the sub string, which is after special string and find it from tail to head.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     SpecialStr: special string.
	 *     SubStr: the buffer of sub string.
	 *     NeedSize: return the size of sub string that need to save(you could set the SubStr NULL to get this size).
	 * Return value description:
	 *     The size of sub string that need to save.
	 *     -1: not found SubStr in PSourceStr or get failed.
	**/
	static int GetSubStr_FormTailToHead_AfterSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize);
	static int GetSubStr_FormTailToHead_AfterSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize);

	/*
	 * Function description:
	 *     Get the sub string, which is before special string and find it from tail to head.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     SpecialStr: special string.
	 *     SubStr: the buffer of sub string.
	 *     NeedSize: return the size of sub string that need to save(you could set the SubStr NULL to get this size).
	 * Return value description:
	 *     The size of sub string that need to save.
	 *     -1: not found SubStr in PSourceStr or get failed.
	**/
	static int GetSubStr_FormTailToHead_BeforeSpecialStrW(wchar_t * PSourceStr,wchar_t * SpecialStr,wchar_t * SubStr,DWORD & NeedSize);
	static int GetSubStr_FormTailToHead_BeforeSpecialStrA(char * PSourceStr,char * SpecialStr,char * SubStr,DWORD & NeedSize);

	/*
	 * Function description:
	 *     Get the sub string, which is after PLeft string and before PRight string.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     PLeft: PLeft string.
	 *     PRight: PRight string.
	 *     SubStr: the buffer of sub string.
	 *     NeedSize: return the size of sub string that need to save(you could set the SubStr NULL to get this size).
	 * Return value description:
	 *     The size of sub string that need to save.
	 *     -1: not found SubStr in PSourceStr or get failed.
	**/
	static int GetSubStr_BetweenSpecialStrW(wchar_t * PSourceStr,wchar_t * PLeft,wchar_t * PRight,wchar_t * SubStr,DWORD & NeedSize);
	static int GetSubStr_BetweenSpecialStrA(char * PSourceStr,char * PLeft,char * PRight,char * SubStr,DWORD & NeedSize);

	/*
	 * Function description:
	 *     Replace the string.
	 * parameters description:
	 *     PSourceStr: source string.
	 *     dwSize: the size of PSourceStr buffer.
	 *     StrWantReplace: the string you want to replace.
	 *     StrReplace: the string replaced.
	 *     NeedSize: return the size of outNewStr string that need to save(you could set the outNewStr NULL to get this size).
	 * Return value description:
	 *     The size of PSourceStr string that need to save.
	 *     -1: not found StrWantReplace in PSourceStr or replace failed.
	**/
	static int ReplaceOneStr_FormHeadToTailW(wchar_t * PSourceStr,DWORD dwSize, wchar_t * StrWantReplace, wchar_t * StrReplace);
	static int ReplaceOneStr_FormHeadToTailA(char * PSourceStr,DWORD dwSize, char * StrWantReplace, char * StrReplace);

	/*
	 * Function description:
	 *     The wide char string and the multi byte string converting function.
	 *     Call the windows API to convert.
	 * parameters description:
	 *     Be omitted.
	 * Return value description:
	 *     Same with Windows API.
	**/
	static int WinWcsToMbs(LPCWSTR lpWideCharStr,int cchWideChar,LPSTR lpMultiByteStr,int cbMultiByte);
	static int WinMbsToWcs(LPCSTR lpMultiByteStr,int cbMultiByte, LPWSTR lpWideCharStr,int cchWideChar);
	static int WinWcsToMbs(LPCWSTR lpWideCharStr,LPSTR lpMultiByteStr,int cbMultiByte);
	static int WinMbsToWcs(LPCSTR lpMultiByteStr,LPWSTR lpWideCharStr,int cchWideChar);

	/*
	 * Function description:
	 *     The wide char string and the multi byte string converting function.
	 *     Call the C library to convert.
	 * parameters description:
	 *     Be omitted.
	 * Return value description:
	 *     -1: have error in the function.
	**/
	static int CWcsToMbs(LPSTR lpMultiByteStr,LPCWSTR lpWideCharStr,int cbMultiByte);
	static int CMbsToWcs(LPWSTR lpWideCharStr,LPCSTR lpMultiByteStr,int cchWideChar);

	/*
	 * Function description:
	 *     Check the string is a DWORD number or not.
	 * parameters description:
	 *     PStr: the string you want to check.
	 * Return value description:
	 *     Whether the string is a DWORD number or not.
	**/
	static bool IsNumberW(wchar_t * PStr);
	static bool IsNumberA(char * PStr);

	/*
	 * Function description:
	 *     Check the string is begin with specific string or not.
	 * parameters description:
	 *     PStr: the string you want to check.
	 *     CheckStart: check begin string
	 * Return value description:
	 *     Whether the string is begin with specific string or not.
	**/
	static bool IsBeginWithW(wchar_t * PStr, wchar_t * CheckBegin);
	static bool IsBeginWithA(char * PStr, char * CheckBegin);

	/*
	 * Function description:
	 *     Check the string is end with specific string or not.
	 * parameters description:
	 *     PStr: the string you want to check.
	 *     CheckStart: check end string
	 * Return value description:
	 *     Whether the string is end with specific string or not.
	**/
	static bool IsEndWithW(wchar_t * PStr, wchar_t * CheckEnd);
	static bool IsEndWithA(char * PStr, char * CheckEnd);

	/*
	* Function description:
	*     Get the length of string, not include last \0 character.
	* parameters description:
	*     PStr: the string.
	**/
	static int GetStrLenthW(const wchar_t * PStr);
	static int GetStrLenthA(const char * PStr);

	/*
	* Function description:
	*     Get the size of buffer to store the string, include last \0 character.
	* parameters description:
	*     PStr: the string.
	**/
	static int GetStrSizeW(const wchar_t * PStr);
	static int GetStrSizeA(const char * PStr);

	/*
	* Function description:
	*     Get const char * file short name from full name.
	* parameters description:
	*     PStr: the file name string.
	**/
	static const char * GetCstFileShortNameFormFileName(const char * PStr);

	/*
	* File change line symbol
	**/
	static const char FileChangeLineStr[3];

	/*
	* File change line symbol
	**/
	static const DWORD SimpleStringBufferSize = 256;

private:
	/*
	 * Can not create the instance.
	**/
	DStr(){}
};

/*
 * DFile class
**/
class DCLIB_API DFile
{
	/* For the object function. */
public:
	enum OPENMODE /* Open mode enum value declaration: r, w, a, r+, w+, a+, rt+, wt+, at+, rb+, wb+, ab+ */
	{
		OPEN_R,	
		OPEN_W,
		OPEN_A,
		OPEN_RP,
		OPEN_WP,
		OPEN_AP,
		OPEN_RTP,
		OPEN_WTP,
		OPEN_ATP,
		OPEN_RBP,
		OPEN_WBP,
		OPEN_ABP,
	};
	enum SEEK_FROMWHERE /* Seek position from where enum value declaration. */
	{
		SEEK_FROM_BEGIN,
		SEEK_FROM_CUR,
		SEEK_FROM_END,
	};
	enum FILEACCESS /* File access check mode. */
	{
		FILEACCESS_EXIST,
		FILEACCESS_EXCUTE,
		FILEACCESS_WRITE,
		FILEACCESS_READ,
		FILEACCESS_READWRITE,
	};
	bool Open(char * mbsFileName, OPENMODE eOpenMode);
	bool Close();
	bool IsOpen();
	bool Seek(DWORD dwOffset, SEEK_FROMWHERE eFromWhere);
	DWORD Read(void * pvBuff, DWORD dwSize);
	DWORD Write(void * pvBuff, DWORD dwSize);
	DWORD GetFileSize();
	DWORD GetCurrentOffsetFromBegin();
	bool IsCurrentOffsetEOF();  /* check whether current offset reach the file end */
	const char * GetFileName();
	DFile();
	~DFile();

	/* For the class function. */
public:
	static bool CreateEmplyFile(char * mbsFileName);
	static bool IsExist(char * mbsFileName);
	static DWORD GetFileSize(char * mbsFileName);
	static bool Copy(char * mbsDestFileName,char* mbsSourceFileName,bool bOverwrite=true);
	static bool Move(char * mbsDestFileName,char* mbsSourceFileName,bool bOverwrite=true);
	static bool Delete(char * mbsFileName);
	static bool CheckAccess(char * mbsFileName,FILEACCESS eAccess);
	static const DWORD MaxFileFullNameLen = 260; /* Max file full name length define. */

protected:
	char m_FileName[MaxFileFullNameLen];
	bool m_bIsBinaryFile;
	DWORD m_FileSize;
	FILE * m_pFile;
};

/*
 * DFolder class
**/
class DCLIB_API DDir
{
public:
	static bool IsExist(char * mbsDirName);
	static bool IsEmpty(char * mbsDirName);
	static bool CreateDir(char * mbsDirName, bool bOverwrite=true);
	static bool CreateDirWithParent(char * mbsDirName, bool bOverwrite=true);
	static bool RemoveDir(char * mbsDirName);
	static bool ClearDir(char * mbsDirName);

	/*
	 * Function description:
	 *     Get Absolute Dir from current dir and relative dir.
	 * parameters description:
	 *     CurrentDir: current dir
	 *     RelativeDir: relative dir
	 *     OutAbsoluteDir: the buff to save absolute dir
	 *     dwSize: the OutAbsoluteDir buff size
	 * Return value description:
	 *     -1: get absolute dir error.
	 *     if OutAbsoluteDir = NULL, it will return the size need to save to buffer.
	**/
	static DWORD GetAbsoluteDir(char * CurrentDir,char * RelativeDir,char * OutAbsoluteDir,DWORD dwSize);
	static DWORD GetAbsoluteDir(char * RelativeDir,char * OutAbsoluteDir,DWORD dwSize);
	
	/*
	 * Function description:
	 *    Get parent dir.
	 * parameters description:
	 *     StrDir: the dir full name or fill full name 
	 * Return value description:
	 *     the min size need to save to buffer
	 *     -1: get parent dir error.
	 *     if OutParentDir = NULL, it will return the min size need to save to buffer. 
	**/
	static DWORD GetParentDir(char * StrDir, char * OutParentDir, DWORD dwSize);


private:
	static bool CreateDirWithParent_Help(char * mbsDirName);
};

/*
* DEnv class
**/
class DCLIB_API DEnv
{
public:
	static DWORD GetSystemPartitionA(char * Buff, DWORD dwSize);
	static DWORD GetWindowsDirA(char * Buff, DWORD dwSize);
	static DWORD GetWindowsTempDirA(char * Buff, DWORD dwSize);
	static DWORD GetExecuteFileFullNameA(char * Buff, DWORD dwSize);
	static DWORD GetExecuteDirFullNameA(char * Buff, DWORD dwSize);
	static DWORD GetEnvVarA(char * EnvName, char * Buff, DWORD dwSize);
};

/*
 * DRegManager class
**/
class DCLIB_API DRegManager
{		
public:
	/*
	 * Function description:
	 *     Write registry value.
	 * parameters description:
	 *     Be omitted.
	 * Return value description:
	 *     true: write registry value successfully.
 	 *     false: write registry value failed.
	 * For example:
	 *     WriteRegistryValueW(HKEY_LOCAL_MACHINE,L"SOFTWARE\\WDKey",L"ValueName",L"ValueData",REG_SZ);
	**/
	static bool WriteRegistryValueW(HKEY HRootKey, LPWSTR RegPath, LPCWSTR ValueName,LPBYTE ValueData,DWORD ValueType);
	static bool WriteRegistryValueA(HKEY HRootKey, LPSTR RegPath, LPSTR ValueName,LPBYTE ValueData,DWORD ValueType);
	
	/*
	 * Function description:
	 *     Read registry value.
	 * parameters description:
	 *     Be omitted.
	 * Return value description:
	 *     true: read registry value successfully.
 	 *     false: read registry value failed.
	 * For example:
	 *     LPBYTE data=new BYTE[256];
	 *     RegSetValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\WDKey",L"ValueName",data,REG_SZ); 
	 *     wcout<<LPCWSTR(data)<<endl;
	**/
	static bool ReadRegistryValueW(HKEY HRootKey, LPCWSTR RegPath, LPCWSTR ValueName,LPBYTE ValueData,DWORD ValueType);
	static bool ReadRegistryValueA(HKEY HRootKey, LPCSTR RegPath, LPCSTR ValueName,LPBYTE ValueData,DWORD ValueType);

	/*
	 * Function description:
	 *     Delete registry key.
	 * parameters description:
	 *     Be omitted.
	 * Return value description:
	 *     true: delete registry key successfully.
 	 *     false: delete registry key failed.
	 * For example:
	 *     DeleteRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WDKey");
	**/
	static bool DeleteRegistryKeyW(HKEY HRootKey, LPCWSTR RegPath);
	static bool DeleteRegistryKeyA(HKEY HRootKey, LPCSTR RegPath);

	/*
	 * Max key value length define.
	**/
	static const DWORD MaxKeyValueLen = 260;
};

/*
 * DTextFile class
**/
class DCLIB_API DTextFile: protected DFile
{
public:
	enum TEXTOPENMODE
	{
		TOPEN_RP,
		TOPEN_WP,
		TOPEN_AP,
	};
	bool Open(char * mbsFileName,TEXTOPENMODE eOpenMode);
	bool Close();
	DWORD Read(char * pcBuff, DWORD dwSize);
	DWORD ReadLine(char * pcBuff, DWORD dwSize);
	DWORD Write(const char * pvBuff, DWORD dwSize);
	DWORD WriteLine(const char * pvBuff, DWORD dwSize);
	bool IsToEOF();
	DTextFile();
	~DTextFile();
private:
	TEXTOPENMODE m_OpenMode;
	bool m_IsFirstOpenWithAPModeNeedAddChangeLine;
};

/*
 * DPerformanceChecker class
**/
struct DCLIB_API PerformanceCheckerItem
{
	char ProcName[DStr::SimpleStringBufferSize];
	char TestCaseName[DStr::SimpleStringBufferSize];
	DWORD TickCountBegin;
	DWORD TickCountEnd;
	DWORD ThreadTimeBegin;
	DWORD ThreadTimeEnd;
};
class DCLIB_API DPerformanceChecker
{
public:
	static void SetOutPutFileName(char * FileName);
	static void SetEnableConsoleOutput(bool bEnable);
	static void SetEnableFileOutput(bool bEnable);
	static DWORD GetTickCount(); /* unit: millisecond */
	static DWORD GetThreadTime(); /* unit: millisecond */
	static bool CreateOneTestFile(char* FileName, char* RepeatBuff, DWORD dwBuffSize, DWORD dwFileSize);
	static void PerformanceCheckBegin(char * ProcName, char * TestCaseName);
	static void PerformanceCheckEnd();
	static bool OutPutResult();
private:
	static bool m_bEnableFileOutput;
	static bool m_bEnableConsoleOutput;
	static bool m_IsBegining;
	static PerformanceCheckerItem curPFCI;
	static char m_OutPutFileName[DFile::MaxFileFullNameLen];
};
#define CheckPerformanceBegin(ProcName,TestCaseName) DPerformanceChecker::PerformanceCheckBegin(ProcName,TestCaseName)
#define CheckPerformanceEnd() DPerformanceChecker::PerformanceCheckEnd()

/*
 * DFileLog class
**/
#define GLOBAL_LOG_FILENAME "log.txt"
#define GLOBAL_LOG_SYNCOBJNAME "GLOBAL_LOG_SYNCOBJNAME"
class DSyncResource;
class DCLIB_API DFileLog
{
public:
	static DFileLog * GetInstance();
	static void Destory();

	DFileLog(char * FileName, char * SyncObjName = NULL);
	~DFileLog();
	bool Clear();
	void EnableSaveLog(bool Enable);
	bool __cdecl OutoutW(const wchar_t * lpwcsFormat,...);
	bool __cdecl OutoutA(const char * lpmbsFormat,...);

private:
	static DFileLog * m_Instance;
	bool m_bEnableSaveLog;
	DTextFile * m_pDTFile;
	char m_FileLogName[DFile::MaxFileFullNameLen];
	DSyncResource * m_DSyncRes;
};

/*
 * DMath class
**/
class DCLIB_API DMath
{
public:
	static long Min(long N1,long N2);
	static long Max(long N1,long N2);
};

/*
 * DConfigFile class
**/
class DCLIB_API DConfigFile
{
public:
	/*
	 * Function description:
	 *     Get value data from the configuration file.
	 * parameters description:
	 *     ValueName: the value name you want to get.
	 *     ValueData: the value data buffer to receive.
	 *     dwSize: the value data buffer size.
	 * Return value description:
	 *     true: get value data from configuration file successfully.
	 *     false: get value data from configuration file failed.
	**/
	bool GetValueDataA(char * ValueName,char * ValueData,DWORD dwSize);

	/*
	 * Function description:
	 *     Set value data to the configuration file.
	 * parameters description:
	 *     ValueName: the value name you want to set.
	 *     ValueData: the value data.
	 * Return value description:
	 *     true: set value data to the configuration file successfully.
	 *     false: set value data to the configuration file failed.
	**/
	bool SetValueDataA(char * ValueName,char * ValueData);

	/*
	 * Function description:
	 *     Constructor.
	 * parameters description:
	 *     ConfigFileName: the configuration file.
	**/
	DConfigFile(char * ConfigFileName);
	DConfigFile(wchar_t * ConfigFileName);

	/*
	 * Function description:
	 *     Destructor.
	**/
	~DConfigFile();

private:
	char m_fileName[DFile::MaxFileFullNameLen];
	DTextFile * m_pDTFile;
	/*
	 * Max file full name length define.
	**/
	static const DWORD MaxSizeOfOneLineInConfigDataFile = 512;
};

/*
* CSecEnDecode class
**/
class DCLIB_API DEncode
{
public:
	/*
	* Function description:
	*     Security encode.
	*     [encode function]  one byte - 12345678 -> 78123456
	* parameters description:
	*     PSourceByte: the buffer you want to encode.
	*     dwSize: the size of buffer.
	* Return value description:
	*     true: encode successfully.
	*     false: encode failed.
	**/
	static bool SecurityEncode(BYTE * PSourceByte,DWORD dwSize);

	/*
	* Function description:
	*     Decode encode.
	*     [decode function]  one byte - 78123456 -> 12345678
	* parameters description:
	*     PSourceByte: the buffer you want to decode.
	*     dwSize: the size of buffer.
	* Return value description:
	*     true: decode successfully.
	*     false: decode failed.
	**/
	static bool SecurityDecode(BYTE * PSourceByte,DWORD dwSize);

};

/*
* DList class
**/
class DCLIB_API DListNode
{
public:
	DListNode(){PData=NULL;NextPoint=NULL;PrePoint=NULL;}
public:
	void * PData;
	DListNode * NextPoint;
	DListNode * PrePoint;
};
class DCLIB_API DList
{
	enum LISTSEEK_FROMWHERE
	{
		LISTSEEK_FROM_BEGIN,
		LISTSEEK_FROM_CUR,
		LISTSEEK_FROM_END,
	};
public:
	bool AddToTail(void * pvData);
	bool AddToHead(void * pvData);
	bool GerFromTail(void * &pvData);
	bool GerFromHead(void * &pvData);
	bool PeekTail(void * &pvData);
	bool PeekHead(void * &pvData);
	bool SeekCurrent(DWORD dwOffset, LISTSEEK_FROMWHERE eFromWhere);
	bool AddAfterCurrent(void * pvData);
	bool AddBeforeCurrent(void * pvData);
	bool UptateCurrent(void * pvData, void * &pvBefore);
	bool GetCurrent(void * &pvData);
	bool PeekCurrent(void * &pvData);
	bool GetCurrentPos(DWORD & dwPos);
	DList(){PHead=NULL;PTail=NULL;Count=0;PCurrent=NULL;}
private:
	DListNode * PHead;
	DListNode * PTail;
	DListNode * PCurrent;
	int Count;
};

/*
* DThread class
**/
class DCLIB_API DThread
{
public:
	DThread();
	virtual ~DThread();
	virtual DWORD ThreadProc(void * lpParam) = 0;
	virtual HANDLE Begin(void * lpParam); /* If the function succeeds, the return value is the thread's handle. */
	virtual DWORD Suspend(); /* If the function succeeds, the return value is the thread's previous suspend count. else(-1). */
	virtual DWORD Resume(); /* If the function succeeds, the return value is the thread's previous suspend count. else(-1). */
	virtual bool GetExitCode(DWORD * pdwRetVal);
public:
	friend DWORD WINAPI DThreadProc(LPVOID lpParam);
private:
	DWORD m_dwThreadID;
	HANDLE m_hThread;
	void * m_pvThreadParam;
};

/*
* DTimer class
**/
class DCLIB_API DTimer
{
public:
	DTimer(DWORD dwTimerIntervalMillisecond = 1000, bool bIsCycle = false);
	virtual ~DTimer();
	virtual bool Start();
	virtual void Run() = 0; /* user implement */
public:
	friend class DTimerThread;
private:
	HANDLE m_hWaitableTimer;
	DTimerThread * m_pDTimerThread;
	DWORD m_dwTimerIntervalMillisecond;
	DWORD m_bIsCycle;
};

/*
* DSyncResource class
**/
class DCLIB_API DSyncResource
{
public:
	DSyncResource(long lInitResCnt = 1,long lMaxResCnt = 1, const char * mbsSyncResObjName = NULL);
	virtual ~DSyncResource();
	virtual bool ApplyResource(long lResCnt = 1);
	virtual bool ReleaseResource(long lResCnt = 1, long * plPreCnt = NULL);
private:
	HANDLE m_hSemaphore;
	long m_lInitResCnt;
	long m_lMaxResCnt;
};

/*
* DGUID class
**/
class DCLIB_API DGUID
{
	/* e.g 6F9619FF-8B86-D011-B42D-00C04FC964FF */
public:
	DGUID();
	GUID Guid;
	char GuidStr[64];
public:
	static DWORD CreateNewGUIDStr(char * buf, DWORD dwBufSize); /* need 37 char at least */
	static DWORD CreateNewGUID(GUID * pGuid);
};

/*
* DTestHelper class
**/
class DCLIB_API DTestHelper
{
public:
	/* TestHelper OutPut */
	static void TestHelperOutPutA(const char * lpmbsFormat,...);
	static void SetEnableConsoleOutput(bool bEnable);
	static void SetEnableFileOutput(bool bEnable);

	/* check bool type value */
	static bool TestValueEQ(char * mbsFileName, DWORD dwLineNo, 
		bool cValue, bool cExpect, char * mbsCaseName);

	/* check int type value */
	static bool TestValueEQ(char * mbsFileName, DWORD dwLineNo, 
		int cValue, int cExpect, char * mbsCaseName);

	/* check multi byte string type value */
	static bool TestStrAEQ(char * mbsFileName, DWORD dwLineNo, 
		char * cValue, char  * cExpect, char * mbsCaseName);

	/* check wide char string type value */
	static bool TestStrWEQ(char * mbsFileName, DWORD dwLineNo, 
		wchar_t * cValue, wchar_t  * cExpect, char * mbsCaseName);

	static bool TestPointEQ(char * mbsFileName, DWORD dwLineNo, 
		void * cValue, void  * cExpect, char * mbsCaseName);

private:
	static bool m_bEnableConsoleOutput;
	static bool m_bEnableFileOutput;
};

#define CheckValue_EQ(CheckValue,ExpectValue,TestCase) DTestHelper::TestValueEQ(__FILE__,__LINE__,CheckValue,ExpectValue,TestCase);
#define CheckPoint_EQ(CheckPoint,ExpectPoint,TestCase) DTestHelper::TestPointEQ(__FILE__,__LINE__,CheckPoint,ExpectPoint,TestCase);
#define CheckStrA_EQ(CheckValue,ExpectValue,TestCase) DTestHelper::TestStrAEQ(__FILE__,__LINE__,CheckValue,ExpectValue,TestCase);
#define CheckStrW_EQ(CheckValue,ExpectValue,TestCase) DTestHelper::TestStrWEQ(__FILE__,__LINE__,CheckValue,ExpectValue,TestCase);

#endif /* #ifndef INCLUDE_DCLIB */

/************************************************************************
*	END OF FILE
*************************************************************************/