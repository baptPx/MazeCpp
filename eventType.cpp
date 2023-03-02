#include "include/eventType.h"

using namespace std;

eventType::eventType()
{}
bool eventType::OnEvent(const irr::SEvent &event)
{
    if(event.EventType == irr::EET_KEY_INPUT_EVENT && (event.KeyInput.Key == irr::KEY_KEY_F || event.KeyInput.Key == irr::KEY_KEY_G))
    {
        if(event.KeyInput.Key == irr::KEY_KEY_F)
            f_Pressed = true;
         else f_Pressed = false;
         if(event.KeyInput.Key == irr::KEY_KEY_G)
            g_Pressed = true;
         else g_Pressed = false;
        return true;
    }
    return false;
}
bool eventType::getF()
{   return f_Pressed; }
bool eventType::getG()
{   return g_Pressed; }


