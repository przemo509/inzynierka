/*
 * Scene.cpp
 *
 *  Created on: 24 sty 2014
 *      Author: Przemo
 */

#include "Scene.h"

Scene::Scene() {
	// TODO Auto-generated constructor stub

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::draw() {
	skybox.draw(); //skybox na ko�cu, �eby niepotrzebnie nie rysowa� jego zas�oni�tych fragment�w
}
