#include "ExplosionVisualization.h"
#include "../utils/OpenGLInclude.h"
#include "../utils/GlutUtils.h"
#include "../utils/Logger.h"
#include "../utils/Config.h"
#include "../utils/ColorUtils.h"
#include "../utils/MathUtils.h"

ExplosionVisualization::ExplosionVisualization(ExplosionSimulation *simulation, Camera *camera) :
    simulation(simulation),
    camera(camera),
    gauss {
        {0.00f, 0.03f, 0.08f, 0.12f, 0.08f, 0.03f, 0.00f},
        {0.03f, 0.18f, 0.43f, 0.55f, 0.43f, 0.18f, 0.03f},
        {0.09f, 0.43f, 0.79f, 0.91f, 0.79f, 0.43f, 0.09f},
        {0.12f, 0.55f, 0.91f, 0.98f, 0.91f, 0.55f, 0.12f},
        {0.09f, 0.43f, 0.79f, 0.91f, 0.79f, 0.43f, 0.09f},
        {0.03f, 0.18f, 0.43f, 0.55f, 0.43f, 0.18f, 0.03f},
        {0.00f, 0.03f, 0.08f, 0.12f, 0.08f, 0.03f, 0.00f}} {

    size = 20.0f;
    elementSize = size / simulation->N;
    origin = Point(0.0f, 0.1f, 0.0f);
    cornersCount = 8;
    corners = new Point[cornersCount];
    corners[0] = Point(origin.x - size / 2, origin.y, origin.z - size / 2);
    corners[1] = Point(origin.x - size / 2, origin.y, origin.z + size / 2);
    corners[2] = Point(origin.x + size / 2, origin.y, origin.z - size / 2);
    corners[3] = Point(origin.x + size / 2, origin.y, origin.z + size / 2);
    corners[4] = Point(origin.x - size / 2, origin.y + size, origin.z - size / 2);
    corners[5] = Point(origin.x - size / 2, origin.y + size, origin.z + size / 2);
    corners[6] = Point(origin.x + size / 2, origin.y + size, origin.z - size / 2);
    corners[7] = Point(origin.x + size / 2, origin.y + size, origin.z + size / 2);
    moveToStartCorner = Vector(origin, corners[1]);

    textureResolution = Config::getInstance()->textureResolution;
    render = new float*[textureResolution];
    for (int i = 0; i < textureResolution; ++i) {
        render[i] = new float[textureResolution];
    }

    tmpColor = new float[4];
}

// musi być po glewInit(), czyli nie może być w konstruktorze
void ExplosionVisualization::initFBO() {
    glGenFramebuffers(1, &frameBufferID);
    glGenTextures(1, &textureID);
    glGenRenderbuffers(1, &depthRenderBufferID);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureResolution, textureResolution, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, textureResolution, textureResolution);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBufferID);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ExplosionVisualization::~ExplosionVisualization() {
    delete[] corners;

    for (int i = 0; i < textureResolution; ++i) {
        delete[] render[i];
    }
    delete[] render;

    delete[] tmpColor;

    glDeleteTextures(1, &textureID);
    glDeleteRenderbuffers(1, &depthRenderBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &frameBufferID);
}

