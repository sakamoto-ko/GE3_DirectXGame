#pragma once

#include <Windows.h>

#pragma comment(lib, "winmm.lib")

class WinApp
{
public:
	void Initialize();
	bool Update();

	void Finalize();

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND GetHWND() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }

public:
	// ウィンドウサイズ
	static const int window_width = 1280;  // 横幅
	static const int window_height = 720;  // 縦幅

private:
	HWND hwnd;
	WNDCLASSEX w{};
	MSG msg{}; 
};

