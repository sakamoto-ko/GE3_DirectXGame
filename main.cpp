#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "ImGuiManager.h"

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

    ImGuiManager* imGuiManager = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp->GetHWND(), dxCommon);

    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon);

    Sprite* sprite = new Sprite();
    sprite->Initialize(spriteCommon);

    // ゲームループ
    while (true) {
        if (winApp->Update()) {
            break;
        }
        ImGuiManager::NewFrame();
        imGuiManager->ShowDemo();

        input->Update();

        sprite->Update();

        ImGuiManager::CrateCommand();

        dxCommon->PreDraw();
        spriteCommon->SpritePreDraw();

        sprite->Draw();

        ImGuiManager::CommandExcute(dxCommon->GetCommandList());

        dxCommon->PostDraw();
    }

    //各種解放
    delete sprite;
    delete spriteCommon;

    delete imGuiManager;

    delete input;

    delete dxCommon;

    winApp->Finalize();
    delete winApp;

    return 0;
}
