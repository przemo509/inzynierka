/*
 * Scene.h
 *
 *  Created on: 24 sty 2014
 *      Author: Przemo
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "Skybox.h"

class Scene {
public:
	Scene();
	virtual ~Scene();
	void draw();

private:
	Skybox skybox;
};

#endif /* SCENE_H_ */
