#pragma once

#include "Singleton.h"

#include <Keyboard.h>
#include <Mouse.h>
#include <SpriteFont.h>
#include <CommonStates.h>

namespace DXTK
{
	class DXTKGroup :public Singleton<DXTKGroup>
	{
	public:
		void Initializer(ID3D11Device* device, ID3D11DeviceContext* context);

		void UpdateInputState();

		/*�f�o�C�X*/
		ID3D11Device* m_device;

		/*�R���e�X�g*/
		ID3D11DeviceContext* m_context;

		/*�L�[�{�[�h�֌W*/
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;

		/*�}�E�X�֌W*/
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;

		/*�R�����X�e�[�g*/
		std::unique_ptr<DirectX::CommonStates> m_state;

		/*�X�v���C�g�o�b�`*/
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

		/*�X�v���C�g�t�H���g*/
		std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	private:
		friend class Singleton<DXTKGroup>;

		DXTKGroup();
	};
}