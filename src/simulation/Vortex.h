#ifndef SIMULATION_VORTEX_H_
#define SIMULATION_VORTEX_H_

#include "../utils/GeometryUtils.h"

class Vortex {
    public:
        Vortex(int x, int y, int z, int startFrame);
        virtual ~Vortex();
        bool isActive();
        void apply(vect3f vx, vect3f vy, vect3f vz, int N);
    private:
        Point position;
        Point startingPosition;
        Vector direction; // rotacja + prędkość
        int radius;
        int startFrame;
        int lifeFrames;

        friend class ExplosionVisualization;
};

#endif /* SIMULATION_VORTEX_H_ */
