#include <windows.h>
#include <windowsx.h>
#include <stdint.h>

#include "mandelbrot.h"
#include "scomplex.h"

/* VARIABLES GLOBALES */

/* Por ahora lo dejamos como global */
static bool running_window;

static BITMAPINFO bitmapinfo;
static void		 *BitmapMemory;
static int		  BitmapWidth;
static int		  BitmapHeight;
static const int  BytesPerPixel = 4; // 4 Bytes = 32 bits = RGB 

static float low_r;
static float high_r;
static float low_i;
static float high_i;
static bool fractal_changed;
/* FIN VARIABLES GLOBALES */

/* CABECERAS DE FUNCIONES */

LRESULT CALLBACK WindowProc( HWND window, UINT message, WPARAM wparam,
			     LPARAM lparam );

void ResizeDIBSection( int, int );

void Win32UpdateWindow( HDC, RECT );

void renderFractal( float, float, float, float );

/* FIN CABECERAS DE FUNCIONES */

int CALLBACK
WinMain( HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow )
{
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = Instance;
	// WindowClass.hIcon;
	WindowClass.lpszClassName = "MandelBrotWindowClass";

	if ( RegisterClass( &WindowClass ) ) {
	HWND WindowHandle = 
	  CreateWindowEx( 0
			  , WindowClass.lpszClassName
			  , "Mandel Brot"
			  , WS_OVERLAPPEDWINDOW | WS_VISIBLE
			  , CW_USEDEFAULT
			  , CW_USEDEFAULT
			  , CW_USEDEFAULT
			  , CW_USEDEFAULT
			  , 0 
			  , 0 
			  , Instance
			  , 0 );
		if ( WindowHandle ) {
			running_window = true;
			MSG Message;

			low_r  = -2.5;
			high_r = 1;
			low_i  = -1;
			high_i = 1;

			fractal_changed = false;

			while( running_window ) { 

				while ( PeekMessage( &Message, 0, 0, 0, PM_REMOVE ) ) {
					if ( Message.message == WM_QUIT ) {
						running_window = false;
					}
					TranslateMessage( &Message ); 
					DispatchMessage ( &Message );
				}

				if ( !fractal_changed ) {
					renderFractal( low_r, high_r, low_i, high_i);

					OutputDebugStringA("Fractal renderizado\n");

					RECT window_rect; 
					GetClientRect( WindowHandle, &window_rect );

					HDC DeviceContext = GetDC( WindowHandle );

					Win32UpdateWindow( DeviceContext, window_rect );
					ReleaseDC( WindowHandle, DeviceContext );
					fractal_changed = true;
				}
			}  
		} else { }
	} else { }

	return 0;
}

LRESULT CALLBACK
 WindowProc( HWND window, UINT message, WPARAM wparam,
			     LPARAM lparam )
{
	LRESULT Result = 0;

	switch( message ) {
		case WM_LBUTTONDOWN:
		{
			POINT coord;

			GetCursorPos(&coord);

			LONG x = coord.x;
			LONG y = coord.y;

			double n_x0 = scalate( x, low_r, high_r, BitmapWidth);
			double n_y0 = scalate( y, low_i, high_i, BitmapHeight);

			low_r  = n_x0 - 0.2;
			high_r = n_x0 + 0.2;

			low_i  = n_y0 - 0.2;
			high_i = n_y0 + 0.2;

			fractal_changed = false;

		}break;
		case WM_DESTROY:
		{
			running_window = false;
			OutputDebugStringA("WM_DESTROY\n");
		}break;
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
			RECT ClientRect;
			GetClientRect( window, &ClientRect );

			int width  = ClientRect.right - ClientRect.left;
			int height = ClientRect.bottom - ClientRect.top;
			/* Obtain the new bitmap */
			ResizeDIBSection( width, height );
			fractal_changed = false;
		}break;
		case WM_CLOSE:
		{
			running_window = false;
			OutputDebugStringA("WM_CLOSE\n");
		}break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		}break;
		case WM_PAINT:
		{
			// OutputDebugStringA("WM_PAINT\n");
			PAINTSTRUCT Paint;

			// REF : https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint

			HDC DeviceContext = BeginPaint( window, &Paint );
			RECT window_rect;

			GetClientRect( window, &window_rect );

			int x	    = Paint.rcPaint.left;
			int y	    = Paint.rcPaint.top;
			int height	= Paint.rcPaint.bottom - y;
			int width 	= Paint.rcPaint.right  - x;
			
			/* Update the window with the bitmap stored */
			Win32UpdateWindow( DeviceContext, window_rect );

			EndPaint( window, &Paint );
		}
		default:
		{
			Result = DefWindowProc(window, message, wparam, lparam);
		}break;
	}

	return Result;
}

