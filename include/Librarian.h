#ifndef LIBRARIAN_H_
#define LIBRARIAN_H_
#include <irrlicht/irrlicht.h>
using namespace irr;

class Librarian{
private:
    scene::IAnimatedMeshSceneNode* node;
    scene::ISceneManager* smgr;
public:
    Librarian(scene::ISceneManager* mgr, video::IVideoDriver* driver);
    ~Librarian();
    void SetMaterial(s32 material);
};

#endif
