#include <windows.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE hInst;
HWND g_hEdit;
HWND g_hButton;
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "SPROGLAB6";

// Глобальні змінні для збереження значень флагів
DWORD flags_before;
DWORD flags_after;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd) {
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

char* intToBinaryString(int num, char* binaryString)
{
	int flags_before = 0;
	int beforeCF = 0;
	int beforePF = 0;
	int beforeAF = 0;
	int beforeZF = 0;
	int beforeSF = 0;
	int beforeOF = 0;

	int flags_after = 0;
	int afterCF = 0;
	int afterPF = 0;
	int afterAF = 0;
	int afterZF = 0;
	int afterSF = 0;
	int afterOF = 0;

	__asm {
		pushfd // Зберігаємо стан регістрів флагів на стеку
		pop flags_before // Зберігаємо значення флагів у змінну flags_before
		// Визначаємо значення флагів до виконання операції
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 0 // Зсуваємо значення флагів на 0 біт
		and eax, 1 // Перевіряємо значення флагу CF
		mov beforeCF, eax // Зберігаємо значення флагу CF у змінну beforeCF
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 2 // Зсуваємо значення флагів на 2 біти
		and eax, 1 // Перевіряємо значення флагу PF
		mov beforePF, eax // Зберігаємо значення флагу PF у змінну beforePF
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 4 // Зсуваємо значення флагів на 4 біти
		and eax, 1 // Перевіряємо значення флагу AF
		mov beforeAF, eax // Зберігаємо значення флагу AF у змінну beforeAF
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 6 // Зсуваємо значення флагів на 6 біт
		and eax, 1 // Перевіряємо значення флагу ZF
		mov beforeZF, eax // Зберігаємо значення флагу ZF у змінну beforeZF
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 7 // Зсуваємо значення флагів на 7 біт
		and eax, 1 // Перевіряємо значення флагу SF
		mov beforeSF, eax // Зберігаємо значення флагу SF у змінну beforeSF
		mov eax, flags_before // Переміщаємо значення флагів у регістр eax
		shr eax, 11 // Зсуваємо значення флагів на 11 біт
		and eax, 1 // Перевіряємо значення флагу OF
		mov beforeOF, eax // Зберігаємо значення флагу OF у змінну beforeOF
		mov eax, num // Move the number to register eax
		mov edi, binaryString // Move the address of binaryString to edi
		mov byte ptr[edi + 32], 0 // Null-terminate the string
		mov ecx, 32 // Counter for 32 bits
		loop_start:
		shr eax, 1 // Shift right by 1 (to get the least significant bit)
			jnc zero_bit // If CF = 0, jump to zero_bit
			mov byte ptr[edi + 31], '1' // Store '1' in binaryString
			jmp next_bit // Jump to next_bit
			zero_bit :
		mov byte ptr[edi + 31], '0' // Store '0' in binaryString
			next_bit :
			dec edi // Move to the next byte in binaryString
			loop loop_start // Repeat loop until ecx becomes 0
			pushfd // Зберігаємо стан регістрів флагів на стеку
			pop flags_after // Зберігаємо значення флагів у змінну flags_before
			// Визначаємо значення флагів після виконання операції
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 0 // Зсуваємо значення флагів на 0 біт
			and eax, 1 // Перевіряємо значення флагу CF
			mov afterCF, eax // Зберігаємо значення флагу CF у змінну afterCF
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 2 // Зсуваємо значення флагів на 2 біти
			and eax, 1 // Перевіряємо значення флагу PF
			mov afterPF, eax // Зберігаємо значення флагу PF у змінну afterPF
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 4 // Зсуваємо значення флагів на 4 біти
			and eax, 1 // Перевіряємо значення флагу AF
			mov afterAF, eax // Зберігаємо значення флагу AF у змінну afterAF
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 6 // Зсуваємо значення флагів на 6 біт
			and eax, 1 // Перевіряємо значення флагу ZF
			mov afterZF, eax // Зберігаємо значення флагу ZF у змінну afterZF
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 7 // Зсуваємо значення флагів на 7 біт
			and eax, 1 // Перевіряємо значення флагу SF
			mov afterSF, eax // Зберігаємо значення флагу SF у змінну afterSF
			mov eax, flags_after // Переміщаємо значення флагів у регістр eax
			shr eax, 11 // Зсуваємо значення флагів на 11 біт
			and eax, 1 // Перевіряємо значення флагу OF
			mov afterOF, eax // Зберігаємо значення флагу OF у змінну afterOF
	}
	// Виводимо значення флагів до та після виконання операції
	char flags[100];
	sprintf_s(flags, "CF=%d PF=%d AF=%d ZF=%d SF=%d OF=%d", beforeCF, beforePF, beforeAF, beforeZF, beforeSF, beforeOF);
	TextOut(GetDC(g_hEdit), 5, 130, flags, strlen(flags));
	sprintf_s(flags, "CF=%d PF=%d AF=%d ZF=%d SF=%d OF=%d", afterCF, afterPF, afterAF, afterZF, afterSF, afterOF);
	TextOut(GetDC(g_hEdit), 5, 150, flags, strlen(flags));
	// Виводимо значення флагів до та після виконання операції
	// Виводимо значення флагів до та після виконання операції
	return binaryString;
}

void ConvertAndDisplayBinary() {
	char inputText[100];
	GetWindowText(g_hEdit, inputText, 100);

	int num = atoi(inputText);
	// Convert the number to binary string
	char binaryString[33];

	// Display the result in a message box
	TextOut(GetDC(g_hEdit), 5, 100, intToBinaryString(num, binaryString), 32);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message) {
	case WM_CREATE: {
		// Create a text edit control
		g_hEdit = CreateWindow(
			"EDIT",
			"",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			5,
			30,
			200,
			25,
			hWnd,
			NULL,
			hInst,
			NULL
		);

		// Create a button
		g_hButton = CreateWindow(
			"BUTTON",
			"Convert to Binary",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			60,
			200,
			25,
			hWnd,
			(HMENU)ID_B_BUTTON,
			hInst,
			NULL
		);

		break;
	}

	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_B_BUTTON) {
			ConvertAndDisplayBinary();
		}
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		char text[100] = "Enter number";
		int len = strlen(text);
		TextOut(hdc, 55, 5, text, len);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	default: {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}