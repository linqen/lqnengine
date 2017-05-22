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
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
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
		D3DCOLOR_XRGB(0, 65, 120), 1.0f, 0);
}

bool Graphics::SetupScene()
{
	HRESULT hRes;
	// Obtengo el viewport
	hRes = pd3dDevice->GetViewport(&viewport);
	if (FAILED(hRes)) {
		return false;
	}

	//Create Texture
	//D3DXCreateTextureFromFile(pd3dDevice, L"C:\\Users\\Sebastian\\Pictures\\Fotos\\prueba.png", &m_texture);
	//D3DXCreateTextureFromFile(pd3dDevice, L"wood.png", &m_texture);

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

	D3DXMATRIX lookAtMat;
	D3DXMatrixIdentity(&lookAtMat);
	D3DXVECTOR3 eyePos(viewport.Width / 2.0f, viewport.Height / 2.0f, -5.0f);
	D3DXVECTOR3 lookPos(viewport.Width / 2.0f, viewport.Height / 2.0f, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&lookAtMat, &eyePos, &lookPos, &upVec);
	pd3dDevice->SetTransform(D3DTS_VIEW, &lookAtMat);

	// -----------------------------------------------------------------------
	// Seteo la Matriz de Proyección, que es la que transforma nuestro mundo
	// 3d en un viewport 2d que es mostrado en pantalla
	// -----------------------------------------------------------------------
	D3DXMATRIX mProjectionMatrix;
	D3DXMatrixIdentity(&mProjectionMatrix);
	float fAspectRatio = (float)viewport.Width / viewport.Height;

	D3DXMatrixOrthoLH(&mProjectionMatrix, (float)viewport.Width*5, (float)viewport.Height*5, -25.0f, 25.0f);
	hRes = pd3dDevice->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);
	if (FAILED(hRes)) {
		return false;
	}

	pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DXToRadian(45), fAspectRatio, -51.0f, 100.0f);
	//_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80));			//ambient light
	//_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW
	// TEMPORAL
	//pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// Fijo valores por defecto para operaciones con el canal alpha
	//pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// Deshabilito los speculars
	//pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	// Deshabilito el stencil
	//pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	return true;
}


void Graphics::Begin() {

	pd3dDevice->BeginScene();
	//pd3dDevice->SetTexture(0,m_texture);
	//pd3dDevice->SetFVF(VertexUV::fvf);
	//pd3dDevice->SetVertexShader(NULL);
	//pd3dDevice->SetStreamSource(
	//	0,
	//	vBuffer,
	//	0,
	//	sizeof(VertexUV));
	//HRESULT hRes = pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
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

void Graphics::LoadIdentity() {
	D3DXMatrixIdentity(&d3dmat);
	pd3dDevice->SetTransform(D3DTS_WORLD, &d3dmat);
}
void Graphics::Translate(float xPos, float yPos, float zPos) {
	D3DXMatrixTranslation(&d3dmat, xPos, yPos, zPos);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}
void Graphics::RotateZ(float zRot) {
	D3DXMatrixRotationZ(&d3dmat, zRot);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}
void Graphics::Scale(float xScale, float yScale, float zScale) {
	D3DXMatrixScaling(&d3dmat, xScale, yScale, zScale);
	pd3dDevice->MultiplyTransform(D3DTS_WORLD, &d3dmat);
}

void Graphics::Draw2D(Vertex* vertex, _D3DPRIMITIVETYPE primitive, float vertexCount) {
	vertexManager.Bind();
	vertexManager.Draw(vertex, primitive, vertexCount);
	//Esto dibuja un triangulo
	//VertexUV vertices[] =
	//{
	//	{ 320.0f, 50.0f, 0.5f, 0.5f, 0.0f },
	//	{ 520.0f, 400.0f, 0.5f, 0.0f, 1.0f },
	//	{ 120.0f, 400.0f, 0.5f, 1.0f, 1.0f},
	//};
	////Ésto dibuja un cuadrado si está activado TriangleStrip
	//VertexUV vertices[] =
	//{
	//	{ 120.0f, 400.0f, 0.5f, 0.0f, 1.0f },
	//	{ 120.0f, 50.0f, 0.5f, 0.0f, 0.0f },
	//	{ 520.0f, 400.0f, 0.5f, 1.0f, 1.0f },
	//	{ 520.0f, 50.0f, 0.5f, 1.0f, 0.0f },
	//};
	//Vertex* vertex;
	//VOID* pVoid;    // the void pointer
	//vBuffer->Lock(0, 0, (void**)&pVoid,
	//	0);
	//memcpy(pVoid, vertices, sizeof(vertices));
	//vBuffer->Unlock();
	//End of Vertex Buffer
}
//
void Graphics::DrawSprite(VertexUV* vertexUV, _D3DPRIMITIVETYPE primitive, float vertexCount, IDirect3DTexture9* texture) {
	textureVertexManager.Bind();
	pd3dDevice->SetTexture(0, texture);
	textureVertexManager.Draw(vertexUV, primitive, vertexCount);

}