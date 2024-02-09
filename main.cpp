#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
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

	TextureManager::GetInstance()->Initialize(dxCommon);
	TextureManager::GetInstance()->LoadTexture(L"Resources/mario.jpg");
	TextureManager::GetInstance()->LoadTexture(L"Resources/reimu.png");

	std::vector<Sprite*> sprite;
	for (int i = 0; i < 3; ++i) {
		Sprite* tmp = new Sprite();
		if (i % 2 == 0) { tmp->Initialize(spriteCommon, L"Resources/mario.jpg"); }
		else if (i % 2 == 1) { tmp->Initialize(spriteCommon, L"Resources/reimu.png"); }
		tmp->SetPosition(DirectX::XMFLOAT2((float)i * 120 + 256.0f, 256.0f));
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

		for (int i = 0; i < 3; ++i) {
			DirectX::XMFLOAT2 pos = sprite[i]->GetPosition();
			pos.x += 0.05f;
			sprite[i]->SetPosition(pos);

			float rot = sprite[i]->GetRotation();
			rot += 0.01f;
			sprite[i]->SetRotation(rot);

			DirectX::XMFLOAT2 scale = sprite[i]->GetScale();
			scale.x += 0.01f;
			sprite[i]->SetScale(scale);

			DirectX::XMFLOAT4 color = sprite[i]->GetColor();
			color.x -= 0.01f;
			if (color.x < 0.0f) {
				color.x = 1.0f;
			}
			sprite[i]->SetColor(color);

			sprite[i]->SetFlipX(true);
			sprite[i]->SetFlipY(true);

			sprite[i]->Update();
		}

		ImGuiManager::CrateCommand();

		dxCommon->PreDraw();
		spriteCommon->SpritePreDraw();

		for (int i = 0; i < 3; ++i) {
			sprite[i]->Draw();
		}

		ImGuiManager::CommandExcute(dxCommon->GetCommandList());

		dxCommon->PostDraw();
	}

	//各種解放
	for (int i = 0; i < 3; ++i) {
		delete sprite[i];
	}

	TextureManager::GetInstance()->Finalize();

	delete spriteCommon;

	delete imGuiManager;

	delete input;

	delete dxCommon;

	winApp->Finalize();
	delete winApp;

	return 0;
}
