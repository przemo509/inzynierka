/*
 * Debugger.h
 *
 *  Created on: 4 lut 2014
 *      Author: Przemo
 */

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include <string>
#include <vector>

class Logger {
    public:

        static Logger& getInstance() {
            static Logger instance; // Guaranteed to be destroyed.
                                    // Instantiated on first use.
            return instance;
        }

        void printOnScreen();
        void addLineToScreen(int lineNumber, char* format, ...);

    private:

        Logger();                   // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        Logger(Logger const&);              // Don't Implement
        void operator=(Logger const&); // Don't implement
        virtual ~Logger(); //TODO potrzebny?

        std::vector<std::string> guiTextLines;
};

#endif /* DEBUGGER_H_ */
