//WinAPI
#include <Windows.h>
#include "resource.h"
 
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//#define MSG_BOX


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//INT - тип возвращаемого значения
	//WINAPI - соглашение о вызове функции (Calling convention)
	//Calling convention  определяет, какая функция очищает стек, вызывающая или вызываемая, 
	//а также определяет, как параметры передаются в функцию.
	//для обычных С/С++ приложений, по умолчанию используется конвенция _cdecl,
	//в WinAPI используется конвенция _stdcall
	//caller - вызывающая функция
	//callee - вызываемая функция

	/*
	_________________________________________________________

	hInstance - *.exe - файл программы
	hPrevInst - предыдущий экземпляр программы, использовался ранее для 16-битной Windows, сейчас всегда равен 0
	lpCmdLine - командная строка, которую приложение получает при запуске
				Если это текстовый редактор, то в него можно передать открываемый файл
				Если это браузер - в него можно передать загружаемую страницу, и т.д.
				Командная строка представляет собой массив строк, нулевым элементов которого всегда является имя *.exe - файла
				lp - LongРointer (Венгерская нотация)
	nCmdShow - режим отображения окна при запуске (развернуто на весь экран, свернуто в окно, свернуто на панель задачь и т.д.)
				n - number (Венгерская нотация)
	_________________________________________________________
	*/

#ifdef MSG_BOX
	MessageBox(
		NULL,  //Родительское окно
		"Привет! Это наше первое сообщение",
		"Заголовок окна сообщения",
		MB_YESNOCANCEL | MB_HELP //Набор кнопок
		| MB_ICONASTERISK		//Значок
		| MB_DEFBUTTON3			//Кнопка по умолчанию
		| MB_SYSTEMMODAL);		// WS_EX_TOPMOST - поверх всех окон
	

#endif // MCG_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	// для создания элементов окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
		break;
	case WM_COMMAND:	// обработка команд нажатия кнопок
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)buffer);
		}
			break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:		// закрытие окна
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
