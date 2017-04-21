/*
 * CScene.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#include "CScene.h"
#include "CPoint.h"
#include "CLine.h"
#include "CPolygon.h"

CScene::CScene() {
	// TODO Auto-generated constructor stub

}

CScene::~CScene() {
	// TODO Auto-generated destructor stub
}

void CScene::Init()
{
	for(int i = 50; i < 150; i++)
	{
		CPoint* point = (CPoint*)CreateObject(PointObject);
		point->SetPosition(i, 10);
	}


	CPolygon* poly = (CPolygon*)CreateObject(PolygonObject);
	poly->AddVertex(60, 60);
	poly->AddVertex(160, 60);
	poly->AddVertex(90, 160);
	poly->SetColor(0, 255, 0);

	poly = (CPolygon*)CreateObject(PolygonObject);
	poly->AddVertex(60, 60);
	poly->AddVertex(160, 60);
	poly->AddVertex(190, 20);
	poly->SetColor(0, 255, 0);
	poly->SetColor(0, 0, 255);

	CLine* line = (CLine*)CreateObject(LineObject);
	line->SetStart(60, 90);
	line->SetEnd(260, 60);
	line->SetColor(255, 0, 0);
	line = (CLine*)CreateObject(LineObject);
	line->SetStart(260, 60);
	line->SetEnd(160, 260);
	line->SetColor(255, 0, 0);
	line = (CLine*)CreateObject(LineObject);
	line->SetStart(160, 260);
	line->SetEnd(60, 90);
	line->SetColor(255, 0, 0);
}

void CScene::Update(float dt)
{
	for(std::vector<CDummyObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it ++)
	{
		(*it)->Update(dt);
	}
}

void CScene::Render()
{
	for(std::vector<CDummyObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it ++)
	{
		(*it)->Render();
	}
}

void CScene::Release()
{
	for(std::vector<CDummyObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it ++)
	{
		(*it)->Release();
		delete (*it);
	}
	m_Objects.clear();
}

CDummyObject* CScene::CreateObject(unsigned int type, CDummyObject* parent /*= NULL*/)
{
	// TODO: parents
	// TODO: objectsCash instead of new/delete
	CDummyObject* obj = NULL;
	switch(type)
	{
	case DummyObject:
	{
		obj = new CDummyObject();
		obj->SetScene(this);
		break;
	}
	case PointObject:
	{
		obj = new CPoint();
		obj->SetScene(this);
		break;
	}
	case LineObject:
	{
		obj = new CLine();
		obj->SetScene(this);
		break;
	}
	case PolygonObject:
	{
		obj = new CPolygon();
		obj->SetScene(this);
		break;
	}
	default:
	{
		break;
	}
	}
	if(obj)
	{
		obj->Init();
		m_Objects.push_back(obj);
	}
	return obj;
}

void CScene::ReleaseObject(CDummyObject* obj)
{
	// TODO: find in m_Objects and delete, then remove from vector,
	// Or mark as unused to use next time when
	// CreateObject is called with the type of this obj
}


