#include "..\includes\Graphics.h"

bool Graphics::Initialize(HWND wndHandle) {
	pD3D = NULL;
	pd3dDevice = NULL;

	// Create the DirectX object
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	// Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 480;
	d3dpp.BackBufferWidth = 640;
	d3dpp.hDeviceWindow = wndHandle;

	// Create a default DirectX device 
	if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, wndHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice ) ) ) 
	{ 
		return false;
	}
	return true;
}

void Graphics::Shutdown() {
	// Release the device and the Direct3D object 
	if( pd3dDevice != NULL ) 
		pd3dDevice->Release( );

	if (pD3D != NULL) 
		pD3D->Release();
}

void Graphics::Present() {
	// Present the back buffer contents to the display 
	pd3dDevice->Present( NULL, NULL, NULL, NULL ); 
}

void Graphics::Clear() {
	// Check to make sure you have a valid Direct3D device
	if (NULL == pd3dDevice)
		return;
	// Clear the back buffer to a blue color
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
}

void Graphics::Begin() {}

void Graphics::End() {}