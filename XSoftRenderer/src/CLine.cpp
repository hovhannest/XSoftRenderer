/*
 * CLine.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#include "CLine.h"
#include "CApp.h"
#include "XRenderer.h"

CLine::CLine() {
	// TODO Auto-generated constructor stub

}

CLine::~CLine() {
	// TODO Auto-generated destructor stub
}

void CLine::Render()
{
	auto renderer = CApp::GetInstance()->GetRenderer();
	if(renderer)
	{
		renderer->DrowLine(m_Start, m_End, m_Color);
	}
}

