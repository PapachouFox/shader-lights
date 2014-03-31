#include <irrlicht/irrlicht.h>
using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv){
    irr::IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          core::dimension2d<u32>(640, 480), 16,
                                          false, false, true, 0);
    device->setWindowCaption(L"Shaders and lights - Irrlicht");

    if (!device)
        return 1;

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    scene::IAnimatedMesh* mesh = smgr->getMesh("../librarian/Librarian.3ds");
    scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
    if (node){
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("../librarian/act_bibliotekar.jpg") );
    }

    smgr->addCameraSceneNode(0, core::vector3df(90,120,-180), core::vector3df(0,120,0));
    core::vector3df rot = node->getRotation();
    u32 frames=0;
    while(device->run()){
        driver->beginScene(true, true, video::SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();

        rot.Y += 0.03f;
        if(rot.Y >= 360.f)
            rot.Y -= 360.f;
        node->setRotation(rot);

        if (++frames==100){
            core::stringw str = L"Shaders and lights - Irrlicht - ";
            str += L" [FPS: ";
            str += (s32)driver->getFPS();
            str += L"]";

            device->setWindowCaption(str.c_str());
            frames=0;
        }
    }

    device->drop();
	return 0;
}
