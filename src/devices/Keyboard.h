#ifndef KEYBOARD_H_
#define KEYBOARD_H_

class Keyboard {
    public:
        Keyboard();
        virtual ~Keyboard();

        bool isAsciiKeyPressed(unsigned char key);
        void asciiKeyDown(unsigned char key);
        void asciiKeyUp(unsigned char key);

    private:
        bool asciiKeys[256];
};

#endif /* KEYBOARD_H_ */
