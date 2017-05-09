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
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
	d3dpp.hDeviceWindow = wndHandle;

	// Create a default DirectX device 
	if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wndHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice ) ) ) 
	{ 
		return false;
	}
	//return true;
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
	// Clear the back buffer to a green color
	pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET/* | D3DCLEAR_ZBUFFER*/,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

bool Graphics::SetupScene()
{
	HRESULT hRes;

	// Obtengo el viewport
	hRes = pd3dDevice->GetViewport(&viewport);

	if (FAILED(hRes)) {
		//Error::setError(5);
		return false;
	}

	hRes = pd3dDevice->CreateVertexBuffer(3 * sizeof(VertexUV),
		D3DUSAGE_WRITEONLY,
		VertexUV::fvf,
		D3DPOOL_MANAGED,
		&vBuffer,
		NULL);

	VertexUV vertices[] =
	{
		{ 320.0f, 50.0f, 0.5f, 0.5f, 0.0f },
		{ 520.0f, 400.0f, 0.5f, 0.0f, 1.0f },
		{ 120.0f, 400.0f, 0.5f, 1.0f, 1.0f},
	};


	//Ésto se supone debería hacerme un cuadrado :(
	//VertexUV vertices[] =
	//{
	//	{ 120.0f, 400.0f, 0.5f, 0.0f, 1.0f },
	//	{ 120.0f, 50.0f, 0.5f, 0.0f, 0.0f },
	//	{ 520.0f, 50.0f, 0.5f, 1.0f, 0.0f },
	//	{ 520.0f, 400.0f, 0.5f, 1.0f, 1.0f },
	//};

	//Vertex* vertex;
	VOID* pVoid;    // the void pointer
	vBuffer->Lock(0, 0, (void**)&pVoid,
		0);
	memcpy(pVoid, vertices, sizeof(vertices));

	hRes = vBuffer->Unlock();
	//End of Vertex Buffer

	//Create Texture

	//D3DXCreateTextureFromFile(pd3dDevice, L"C:\\Users\\Sebastian\\Pictures\\Fotos\\prueba.png", &m_texture);

	D3DXCreateTextureFromFile(pd3dDevice, L"wood.png", &m_texture);

	// Registro el viewport obtenido
	//FileLog::Write("Viewport {x=%d, y=%d, w=%d, h=%d}\n", _viewport.X, _viewport.Y, _viewport.Width, _viewport.Height);

	// -----------------------------------------------------------------------
	// Fijo la Matriz del Mundo, que es la que transforma de coordenadas
	// locales de los objetos a la de mundo
	// -----------------------------------------------------------------------
	D3DXMATRIX d3dmat;
	D3DXMatrixIdentity(&d3dmat);
	pd3dDevice->SetTransform(D3DTS_WORLD, &d3dmat);

	// -----------------------------------------------------------------------
	// Fijo la matriz de vista, que es la transforma a todos los vértices
	// para cambiar el punto de visión de la escena
	// -----------------------------------------------------------------------
	D3DXVECTOR3 eyePos(viewport.Width / 2.0f, viewport.Height / 2.0f, -5.0f);
	D3DXVECTOR3 lookPos(viewport.Width / 2.0f, viewport.Height / 2.0f, 0.0f);
	D3DXVECTOR3 upVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&d3dmat, &eyePos, &lookPos, &upVec);
	pd3dDevice->SetTransform(D3DTS_VIEW, &d3dmat);

	// -----------------------------------------------------------------------
	// Seteo la Matriz de Proyección, que es la que transforma nuestro mundo
	// 3d en un viewport 2d que es mostrado en pantalla
	// -----------------------------------------------------------------------
	D3DXMATRIX mProjectionMatrix;
	float fAspectRatio = (float)viewport.Width / viewport.Height;

	//D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, D3DX_PI*0.5f, fAspectRatio, 1.0f, 1000.0f);
	D3DXMatrixOrthoLH(&mProjectionMatrix, (float)viewport.Width, (float)viewport.Height, -25.0f, 25.0f);
	hRes = pd3dDevice->SetTransform(D3DTS_PROJECTION, &mProjectionMatrix);

	if (FAILED(hRes)) {
		//Error::setError(6);
		return false;
	}

	//_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80));			//ambient light
	//pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // D3DCULL_CCW

	// TEMPORAL
	//pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
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
	pd3dDevice->SetTexture(0,m_texture);
	pd3dDevice->SetFVF(VertexUV::fvf);
	pd3dDevice->SetVertexShader(NULL);
	pd3dDevice->SetStreamSource(
		0,
		vBuffer,
		0,
		sizeof(VertexUV));
	HRESULT hRes = pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
}

void Graphics::End() {
	pd3dDevice->EndScene();
}


void Graphics::Shutdown() {
	// Release the device and the Direct3D object 
	vBuffer->Release();

	if (pd3dDevice != NULL)
		pd3dDevice->Release();

	if (pD3D != NULL)
		pD3D->Release();

}