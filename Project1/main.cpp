#include<Windows.h>
#include"resource.h"
#include<winapifamily.h>

CHAR sz_login_invitation[] = "¬ведите логин";
CHAR sz_password_invitation[] = "¬ведите пароль";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//запускает окно и обрабатывает его команды

	
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(NULL, "HelloWorld", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP
	 | MB_DEFBUTTON4 | MB_SYSTEMMODAL | MB_SETFOREGROUND);*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)//распередел€ет сообщени€
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//получаем ID текстого пол€ по имени ресурса
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//при выполении различных действий над каким_либо из элементов интерфейса 
			//этот элемент интерфейса (окно) получает уведомлени€. ”ведомлени€,это самые обычные сообщени€
			//Ќапример, когда мы становимс€ в текстовое поле, тоо это текстовое поле получает уведомлени€
			//когда мы "уходим" из текстого пол€, то оно получает уведомлени€ EN_KILLFOCUS
			// фокус  - часть окна, котора€ принимает команды с клавиатуры
			/*CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};*/
			//HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(sz_buffer, sz_login_invitation) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)" "); break;
			case EN_KILLFOCUS:
				if (strlen(sz_buffer) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
				break;

			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			//CONST INT SIZE = 256;// размер буфер 
			//CHAR sz_buffer[SIZE]{};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//получаем ID текстого пол€ по имени ресурса
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//копируем текст из текстого пол€ password в sz_buffer
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		case IDC_BUTTON_SET_TITLE:
		{
			//CONST INT SIZE = 256;
			//CHAR sz_buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//SendMessage(FindWindow(NULL,"WinAPI - Microsoft Visual Studio"),WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "Ѕыла нажата кнопка ќ ", "Info", MB_OK | MB_ICONWARNING); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}