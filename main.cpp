#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    //ポインタ
    WinApp* winApp = nullptr;
    DirectXCommon* dxCommon = nullptr;
    Input* input = nullptr;

    winApp = new WinApp();
    winApp->Initialize();

    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);

    input = new Input();
    input->Initialize(winApp);

    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon);

    Sprite* sprite = new Sprite();
    sprite->Initialize(dxCommon,spriteCommon);

    // ゲームループ
    while (true) {
        if (winApp->Update()) {
            break;
        }

        input->Update();

        dxCommon->PreDraw();

        sprite->Draw();

        dxCommon->PostDraw();
    }

    //各種解放
    delete sprite;
    delete spriteCommon;

    delete input;

    delete dxCommon;

    winApp->Finalize();
    delete winApp;

    return 0;
}
