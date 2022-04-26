#include<Windows.h>

CONST CHAR g_szClassName[] = "My Window Class";
//g - global
//sz - string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//����������� ������ ����
	WNDCLASSEX wc;//������� ��������� wc - Window Class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));//�������� ��������� wc
	//�������������� ���� ��������� wc
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;//������ ��������� ���� ��� ������� ������
	wc.style = 0;//����� ���� ���������� ��� ������������� ��������
	//����� ��������� ������ �������� �� ������ ����
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));//������ ������������ � ������ �����
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));//������ ������������ � ������ ���������(Icon Small)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;//id - ���� ����, ���� ���� �������,id �������, ���� ���� ��������.NULL - ���� �����������
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))//����������� ������ ����
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//�������� ����
	HWND hwnd = CreateWindowEx
	(
		NULL,//ex-style
		g_szClassName,//��� ������ ���� 
		"Main Window",//��������� ����
		WS_OVERLAPPEDWINDOW,//����� ����. � �������� ���� ���������� �����. ������(WS_OVERLAPPEDWINDOW)
		CW_USEDEFAULT, CW_USEDEFAULT,//��������� ���� �� ������
		CW_USEDEFAULT, CW_USEDEFAULT,//������ ����
		NULL,//null - �����������, ������������ ����
		NULL,//ID ���� ����, ���� ���� �������, ��� ID �������, ���� ���� ��������.NULL
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;//���� ���� �� �������
	}
	ShowWindow(hwnd, nCmdShow);//������ ����� �����������
	UpdateWindow(hwnd);//���������� ���� 

	//������ ����� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)//GetMessage - ����� ��������� �� ������� ���������
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);//���������� ��������� � ��������� ����
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE://��������� �������� ����(������ ���� ������)
		//������ ��������� WM_INITDIALOG � ���������� ����
		//��� ��������� ������������ ���� ��� - ��� �������� ����
		break;
	case WM_COMMAND:break;
	case WM_CLOSE://�������� ��������� DestroyWindow ������ ����
		if (MessageBox(hwnd, "�� ������������� ������ ������� ����?", "��, �������?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY://���������� �������� ��������� � ������� ���������
		PostQuitMessage(0);//�������� ��������� � ����������� ������
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}