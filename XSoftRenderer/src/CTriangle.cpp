/*
 * CTriangle.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: coder
 */

#include "CTriangle.h"
#include "CApp.h"
#include "XSoftwareRenderer.h"

CTriangle2D::CTriangle2D():
m_Bilinear(false) {
	// TODO Auto-generated constructor stub

}

CTriangle2D::~CTriangle2D() {
	// TODO Auto-generated destructor stub
}

CTriangle2D::CTriangle2D(float x0, float y0,
		float x1, float y1,
		float x2, float y2):
		m_Bilinear(false)
{
	AddVertex(x0, y0, 0.0);
	AddVertex(x1, y1, 0.0);
	AddVertex(x2, y2, 0.0);
}

void CTriangle2D::Render()
{
	if(m_Bilinear)
	{
		auto renderer = CApp::GetInstance()->GetRenderer();
		if(renderer)
		{
			renderer->FillPolygon(m_Vertexes, m_Color);
		}
	}
	else
	{
		CPolygon::Render();
	}
}

