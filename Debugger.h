/*
 * Debugger.h
 *
 *  Created on: 4 lut 2014
 *      Author: Przemo
 */

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

class Debugger {
public:

    static Debugger& getInstance() {
        static Debugger instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }

private:
//    const int MAX_GUI_LINES_NUMBER;

    Debugger();                   // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Debugger(Debugger const&);              // Don't Implement
    void operator=(Debugger const&); // Don't implement
	virtual ~Debugger(); //TODO potrzebny?

//    std::string guiTextLines[MAX_GUI_LINES_NUMBER];
};

#endif /* DEBUGGER_H_ */
