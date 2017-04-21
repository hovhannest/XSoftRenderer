/*
 * CPoint.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#include "CPoint.h"
#include "Utils.h"
#include "CApp.h"
#include "XRenderer.h"

CPoint::CPoint() {
	// TODO Auto-generated constructor stub

}

CPoint::~CPoint() {
	// TODO Auto-generated destructor stub
}

void CPoint::Render()
{
	auto renderer = CApp::GetInstance()->GetRenderer();
	if(renderer)
	{
		renderer->DrowPoint(m_Position, m_Color);
	}
}
