#ifndef EVENT_RECEIVER_H_
#define EVENT_RECEIVER_H_
#include "BasicShaderCallBack.h"

struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
};


class EventReceiver : public IEventReceiver
{
public:
    EventReceiver(SAppContext & context) : Context(context) { }
    virtual bool OnEvent(const SEvent& event);

private:
    SAppContext & Context;
};

#endif
