// PhilosophersDinner.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "PhilosophersDinner.h"

#define BUTTON_CLOSE 100
#define	PHILOSOPHER_COUNT 5
#define WM_INVALIDATE WM_USER + 1

typedef struct _tagCOMMUNICATIONOBJECT
{
	HWND hWnd;
	bool bExitApplication;
	int iPhilosopherArray[PHILOSOPHER_COUNT];
	int PhilosopherCount;
}COMMUNICATIONOBJECT,*PCOMMUNICATIONOBJECT;


//初始化实例函数
HWND InitInstance(HINSTANCE hInstance, int nCmdShow);
//注册类函数，注册一个窗口类
ATOM MyRegisterClass(HINSTANCE hInstance);
//窗口回掉函数？
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//哲学家通过函数？
int PhilosopherPass(int iPhilosopher);

void FillEllipse(HWND hWnd, HDC hDC, int iLeft, int iTop, int iRight, int iBottom, int iPass);

TCHAR* szTitle = TEXT("Philosophers Dinner Demo");
TCHAR* szWindowClass = TEXT("__PD_WND_CLASS__");
TCHAR* szSemaphoreName = TEXT("__PD_SEMAPHORE__");
TCHAR* szMappingName = TEXT("__SHARED_FILE_MAPPING__");
PCOMMUNICATIONOBJECT pCommObject = NULL;

