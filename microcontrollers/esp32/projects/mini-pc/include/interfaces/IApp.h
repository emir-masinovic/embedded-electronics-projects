#ifndef I_APP_H
#define I_APP_H

class IApp {
public:
    virtual void onEnter() = 0;
    virtual void onKeyEvent(char key) = 0;
    virtual void draw() = 0;
    virtual ~IApp() {}
};

#endif