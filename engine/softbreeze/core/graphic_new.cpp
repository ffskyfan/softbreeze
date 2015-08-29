
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

#include "../softbreeze.h"
#include "graphic_new.h"




softbreeze_namespace_beg

Graphic* Graphic::_inst = nullptr;


Graphic& Graphic::Instance()
{
	if(_inst == nullptr) {
		_inst = new Graphic;
	}

	return *_inst;
}


Graphic::Graphic()
{

}

Graphic::~Graphic()
{

}


HRESULT Graphic::Init(HWND hWnd)
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pImmediateContext );
        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    if( FAILED( hr ) )
        return hr;

    hr = pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &pRenderTargetView );
    pBackBuffer->Release();
    if( FAILED( hr ) )
        return hr;

    pImmediateContext->OMSetRenderTargets( 1, &pRenderTargetView, NULL );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pImmediateContext->RSSetViewports( 1, &vp );

    return S_OK;

}


void Graphic::Render()
{
    // Just clear the backbuffer
    float ClearColor[4] = { 0.0f, 0.0, 0.0f, 0.0f }; //red,green,blue,alpha
    pImmediateContext->ClearRenderTargetView( pRenderTargetView, ClearColor );
    pSwapChain->Present( 0, 0 );

}

void Graphic::Cleanup()
{

    if( pImmediateContext ) pImmediateContext->ClearState();

    if( pRenderTargetView ) pRenderTargetView->Release();
    if( pSwapChain ) pSwapChain->Release();
    if( pImmediateContext ) pImmediateContext->Release();
    if( pd3dDevice ) pd3dDevice->Release();


}




softbreeze_namespace_end



