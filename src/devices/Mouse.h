#ifndef MOUSE_H_
#define MOUSE_H_

class Mouse {
    public:
        Mouse();
        virtual ~Mouse();

        void toggleButton(int button, int state);
        bool isLeftButtonPressed() const;
        bool isRightButtonPressed() const;

    private:
        bool leftButtonPressed;
        bool rightButtonPressed;
};

#endif /* MOUSE_H_ */
