#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include <vector>

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

    std::vector<Sprite*> sprite;
    for (int i = 0; i < 5; ++i) {
        Sprite* tmp = new Sprite();
        tmp->Initialize(spriteCommon);
        tmp->SetPosition(DirectX::XMFLOAT2((float)i + 1, 0.0f));
        sprite.push_back(tmp);
    }

    // ゲームループ
    while (true) {
        if (winApp->Update()) {
            break;
        }
        ImGuiManager::NewFrame();
        imGuiManager->ShowDemo();

        input->Update();

      /*DirectX::XMFLOAT2 pos = sprite->GetPosition();
        pos.x += 0.01;
        sprite->SetPosition(pos);

        float rot = sprite->GetRotation();
        rot += 0.01f;
        sprite->SetRotation(rot);

        DirectX::XMFLOAT2 scale = sprite->GetScale();
        scale.x += 0.01f;
        sprite->SetScale(scale);

        DirectX::XMFLOAT4 color = sprite->GetColor();
        color.x -= 0.01f;
        if (color.x < 0.0f) {
            color.x = 1.0f;
        }
        sprite->SetColor(color);*/

        for (int i = 0; i < 5; ++i) {
            sprite[i]->Update();
        }

        ImGuiManager::CrateCommand();

        dxCommon->PreDraw();
        spriteCommon->SpritePreDraw();

        for (int i = 0; i < 5; ++i) {
            sprite[i]->Draw();
        }

        ImGuiManager::CommandExcute(dxCommon->GetCommandList());

        dxCommon->PostDraw();
    }

    //各種解放
    for (int i = 0; i < 5; ++i) {
        delete sprite[i];
    }
    delete spriteCommon;

    delete imGuiManager;

    delete input;

    delete dxCommon;

    winApp->Finalize();
    delete winApp;

    return 0;
}
