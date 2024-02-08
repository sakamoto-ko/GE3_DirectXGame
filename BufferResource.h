#pragma once
#include <d3d12.h>
#include <DirectXTex.h>

ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInByte);

ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);