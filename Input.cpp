#include "Input.h"

#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//初期化
void Input::Initialize(HINSTANCE hInstance, HWND hwnd) {

    HRESULT result;

    //前回のキー入力を保存
    memcpy(keyPre, key, sizeof(key));

    // DirectInputのインスタンス生成
    result = DirectInput8Create(
        hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイスの生成
    result = dInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));
    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // 排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(
        hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

//更新
void Input::Update() {

    // キーボード情報の取得開始
    keyboard->Acquire();
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber) {

    //指定キーを押していればtrueを返す
    if (key[keyNumber]) {
        return true;
    }
    //そうでなければfalseを返す
    return false;
}

bool Input::TriggerKey(BYTE keyNumber) {

    //指定キーをトリガーしていればtrueを返す
    if (key[keyNumber] &&
        keyPre[keyNumber] != 1) {
        return true;
    }
    //そうでなければfalseを返す
    return false;
}