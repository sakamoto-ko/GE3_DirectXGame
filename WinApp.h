#include <Windows.h>
#pragma once

class WinApp
{
public:
	void Initialize();
	void Update();

	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	// ウィンドウサイズ
	const int window_width = 1280;  // 横幅
	const int window_height = 720;  // 縦幅

};

