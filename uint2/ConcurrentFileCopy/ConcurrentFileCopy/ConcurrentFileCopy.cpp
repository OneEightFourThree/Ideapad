// ConcurrentFileCopy.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include "ConcurrentFileCopy.h"

TCHAR* szTitle = _T("Concurrent file copy");
TCHAR* szWindowClass = _T("__CFC_WND_CLASS");

DWORD dwReadBytes = 0;
DWORD dwWriteBytes = 0;
DWORD dwBlockSize = 0;
DWORD dwFileSize = 0;
HLOCAL pMemory = NULL;

//#define MAX_LOADSTRING 100
//
//// 全局变量: 
//HINSTANCE hInst;								// 当前实例
//TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
//TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
//
//// 此代码模块中包含的函数的前向声明: 
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	RegisterWndClass(hInstance);

	HWND hWnd = NULL;
	HWND hWndPB = NULL;

	if (!(hWnd = InitializeInstance(hInstance, nCmdShow, hWndPB)))
	{
		return 1;
	}
	MSG msg = { 0 };
	TCHAR szReadFile[MAX_PATH];
	TCHAR szWriteFile[MAX_PATH];

	if (FileDialog(hWnd, szReadFile, FILE_OPEN) && FileDialog(hWnd, szWriteFile, FILE_SAVE))
	{
		COPYDETAILS copyDetails = { hInstance, hWndPB, szReadFile, szWriteFile };
		HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
		HANDLE hReadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadRoutine, &copyDetails, 0, NULL);
		while (GetMessage(&msg, NULL,0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		CloseHandle(hReadThread);
		CloseHandle(hMutex);
	}
	else
	{
		MessageBox(hWnd, _T("Cannot open file!"), _T("Error!"), MB_OK);
	}
	LocalFree(pMemory);
	UnregisterClass(szWindowClass, hInstance);
	return (int)msg.wParam;


 //	// TODO:  在此放置代码。
	//MSG msg;
	//HACCEL hAccelTable;

	//// 初始化全局字符串
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_CONCURRENTFILECOPY, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	//// 执行应用程序初始化: 
	//if (!InitInstance (hInstance, nCmdShow))
	//{
	//	return FALSE;
	//}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONCURRENTFILECOPY));

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
ATOM RegisterWndClass(HINSTANCE hInstance)
{
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
HWND InitializeInstance(HINSTANCE hInstance, int nCmdShow,HWND& hWndPB)
{
   HWND hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,200,200,440,290,NULL,NULL,hInstance,NULL);

   RECT rcClient = { 0 };
   int cyVScroll = 0;

  /* hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/
   if (!hWnd)
   {
      return FALSE;
   }
   HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, BALTIC_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Microsoft Sans Serif"));

   HWND hButton = CreateWindow(_T("BUTTON"), _T("Close"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 310, 200, 100, 25, hWnd, (HMENU)BUTTON_CLOSE, hInstance, NULL);

   SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);

   GetClientRect(hWnd, &rcClient);
   cyVScroll = GetSystemMetrics(SM_CYVSCROLL);

   hWndPB = CreateWindow(PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE, rcClient.left, rcClient.bottom - cyVScroll, rcClient.right, cyVScroll, hWnd, (HMENU)0, hInstance, NULL);
   SendMessage(hWndPB, PBM_SETSTEP, (WPARAM)1, 0);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return hWnd;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

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
	switch (message)
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
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

// “关于”框的消息处理程序。
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}

DWORD WINAPI ReadRoutine(LPVOID lpParameter)
{
	PCOPYDETAILS pCopyDetails = (PCOPYDETAILS)lpParameter;
	HANDLE hFile = CreateFile(pCopyDetails->szReadFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == (HANDLE)INVALID_HANDLE_VALUE)
	{
		return false;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	dwBlockSize = GetBlockSize(dwFileSize);
	HANDLE hWriteThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WriteRoutine, pCopyDetails, 0, NULL);
	size_t uBufferLength = (size_t)ceil((double)dwFileSize / (double)dwBlockSize);
	SendMessage(pCopyDetails->hWndPB, PBM_SETRANGE, 0, MAKELPARAM(0, uBufferLength));
	pMemory = LocalAlloc(LPTR, dwFileSize);
	void *pBuffer = LocalAlloc(LPTR, dwBlockSize);

	int iOffset = 0;
	DWORD dwBytesRed = 0;
	do
	{
		ReadFile(hFile, pBuffer, dwBlockSize, &dwBytesRed, NULL);
		if (!dwBytesRed)
		{
			break;
		}
		HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
		WaitForSingleObject(hMutex, INFINITE);
		memcpy((char*)pMemory + iOffset, pBuffer, dwBytesRed);
		
		dwReadBytes += dwBytesRed;
		ReleaseMutex(hMutex);
		iOffset += (int)dwBlockSize;
	} while (true);
	LocalFree(pBuffer);
	CloseHandle(hFile);
	CloseHandle(hWriteThread);
	return 0;
}

DWORD WINAPI WriteRoutine(LPVOID lpParameter)
{
	PCOPYDETAILS pCopyDetails = (PCOPYDETAILS)lpParameter;
	HANDLE hFile = CreateFile(pCopyDetails->szWriteFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == (HANDLE)INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	DWORD dwBytesWritten = 0;
	int iOffset = 0;
	do
	{
		int iRemainingBytes = (int)dwFileSize - iOffset;
		if (iRemainingBytes <= 0)
		{
			break;
		}
		Sleep(10);
		if (dwWriteBytes < dwReadBytes)
		{
			DWORD dwBytesToWrite = dwBlockSize;
			if (!(dwFileSize / dwBlockSize))
			{
				dwBytesToWrite = (DWORD)iRemainingBytes;
			}
			HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
			WaitForSingleObject(hMutex, INFINITE);
			
			WriteFile(hFile, (char *)pMemory + iOffset, dwBytesToWrite,&dwBytesWritten,NULL);

			dwWriteBytes += dwBytesWritten;

			ReleaseMutex(hMutex);
			SendMessage(pCopyDetails->hWndPB, PBM_STEPIT, 0, 0);
			iOffset += (int)dwBlockSize;
		}
	} while (true);
	CloseHandle(hFile);
	return 0;
}

BOOL FileDialog(HWND hWnd, LPTSTR szFileName, DWORD dwFileOperation)
{
#ifdef _UNICODE
	OPENFILENAMEW ofn;

#else
	OPENFILENAMEA ofn;
#endif
	TCHAR szFile[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = dwFileOperation == FILE_OPEN ? OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST : OFN_SHOWHELP | OFN_OVERWRITEPROMPT;

	if (dwFileOperation == FILE_OPEN)
	{
		if (GetOpenFileName(&ofn) == TRUE)
		{
			_tcscpy_s(szFileName, MAX_PATH - 1, szFile);
			return TRUE;
		}
	}
	else
	{
		if (GetSaveFileName(&ofn) == TRUE)
		{
			_tcscpy_s(szFileName, MAX_PATH - 1, szFile);
			return TRUE;
		}
	}
	return FALSE;
}

DWORD GetBlockSize(DWORD dwFileSize)
{
	return dwFileSize > 4096 ? 4096 : 512;
}