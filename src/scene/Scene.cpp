#include "Scene.h"

Scene::Scene(Camera *camera) {
    skybox = new Skybox();
    simulation = new ExplosionSimulation();
    visualization = new ExplosionVisualization(simulation, camera);
}

Scene::~Scene() {
    delete skybox;
    delete simulation;
    delete visualization;
}

void Scene::initFBO() {
    visualization->initFBO();
}

void Scene::tooglePlayback() {
    simulation->tooglePlayback();
}

void Scene::proceed() {
    simulation->proceed();
}

void Scene::setStartingConditions() {
    simulation->setStartingConditions();
}

void Scene::draw() {
    skybox->draw();
    visualization->draw();
}
