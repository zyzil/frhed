/*
zhed - Free hex editor based on Frhed
Copyright (C) 2000 Raihan Kibria
Copyright (C) 2016 Kevin Mullins

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

Last change: 2013-02-24 by Jochen Neubeck
*/
/** 
 * @file  main.cpp
 *
 * @brief WinMain of zhed.
 *
 */
//============================================================================================
// zhed - Free hex editor based on Frhed

#include "precomp.h"
#include "resource.h"
#include "hexwnd.h"
#include "toolbar.h"

static const wchar_t szMainClass[] = L"zhed wndclass";
static const wchar_t szHexClass[] = L"hexeditctl";

HINSTANCE hMainInstance;

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HexWndProc(HWND, UINT, WPARAM, LPARAM);

static BOOL CALLBACK WndEnumProcCountInstances(HWND hwnd, LPARAM lParam)
{
	TCHAR buf[64];
	if (GetClassName(hwnd, buf, RTL_NUMBER_OF(buf)))
		if (StrCmp(buf, szMainClass) == 0)
			++*reinterpret_cast<int *>(lParam);
	return TRUE;
}

static HWND hwndMain = nullptr;
static HWND hwndHex = nullptr;
static HWND hwndToolBar = nullptr;
static HWND hwndStatusBar = nullptr;
static HexEditorWindow *pHexWnd = nullptr;
static BOOL bIsNT = FALSE;

/**
 * @brief The application starting point.
 */

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR szCmdLine, int)
{
	int iSelStart = 0;
	int iSelLength = 0;
	int iSelEnd = 0;
	int iCmd = 0;
	int iInstCount = 0;

	EnumWindows(WndEnumProcCountInstances, reinterpret_cast<LPARAM>(&iInstCount));

	if (*szCmdLine != '\0')
	{
		bool opting = false;
		bool quoting = false;
		// Command line not empty: open a file on startup.
		LPWSTR p = szCmdLine;
		LPWSTR q = szCmdLine;
		while ((*p = *q) != '\0')
		{
			switch (*q++)
			{
			case '/': // switch coming up
				opting = true;
				switch (*q)
				{
				case 'S': // Start offset
				case 's':
					StrToIntExW(++q, STIF_SUPPORT_HEX, &iSelStart);
					break;
				case 'L': // Length of selection
				case 'l':
					StrToIntExW(++q, STIF_SUPPORT_HEX, &iSelLength);
					break;
				case 'E': // End of selection
				case 'e':
					StrToIntExW(++q, STIF_SUPPORT_HEX, &iSelEnd);
					break;
				case 'I':
				case 'i':
					StrToIntExW(++q, STIF_SUPPORT_HEX, &iInstCount);
					break;
				case 'C':
				case 'c':
					StrToIntExW(++q, STIF_SUPPORT_HEX, &iCmd);
					break;
				}
				break;
			case '"':
				opting = false;
				quoting = !quoting;
				break;
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				opting = false;
				if (!quoting)
					break;
				// fall through
			default:
				if (opting)
					break;
				++p;
				break;
			}
		}
		if (iSelLength)
			iSelEnd = iSelStart + iSelLength - 1;
	}

	CoInitialize(nullptr);
	InitCommonControls();

	hMainInstance = hInstance;
	WNDCLASSEX editwndclass;
	ZeroMemory(&editwndclass, sizeof editwndclass);
	editwndclass.cbSize = sizeof editwndclass;
	editwndclass.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
	editwndclass.lpfnWndProc = HexWndProc;
	editwndclass.hInstance = hInstance;
	editwndclass.hCursor = 0;
	editwndclass.lpszClassName = szHexClass;
	RegisterClassEx(&editwndclass);
	HexEditorWindow::LoadStringTable();

	MSG msg;

	WNDCLASS wndclass;
	SecureZeroMemory(&wndclass, sizeof wndclass);

	//Register the main window class
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ZHED));
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hInstance = hMainInstance;
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
	wndclass.lpszClassName = szMainClass;

	RegisterClass(&wndclass);

	CreateWindow(szMainClass, nullptr, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hMainInstance, NULL);

	if (!pHexWnd)
	{
		MessageBox(nullptr, _T("Unable to create the hexeditctl control"), nullptr, MB_ICONSTOP);
		return 3;
	}

	// Read in the last saved preferences.
	pHexWnd->iInstCount = iInstCount;
	pHexWnd->read_ini_data();

	// The if prevents the window from being resized to 0x0 it becomes just a title bar
	if (pHexWnd->iWindowX != CW_USEDEFAULT)
	{
		// Prevent window creep when Taskbar is at top or left of screen
		WINDOWPLACEMENT wp;
		wp.length = sizeof wp;
		GetWindowPlacement(hwndMain, &wp);
		wp.showCmd = pHexWnd->iWindowShowCmd;
		wp.rcNormalPosition.left = pHexWnd->iWindowX;
		wp.rcNormalPosition.top = pHexWnd->iWindowY;
		wp.rcNormalPosition.right = pHexWnd->iWindowWidth + pHexWnd->iWindowX;
		wp.rcNormalPosition.bottom = pHexWnd->iWindowHeight + pHexWnd->iWindowY;
		SetWindowPlacement(hwndMain, &wp);
	}
	ShowWindow(hwndMain, pHexWnd->iWindowShowCmd);
	UpdateWindow(hwndMain);

	if (*szCmdLine != '\0')
	{
		pHexWnd->open_file(szCmdLine);
		if (iSelEnd != 0)
			pHexWnd->CMD_setselection(iSelStart, iSelEnd);
	}

	if (iCmd != 0)
		PostMessage(hwndMain, WM_COMMAND, iCmd, 0);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!pHexWnd || !pHexWnd->translate_accelerator(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	HexEditorWindow::FreeStringTable();

#ifdef _DEBUG
	// The System32 build cannot safely FreeLibrary(hMainInstance) because
	// zhed.exe and hexeditctl.dll share the same atexit list.
	_CrtDumpMemoryLeaks();
#endif
	CoUninitialize();
	return static_cast<int>(msg.wParam);
}

