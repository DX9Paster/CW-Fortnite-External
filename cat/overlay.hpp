#pragma once
#include "common.h"

namespace overlay
{
	void Render();
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

__forceinline std::string string_To_UTF8(const std::string& str) {
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}

static auto DrawCircleFilled(int x, int y, int radius, RGBA* color) -> void
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

__forceinline void DrawFilledRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}
__forceinline void DrawRect(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

__forceinline void DrawRoundedRect(int x, int y, int w, int h, ImU32& color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 0, 0, 3);
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::GetColorU32(color), 0, 0, thickness);
}
__forceinline void FilledRect(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 150)), 0, 0);
}

__forceinline void DrawCornerBox(int x, int y, int w, int h, int borderPx, ImU32 color) {
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x, y, borderPx, h / 3, color);
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
}


__forceinline bool DirectXInit() {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9Interface::Direct3D9))) {
		return false;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = OverlayWindow::Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = Process::WindowWidth;
	Params.BackBufferHeight = Process::WindowHeight;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	if (FAILED(DirectX9Interface::Direct3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, OverlayWindow::Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9Interface::pDevice))) {
		DirectX9Interface::Direct3D9->Release();
		return false;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 14);

	ImGui_ImplWin32_Init(OverlayWindow::Hwnd);
	ImGui_ImplDX9_Init(DirectX9Interface::pDevice);
	DirectX9Interface::Direct3D9->Release();
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message) {
	case WM_DESTROY:
		if (DirectX9Interface::pDevice != NULL) {
			DirectX9Interface::pDevice->EndScene();
			DirectX9Interface::pDevice->Release();
		}
		if (DirectX9Interface::Direct3D9 != NULL) {
			DirectX9Interface::Direct3D9->Release();
		}
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (DirectX9Interface::pDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9Interface::pParams.BackBufferWidth = LOWORD(lParam);
			DirectX9Interface::pParams.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

__forceinline void SetupWindow() {
	OverlayWindow::WindowClass = {
		sizeof(WNDCLASSEX), 0, WinProc, 0, 0, nullptr, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, OverlayWindow::Name, LoadIcon(nullptr, IDI_APPLICATION)
	};

	RegisterClassEx(&OverlayWindow::WindowClass);
	if (Process::Hwnd) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect(Process::Hwnd, &TempRect);
		ClientToScreen(Process::Hwnd, &TempPoint);
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		Process::WindowWidth = TempRect.right;
		Process::WindowHeight = TempRect.bottom;
	}

	OverlayWindow::Hwnd = CreateWindowEx(NULL, OverlayWindow::Name, OverlayWindow::Name, WS_POPUP | WS_VISIBLE, Process::WindowLeft, Process::WindowTop, Process::WindowWidth, Process::WindowHeight, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(OverlayWindow::Hwnd, &DirectX9Interface::Margin);
	SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	ShowWindow(OverlayWindow::Hwnd, SW_SHOW);
	UpdateWindow(OverlayWindow::Hwnd);
}

DWORD WINAPI ProcessCheck(LPVOID lpParameter) {
	while (true) {
		if (Process::Hwnd != NULL) {
			if (GetProcessId(TargetProcess) == 0) {
				exit(0);
			}
		}
	}
}

__forceinline void InitOverlay()
{
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetProcessId(TargetProcess) == ForegroundWindowProcessID) {
			Process::ID = GetCurrentProcessId();
			Process::Handle = GetCurrentProcess();
			Process::Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process::Hwnd, &TempRect);
			Process::WindowWidth = TempRect.right - TempRect.left;
			Process::WindowHeight = TempRect.bottom - TempRect.top;
			Process::WindowLeft = TempRect.left;
			Process::WindowRight = TempRect.right;
			Process::WindowTop = TempRect.top;
			Process::WindowBottom = TempRect.bottom;

			char TempTitle[MAX_PATH];
			GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
			Process::Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
			Process::ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
			Process::Path = TempPath;

			WindowFocus = true;
		}
	}

	OverlayWindow::Name = RandomString(10).c_str();
	SetupWindow();
	DirectXInit();
	CreateThread(0, 0, ProcessCheck, 0, 0, 0);

	while (TRUE) {
		static RECT OldRect;
		ZeroMemory(&DirectX9Interface::Message, sizeof(MSG));

		while (DirectX9Interface::Message.message != WM_QUIT) {
			if (PeekMessage(&DirectX9Interface::Message, OverlayWindow::Hwnd, 0, 0, PM_REMOVE)) {
				TranslateMessage(&DirectX9Interface::Message);
				DispatchMessage(&DirectX9Interface::Message);
			}
			HWND ForegroundWindow = GetForegroundWindow();
			if (ForegroundWindow == Process::Hwnd) {
				HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
				SetWindowPos(OverlayWindow::Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}

			RECT TempRect;
			POINT TempPoint;
			ZeroMemory(&TempRect, sizeof(RECT));
			ZeroMemory(&TempPoint, sizeof(POINT));

			GetClientRect(Process::Hwnd, &TempRect);
			ClientToScreen(Process::Hwnd, &TempPoint);

			TempRect.left = TempPoint.x;
			TempRect.top = TempPoint.y;
			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = Process::Hwnd;

			POINT TempPoint2;
			GetCursorPos(&TempPoint2);
			io.MousePos.x = TempPoint2.x - TempPoint.x;
			io.MousePos.y = TempPoint2.y - TempPoint.y;

			if (GetAsyncKeyState(0x1)) {
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].x = io.MousePos.y;
			}
			else {
				io.MouseDown[0] = false;
			}

			if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
				OldRect = TempRect;
				Process::WindowWidth = TempRect.right;
				Process::WindowHeight = TempRect.bottom;
				DirectX9Interface::pParams.BackBufferWidth = Process::WindowWidth;
				DirectX9Interface::pParams.BackBufferHeight = Process::WindowHeight;
				SetWindowPos(OverlayWindow::Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Process::WindowWidth, Process::WindowHeight, SWP_NOREDRAW);
				DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			}
			if (GetAsyncKeyState(VK_INSERT) & 1) ShowMenu = !ShowMenu;
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::GetIO().MouseDrawCursor = ShowMenu;

			overlay::Render();
			ImGui::EndFrame();

			DirectX9Interface::pDevice->SetRenderState(D3DRS_ZENABLE, false);
			DirectX9Interface::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			DirectX9Interface::pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

			DirectX9Interface::pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
			if (DirectX9Interface::pDevice->BeginScene() >= 0) {
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				DirectX9Interface::pDevice->EndScene();
			}

			HRESULT result = DirectX9Interface::pDevice->Present(NULL, NULL, NULL, NULL);
			if (result == D3DERR_DEVICELOST && DirectX9Interface::pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
				ImGui_ImplDX9_InvalidateDeviceObjects();
				DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		if (DirectX9Interface::pDevice != NULL) {
			DirectX9Interface::pDevice->EndScene();
			DirectX9Interface::pDevice->Release();
		}
		if (DirectX9Interface::Direct3D9 != NULL) {
			DirectX9Interface::Direct3D9->Release();
		}
		DestroyWindow(OverlayWindow::Hwnd);
		UnregisterClass(OverlayWindow::WindowClass.lpszClassName, OverlayWindow::WindowClass.hInstance);
	}
}

struct {
	float titley = 4;
	float titlex = 6;
	float checkboxX = 80;
	float checkboxY = 10;
}MenuPos;

__forceinline void Spacing() {
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + MenuPos.checkboxY);

}
__forceinline void SpacingRight() {
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + MenuPos.checkboxX);
}
