#ifndef BASIC_SHADER_CB_H_
#define BASIC_SHADER_CB_H_
#include <irrlicht/irrlicht.h>
using namespace irr;

extern f32 model_shininess;

class BasicShaderCallBack : public video::IShaderConstantSetCallBack{
private:
    IrrlichtDevice* device;
    gui::IGUIScrollBar* scrollbar;
public:
    BasicShaderCallBack(IrrlichtDevice* irrDevice);
    virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);
};
#endif
