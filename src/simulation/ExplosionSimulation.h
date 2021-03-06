#ifndef EXPLOSIONSIMULATION_H_
#define EXPLOSIONSIMULATION_H_

#include "../utils/GeometryUtils.h"
#include "Vortex.h"

enum BoundDirection {
    X_DIR, Y_DIR, Z_DIR, NO_DIR
};

class ExplosionSimulation {
    public:
        ExplosionSimulation();
        virtual ~ExplosionSimulation();

        void tooglePlayback();
        void proceed();
        void setStartingConditions();

    private:
        int N;
        vect3f vxPrev, vyPrev, vzPrev, vx, vy, vz;
        vect3f densPrev, dens;
        float dt, viscosity, diffusionRate;
        int relaxationSteps;
        bool playbackIsOn;

        Vortex** vortices;

        int resX;

        void calculateVelocities();
        void calculateDensities();
        void setBoundaries(BoundDirection dir, vect3f x);
        void project(vect3f u, vect3f v, vect3f w, vect3f p, vect3f div);
        void advect(BoundDirection dir, vect3f d, vect3f d0, vect3f u, vect3f v, vect3f w);
        void diffuse(BoundDirection dir, float factor, vect3f x, vect3f x0);

        void allocate3D(vect3f &what);
        void deallocate3D(vect3f &what);

        void addSources();
        void addForces();
        void addTurbulences();
        void clearSpace();

        void clearVorticesIfNeeded();

        void createNewVortices();

        friend class ExplosionVisualization;

};

#endif /* EXPLOSIONSIMULATION_H_ */
