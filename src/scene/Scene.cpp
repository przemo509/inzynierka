/*
 * Scene.cpp
 *
 *  Created on: 24 sty 2014
 *      Author: Przemo
 */

#include "Scene.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::draw(Camera *camera) {

    skybox.draw();
    visualization.draw(camera, &simulation);
}
