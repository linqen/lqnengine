#include "..\includes\Graphics.h"

bool Graphics::Initialize(HWND wndHandle, int screenWidth, int screenHeight) {
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = wndHandle;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	D3D11CreateDeviceAndSwapChain(
	nullptr, 
	D3D_DRIVER_TYPE_HARDWARE,
	nullptr,
	0,
	nullptr,
	0,
	D3D11_SDK_VERSION,
	&sd,
	&pSwap,
	&pDevice,
	nullptr,
	&pContext);

	/*
	if (!vertexManager.Create(pd3dDevice, true)) {
		return false;
	}
	if (!textureVertexManager.Create(pd3dDevice, true)) {
		return false;
	}*/
	return Graphics::SetupScene();
}

void Graphics::Present() {
	// Present the back buffer contents to the display 
	pd3dDevice->Present( NULL, NULL, NULL, NULL ); 
}

void Graphics::Clear() {
	// Check to make sure you have a valid Direct3D device
	if (NULL == pd3dDevice)
		return;
	// Clear the back buffer to a black color
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(81, 81, 81), 1.0f, 0);
}

bool Graphics::SetupScene()
{
	HRESULT hRes;
	// Obtengo el viewport
	hRes = pd3dDevice->GetViewport(&viewport);
	if (FAILED(hRes)) {
		return false;
	}

	// -----------------------------------------------------------------------
	// Fijo la Matriz del Mundo, que es la que transforma de coordenadas
	// locales de los objetos a la de mundo
	// -----------------------------------------------------------------------
	D3DXMatrixIdentity(&d3dmat);
	pd3dDevice->SetTransform(D3DTS_WORLD, &d3dmat);

	// -----------------------------------------------------------------------
	// Fijo la matriz de vista, que es la transforma a todos los vértices
	// para cambiar el punto de visión de la escena
	// -----------------------------------------------------------------------
	//2D
	//D3DXMATRIX lookAtMat;
	//D3DXMatrixIdentity(&lookAtMat);
	//D3DXVECTOR3 eyePos(viewport.Width / 2.0f, viewport.Height / 2.0f, -5.0f);
	//D3DXVECTOR3 lookPos(viewport.Width / 2.0f, viewport.Height / 2.0f, 0.0f);
	//D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	//D3DXMatrixLookAtLH(&lookAtMat, &eyePos, &lookPos, &upVec);
	//pd3dDevice->SetTransform(D3DTS_VIEW, &lookAtMat);

	//3D
	D3DXMATRIX lookAtMat;
	D3DXMatrixIdentity(&lookAtMat);
	D3DXVECTOR3 eyePos(0, 0, -0.1f);
	D3DXVECTOR3 lookPos(0, 0, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&lookAtMat, &eyePos, &lookPos, &upVec);
	//pd3dDevice->SetTransform(D3DTS_VIEW, &lookAtMat);

	// -----------------------------------------------------------------------
	// Seteo la Matriz de Proyección, que es la que transforma nuestro mundo
	// 3d en un viewport 2d que es mostrado en pantalla
	// -----------------------------------------------------------------------
	//Modo 2D
	//D3DXMATRIX mProjectionMatrix;
	//D3DXMatrixIdentity(&mProjectionMatrix);
	//float fAspectRatio = (float)viewport.Width / viewport.Height;
	//D3DXMatrixOrthoLH(&mProjectionMatrix, (float)viewport.Width * 5, (float)viewport.Height * 5, -25.0f, 25.0f);
	//hRes = pd3dDevice->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);

	//Modo 3D
	D3DXMATRIX mProjectionMatrix;
	D3DXMatrixIdentity(&mProjectionMatrix);
	float fAspectRatio = (float)viewport.Width / viewport.Height;
	D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DXToRadian(60), fAspectRatio, 0.1f, 1000.0f);

	pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	// Fijo valores por defecto para operaciones con el canal alpha
	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);




	//pd3dDevice->SetLight(D3DLIGHT_POINT,0)
	// Assume d3dDevice is a valid pointer to an IDirect3DDevice9 interface.
	//D3DLIGHT9 d3dLight;
	HRESULT   hr;

	// Initialize the structure.
	ZeroMemory(&d3dLight, sizeof(d3dLight));
	
	// Set up a white point light.
	d3dLight.Type = D3DLIGHT_DIRECTIONAL;
	d3dLight.Diffuse = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
	D3DVECTOR direction=D3DVECTOR();
	direction.x = -1;
	direction.y = -1;
	direction.z = -1;
	d3dLight.Direction = direction;
	
	d3dLight.Position.x = 0.0f;
	d3dLight.Position.y = 500.0f;
	d3dLight.Position.z = 0.0f;
	
	// Don't attenuate.
	d3dLight.Attenuation0 = 1.0f;
	d3dLight.Attenuation1 = 0.1f;
	d3dLight.Attenuation2 = 0.0f;
	
	//d3dLight.Theta = 0.4;
	//d3dLight.Phi = 0.6;
	//d3dLight.Falloff = 1.0;
	
	d3dLight.Range = 6000.0f;

	// Set the property information for the first light.
	hr = pd3dDevice->SetLight(0, &d3dLight);
	//if (SUCCEEDED(hr)) {
	//	int j = 2;
	//}
	//else {
	//	int i = 2;
	//}

	pd3dDevice->LightEnable(0, true);
	pd3dDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DXToRadian(45), fAspectRatio, -51.0f, 100.0f);
	//pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80));			//ambient light
	//_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW
	// TEMPORAL
	//pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// Deshabilito los speculars
	//pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	// Deshabilito el stencil
	//pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	return true;
}


