#include "..\includes\Window.h"

#include <iostream>
// ---------------------------------------------------------------------
// Create Window
// Crea la Window en cuesti�n con un t�tulo y tama�o espec�fico
// ---------------------------------------------------------------------



Window::Window() {
	Window::className = L"Window";
}
bool Window::createWindow(HINSTANCE hInstance, wstring title,
	int width, int height)
{
	hWnd = CreateWindow((LPCWSTR)(className.c_str()),	// Nombre de la clase
		(LPCWSTR)(title.c_str()),		// T�tulo de la Window
		WS_OVERLAPPEDWINDOW,			// Tipo de Window
		0,								// Posici�n X inicial
		0,								// Posici�n Y inicial
		width,							// Ancho
		height,							// Alto
		NULL,							// Window padre (en nuestro caso es NULL)
		NULL,							// Menu (en nuestro caso NULL)
		hInstance,						// Handler de la instancia de la Window (en XP es ignorado)
		NULL							// Siempre va NULL en estos casos
	);
	//DWORD asd = GetLastError();
	//string debug;
	//debug = asd;
	if (!hWnd) {	// Si hubo error retorno false
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);	//Fuerzo a mostrar la Window
	UpdateWindow(hWnd);			// Actualizo la Window

	return true;				// No hubo problemas, retorno verdadero
}
// ---------------------------------------------------------------------
// Window Procedure
// Cuando registramos la clase, deberemos especificar una funci�n que
// atienda los mensajes que llegan a nuestra Window.
// ---------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND:	// Selecci�n del men�
		break;
//	case WM_PAINT:		// Repintar la ventana
//		break;
	case WM_DESTROY:	// Destruir la Window
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // Devuelvo los mensajes al Windows Procedure por defecto
	}
	return(0);
}

// ---------------------------------------------------------------------
// Register Class
// Registramos la clase Window
// ---------------------------------------------------------------------
void Window::registerClass(HINSTANCE hInstance)
{
	WNDCLASS wc;

	memset(static_cast<void *> (&wc), 0, sizeof(WNDCLASS));  // Vac�o la estrcutura WNDCLASS

	wc.style = CS_HREDRAW | CS_VREDRAW;					// Fuerza a enviar un Redraw si la Window es reescalada 
														// movida horizontal o verticalmente
	wc.lpfnWndProc = (WNDPROC)WndProc;					// Asigna el Windows Procedure apropiado
	wc.hInstance = hInstance;							// Handler de la instancia de la aplicaci�n
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;		// C�mo debe pintarse el fondo de la Window
	wc.lpszClassName = (LPCWSTR)(className.c_str());	// Nombre de la clase

	RegisterClass(&wc);									// Registrando la clase
}
HWND Window::getHwnd() {
	return hWnd;

}