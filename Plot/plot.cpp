#include "plot.h"

#include <algorithm>

Plot::Plot()
{
	
}

Plot::~Plot()
{
}

void Plot::show(Graphics & graphics, Rect rect){
	
	rect.Inflate(-50,-50);
	m_r = rect;
	Pen pen(Color::White,2);
	graphics.DrawRectangle(&pen, rect);
	
	int x0 = rect.GetLeft();
	int y0 = rect.GetBottom();
	int wr = rect.GetRight()-rect.GetLeft();
	int hr = rect.GetTop()-rect.GetBottom();
	
	graphics.TranslateTransform(x0,y0+hr/2);
	graphics.ScaleTransform(1,-1);
		
	graphics.DrawLine(&pen,Point(0,0),Point(wr,0));
	//ticks
	graphics.DrawLine(&pen,wr/2,-10,wr/2,10);
	graphics.DrawLine(&pen,wr/4,-5,wr/4,5);
	graphics.DrawLine(&pen,3*wr/4,-5,3*wr/4,5);
	
	pen.SetDashStyle(DashStyleDot);
	pen.SetWidth(1);
	// lineas punteadas verticales
	graphics.DrawLine(&pen,wr/2,-hr/2,wr/2,hr/2);
	graphics.DrawLine(&pen,wr/4,-hr/2,wr/4,hr/2);
	graphics.DrawLine(&pen,3*wr/4,-hr/2,3*wr/4,hr/2);
	// lineas punteadas horizontales
	graphics.DrawLine(&pen,0,hr/4,wr,hr/4);
	graphics.DrawLine(&pen,0,-hr/4,wr,-hr/4);
	
	// reasignar los puntos de las coordenadas x para ajustar
	// al redimensionamiento de la ventana
	for(int i = 1; i < NUM_PTS; i++){
		pts[i].X = i*wr/(NUM_PTS-1);
	}
	
}

void Plot::addPoint(Graphics & graphics, Point pt){
	
	Matrix m;
	graphics.GetTransform(&m);
	
	Point origen(0,0);
	m.TransformPoints(&origen);
	
	Point ptr = pt - origen;
	m.TransformPoints(&ptr);
	ptr = ptr - origen;
	
	int d0 = abs(pts[0].X-ptr.X);
	int i = 1;
	while(abs(pts[i].X-ptr.X) < d0 && i < NUM_PTS){
		d0 = abs(pts[i].X-ptr.X);
		i++;
	}
	
	pts[i-1].Y = ptr.Y; 
	
}

void Plot::drawPoints(Graphics & graphics){
	
	GraphicsPath gpath;
	gpath.AddRectangle(m_r);
	
	Region region(&gpath);
	
	Matrix m;
	graphics.GetTransform(&m);
	graphics.ResetTransform();	
	graphics.SetClip(&region);
	graphics.SetTransform(&m);
	
	Pen pen(Color::Green,2);	
	for(int i = 0; i < (NUM_PTS-1); i++){
		graphics.DrawLine(&pen,pts[i],pts[i+1]);
	}
}