void Graphics::Begin() {
	pd3dDevice->BeginScene();
}

void Graphics::End() {
	pd3dDevice->EndScene();
}

void Graphics::Shutdown() {
	// Release the device and the Direct3D object 
	vertexManager.Release();
	textureVertexManager.Release();
	if (pd3dDevice != NULL)
		pd3dDevice->Release();
	if (pD3D != NULL)
		pD3D->Release();
}

/*

//Draw 2D Object
void Graphics::Draw2D(Vertex* vertex, _D3DPRIMITIVETYPE primitive, float vertexCount) {
	vertexManager.Bind();
	vertexManager.Draw(vertex, primitive, vertexCount);
}
//Draw 3D Object
void Graphics::Draw3D(VertexUV* vertex,int* index,int vertexCount,int indexCount, _D3DPRIMITIVETYPE primitive) {


}
//Draw Sprite
void Graphics::DrawSprite(VertexUV* vertexUV, _D3DPRIMITIVETYPE primitive, float vertexCount) {
	textureVertexManager.Bind();
	textureVertexManager.Draw(vertexUV, primitive, vertexCount);

}
//Load a texture, return null if can't load
IDirect3DTexture9* Graphics::LoadTexture(LPCWSTR texturePath) {
	IDirect3DTexture9* temporalTexture = 0;
	//Used D3DXCreateTextureFromFileEx with D3DX_DEFAULT_NONPOW2 to let the texture on the
	//original size
	HRESULT result = D3DXCreateTextureFromFileEx(
		pd3dDevice, texturePath, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&temporalTexture);
	//HRESULT result = D3DXCreateTextureFromFile(pd3dDevice, texturePath, &temporalTexture);
	if (FAILED(result)) {
		wstring tempWstring(texturePath);
		string tempString(tempWstring.begin(), tempWstring.end());
		LogFile::Write("Texture Not Found"+ tempString);
		return NULL;
	}
	return temporalTexture;
}

void Graphics::BindTexture(Texture* textureToBind) {
	if (textureToBind == NULL)
	{
		pd3dDevice->SetTexture(0, NULL);
		lastTexture = textureToBind;
	}
	else if (textureToBind != lastTexture) {
		pd3dDevice->SetTexture(0, textureToBind->GetD3DTexture());
		lastTexture = textureToBind;
	}
}

void Graphics::ReleaseTexture(Texture* textureToUnload) {
	textureToUnload->GetD3DTexture()->Release();
}

void Graphics::SetViewTransform(D3DXMATRIX * viewTransform) {
	pd3dDevice->SetTransform(D3DTS_VIEW, viewTransform);
}

void Graphics::SetProjectionMatrix(D3DXMATRIX * projectionMatrix) {
	pd3dDevice->SetTransform(D3DTS_PROJECTION, projectionMatrix);
}*/