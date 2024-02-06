#pragma once
#include <Windows.h>

//#include "externals/imgui/imgui.h"
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WinApp
{
public:
	void Initialize();
	void Update();

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND GetHWND() const { return hwnd; }

public:
	// ウィンドウサイズ
	static const int window_width = 1280;  // 横幅
	static const int window_height = 720;  // 縦幅

private:
	HWND hwnd;
};
