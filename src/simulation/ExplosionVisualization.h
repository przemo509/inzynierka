#ifndef EXPLOSIONVISUALIZATION_H_
#define EXPLOSIONVISUALIZATION_H_

#include "../utils/OpenGLInclude.h"
#include "ExplosionSimulation.h"
#include "../scene/Camera.h"
#include "../utils/GeometryUtils.h"

class ExplosionVisualization {
    public:
        ExplosionVisualization(ExplosionSimulation *simulation, Camera *camera);
        virtual ~ExplosionVisualization();

        void draw();
        void initFBO();

    private:
        ExplosionSimulation *simulation;
        Camera *camera;

        Point origin;
        float size;
        float elementSize;
        int cornersCount;
        Point *corners;
        Vector moveToStartCorner;

        int textureResolution;
        float **render;
        GLuint textureID, frameBufferID, depthRenderBufferID;

        void drawVortices();
        void drawDomain();
        int getCornerClosestToCamera();
        Vector getUpDirection(int closest, Plane& plane);

        void drawTextureOnScreen(const Point& leftBottom, const Point& rightBottom, const Point& rightTop, const Point& leftTop);

        void drawRenderToTexture();

        static const int gaussSize = 7;
        float gauss[gaussSize][gaussSize];

        float * tmpColor;
};

/*
 * GAUSS 11x11
 {
 {0.00f, 0.01f, 0.02f, 0.04f, 0.07f, 0.08f, 0.07f, 0.04f, 0.02f, 0.01f, 0.00f},
 {0.01f, 0.03f, 0.09f, 0.17f, 0.25f, 0.28f, 0.25f, 0.17f, 0.09f, 0.03f, 0.01f},
 {0.02f, 0.09f, 0.23f, 0.40f, 0.54f, 0.59f, 0.54f, 0.40f, 0.23f, 0.09f, 0.02f},
 {0.05f, 0.17f, 0.40f, 0.64f, 0.79f, 0.84f, 0.79f, 0.64f, 0.40f, 0.17f, 0.05f},
 {0.07f, 0.25f, 0.54f, 0.79f, 0.93f, 0.96f, 0.93f, 0.79f, 0.54f, 0.25f, 0.07f},
 {0.08f, 0.28f, 0.59f, 0.84f, 0.96f, 0.98f, 0.96f, 0.84f, 0.59f, 0.28f, 0.08f},
 {0.07f, 0.25f, 0.54f, 0.79f, 0.93f, 0.96f, 0.93f, 0.79f, 0.54f, 0.25f, 0.07f},
 {0.05f, 0.17f, 0.40f, 0.64f, 0.79f, 0.84f, 0.79f, 0.64f, 0.40f, 0.17f, 0.05f},
 {0.02f, 0.09f, 0.23f, 0.40f, 0.54f, 0.59f, 0.54f, 0.40f, 0.23f, 0.09f, 0.02f},
 {0.01f, 0.03f, 0.09f, 0.17f, 0.25f, 0.28f, 0.25f, 0.17f, 0.09f, 0.03f, 0.01f},
 {0.00f, 0.01f, 0.02f, 0.04f, 0.07f, 0.08f, 0.07f, 0.04f, 0.02f, 0.01f, 0.00f}
 }
 */

#endif /* EXPLOSIONVISUALIZATION_H_ */
