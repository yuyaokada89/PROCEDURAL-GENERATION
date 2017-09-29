//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "DXTKGroup.h"

#include <d3d11.h>



extern void ExitGame();

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;
using VT = VertexPositionNormalColor;		//���̓��C�A�E�g���ʒu�A�F
using PB = PrimitiveBatch<VT>;


// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_n[] =
{
	// ����
	{  Vector3(-0.5f, 0.5f, 0.5f),  Vector3(0.0f, 0.0f, 1.0f)  ,Colors::Red  },
 	{  Vector3(0.5f, 0.5f, 0.5f),   Vector3(0.0f, 0.0f, 1.0f)  ,Colors::Red  },
	{  Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f)  ,Colors::Red  },
	{  Vector3(0.5f, -0.5f, 0.5f),  Vector3(0.0f, 0.0f, 1.0f)  ,Colors::Red  },
															  			    
	// ���													  			    
	{ Vector3(-0.5f, 0.5f, -0.5f),  Vector3(0.0f, 0.0f, -1.0f) ,Colors::Red  },
	{ Vector3(0.5f, 0.5f, -0.5f),   Vector3(0.0f, 0.0f, -1.0f) ,Colors::Red  },
	{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f) ,Colors::Red  },
	{ Vector3(0.5f, -0.5f, -0.5f),  Vector3(0.0f, 0.0f, -1.0f) ,Colors::Red  },
															  			    
	// ���													  			    
	{ Vector3(-0.5f, 0.5f, -0.5f),  Vector3(0.0f, 1.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(0.5f, 0.5f, -0.5f),   Vector3(0.0f, 1.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(-0.5f, 0.5f, 0.5f),   Vector3(0.0f, 1.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(0.5f, 0.5f, 0.5f),    Vector3(0.0f, 1.0f, 0.0f)  ,Colors::Red  },
															 			    
	// ����													 			    
	{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f) ,Colors::Red  },
	{ Vector3(0.5f, -0.5f, -0.5f),  Vector3(0.0f, -1.0f, 0.0f) ,Colors::Red  },
	{ Vector3(-0.5f, -0.5f, 0.5f),  Vector3(0.0f, -1.0f, 0.0f) ,Colors::Red  },
	{ Vector3(0.5f, -0.5f, 0.5f),   Vector3(0.0f, -1.0f, 0.0f) ,Colors::Red  },
															  			    
	// �E��													  			    
	{ Vector3(0.5f, 0.5f, 0.5f),    Vector3(1.0f, 0.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(0.5f, 0.5f, -0.5f),   Vector3(1.0f, 0.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(0.5f, -0.5f, 0.5f),   Vector3(1.0f, 0.0f, 0.0f)  ,Colors::Red  },
	{ Vector3(0.5f, -0.5f, -0.5f),  Vector3(1.0f, 0.0f, 0.0f)  ,Colors::Red  },
															 
	// ����													 
	{ Vector3(-0.5f, 0.5f, 0.5f),   Vector3(-1.0f, 0.0f, 0.0f) ,Colors::Red  },
	{ Vector3(-0.5f, 0.5f, -0.5f),  Vector3(-1.0f, 0.0f, 0.0f) ,Colors::Red  },
	{ Vector3(-0.5f, -0.5f, 0.5f),  Vector3(-1.0f, 0.0f, 0.0f) ,Colors::Red  },
	{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f) ,Colors::Red  },
};

// �C���f�b�N�X�f�[�^
uint16_t indexes[] = {
	0, 1, 2, 1, 3, 2,
	0 + 4, 2 + 4, 1 + 4, 1 + 4, 2 + 4, 3 + 4,
	0 + 8, 1 + 8, 2 + 8, 1 + 8, 3 + 8, 2 + 8,
	0 + 12, 2 + 12, 1 + 12, 1 + 12, 2 + 12, 3 + 12,
	0 + 16, 1 + 16, 2 + 16, 1 + 16, 3 + 16, 2 + 16,
	0 + 20, 2 + 20, 1 + 20, 1 + 20, 2 + 20, 3 + 20,
};



Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	// DirectXTK�̊Ǘ��I�u�W�F�N�g�̏�����
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	dxtk.Initializer(m_d3dDevice.Get(), m_d3dContext.Get());

	PolygonInit();

	//�@�f�o�b�O�J�����̐���
	m_debugcamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);

	//�@�J�����̐���
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	// �r���[�s��̐ݒ�
	m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),
		Vector3::Zero, Vector3::UnitY);
	//�@�ˉe�s��̐ݒ�
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(m_outputWidth) / float(m_outputHeight), 0.1f, 1000.f);


	

	//�@3D�I�u�W�F�N�g�N���X�̐ÓI�����o��������
	Obj3d::InitializeStatic(
		m_camera.get()
		, dxtk.m_device
		, dxtk.m_context
	);

	m_angle = 0;

	m_map = std::make_unique<RandomMapMaker>();

	
	

}

