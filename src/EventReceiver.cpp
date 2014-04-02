#include "EventReceiver.h"
bool EventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();
        switch(event.GUIEvent.EventType)
        {
            case gui::EGET_SCROLL_BAR_CHANGED:
                if (id == 3){
                    s32 pos = ((gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    model_shininess = pos;
                }
                break;
        }
    }
    return false;
}
