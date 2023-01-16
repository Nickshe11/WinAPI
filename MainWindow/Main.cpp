#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

CONST CHAR gsz_MY_WINDOW_CLASS[] = "MyWindowClass";
CONST CHAR gsz_WINDOW_NAME[] = "My First Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна: 
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, "Envelope.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "Globe.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = (HICON)LoadCursorFromFile("StarCraftCursor.ani");
	//wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = gsz_MY_WINDOW_CLASS;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	//2) Создание окна:

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * .75;
	int window_height = screen_height * .75;
	int start_x = (screen_width - screen_width * .75) / 2;
	int start_y = screen_height/8;

	HWND hwnd = CreateWindowEx
	(
		NULL, //ExStyle
		gsz_MY_WINDOW_CLASS, // class name
		gsz_WINDOW_NAME, // Window name
		WS_OVERLAPPEDWINDOW,
		start_x, start_y, //Начальная позиция окна
		window_width, window_height, //Размер окна
		NULL, //HWND родительского окна. У главного окна нет родительского окна
		NULL, //Menu Отсутствует
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow); //Заает реим отображения окна (свернуто в окно, развернуто на весь экран, свернуто на панель задач и тд)
	UpdateWindow(hwnd); // Прорисовывает содержимое окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:break;
	case WM_COMMAND:break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		sprintf(sz_buffer, "%s, Size: %i:%i, Position %i:%i", gsz_WINDOW_NAME,
			rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE:
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Вопрос на миллион долларов", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:	
			MessageBox(hwnd, "Лучше бы двери закрыли)", "Полезная инфа", MB_OK|MB_ICONINFORMATION);
			DestroyWindow(hwnd); 
			break;
		}
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
