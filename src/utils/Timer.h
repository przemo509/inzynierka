/*
 * Timer.h
 *
 *  Created on: 4 lut 2014
 *      Author: Przemo
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:

    static Timer& getInstance() {
        static Timer instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }

    void incrementFrame();
    int getCurrentTime();
    int getCurrentFrame();

private:

    Timer();                   // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Timer(Timer const&);              // Don't Implement
    void operator=(Timer const&); // Don't implement
	virtual ~Timer(); //TODO potrzebny?

	long framesInSecond;
	long allFrames;
	int currTime;
	int prevTime;
};

#endif /* TIMER_H_ */
