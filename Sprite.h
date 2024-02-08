#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include <DirectXMath.h>

class Sprite
{
public://namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	struct Transform {
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT3 translate;
	};

	struct VertexData {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcoord;
	};

	struct MaterialData {
		DirectX::XMFLOAT4 color;
		DirectX::XMMATRIX uvTransform;
	};

public:
	void Initialize(SpriteCommon* common, std::wstring textureFilePath);
	void Update();
	void Draw();

	DirectX::XMFLOAT2 GetPosition() { return postion; }
	float GetRotation() { return rotation; }
	DirectX::XMFLOAT4 GetColor() { return color_; }
	DirectX::XMFLOAT2 GetScale() { return scale; }
	DirectX::XMFLOAT2 GetAnchorPoint() { return anchorPoint; }
	bool GetFlipX() { return isFlipX; }
	bool GetFlipY() { return isFlipY; }
	DirectX::XMFLOAT2 GetTextureLeftTop() { return textureLeftTop; }
	DirectX::XMFLOAT2 GetTextureSize() { return textureSize; }

	void SetPosition(DirectX::XMFLOAT2 pos) { postion = pos; }
	void SetRotation(float rot) { rotation = rot; }
	void SetScale(DirectX::XMFLOAT2 scl) { scale = scl; }
	void SetColor(DirectX::XMFLOAT4 color) { color_ = color; }
	void SetAnchorPoint(DirectX::XMFLOAT2 ap) { anchorPoint = ap; }
	void SetFlipX(bool isFlag) { isFlipX = isFlag; }
	void SetFlipY(bool isFlag) { isFlipY = isFlag; }
	void SetTextureLeftTop(DirectX::XMFLOAT2 leftTop) { textureLeftTop = leftTop; }
	void SetTextureSIze(DirectX::XMFLOAT2 size) { textureSize = size; }

	void SetTexture(std::wstring textureFilePath);

private:
	void CreateVertex();
	void CreateIndex();
	void CreateMaterial();
	void CreateWVP();

	void AdjustTextureSize();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	ComPtr<ID3D12Resource>vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	VertexData* vertexData = nullptr;

	ComPtr<ID3D12Resource>indexResource;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	ComPtr<ID3D12Resource>materialResource;
	MaterialData* materialData = nullptr;

	ComPtr<ID3D12Resource> wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	Transform uvTransform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	Transform transform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	DirectX::XMFLOAT2 postion = { 0.0f,0.0f };
	float rotation = 0.0f;
	DirectX::XMFLOAT2 scale = { 512.0f,512.0f };

	DirectX::XMFLOAT2 anchorPoint = { 0.5f,0.5f };

	bool isFlipX = false;
	bool isFlipY = false;

	DirectX::XMFLOAT2 textureLeftTop = { 0.0f,0.0f };
	DirectX::XMFLOAT2 textureSize = { 414.0f,410.0f };

	uint32_t textureIndex_ = 0;

	Transform cametaTransform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-5.0f}
	};
};