#define MAX_LOADSTRING 100
//
//// 全局变量: 
//HINSTANCE hInst;								// 当前实例
//TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
//TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
// 此代码模块中包含的函数的前向声明: 
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HANDLE	hMapping = CreateFileMapping((HANDLE)-1,NULL,PAGE_READWRITE,0,sizeof(COMMUNICATIONOBJECT),szMappingName);
	if (!hMapping)
	{
		//显示一个模态对话框
		MessageBox(NULL,TEXT("Cannot open file mapping"),TEXT("Error!"),MB_OK);
		return 1;
	}
	pCommObject = (PCOMMUNICATIONOBJECT)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!pCommObject)
	{
		MessageBox(NULL, TEXT("Cannot get access to file mapping! "), TEXT("Error!"), MB_OK);
		CloseHandle(hMapping);
		return 1;
	}
	//注册并初始化某些通用控件窗口类
	InitCommonControls();
	//注册一个窗口类
	MyRegisterClass(hInstance);
	HWND hWnd = NULL;
	if (!(hWnd = InitInstance(hInstance, nCmdShow)))
	{
		return FALSE;
	}
	pCommObject->bExitApplication = false;
	pCommObject->hWnd = hWnd;
	memset(pCommObject->iPhilosopherArray, 0, sizeof(*pCommObject->iPhilosopherArray));
	pCommObject->PhilosopherCount = PHILOSOPHER_COUNT;
	HANDLE hSemaphore = CreateSemaphore(NULL, int(PHILOSOPHER_COUNT / 2), int(PHILOSOPHER_COUNT / 2), szSemaphoreName);
	STARTUPINFO startupInfo[PHILOSOPHER_COUNT] = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };
	PROCESS_INFORMATION processInformation[PHILOSOPHER_COUNT] = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };
	HANDLE hProcesses[PHILOSOPHER_COUNT];
	TCHAR szBuffer[8];
	for (int iIndex = 0; iIndex < PHILOSOPHER_COUNT; iIndex++)
	{
#ifdef UNICODE
		wsprintf(szBuffer, L"%d", iIndex);
#else
		sprintf(szBuffer, "%d", iIndex);
#endif
		if (CreateProcess(TEXT("..\\Debug\\Philosopher.exe"), szBuffer, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo[iIndex], &processInformation[iIndex]))
		{
			hProcesses[iIndex] = processInformation[iIndex].hProcess;
		}
	}
 	// TODO:  在此放置代码。
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	pCommObject->bExitApplication = true;
	UnmapViewOfFile(pCommObject);
	WaitForMultipleObjects(PHILOSOPHER_COUNT, hProcesses, TRUE, INFINITE);
	for (int iIndex = 0; iIndex < PHILOSOPHER_COUNT; iIndex++)
	{
		CloseHandle(hProcesses[iIndex]);
	}
	CloseHandle(hSemaphore);
	CloseHandle(hMapping);
	return (int)msg.wParam;
	//HACCEL hAccelTable;

	//// 初始化全局字符串
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_PHILOSOPHERSDINNER, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	//// 执行应用程序初始化: 
	//if (!InitInstance (hInstance, nCmdShow))
	//{
	//	return FALSE;
	//}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHILOSOPHERSDINNER));

	//// 主消息循环: 
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}

	//return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	/*WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHILOSOPHERSDINNER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PHILOSOPHERSDINNER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);*/
	WNDCLASSEX wndEx;
	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.style = CS_HREDRAW | CS_VREDRAW;
	wndEx.lpfnWndProc = WndProc;
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hInstance = hInstance;
	wndEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndEx.lpszMenuName = NULL;
	wndEx.lpszClassName = szWindowClass;
	wndEx.hIconSm = LoadIcon(wndEx.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	return RegisterClassEx(&wndEx);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//创建重叠、弹出式窗口或子窗口
   HWND hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,200,200,540,590,NULL,NULL,hInstance,NULL);
   if (!hWnd)
   {
	   return NULL;
   }
	//创建一个具有特定特征的逻辑字体
   HFONT hFont = CreateFont(14,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,BALTIC_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN,TEXT("Microsoft Sans Serif"));
   HWND	hButton = CreateWindow(TEXT("BUTTON"), TEXT("Close"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 410, 520, 100, 25, hWnd, (HMENU)BUTTON_CLOSE, hInstance, NULL);
   //将指定的消息发送到一个或多个窗口
   SendMessage(hButton,WM_SETFONT,(WPARAM)hFont,TRUE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return hWnd;

   //hInst = hInstance; // 将实例句柄存储在全局变量中

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   //if (!hWnd)
   //{
   //   return FALSE;
   //}

   //ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);

   //return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;*/

	//switch (message)
	//{
	//case WM_COMMAND:
	//	wmId    = LOWORD(wParam);
	//	wmEvent = HIWORD(wParam);
	//	// 分析菜单选择: 
	//	switch (wmId)
	//	{
	//	case IDM_ABOUT:
	//		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
	//		break;
	//	case IDM_EXIT:
	//		DestroyWindow(hWnd);
	//		break;
	//	default:
	//		return DefWindowProc(hWnd, message, wParam, lParam);
	//	}
	//	break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	// TODO:  在此添加任意绘图代码...
	//	EndPaint(hWnd, &ps);
	//	break;
	//case WM_DESTROY:
	//	PostQuitMessage(0);
	//	break;
	//default:
	//	return DefWindowProc(hWnd, message, wParam, lParam);
	//}
	switch(uMsg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
		}
		break;
	}
	case WM_INVALIDATE:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT	paintStruct;
		HDC hDC = BeginPaint(hWnd, &paintStruct);
		FillEllipse(hWnd, hDC, 210, 10, 310, 110, PhilosopherPass(1));
		FillEllipse(hWnd, hDC, 410, 170, 510, 270, PhilosopherPass(1));
		FillEllipse(hWnd, hDC, 335, 400, 435, 500, PhilosopherPass(1));
		FillEllipse(hWnd, hDC, 80, 400, 180, 500, PhilosopherPass(1));
		FillEllipse(hWnd, hDC, 10, 170, 110, 270, PhilosopherPass(1));
		EndPaint(hWnd, &paintStruct);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}

int PhilosopherPass(int iPhilosopher)
{
	return pCommObject->iPhilosopherArray[iPhilosopher - 1];
}

void FillEllipse(HWND hWnd, HDC hDC, int iLeft, int iTop, int iRight, int iBottom, int iPass)
{
	HBRUSH hBrush = NULL;
	if (iPass)
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
	}
	else
	{
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
	}
	//把一个对象(位图、画笔、画刷等)选入指定的设备描述表。新的对象代替同一类型的老对象。
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	//用于画一个椭圆，椭圆的中心是限定矩形的中心，使用当前画笔画椭圆，用当前的画刷填充椭圆
	Ellipse(hDC, iLeft, iTop, iRight, iBottom);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
