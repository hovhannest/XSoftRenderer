/*
 * IGameObject.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include <stdio.h>

class CScene;

class IGameObject {
public:
	IGameObject() : m_Scene(NULL) {};
	virtual ~IGameObject() {};

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	CScene* GetScene() const { return m_Scene; }

	// May be this function should be defined as protected
	// and used as friend in CScene
	void SetScene(CScene* scene) { m_Scene = scene;}
protected:
	CScene* m_Scene;
};

#endif /* IGAMEOBJECT_H_ */
