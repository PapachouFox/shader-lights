#include "Librarian.h"
Librarian::Librarian(scene::ISceneManager* mgr, video::IVideoDriver* driver){
    smgr = mgr;
    scene::IAnimatedMesh* mesh = smgr->getMesh("../librarian/Librarian.3ds");
    node = smgr->addAnimatedMeshSceneNode( mesh );
    if (node){
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        video::ITexture* normalMap = driver->getTexture("../librarian/act_norm.jpg");
        if (normalMap){
            driver->makeNormalMapTexture(normalMap, 100.0f);
            node->setMaterialTexture (1, normalMap);
            node->setMaterialType(video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA);
        }
    }

    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.0f, 0.3f, 0.0f));
    if(anim){
        node->addAnimator(anim);
        anim->drop();
    }
}

Librarian::~Librarian(){
    node->removeAll();
}

void Librarian::SetMaterial(s32 material){
    node->setMaterialType((video::E_MATERIAL_TYPE)material);
}
