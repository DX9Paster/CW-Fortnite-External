#pragma once

//winapi
#include <Windows.h>
#include <iostream>
#include <random>
#include <memory>
#include <array>
#include <psapi.h>
#include <string_view>
#include <tchar.h>
#include <iterator>
#include <cstdint>
#include <string>
#include <tlhelp32.h>
#include <random>
#include <thread>
#include <dwmapi.h>
#include <functional>
#include <mutex>

//etc
#include <options.h>

//ImGui
#include <dependencies/ImGui/imgui.h>
#include <dependencies/ImGui/imgui_impl_win32.h>
#include <dependencies/ImGui/imgui_impl_dx9.h>

//driver
#include <dependencies/Controller/driver.h>

//dx
#include <d3d9.h>

//lib
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Dwmapi.lib")

inline LPCSTR TargetProcess = "FortniteClient-Win64-Shipping.exe";//FortniteClient-Win64-Shipping
//inline LPCSTR TargetProcess = "notepad.exe";//for menu and stuff
bool ShowMenu = true;
bool ImGui_Initialised = false;
bool CreateConsole = true;

namespace Process {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	int WindowLeft;
	int WindowRight;
	int WindowTop;
	int WindowBottom;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}

namespace OverlayWindow {
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}

namespace DirectX9Interface {
	IDirect3D9Ex* Direct3D9 = NULL;
	IDirect3DDevice9Ex* pDevice = NULL;
	D3DPRESENT_PARAMETERS pParams = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}

DWORD GetProcessId(LPCSTR ProcessName) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) {
		do {
			if (!lstrcmpi(pt.szExeFile, ProcessName)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap);
	return 0;
}

void SetMouseAbsPosition(DWORD x, DWORD y)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = x;
	input.mi.dy = y;
	SendInput(1, &input, sizeof(input));
}

inline void aimat(float x, float y)
{
	float ScreenCenterX = (Process::WindowWidth / 2);
	float ScreenCenterY = (Process::WindowHeight / 2);
	int AimSpeed = options::mousesmoothness;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0) { if (x > ScreenCenterX) { TargetX = -(ScreenCenterX - x); TargetX /= AimSpeed; if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0; }
		if (x < ScreenCenterX) { TargetX = x - ScreenCenterX; TargetX /= AimSpeed; if (TargetX + ScreenCenterX < 0) TargetX = 0; } }

	if (y != 0) { if (y > ScreenCenterY) { TargetY = -(ScreenCenterY - y); TargetY /= AimSpeed; if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0; }
	if (y < ScreenCenterY) { TargetY = y - ScreenCenterY; TargetY /= AimSpeed; if (TargetY + ScreenCenterY < 0) TargetY = 0; } }

	//mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
	SetMouseAbsPosition(TargetX, TargetY);

	return;
}

std::string RandomString(int len) {
	srand(time(NULL));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}