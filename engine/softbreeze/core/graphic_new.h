

#ifndef SOFTBREEZE_GRAPHIC_NEW_H
#define SOFTBREEZE_GRAPHIC_NEW_H


softbreeze_namespace_beg


class Graphic
{
public:
	~Graphic();

	static Graphic& Instance();

	HRESULT			Init(HWND hWnd);
	void			Render();
	void			Cleanup();

private:
	Graphic();
	

	static Graphic* _inst;


	D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           pd3dDevice = NULL;
	ID3D11DeviceContext*    pImmediateContext = NULL;
	IDXGISwapChain*         pSwapChain = NULL;
	ID3D11RenderTargetView* pRenderTargetView = NULL;

};



softbreeze_namespace_end

#endif