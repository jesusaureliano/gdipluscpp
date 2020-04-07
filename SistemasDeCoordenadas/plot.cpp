#include "plot.h"

CPlot::CPlot():rect(0,0,300,200)
{
	double x,y;
	x = 0;
	for(int i =0; i < 300;i++){
		x = (double)i/299*10;  // x de cero a 10; (e.g., segundos)
		y =  100 + 100*sin(2*M_PI/5.0*x); // 2 períodos (pixeles)
		pts[i] = Point(i,y);
	}
}

CPlot::~CPlot()
{
}

void CPlot::Draw(Graphics & graphics){
	
	Pen pen(Color::Red,2);
	Pen wpen(Color::White,2);
	Pen dpen(Color::White);
	dpen.SetDashStyle(DashStyleDash);
	
	graphics.DrawRectangle(&pen,rect);
	graphics.DrawLine(&wpen,0,100,300,100);
	graphics.DrawLine(&dpen,0,50,300,50);
	graphics.DrawLine(&dpen,0,150,300,150);
	graphics.DrawLine(&dpen,100,0,100,200);
	graphics.DrawLine(&dpen,200,0,200,200);
	graphics.DrawLines(&wpen,pts,300);
}

void CPlot::CheckMouse(Graphics & graphics, Point pt){
	SolidBrush br(Color::White);
	if(rect.Contains(pt)){
		graphics.FillEllipse(&br,Rect(pt-Point(10,10),Size(20,20)));
	}
}
