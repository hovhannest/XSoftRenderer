/*
 * CPolygon.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#include "CPolygon.h"
#include "CApp.h"
#include "XRenderer.h"

#include <iostream>

CPolygon::CPolygon() {
	// TODO Auto-generated constructor stub

}

CPolygon::~CPolygon() {
	// TODO Auto-generated destructor stub
}

void CPolygon::Release()
{
	CDummyObject::Release();
	for(std::vector<PointF*>::iterator it = m_Vertexes.begin(); it != m_Vertexes.end(); it++)
	{
		delete (*it);
	}
	m_Vertexes.clear();
}

void CPolygon::Update(float dt)
{
	//std::cout << "Update(" << dt << ");" << std::endl;
}

void CPolygon::Render()
{
	auto renderer = CApp::GetInstance()->GetRenderer();
	if(renderer)
	{
		renderer->FillPolygon(m_Vertexes, m_Color);
	}
}
