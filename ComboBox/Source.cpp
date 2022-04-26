//������� ���� �����, ��� � ListBox
//���������� ���� � ��������
//ComboBox
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR* string[] =
{
	//��� ������ ������� � COMBOBOX
	"������ ������",
	"������ ������",
	"������ ������",
	"This","is","my","first","List","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//type name(parameters)
//type calling_convention name(parameters)
//type - ��� ������������� ��������
//calling_convention - ��������� �������(���������� � ������ �������)
//__syscall
//__stdcall - WinApi
//__fastcall(x64)
//__cdecl - C/C++
//��������� ������� ���������� ������� ������ �������:
// - ��� ������� ����, ���������� �������(caller) � ���������� �������(callee)
// - ��� �������� ������ ������������ ���������� - ����� ����������� ������ ������
// - ��� �� ��������� ���������� ����� ��������(_fastcall)

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
//HINSTANCE hInstance- ��������� ������������ �����(*exe). ��� ����������� � ������ *exe - ���� ����� ���������
//HINSTANCE hPrevInst - ���������� ��������� *exe - �����.���� �������� ������������� � Windows 98,�������� ��� �������� �������������
//LPSTR lpCmdLine - ��������� ������ � ������� ���� �������� ���������.
//LPSTR - LongPointer to string(��������� �� ������)
//int nCmdShow - ����� ����������� ����: �������� � ���� , ���������� �� ���� �����, �������� �� ������ �����

{
	//HWND - Handler to Window(���������� ����),���������� ����(���������)
	//HWND - ��� ������������� ���� ����� ������� � ���� ����� ����������.
	//HWND - ��� ��� ��� ���������� ��� �������
	//DialogBoxParam - �������,������� ��������� ���������� ����
	//MAKEINTRESOURCE - ������� ���������� �� ������ ������� ��� �������
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

//HWND - ��� ����
//UINT uMsg - message.UINT - unsigned int
//wParam, lParam - ��������� ��������,��� ������� �� ����,����� ������ uMsg �� �������� ���� 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //��� ��������� ������������ � ���� ��� ��� ��������
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hComboBox = GetDlgItem(hwnd, IDC_LIST1);

		//GetDlgItem - ���������� HWND �������� ���� �� ID �������
		for (int i{ 0 }; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hComboBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			//SendMessage ���������� ��������� LB_ADDSTRING - ��������� ��������� ������ � ListBox
		}
	}
	break;
	case WM_COMMAND://��� ��������� ������������ ������� �� ������, ������ �������� ����������
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			CHAR sz_message[SIZE]{};//��� ������ ����� ���������� � MessageBox
			HWND hComboBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hComboBox, LB_GETCURSEL, 0, 0);//�������� �������� ������ ����������� �������� ListBox
			SendMessage(hComboBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "�� ������� ������� � %d �� ��������� \"%s\"", index, sz_buffer);
			//������� sprintf - ��������� �������������� �����
			//sz_message - ��� �����, � ������� ���������� ���������������� ������
			//�� ������� ... - ��� ������ ������, ��� ��� ����� ���������
			//%d - �������� � ������ ���������� ����� �����(decimal)
			//%s - �������� � ��������� ������ ���������
			//��� ����������� �������� ����������� ����� � ������������ ����������:index,sz_buffer....
			//���������� ���������� ������� sprintf() �������������
			//sprintf() - ��������� ��������� � ������ ����� ������ ��������

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