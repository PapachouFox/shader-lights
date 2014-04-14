#include <irrlicht/irrlicht.h>
#include <iostream>
#include "BasicShaderCallBack.h"
#include "EventReceiver.h"
#include "CustomNode.h"
using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv){
    IrrlichtDevice* device =
            createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false, false, true, 0);
    if (!device) return 1;
    else device->setWindowCaption(L"Shaders and lights - Irrlicht");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

    smgr->addCameraSceneNode(0, core::vector3df(0,0,-200), core::vector3df(0,0,0));
    scene::ILightSceneNode* light = smgr->addLightSceneNode(0, core::vector3df(500, 0, -100), video::SColorf(), 0.f);

    //shaders loading
    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
    s32 defaultShader = 0;

    BasicShaderCallBack* mc = new BasicShaderCallBack(device);
    if (gpu){
       defaultShader = gpu->addHighLevelShaderMaterialFromFiles(
                   "../shaders/light.vert",
                   "../shaders/default.frag",
                   mc, video::EMT_SOLID, 0);
    }
    mc->drop();

    CustomNode* planet = new CustomNode(smgr, driver);
    planet->SetMaterial(defaultShader);

    //scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(core::vector3df(), 200.f, 0.001f, core::vector3df(0.f, 1.f, 0.f));
    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.f, 0.1f, 0.f));
    if(anim){
        //smgr->getActiveCamera()->addAnimator(anim);
        //light->addAnimator(anim);
        planet->addAnimator(anim);
        anim->drop();
    }

    SAppContext context;
    context.device = device;
    context.counter = 0;

    EventReceiver receiver(context);
    device->setEventReceiver(&receiver);

    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,100,101,140));
        smgr->drawAll();
        device->getGUIEnvironment()->drawAll();
        driver->endScene();

        LIGHT_SOURCE = light->getAbsolutePosition();
    }

    delete planet;

    device->drop();
	return 0;
}
