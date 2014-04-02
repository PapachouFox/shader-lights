#ifndef LIBRARIAN_H_
#define LIBRARIAN_H_
#include <irrlicht/irrlicht.h>
using namespace irr;

class CustomNode{
private:
    //scene::IAnimatedMeshSceneNode* node;
    scene::IMeshSceneNode* node;
    scene::ISceneManager* smgr;
public:
    CustomNode(scene::ISceneManager* mgr, video::IVideoDriver* driver);
    ~CustomNode();
    void SetMaterial(s32 material);
};

#endif
