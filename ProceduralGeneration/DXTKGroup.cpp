#include "../pch.h"
#include "../System/DXTKGroup.h"

using namespace DirectX;

DXTK::DXTKGroup::DXTKGroup()
{
	m_keyboard = std::make_unique<Keyboard>();
	m_keyTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
	m_mouse = std::make_unique<Mouse>();
	m_mouseTracker = std::make_unique<Mouse::ButtonStateTracker>();
}

void DXTK::DXTKGroup::Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;

	// �R�����X�e�[�g���쐬
	m_state = std::make_unique<CommonStates>(device);

	// �X�v���C�g�o�b�`
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	// �X�v���C�g�t�H���g
	m_spriteFont = std::make_unique<SpriteFont>(device, L"myfile.spritefont");
}

void DXTK::DXTKGroup::UpdateInputState()
{
	// �L�[���͏����擾
	Keyboard::State key = m_keyboard->GetState();
	m_keyTracker->Update(key);

	// �}�E�X�����擾
	Mouse::State mouse = m_mouse->GetState();
	m_mouseTracker->Update(mouse);
}
