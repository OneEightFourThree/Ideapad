#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThis, HINSTANCE hPrev, LPSTR szCmdLine, int iCmdShow)
{
	//不使用某些参数，方便编译器进行一下额外的优化
	UNREFERENCED_PARAMETER(hPrev);
	UNREFERENCED_PARAMETER(szCmdLine);
	//实例化WNDCLASSEX窗口结构
	WNDCLASSEX	wndEx = { 0 };
	//定义了在实例化窗口类后分配的额外字节数
	wndEx.cbClsExtra = 0;
	//定义了窗口结构的大小（以字节为单位）
	wndEx.cbSize = sizeof(wndEx);
	//定义了实例化窗口实例后分配的额外字节数
	wndEx.cbWndExtra = 0;
	//定义了窗口类背景画刷的句柄
	wndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//定义了窗口类光标的句柄
	wndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	//定义了窗口类图标的句柄
	wndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//定义了包含窗口过程的实例句柄
	wndEx.hInstance = hThis;
	//定义了指向窗口过程的指针
	wndEx.lpfnWndProc = WndProc;
	//定义了指向以空字符结尾的字符串或原子的指针
	wndEx.lpszClassName = TEXT("GUI Project");
	//定义了指向以空字符结尾的字符串 的指针，该字符串指定了窗口类菜单的资源名
	wndEx.lpszMenuName = NULL;
	//定义了窗口类的样式
	wndEx.style = CS_HREDRAW | CS_VREDRAW;
	//注册一个窗口类，供CreateWindow或CreateWindowEx函数稍后使用
	if (!RegisterClassEx(&wndEx))
	{
		return -1;
	}
	//创建一个重叠、弹出的窗口或者子窗口
	HWND hWnd = CreateWindow(wndEx.lpszClassName, TEXT("GUI Project"), WS_OVERLAPPEDWINDOW, 200, 200, 400, 300, HWND_DESKTOP, NULL, hThis, 0);
	if (!hWnd)
	{
		return -1;
	}
	//向窗口发送一条WM_PAINT消息，更新指定窗口的客户区
	UpdateWindow(hWnd);
	//设置指定窗口的显示状态
	ShowWindow(hWnd, iCmdShow);

	MSG msg = { 0 };

	//GetMessage API 从主调线程的消息队列中检索信息
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		//把虚拟键消息翻译成字符消息
		TranslateMessage(&msg);
		//分发一条消息给窗口过程
		DispatchMessage(&msg);
	}
	//销毁指定的窗口
	DestroyWindow(hWnd);
	//注销窗口类，释放该类占用的内存
	UnregisterClass(wndEx.lpszClassName, hThis);
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		//释放系统资源，安全关闭该应用程序
		PostQuitMessage(0);
		break;
	}
	default:
	{	//调用默认窗口过程(DefWindowProc)处理应用程序未处理的窗口消息，该函数确保每个消息都被处理
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}




