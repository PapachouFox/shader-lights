#include <irrlicht/irrlicht.h>
#include "BasicShaderCallBack.h"
#include "Librarian.h"
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
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    //shaders loading
    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
    s32 defaultShader = 0;
    BasicShaderCallBack* mc = new BasicShaderCallBack(device);
    if (gpu){
       defaultShader = gpu->addHighLevelShaderMaterialFromFiles(
                   "../shaders/default.vert", "vertexMain", video::EVST_VS_1_1,
                   "../shaders/default.frag", "pixelMain", video::EPST_PS_1_1,
                   mc, video::EMT_SOLID, 0, video::EGSL_DEFAULT);
    }
    mc->drop();

    smgr->addCameraSceneNode(0, core::vector3df(90,120,-180), core::vector3df(0,120,0));

    Librarian* lib = new Librarian(smgr, driver);
    lib->SetMaterial(defaultShader);

    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }

    delete lib;

    device->drop();
	return 0;
}
