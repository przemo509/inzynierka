#ifndef SCENE_H_
#define SCENE_H_

#include "../simulation/ExplosionSimulation.h"
#include "../simulation/ExplosionVisualization.h"
#include "Camera.h"
#include "Skybox.h"

class Scene {
    public:
        Scene(Camera *camera);
        virtual ~Scene();
        void draw();

        void initFBO();

        void tooglePlayback();
        void proceed();
        void setStartingConditions();

    private:
        Skybox *skybox;
        ExplosionSimulation *simulation;
        ExplosionVisualization *visualization;
};

#endif /* SCENE_H_ */
