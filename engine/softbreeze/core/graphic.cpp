
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include "../softbreeze.h"

#include "../math/vector2.h"
#include "../math/matrix4.h"
#include "../math/utility.h"



#include "graphic.h"




softbreeze_namespace_beg

struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

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
	canvas	= nullptr;

	width	= 0;
	height	= 0;
}

Graphic::~Graphic()
{

}

namespace
{
	HRESULT CompileShaderFromFile(CHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
		if(FAILED(hr)) {
			if(pErrorBlob != NULL)
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			if(pErrorBlob) pErrorBlob->Release();
			return hr;
		}
		if(pErrorBlob) pErrorBlob->Release();

		return S_OK;
	}

}


HRESULT Graphic::Init(HWND hWnd)
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( hWnd, &rc );
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;

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

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( "core.fx", "VS", "vs_4_0", &pVSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
        return hr;
    }

	// Create the vertex shader
	hr = pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &pVertexShader );
	if( FAILED( hr ) )
	{	
		pVSBlob->Release();
        return hr;
	}

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );

    // Create the input layout
	hr = pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &pVertexLayout );
	pVSBlob->Release();
	if( FAILED( hr ) )
        return hr;

    // Set the input layout
    pImmediateContext->IASetInputLayout( pVertexLayout );

	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile( "core.fx", "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( NULL,
                    "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
        return hr;
    }

	// Create the pixel shader
	hr = pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pPixelShader );
	pPSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Create vertex buffer
	SimpleVertex vertices[] = {
		{ XMFLOAT3(-1.0f, -1.0f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
	};

    D3D11_BUFFER_DESC bd;
    ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( SimpleVertex ) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = vertices;
    hr = pd3dDevice->CreateBuffer( &bd, &InitData, &pVertexBuffer );
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
    pImmediateContext->IASetVertexBuffers( 0, 1, &pVertexBuffer, &stride, &offset );


    // Set primitive topology
    pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );


	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
		

	hr = pd3dDevice->CreateTexture2D(&textureDesc, NULL, &Texture);
    if( FAILED( hr ) )
        return hr;

	canvas= new UINT[width * height];
	for(uint32 i = 0; i < width * height; i++) {
		canvas[i] = 0x00000000;
	}

	pImmediateContext->UpdateSubresource(Texture, 0, NULL, canvas, width*sizeof(UINT), 0);
	pd3dDevice->CreateShaderResourceView(Texture, NULL, &pTextureRV);

    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = pd3dDevice->CreateSamplerState( &sampDesc, &pSamplerLinear );
    if( FAILED( hr ) )
        return hr;

    return S_OK;

}



void Graphic::Render()
{
    // Clear the back buffer 
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
    pImmediateContext->ClearRenderTargetView( pRenderTargetView, ClearColor );

	// Update canvas
	pImmediateContext->UpdateSubresource(Texture, 0, NULL, canvas, width*sizeof(UINT), 0);

    // Draw
	pImmediateContext->VSSetShader( pVertexShader, NULL, 0 );
	pImmediateContext->PSSetShader( pPixelShader, NULL, 0 );
    pImmediateContext->PSSetShaderResources( 0, 1, &pTextureRV );
    pImmediateContext->PSSetSamplers( 0, 1, &pSamplerLinear );
    pImmediateContext->Draw( 4, 0 );

    // Present the information rendered to the back buffer to the front buffer (the screen)
    pSwapChain->Present( 0, 0 );
}

void Graphic::Cleanup()
{
    if( pImmediateContext ) pImmediateContext->ClearState();


	if(Texture)				Texture->Release();
	if(pSamplerLinear)		pSamplerLinear->Release();
	if(pTextureRV)			pTextureRV->Release();
	if(pIndexBuffer) 		pIndexBuffer->Release();
    if(pVertexBuffer)		pVertexBuffer->Release();
    if(pVertexLayout)		pVertexLayout->Release();
    if(pVertexShader)		pVertexShader->Release();
    if(pPixelShader)		pPixelShader->Release();
    if(pRenderTargetView)	pRenderTargetView->Release();
    if(pSwapChain)			pSwapChain->Release();
    if(pImmediateContext)	pImmediateContext->Release();
    if(pd3dDevice)			pd3dDevice->Release();
}


void Graphic::ClearCanvas(uint32 color)
{
	int canvasLength = width*height;
	for(int i = 0; i < canvasLength; i++) {
		canvas[i] = color;
	}
}


void Graphic::SetPixel(uint32 x, uint32 y, uint32 color)
{
	if(x < 0) return;
	if(y < 0) return;
	if(x > width) return;
	if(y > height) return;

	canvas[y*width + x] = color;
}


void Graphic::DrawLine(Vector2 begin, Vector2 end, uint32 color)
{
	int beginX = (int)begin.x, beginY = (int)begin.y;
	int endX = (int)end.x, endY = (int)end.y;

	bool isInScreen = CohenSutherlandClip(0, width, 0, height, beginX, beginY, endX, endY);
	if(!isInScreen) return;

	int deltaX = endX - beginX;
	int deltaY = endY - beginY;

	SetPixel(beginX, beginY, color);
	if(beginX == endX && beginY==endY) return;

	if(deltaX == 0) { //
		int step = (beginY < endY) ? 1 : -1;
		for(int i = beginY+step; i != endY; i = i + step) {
			SetPixel(beginX, i, color);
		}
	} else if(deltaY == 0) { //

		int step = (beginX < endX) ? 1 : -1;
		for(int i = beginX+step; i != endX; i = i + step) {
			SetPixel(i, beginY, color);
		}

	} else {
		if(deltaY==deltaX || deltaY==-deltaX) { //

			int stepX = (beginX < endX) ? 1 : -1;
			int stepY = (beginY < endY) ? 1 : -1;
			for(int i = beginX + stepX, j = beginY + stepY; i != endX; i = i + stepX, j = j + stepY) {
				SetPixel(i, j, color);
			}

		} else {

			deltaX = abs(deltaX);
			deltaY = abs(deltaY);
			int stepX = (beginX < endX) ? 1 : -1;
			int stepY = (beginY < endY) ? 1 : -1;
			int err = deltaX - deltaY;

			while(true) {
				if((beginX == endX) && (beginY == endY)) break;

				int err2 = 2 * err;
				if(err2 > -deltaY) { err -= deltaY; beginX += stepX; }
				if(err2 < deltaX) { err += deltaX; beginY += stepY; }

				SetPixel(beginX, beginY, color);
			}

		}
	}


}


softbreeze_namespace_end