void
ResizeDIBSection( int width, int height )
{
	/* If already allocated, free memory */
	if ( BitmapMemory )
	{
		VirtualFree( BitmapMemory, 0, MEM_RELEASE );
	}
	
	BitmapWidth = width;
	BitmapHeight = height;

	/* msdn BITMAPINFO */

	bitmapinfo.bmiHeader.biSize 			= sizeof( bitmapinfo.bmiHeader );
	bitmapinfo.bmiHeader.biWidth 	        = BitmapWidth;
	bitmapinfo.bmiHeader.biHeight      		= -BitmapHeight;
	bitmapinfo.bmiHeader.biPlanes			= 1;
	bitmapinfo.bmiHeader.biBitCount  		= 32;
	bitmapinfo.bmiHeader.biCompression		= BI_RGB;
	
	/* BitmapMemory size = RGBsize * width * height */
	int BitmapMemorySize = BytesPerPixel * width * height;

	/* Buffer containing the bitmap */
	BitmapMemory = VirtualAlloc( 0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE );
}

void
Win32UpdateWindow( HDC DeviceContext, RECT WindowRect )
{
	int WindowWidth  = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;
	
	/* StretchDIBits copies the color data for a rectangle of pixels in a DIB, JPEG, or PNG image
	 * to the specified destination rectangle. If the rectangle is larger than the source rectangle
	 * this function stretches the rows and columns of color data to fit the destination rectangle.
	 * If the destination rectangle is smaller than the source rectangle, this function compresses
	 * the rows and columns by using the specified raster operation.
	 *
	 * REF : https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-stretchdibits
	 * */
	StretchDIBits( DeviceContext
			, 0, 0, BitmapWidth, BitmapHeight 	// Source
			, 0, 0, WindowWidth, WindowHeight 	// Destination
			, BitmapMemory						// Pointer to image bits
			, &bitmapinfo						// Pointer to BITMAPINFO
			, DIB_RGB_COLORS					// No compression, RGB
			, SRCCOPY );						// Copy
}

void renderFractal( float low_range, float high_range, float low_rangei, float high_rangei ) 
{
	int Pitch = BitmapWidth * BytesPerPixel;
	uint8_t*row = (uint8_t*)BitmapMemory;
	int MAX_ITER = 2 << 10;

	for( double Y = 0; Y < BitmapHeight; ++Y ) {

		uint32_t *Pixel = (uint32_t *)row;
		for ( double X = 0; X < BitmapWidth; ++X ) {
			double normalized_x = scalate( X, low_range, high_range, BitmapWidth );
			double normalized_y = scalate( Y, low_rangei, high_rangei, BitmapHeight );

			Complex normalized{normalized_x, normalized_y};

			unsigned int m_color = mandelbrot( normalized, MAX_ITER );

			/* Normalize iterations to be of range [0, 256)*/
			uint8_t t = m_color * 255 / MAX_ITER;

			/* In memory, RGB is stored as BGRxx, xx is padding, because of little ENDIANNESS
				Memory:   	BB GG RR pp                    
				Register: 	pp RR GG BB
				Pixel:    	32 bits
						
				Pixel : 00000000  00000000   00000000   00000000
					     Padding  Red << 16  Green << 8    Blue
			*/

			uint32_t pix = (( m_color * 2556) << 16 | ( m_color * 256 ) << 8 | m_color );

			/*
			uint8_t Red   = (uint8_t)(0x00FF0000 & pix);
			uint8_t Green = (uint8_t)(0x0000FF00 & pix);
			uint8_t Blue  = (uint8_t)pix;
			*/

			*Pixel++ = ( (uint8_t)(pix >> 16) |
							(uint8_t)(pix >> 8) | (uint8_t)pix );
		}
		row += Pitch;
	}
}
