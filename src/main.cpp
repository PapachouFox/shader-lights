#include <irrlicht/irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv){
    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE,
                                          dimension2d<u32>(640, 480), 16,
                                          false, false, false, 0);
    device->setWindowCaption(L"Shaders and lights - Irrlicht");

    if (!device)
        return 1;

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    while(device->run()){
        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }

    device->drop();
	return 0;
}