void ExplosionVisualization::draw() {
    drawDomain();
    drawVortices();

    int closest = getCornerClosestToCamera();

    // wyznaczamy równanie płaszczyzny przechodzącej przez najbliższy narożnik
    Vector planeNormal = camera->direction.flip();
    Plane plane = Plane(planeNormal, corners[closest]);

    Point *intersections = new Point[cornersCount];
    for (int i = 0; i < cornersCount; ++i) {
        intersections[i] = plane.intersection(camera->position, Vector(camera->position, corners[i]));
    }

    Vector up = getUpDirection(closest, plane);
    Vector right = planeNormal.crossProduct(up);
    right.normalize();

    int mostTop, mostBottom, mostLeft, mostRight;
    float distTop, distBottom, distLeft, distRight;
    mostTop = mostBottom = mostLeft = mostRight = closest;
    distTop = distBottom = distLeft = distRight = 0.0f;
    for (int i = 0; i < cornersCount; ++i) {
        if (i == closest) {
            continue;
        }
        Vector v = Vector(corners[closest], intersections[i]);
        float distVertical = up.dotProduct(v);
        float distHorizontal = right.dotProduct(v);
        if (distVertical > distTop) {
            distTop = distVertical;
            mostTop = i;
        }
        if (distVertical < distBottom) {
            distBottom = distVertical;
            mostBottom = i;
        }
        if (distHorizontal > distRight) {
            distRight = distHorizontal;
            mostRight = i;
        }
        if (distHorizontal < distLeft) {
            distLeft = distHorizontal;
            mostLeft = i;
        }
    }

    Point leftBottom = intersections[mostBottom];
    if (mostLeft != mostBottom) {
        float dx = -right.dotProduct(Vector(intersections[mostBottom], intersections[mostLeft]));
        leftBottom.x -= right.x * dx;
        leftBottom.y -= right.y * dx;
        leftBottom.z -= right.z * dx;
    }
    Point rightBottom = intersections[mostBottom];
    if (mostRight != mostBottom) {
        float dx = -right.dotProduct(Vector(intersections[mostBottom], intersections[mostRight]));
        rightBottom.x -= right.x * dx;
        rightBottom.y -= right.y * dx;
        rightBottom.z -= right.z * dx;
    }
    Point leftTop = intersections[mostTop];
    if (mostLeft != mostTop) {
        float dx = -right.dotProduct(Vector(intersections[mostTop], intersections[mostLeft]));
        leftTop.x -= right.x * dx;
        leftTop.y -= right.y * dx;
        leftTop.z -= right.z * dx;
    }
    Point rightTop = intersections[mostTop];
    if (mostRight != mostTop) {
        float dx = -right.dotProduct(Vector(intersections[mostTop], intersections[mostRight]));
        rightTop.x -= right.x * dx;
        rightTop.y -= right.y * dx;
        rightTop.z -= right.z * dx;
    }

    float width = right.dotProduct(Vector(leftBottom, rightBottom));
    float height = up.dotProduct(Vector(leftBottom, leftTop));
    float difference = fabs(width - height);
    if (width > height) {
        leftTop = up.translate(leftTop, difference);
        rightTop = up.translate(rightTop, difference);
        height += difference;
    } else if (width < height) {
        rightBottom = right.translate(rightBottom, difference);
        rightTop = right.translate(rightTop, difference);
        width += difference;
    }

    if(Config::getInstance()->drawSplattingPlane) {
        glColor3ub(0, 255, 255);
        glBegin(GL_LINES);
        drawLine(leftBottom, rightBottom);
        drawLine(rightBottom, rightTop);
        drawLine(rightTop, leftTop);
        drawLine(leftTop, leftBottom);
        glEnd();
    }

    for (int j = 0; j < textureResolution; ++j) {
        for (int i = 0; i < textureResolution; ++i) {
            render[i][j] = 0.0f;
        }
    }
    float renderElementSize = width / textureResolution;

    for (int k = 1; k <= simulation->N; ++k) {
        for (int j = 1; j <= simulation->N; ++j) {
            for (int i = 1; i <= simulation->N; ++i) {
                float densValue = simulation->dens[i][j][k] / (Config::getInstance()->splattingSuperSampling ? 3 : 1.5);
                if (densValue <= 0) {
                    continue;
                }
                Point densityPoint = moveToStartCorner.translate(Point(elementSize * i, elementSize * j, -elementSize * k));
                Vector toCamera = Vector(densityPoint, camera->position);
                Point intersection = plane.intersection(densityPoint, toCamera);
                Vector toIntersection = Vector(leftBottom, intersection);
                float dx = right.dotProduct(toIntersection) * randAroundFloat(1.0, Config::getInstance()->splattingDislocation);
                float dy = up.dotProduct(toIntersection) * randAroundFloat(1.0, Config::getInstance()->splattingDislocation);
                int renderX = dx / renderElementSize;
                int renderY = dy / renderElementSize;
                float distance = toCamera.length();
                float baseValue = densValue / distance * Config::getInstance()->distanceFactor;
                for (int gj = 0; gj < gaussSize; ++gj) {
                    for (int gi = 0; gi < gaussSize; ++gi) {
                        int x = renderX - gi - gaussSize / 2;
                        int y = renderY - gj - gaussSize / 2;
                        if (x >= 0 && x < textureResolution && y >= 0 && y < textureResolution) {
                            render[x][y] += baseValue * gauss[gi][gj];
                        }
                    }
                }

                if(Config::getInstance()->splattingSuperSampling) {
                    densValue = (
                            simulation->dens[i  ][j  ][k  ] +
                            simulation->dens[i  ][j  ][k+1] +
                            simulation->dens[i  ][j+1][k  ] +
                            simulation->dens[i  ][j+1][k+1] +
                            simulation->dens[i+1][j  ][k  ] +
                            simulation->dens[i+1][j  ][k+1] +
                            simulation->dens[i+1][j+1][k  ] +
                            simulation->dens[i+1][j+1][k+1]) / 24;
                    if (densValue <= 0) {
                        continue;
                    }
                    densityPoint = moveToStartCorner.translate(Point(elementSize * (1.0*i+0.5), elementSize * (1.0*j+0.5), -elementSize * (1.0*k+0.5)));
                    toCamera = Vector(densityPoint, camera->position);
                    intersection = plane.intersection(densityPoint, toCamera);
                    toIntersection = Vector(leftBottom, intersection);
                    dx = right.dotProduct(toIntersection) * randAroundFloat(1.0, Config::getInstance()->splattingDislocation);
                    dy = up.dotProduct(toIntersection) * randAroundFloat(1.0, Config::getInstance()->splattingDislocation);
                    renderX = dx / renderElementSize;
                    renderY = dy / renderElementSize;
                    distance = toCamera.length();
                    baseValue = densValue / distance * Config::getInstance()->distanceFactor;
                    for (int gj = 0; gj < gaussSize; ++gj) {
                        for (int gi = 0; gi < gaussSize; ++gi) {
                            int x = renderX - gi - gaussSize / 2;
                            int y = renderY - gj - gaussSize / 2;
                            if (x >= 0 && x < textureResolution && y >= 0 && y < textureResolution) {
                                render[x][y] += baseValue * gauss[gi][gj];
                            }
                        }
                    }
                }
            }
        }
    }

    drawRenderToTexture();
    drawTextureOnScreen(leftBottom, rightBottom, rightTop, leftTop);

    delete[] intersections;

}

