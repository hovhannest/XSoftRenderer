/*
 * CScene.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef CSCENE_H_
#define CSCENE_H_

#include "IGameObject.h"

#include <vector>

class CDummyObject;

class CScene : public IGameObject {
public:
	enum ObjectTypes
	{
		DummyObject = 0,
		PointObject,
		LineObject,
		PolygonObject
	};
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Release();

	virtual CDummyObject* CreateObject(unsigned int type, CDummyObject* parent = NULL);
	virtual void ReleaseObject(CDummyObject* obj);

	//const std::vector<PointF*> ToWorldCoordinates()

protected:
	std::vector<CDummyObject*> m_Objects;
	//std::vector<PointF*> m_tVertexBuffer;
};

#endif /* CSCENE_H_ */
