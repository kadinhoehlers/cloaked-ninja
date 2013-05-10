#include <xtl.h>


//--------------------------------------------------------------------------------------
// Globals
//-------------------------------------------------------------------------------------
IDirect3D9*						g_pD3D = NULL; // Used to create the D3DDevice
IDirect3DDevice9*				g_pd3dDevice = NULL; // the rendering device
D3DPRESENT_PARAMETERS			g_d3dpp;


// in gpu plugin
void PcsxSetD3D(IDirect3DDevice9* device);

void InitD3D() {
	// Create the D3D object.
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	// Set up the structure used to create the D3DDevice.
	XVIDEO_MODE VideoMode;
	ZeroMemory( &VideoMode, sizeof( VideoMode ) );
	XGetVideoMode( &VideoMode );
	BOOL bEnable720p = ( VideoMode.dwDisplayHeight >= 720 ) ? TRUE : FALSE;

	// Set up the structure used to create the D3DDevice.
	ZeroMemory( &g_d3dpp, sizeof( g_d3dpp ) );
	g_d3dpp.BackBufferWidth = bEnable720p ? 1280 : 640;
	g_d3dpp.BackBufferHeight = bEnable720p ? 720  : 480;
	g_d3dpp.BackBufferFormat =  ( D3DFORMAT )MAKESRGBFMT( D3DFMT_A8R8G8B8 );
	g_d3dpp.FrontBufferFormat = ( D3DFORMAT )MAKESRGBFMT( D3DFMT_LE_X8R8G8B8 );
	g_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_d3dpp.MultiSampleQuality = 0;
	g_d3dpp.BackBufferCount = 1;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	// Create the Direct3D device.
	g_pD3D->CreateDevice( 0, D3DDEVTYPE_HAL, NULL, D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_BUFFER_2_FRAMES,
		&g_d3dpp, &g_pd3dDevice );


	PcsxSetD3D(g_pd3dDevice);
}

