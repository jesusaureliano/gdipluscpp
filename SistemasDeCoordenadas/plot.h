#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;

class CPlot
{
	Point pts[300];
	Rect rect;
public:
	CPlot();
	~CPlot();
	void Draw(Graphics &);
	void CheckMouse(Graphics &, Point);
};

