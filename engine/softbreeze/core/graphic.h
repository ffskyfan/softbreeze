

#ifndef SOFTBREEZE_GRAPHIC_NEW_H
#define SOFTBREEZE_GRAPHIC_NEW_H

#include <xnamath.h>


softbreeze_namespace_beg

class Vector2;

struct vertex
{
	XMFLOAT3	pos;
	XMFLOAT4	color;
	XMFLOAT2	texCoord;

	vertex( XMFLOAT3 p, XMFLOAT4 c )
	{
		pos = p;
		color = c;
	}
	
	vertex( XMFLOAT3 p, XMFLOAT4 c, XMFLOAT2 tex )
	{
		pos = p;
		color = c;
		texCoord = tex;
	}
};



class Graphic
{
public:
	~Graphic();

	static Graphic& Instance();

	HRESULT			Init(HWND hWnd);
	void			Render();
	void			Cleanup();

	inline uint32	GetWidth()	{ return width; }
	inline uint32	GetHeight() { return height; }

	void			ClearCanvas(uint32 color);

	void			SetPixel(uint32 x, uint32 y, uint32 color);

	void			DrawLine(Vector2 begin, Vector2 end, uint32 color);//draw line using Bresenham's line algorithm
	


private:
	Graphic();
	

	static Graphic* _inst;

	uint32*								canvas;
	uint32								width;
	uint32								height;

	D3D_DRIVER_TYPE						driverType			= D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL					featureLevel		= D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*						pd3dDevice			= NULL;
	ID3D11DeviceContext*				pImmediateContext	= NULL;
	IDXGISwapChain*						pSwapChain			= NULL;
	ID3D11RenderTargetView*				pRenderTargetView	= NULL;
	ID3D11VertexShader*					pVertexShader		= NULL;
	ID3D11PixelShader*					pPixelShader		= NULL;
	ID3D11InputLayout*					pVertexLayout		= NULL;
	ID3D11Buffer*						pVertexBuffer		= NULL;
	ID3D11Buffer*						pIndexBuffer		= NULL;
	ID3D11ShaderResourceView*           pTextureRV			= NULL;
	ID3D11SamplerState*                 pSamplerLinear		= NULL;
	ID3D11Texture2D*					Texture				= NULL;

};



softbreeze_namespace_end

#endif