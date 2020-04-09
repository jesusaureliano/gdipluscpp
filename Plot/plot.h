#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
using namespace Gdiplus;

#define NUM_PTS 100

class Plot
{
	Point pts[NUM_PTS];
	int indice;
	Rect m_r;
public:
	Plot();
	~Plot();
	void show(Graphics&, Rect);
	void addPoint(Graphics&,Point);
	void drawPoints(Graphics &);
	
};

