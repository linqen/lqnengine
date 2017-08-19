#include "..\includes\Graphics.h"

bool Graphics::Initialize(HWND wndHandle) {
	pD3D = NULL;
	pd3dDevice = NULL;

	// Create the DirectX object
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}
	//Cuando tengo el device llamo al create del manager con if
	// Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = viewport.Height;
	d3dpp.BackBufferWidth = viewport.Width;
	d3dpp.hDeviceWindow = wndHandle;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create a default DirectX device 
	if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wndHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice ) ) ) 
	{ 
		return false;
	}

	if (!vertexManager.Create(pd3dDevice, true)) {
		return false;
	}
	if (!textureVertexManager.Create(pd3dDevice, true)) {
		return false;
	}
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
		D3DCOLOR_XRGB(65, 65, 120), 1.0f, 0);
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
	//hRes = pd3dDevice->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);

	pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// Fijo valores por defecto para operaciones con el canal alpha
	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DXToRadian(45), fAspectRatio, -51.0f, 100.0f);
	//_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80));			//ambient light
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
//Load Identity Matrix
void Graphics::LoadIdentity() {
	D3DXMatrixIdentity(&d3dmat);
	pd3dDevice->SetTransform(D3DTS_WORLD, &d3dmat);
}
//Translate the matrix based on the coordinates
void Graphics::Translate(float xPos, float yPos, float zPos) {
	D3DXMatrixTranslation(&d3dmat, xPos, yPos, zPos);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}
//Rotate the matrix based on Z value
void Graphics::RotateZ(float zRot) {
	D3DXMatrixRotationZ(&d3dmat, zRot);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}
//Scale the matrix based on XYZ coordinates
void Graphics::Scale(float xScale, float yScale, float zScale) {
	D3DXMatrixScaling(&d3dmat, xScale, yScale, zScale);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}
//Draw 2D Object
void Graphics::Draw2D(Vertex* vertex, _D3DPRIMITIVETYPE primitive, float vertexCount) {
	vertexManager.Bind();
	vertexManager.Draw(vertex, primitive, vertexCount);
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
}