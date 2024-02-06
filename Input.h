#pragma once

#include <windows.h>

#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>

#include "WinApp.h"

//����
class Input
{
public://namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();

	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <retuyrns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <retuyrns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

private://�����o�ϐ�	
	WinApp* winApp_ = nullptr;

    // DirectInput�̃C���X�^���X����
	ComPtr<IDirectInput8> dInput = nullptr;

	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard;

	//�S�L�[�̏��
	BYTE key[256] = {};

	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
};