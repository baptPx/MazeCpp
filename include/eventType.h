#ifndef EVENTTYPE_H
#define EVENTTYPE_H
#include <irrlicht.h>
#include <iostream>
#include <cstdlib>


class eventType : public irr::IEventReceiver
{

    public :

    eventType();
    virtual bool OnEvent(const irr::SEvent &event);
    bool getG();
    bool getF();

    private:
    bool keyPressed;
    bool g_Pressed,f_Pressed;



};

#endif // EVENTTYPE_H
