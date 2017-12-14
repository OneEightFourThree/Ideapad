#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThis, HINSTANCE hPrev, LPSTR szCmdLine, int iCmdShow)
{
	//��ʹ��ĳЩ�������������������һ�¶�����Ż�
	UNREFERENCED_PARAMETER(hPrev);
	UNREFERENCED_PARAMETER(szCmdLine);
	//ʵ����WNDCLASSEX���ڽṹ
	WNDCLASSEX	wndEx = { 0 };
	//��������ʵ��������������Ķ����ֽ���
	wndEx.cbClsExtra = 0;
	//�����˴��ڽṹ�Ĵ�С�����ֽ�Ϊ��λ��
	wndEx.cbSize = sizeof(wndEx);
	//������ʵ��������ʵ�������Ķ����ֽ���
	wndEx.cbWndExtra = 0;
	//�����˴����౳����ˢ�ľ��
	wndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//�����˴�������ľ��
	wndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	//�����˴�����ͼ��ľ��
	wndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//�����˰������ڹ��̵�ʵ�����
	wndEx.hInstance = hThis;
	//������ָ�򴰿ڹ��̵�ָ��
	wndEx.lpfnWndProc = WndProc;
	//������ָ���Կ��ַ���β���ַ�����ԭ�ӵ�ָ��
	wndEx.lpszClassName = TEXT("GUI Project");
	//������ָ���Կ��ַ���β���ַ��� ��ָ�룬���ַ���ָ���˴�����˵�����Դ��
	wndEx.lpszMenuName = NULL;
	//�����˴��������ʽ
	wndEx.style = CS_HREDRAW | CS_VREDRAW;
	//ע��һ�������࣬��CreateWindow��CreateWindowEx�����Ժ�ʹ��
	if (!RegisterClassEx(&wndEx))
	{
		return -1;
	}
	//����һ���ص��������Ĵ��ڻ����Ӵ���
	HWND hWnd = CreateWindow(wndEx.lpszClassName, TEXT("GUI Project"), WS_OVERLAPPEDWINDOW, 200, 200, 400, 300, HWND_DESKTOP, NULL, hThis, 0);
	if (!hWnd)
	{
		return -1;
	}
	//�򴰿ڷ���һ��WM_PAINT��Ϣ������ָ�����ڵĿͻ���
	UpdateWindow(hWnd);
	//����ָ�����ڵ���ʾ״̬
	ShowWindow(hWnd, iCmdShow);

	MSG msg = { 0 };

	//GetMessage API �������̵߳���Ϣ�����м�����Ϣ
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		//���������Ϣ������ַ���Ϣ
		TranslateMessage(&msg);
		//�ַ�һ����Ϣ�����ڹ���
		DispatchMessage(&msg);
	}
	//����ָ���Ĵ���
	DestroyWindow(hWnd);
	//ע�������࣬�ͷŸ���ռ�õ��ڴ�
	UnregisterClass(wndEx.lpszClassName, hThis);
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
	{
		//�ͷ�ϵͳ��Դ����ȫ�رո�Ӧ�ó���
		PostQuitMessage(0);
		break;
	}
	default:
	{	//����Ĭ�ϴ��ڹ���(DefWindowProc)����Ӧ�ó���δ����Ĵ�����Ϣ���ú���ȷ��ÿ����Ϣ��������
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}




