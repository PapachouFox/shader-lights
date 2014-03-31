#include <irrlicht/irrlicht.h>
using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv){
    irr::IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE,
                                          core::dimension2d<u32>(640, 480), 16,
                                          false, false, false, 0);
    device->setWindowCaption(L"Shaders and lights - Irrlicht");

    if (!device)
        return 1;

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }

    device->drop();
	return 0;
}
