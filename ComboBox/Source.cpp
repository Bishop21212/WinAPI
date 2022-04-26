//Сделать тоже самое, что с ListBox
//Диалоговое окно с иконокой
//ComboBox
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR* string[] =
{
	//Эти строки добавим в COMBOBOX
	"Первая строка",
	"вторая строка",
	"третья строка",
	"This","is","my","first","List","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//type name(parameters)
//type calling_convention name(parameters)
//type - тип возвращаемого значения
//calling_convention - конвенция вызовов(соглашение о вызове функции)
//__syscall
//__stdcall - WinApi
//__fastcall(x64)
//__cdecl - C/C++
//конвенция вызовов определяет порядок вызова функции:
// - кто очищает стек, вызывающая функция(caller) и вызываемая функция(callee)
// - как читается список передаваемых параметров - слева направоБили справа налево
// - или же параметры передаются через регистры(_fastcall)

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
//HINSTANCE hInstance- ЭКЗЕМПЛЯР ИСПОЛНЯЕМОГО ФАЙЛА(*exe). Это загруженный в память *exe - файд нашей программы
//HINSTANCE hPrevInst - предыдущий экземпляр *exe - файла.Этот параметр использовался в Windows 98,отсавлен для обратной совместимости
//LPSTR lpCmdLine - командная строка с которой была запущена программа.
//LPSTR - LongPointer to string(указатель на строку)
//int nCmdShow - режим отображения окна: свернуто в окно , развернуто на весь экран, свернуто на панель задач

{
	//HWND - Handler to Window(обработчик окна),дескриптор окна(описатель)
	//HWND - это идентификатор окна через которое к нему можно обратиться.
	//HWND - это как имя переменной или функции
	//DialogBoxParam - функция,которая запускает диалоговое окно
	//MAKEINTRESOURCE - функция возвращает по номеру ресурса имя ресурса
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

//HWND - это окно
//UINT uMsg - message.UINT - unsigned int
//wParam, lParam - параметры сообщени,они зависят от того,какое именно uMsg мы посылаем окну 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //это сообщение отправляется в окно при его создании
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hComboBox = GetDlgItem(hwnd, IDC_LIST1);

		//GetDlgItem - возвращает HWND элемента окна по ID ресурса
		for (int i{ 0 }; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hComboBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			//SendMessage отправляет сообщение LB_ADDSTRING - добавляет указанную строку в ListBox
		}
	}
	break;
	case WM_COMMAND://это сообщение обрабатывает нажатие на кнопки, другие элементы интерфейса
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			CHAR sz_message[SIZE]{};//эту строку будем отображать в MessageBox
			HWND hComboBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hComboBox, LB_GETCURSEL, 0, 0);//получаем числовой индекс выделенного элемента ListBox
			SendMessage(hComboBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент № %d со значением \"%s\"", index, sz_buffer);
			//функция sprintf - выполняет форматирование строк
			//sz_message - это буфер, в который сохранится отфоматированная строка
			//вы выбрали ... - это шаблон строки, как она должа выглядеть
			//%d - вставить в строку десятичное уелое число(decimal)
			//%s - вставить в шаблонную строку подстроку
			//Все вставляемые значения перечислены далее в передаваемых параметрах:index,sz_buffer....
			//количество параметров функции sprintf() неограниченно
			//sprintf() - позволяет вставлять в строку какие угодно значения

			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}