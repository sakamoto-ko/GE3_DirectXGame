#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include <DirectXMath.h>

class Sprite
{
public://namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	struct Transform {
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT3 translate;
	};

public:
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);
	void Draw();

private:
	void CreateVertex();
	void CreateMaterial();
	void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	ComPtr<ID3D12Resource>vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	ComPtr<ID3D12Resource>materialResource;

	ComPtr<ID3D12Resource> wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,0.0f,1.0f };
	Transform transform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	Transform cametaTransform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-5.0f}
	};
};