#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <cassert>
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include <DirectXMath.h>

class Sprite
{
public://namespaceè»ó™
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
	void Initialize(SpriteCommon* common);
	void Update();
	void Draw();

	DirectX::XMFLOAT2 GetPosition() { return postion; }
	float GetRotation() { return rotation; }
	DirectX::XMFLOAT4 GetColor() { return color_; }
	DirectX::XMFLOAT2 GetScale() { return scale; }

	void SetPosition(DirectX::XMFLOAT2 pos) { postion = pos; }
	void SetRotation(float rot) { rotation = rot; }
	void SetScale(DirectX::XMFLOAT2 scl) { scale = scl; }
	void SetColor(DirectX::XMFLOAT4 color) { color_ = color; }

private:
	void CreateVertex();
	void CreateIndex();
	void CreateMaterial();
	void CreateWVP();

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
	DirectX::XMFLOAT2 scale = { 1.0f,1.0f };

	Transform cametaTransform = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,-5.0f}
	};

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;
};