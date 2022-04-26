#include<Windows.h>

CONST CHAR g_szClassName[] = "My Window Class";
//g - global
//sz - string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//–егистраци€ класса окна
	WNDCLASSEX wc;//создаем структуру wc - Window Class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));//«јЌ”Ћя≈ћ экземпл€р wc
	//инициализируем пол€ структуры wc
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;//задаем процедуру окна дл€ данного класса
	wc.style = 0;//стиль окна определ€ет его доплнительные свойства
	//Ќабор возможных стилей завсисит от класса окна
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));//иконка отображаема€ в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));//иконка отображаема€ в строке заголовка(Icon Small)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;//id - меню окна, если окно главное,id ресурса, если окно дочернее.NULL - меню отсутствует
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))//–егистраци€ класса окна
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//—оздание окна
	HWND hwnd = CreateWindowEx
	(
		NULL,//ex-style
		g_szClassName,//им€ класса окна 
		"Main Window",//заголовок окна
		WS_OVERLAPPEDWINDOW,//стиль окна. ” главного окна приложени€ стиль. всегда(WS_OVERLAPPEDWINDOW)
		CW_USEDEFAULT, CW_USEDEFAULT,//положение окна на экране
		CW_USEDEFAULT, CW_USEDEFAULT,//размер окна
		NULL,//null - отсутствует, –одительское окно
		NULL,//ID меню окна, если окно главное, или ID ресурса, если окно дочернее.NULL
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;//если окно не создали
	}
	ShowWindow(hwnd, nCmdShow);//задаем режим отображени€
	UpdateWindow(hwnd);//ѕрорисовка окна 

	//«апуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)//GetMessage - берет сообщение из очереди сообщение
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);//отправл€ет сообщение в процедуру окна
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE://создаютс€ элементы окна(кнопки меню значки)
		//аналог сообщени€ WM_INITDIALOG в диалоговом окне
		//это сообщение отрабатывает один раз - при создании окна
		break;
	case WM_COMMAND:break;
	case WM_CLOSE://посылает сообщение DestroyWindow своему окну
		if (MessageBox(hwnd, "¬ы действительно хотите закрыть окно?", "Ўо, внутуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY://отправл€ет выходное сообщение в очередь сообщений
		PostQuitMessage(0);//посылает сообщение о прекращении работы
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}