#ifndef TIMER_H_
#define TIMER_H_

class Timer {
    public:

        static Timer& getInstance() {
            static Timer instance;
            return instance;
        }

        void incrementFrame();
        int getCurrentTime();
        int getCurrentFrame();

    private:

        Timer();
        Timer(Timer const&);
        void operator=(Timer const&);
        virtual ~Timer();

        int currentFrame;
        int framesInSecond;
        int currTime;
        int prevTime;
};

#endif /* TIMER_H_ */