void ExplosionVisualization::drawTextureOnScreen(const Point& leftBottom, const Point& rightBottom, const Point& rightTop, const Point& leftTop) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor4ub(255, 255, 255, 0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    drawPoint(leftBottom);
    glTexCoord2f(1.0f, 0.0f);
    drawPoint(rightBottom);
    glTexCoord2f(1.0f, 1.0f);
    drawPoint(rightTop);
    glTexCoord2f(0.0f, 1.0f);
    drawPoint(leftTop);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void ExplosionVisualization::drawRenderToTexture() {
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    GLint savedViewport[4];
    glGetIntegerv(GL_VIEWPORT, savedViewport);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glViewport(0, 0, textureResolution, textureResolution);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glOrtho(0.0, textureResolution, 0.0, textureResolution, -1.0, 1.0);
    glBegin(GL_POINTS);
    for (int j = 0; j < textureResolution; ++j) {
        for (int i = 0; i < textureResolution; ++i) {
            calculateSmokeColor(tmpColor, render[i][j]);
            glColor4fv(tmpColor);
            glVertex2i(i, j);
        }
    }
    glEnd();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(savedViewport[0], savedViewport[1], savedViewport[2], savedViewport[3]);
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void ExplosionVisualization::drawVortices() {
    if (!Config::getInstance()->drawVortices) {
        return;
    }

    for(int i = 0; i < Config::getInstance()->vorticesCount; ++i) {
        Vortex *v = simulation->vortices[i];
        glPushMatrix();
        {
            glColor3ub(v->isActive() ? 0 : 255, v->isActive() ? 255 : 0, 0);
            Point p = moveToStartCorner.translate(v->position);
            glTranslatef(v->position.x/2 - Config::getInstance()->mainSourceCenterX+20,
                         v->position.y-5,
                         -(v->position.z - Config::getInstance()->mainSourceCenterZ));
            glutWireSphere(elementSize * v->radius/10, 10, 10);
        }
        glPopMatrix();
    }
}

void ExplosionVisualization::drawDomain() {
    if (!Config::getInstance()->drawDomain) {
        return;
    }

    glBegin(GL_LINES);
    glColor3ub(0, 255, 0); // na zielono
    for (int i = 0; i < cornersCount; ++i) {
        for (int j = 0; j < cornersCount; ++j) {
            float xi = corners[i].x;
            float yi = corners[i].y;
            float zi = corners[i].z;
            float xj = corners[j].x;
            float yj = corners[j].y;
            float zj = corners[j].z;
            int differences = (xi == xj ? 0 : 1) + (yi == yj ? 0 : 1) + (zi == zj ? 0 : 1);
            if (differences == 1) {
                drawPoint(corners[i]);
                drawPoint(corners[j]);
            }
        }
    }
    glEnd();
}

/*
 * Zwraca indeks wierzchołka kostki znajdującego się najbliżej kamery.
 */
int ExplosionVisualization::getCornerClosestToCamera() {
    int closest = 0;
    float closestDist = camera->position.distance(corners[0]);

    for (int i = 1; i < cornersCount; ++i) {
        float dist = camera->position.distance(corners[i]);
        if (dist < closestDist) {
            closest = i;
            closestDist = dist;
        }
    }

    return closest;
}

/**
 *
 */
Vector ExplosionVisualization::getUpDirection(int closest, Plane& plane) {
    Point aboveClosest = Vector(0.0, 10.0, 0.0).translate(corners[closest]);
    Point aboveClosestThrewOnPlane = plane.intersection(aboveClosest, camera->direction);
    Vector up = Vector(corners[closest], aboveClosestThrewOnPlane);
    up.normalize();
    return up;
}