#ifndef _DEBUG
void WINAPI wWinMainCRTStartup()
{
	HINSTANCE hIconInstance = GetModuleHandle(NULL);
	LPWSTR szExePath = GetCommandLineW();
	LPWSTR szCmdLine = PathGetArgsW(szExePath);
	ExitProcess(wWinMain(hIconInstance, NULL, szCmdLine, SW_SHOWNORMAL));
}
#endif

// The hex window procedure.
LRESULT CALLBACK HexWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (iMsg == WM_NCCREATE)
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(new HexEditorWindow));
	HexEditorWindow *pHexWnd = reinterpret_cast<HexEditorWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	LRESULT lResult = pHexWnd->OnWndMsg(hwnd, iMsg, wParam, lParam);
	if (iMsg == WM_NCDESTROY)
		delete pHexWnd;
	return lResult;
}

//--------------------------------------------------------------------------------------------
// The main window procedure.
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		hwndMain = hwnd;
		hwndHex = CreateWindowEx(WS_EX_CLIENTEDGE, szHexClass, nullptr,
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
			10, 10, 100, 100, hwnd, nullptr, hMainInstance, nullptr);
		pHexWnd = reinterpret_cast<HexEditorWindow *>(GetWindowLongPtr(hwndHex, GWLP_USERDATA));
		if (!pHexWnd)
			return -1;
		hwndToolBar = CreateTBar(hwndHex, hMainInstance);
		SetParent(hwndToolBar, hwnd);
		hwndStatusBar = CreateStatusWindow(
			CCS_BOTTOM | WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, nullptr, hwnd, 2);
		SetParent(hwndStatusBar, hwndHex);
		SendMessage(hwndHex, WM_PARENTNOTIFY, MAKEWPARAM(WM_CREATE, 2), reinterpret_cast<LPARAM>(hwndStatusBar));
		SetParent(hwndStatusBar, hwnd);
		pHexWnd->hwndMain = hwnd;
		pHexWnd->bSaveIni = TRUE;
		pHexWnd->bCenterCaret = TRUE;
		pHexWnd->resize_window();
		return 0;
	case WM_COMMAND:
		// Exit command must be handled in zhed executable,
		// not in hexeditctl dll.
		if (LOWORD(wParam) == IDM_EXIT)
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		else
			pHexWnd->command(LOWORD(wParam));
		break;
	case WM_NOTIFY:
		return SendMessage(hwndHex, WM_NOTIFY, wParam, lParam);
	case WM_SETFOCUS:
		SetFocus(hwndHex);
		break;
	case WM_CLOSE: 
		if (!pHexWnd->close())
			return 0;
		break;
	case WM_INITMENUPOPUP:
		pHexWnd->initmenupopup(wParam, lParam);
		break;
	case WM_SIZE:
		{
			int cx = GET_X_LPARAM(lParam);
			int cy = GET_Y_LPARAM(lParam);
			RECT rect;
			// Adjust tool bar width so buttons will wrap accordingly.
			MoveWindow(hwndToolBar, 0, 0, cx, 0, TRUE);
			// Set tool bar height to bottom of last button plus some padding.
			if (int n = static_cast<int>(SendMessage(hwndToolBar, TB_BUTTONCOUNT, 0, 0)))
			{
				SendMessage(hwndToolBar, TB_GETITEMRECT, n - 1, reinterpret_cast<LPARAM>(&rect));
				MoveWindow(hwndToolBar, 0, 0, cx, rect.bottom + 2, TRUE);
			}
			GetWindowRect(hwndToolBar, &rect);
			int cyToolBar = rect.bottom - rect.top;
			// Moves status bar back to the bottom
			SendMessage(hwndStatusBar, WM_SIZE, 0, 0);
			GetWindowRect(hwndStatusBar, &rect);
			int cyStatusBar = rect.bottom - rect.top;
			//--------------------------------------------
			// Set statusbar divisions.
			// Calculate the right edge coordinate for each part
			int parts[] = { MulDiv(cx, 4, 6), MulDiv(cx, 5, 6), cx };
			SendMessage(hwndStatusBar, SB_SETPARTS, RTL_NUMBER_OF(parts), reinterpret_cast<LPARAM>(parts));
			MoveWindow(hwndHex, 0, cyToolBar, cx, cy - cyToolBar - cyStatusBar, TRUE);
		}
		break;
	case WM_DESTROY:
		if (pHexWnd)
		{
			// Store window position for next startup.
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hwnd, &wndpl);
			pHexWnd->iWindowShowCmd = wndpl.showCmd;
			pHexWnd->iWindowX = wndpl.rcNormalPosition.left;
			pHexWnd->iWindowY = wndpl.rcNormalPosition.top;
			pHexWnd->iWindowWidth = wndpl.rcNormalPosition.right - pHexWnd->iWindowX;
			pHexWnd->iWindowHeight = wndpl.rcNormalPosition.bottom - pHexWnd->iWindowY;
			pHexWnd->save_ini_data();
			pHexWnd = nullptr;
		}
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam );
}
