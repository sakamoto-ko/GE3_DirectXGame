#pragma once

#include <Windows.h>
#include "externals/imgui/imgui.h"


class WinApp
{
public:
	void Initialize();
	void Update();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	// ウィンドウサイズ
	const int window_width = 1280;  // 横幅
	const int window_height = 720;  // 縦幅

};