void Game::PolygonInit()
{
	// DirectXTK�̊Ǘ��I�u�W�F�N�g�̏�����
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	//�v���~�e�B�u�o�b�`���쐬
	primitiveBatch = std::make_unique<PB>(dxtk.m_context);

	//�G�t�F�N�g���쐬
	basicEffect = std::make_unique<BasicEffect>(dxtk.m_device);

	basicEffect->SetVertexColorEnabled(true);

	basicEffect->SetAmbientLightColor(Vector3(0.5f, 0.5f, 1.0f));

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightEnabled(0, true);

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightDirection(0, Vector3(1.0f, -0.5f, 2.0f));

	basicEffect->SetLightEnabled(1, true);

	basicEffect->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));

	basicEffect->SetLightDirection(1, Vector3(-1.0f, -0.5f, -2.0f));

	////���_�F���g�p����̂��G�t�F�N�g�ɋ�����
	//basicEffect->SetVertexColorEnabled(false);	// ���_�J���[(OFF)
	//basicEffect->SetLightingEnabled(false);		// ���C�g(ON)
	//basicEffect->SetTextureEnabled(true);		// �e�N�X�`��(OFF)
	//basicEffect->SetPerPixelLighting(false);	// �s�N�Z�����C�e�B���O(OFF)

	//���̓��C�A�E�g���쐬����
	//����g�p���钸�_�V�F�[�_�[����������
	void const* shaderByteCode;	// �v���O�����̐擪�A�h���X

	size_t byteCodeLength;		// �v���O�����̃T�C�Y

	basicEffect->GetVertexShaderBytecode(
		&shaderByteCode, &byteCodeLength);

	//byteCodeLength = 4744;

	dxtk.m_device->CreateInputLayout(
		VertexPositionNormalColor::InputElements,
		VertexPositionNormalColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		inputLayout.GetAddressOf());
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	//�@�f�o�b�O�J�����̍X�V
	m_debugcamera->Update();

	//�@�J�����̍X�V
	m_camera->Update();
	m_view = m_camera->GetViewMatrix();
	m_proj = m_camera->GetProjectionMatrix();


	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();
	auto kb = dxtk.m_keyboard->GetState();
	// �L�[���͂̍X�V
	dxtk.UpdateInputState();

	//�@�J�����㏸
	if (kb.IsKeyDown(Keyboard::Keys::Up))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	// �J�������~
	if (kb.IsKeyDown(Keyboard::Keys::Down))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, -0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}
	
	//�@�J�����E�ړ�
	if (kb.IsKeyDown(Keyboard::Keys::Right))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0.1f,0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�������ړ�
	if (kb.IsKeyDown(Keyboard::Keys::Left))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(-0.1f, 0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�����O�i
	if (kb.IsKeyDown(Keyboard::Keys::W))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0, -0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::S))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0, 0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	const float rotSpeed = 0.3f;

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::Q))
	{
		m_angle -= rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::P))
	{
		m_angle += rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}
	m_map->Update();
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.

	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	
	m_map->Draw();

	PolygonDraw();

	//dxtk.m_spriteBatch->Begin();

    Present();
}

void Game::PolygonDraw()
{
	// DirectXTK�̊Ǘ��I�u�W�F�N�g�̏�����
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	// ���[���h�s��A�r���[�s��A�ˉe�s���ݒ�
	basicEffect->SetWorld(m_world);
	basicEffect->SetView(m_view);
	basicEffect->SetProjection(m_proj);
	basicEffect->Apply(dxtk.m_context);

	// �[�x�E�X�e���V���̐ݒ�i�ʏ�̐ݒ�j
	dxtk.m_context->OMSetDepthStencilState(
		dxtk.m_state->DepthDefault(), 0);

	// �u�����h�X�e�[�g�̐ݒ�i�s�����j
	dxtk.m_context->OMSetBlendState(
		dxtk.m_state->Opaque(), nullptr, 0XFFFFFFFF);

	// �J�����O�̐ݒ�i�J�����O�͂��Ȃ��j
	dxtk.m_context->RSSetState(dxtk.m_state->CullCounterClockwise());

	dxtk.m_context->IASetInputLayout(inputLayout.Get());

	// �v���~�e�B�u�̕`��
	primitiveBatch->Begin();

	// �O�p�`���X�g�̕`��
	primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes, 6 * 6, vertexes_n, 4 * 6);

	primitiveBatch->End();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}