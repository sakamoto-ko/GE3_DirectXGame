#pragma once
#include <Windows.h>
#include <wrl.h>
#include <string>
#include <d3d12.h>
#include <dxcapi.h>
#include "DirectXCommon.h"

#include <DirectXTex.h>

class SpriteCommon
{
public://namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	void Initialize(DirectXCommon* dxCommon);
	void SpritePreDraw();

	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
	DirectXCommon* GetDirectXCommon() { return dxCommon_; }

private:
	static IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

private:
	DirectXCommon* dxCommon_ = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState>pipelineState;
};

