// PhilosophersDinner.cpp : ����Ӧ�ó������ڵ㡣
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


//��ʼ��ʵ������
HWND InitInstance(HINSTANCE hInstance, int nCmdShow);
//ע���ຯ����ע��һ��������
ATOM MyRegisterClass(HINSTANCE hInstance);
//���ڻص�������
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//��ѧ��ͨ��������
int PhilosopherPass(int iPhilosopher);

void FillEllipse(HWND hWnd, HDC hDC, int iLeft, int iTop, int iRight, int iBottom, int iPass);

TCHAR* szTitle = TEXT("Philosophers Dinner Demo");
TCHAR* szWindowClass = TEXT("__PD_WND_CLASS__");
TCHAR* szSemaphoreName = TEXT("__PD_SEMAPHORE__");
TCHAR* szMappingName = TEXT("__SHARED_FILE_MAPPING__");
PCOMMUNICATIONOBJECT pCommObject = NULL;

#define MAX_LOADSTRING 100
//
//// ȫ�ֱ���: 
//HINSTANCE hInst;								// ��ǰʵ��
//TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
//TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
// �˴���ģ���а����ĺ�����ǰ������: 
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
		//��ʾһ��ģ̬�Ի���
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
	//ע�Ტ��ʼ��ĳЩͨ�ÿؼ�������
	InitCommonControls();
	//ע��һ��������
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
 	// TODO:  �ڴ˷��ô��롣
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

	//// ��ʼ��ȫ���ַ���
	//LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadString(hInstance, IDC_PHILOSOPHERSDINNER, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	//// ִ��Ӧ�ó����ʼ��: 
	//if (!InitInstance (hInstance, nCmdShow))
	//{
	//	return FALSE;
	//}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHILOSOPHERSDINNER));

	//// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//�����ص�������ʽ���ڻ��Ӵ���
   HWND hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,200,200,540,590,NULL,NULL,hInstance,NULL);
   if (!hWnd)
   {
	   return NULL;
   }
	//����һ�������ض��������߼�����
   HFONT hFont = CreateFont(14,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,BALTIC_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN,TEXT("Microsoft Sans Serif"));
   HWND	hButton = CreateWindow(TEXT("BUTTON"), TEXT("Close"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 410, 520, 100, 25, hWnd, (HMENU)BUTTON_CLOSE, hInstance, NULL);
   //��ָ������Ϣ���͵�һ����������
   SendMessage(hButton,WM_SETFONT,(WPARAM)hFont,TRUE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return hWnd;

   //hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
	//	// �����˵�ѡ��: 
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
	//	// TODO:  �ڴ���������ͼ����...
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
	//��һ������(λͼ�����ʡ���ˢ��)ѡ��ָ�����豸�������µĶ������ͬһ���͵��϶���
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	//���ڻ�һ����Բ����Բ���������޶����ε����ģ�ʹ�õ�ǰ���ʻ���Բ���õ�ǰ�Ļ�ˢ�����Բ
	Ellipse(hDC, iLeft, iTop, iRight, iBottom);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

// �����ڡ������Ϣ�������
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
