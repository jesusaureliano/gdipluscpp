#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "plot.h"

int cxsize, cysize;
int xmouse, ymouse;
bool moviendose;

CPlot plot;


VOID OnPaint(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, cxsize, cysize);

	SelectObject(hMemDC,hBitmap);
	
	Graphics graphics(hMemDC);
	plot.Draw(graphics);
	
	Pen lapizVerde(Color::Green);
	
	Point ptmouse(xmouse,ymouse);
	plot.CheckMouse(graphics,ptmouse);
	
	//1er Transformación
	Matrix m1, m2;
	graphics.TranslateTransform(400,300);
	graphics.ScaleTransform(1,-1);
	graphics.GetTransform(&m1);
	
	//m.Invert();
	const Point origen(0,0);
	Point origen1(0,0);
	
	m1.TransformPoints(&origen1);
	Point ptr1 = ptmouse-origen1;
//	m1.Invert();
    m1.TransformPoints(&ptr1);
	ptr1 = ptr1 - origen1;
	
	plot.Draw(graphics);
	plot.CheckMouse(graphics,ptr1);
	
	
	//2a Transformación
	graphics.TranslateTransform(0,-300);
	graphics.GetTransform(&m2);
	
	Point origen2(0,0);
	m2.TransformPoints(&origen2);
	
	Point ptr2 = ptmouse - origen2;
	m2.TransformPoints(&ptr2);
	ptr2 = ptr2 - origen2;
	
	plot.Draw(graphics);
	plot.CheckMouse(graphics,ptr2);

	BitBlt(hdc,0,0,cxsize,cysize,hMemDC,0,0,SRCCOPY);

	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   moviendose = false;
   
   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = NULL;//(HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Getting Started"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
      
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);
   
   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;
   
   switch(message)
   {
	case WM_ERASEBKGND:
		return 0;
	case WM_SIZE:
		cxsize = LOWORD(lParam);
		cysize = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		moviendose = !moviendose;
		return 0;
	case WM_MOUSEMOVE:
		if(moviendose){
			xmouse = LOWORD(lParam);
			ymouse = HIWORD(lParam);
			InvalidateRect(hWnd,NULL,TRUE);
		}
		
		return 0;
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc