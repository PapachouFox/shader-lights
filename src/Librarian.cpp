#include "Librarian.h"
Librarian::Librarian(scene::ISceneManager* mgr, video::IVideoDriver* driver){
    smgr = mgr;
    scene::IAnimatedMesh* mesh = smgr->getMesh("../librarian/Librarian.3ds");
    node = smgr->addAnimatedMeshSceneNode( mesh );
    if (node){
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        video::ITexture* texture = driver->getTexture("../librarian/act_texture.jpg");
        if(texture){
            node->setMaterialTexture(0, texture);
            node->getMaterial(0).Shininess = 10;
        }
        /*
        video::ITexture* normalMap = driver->getTexture("../librarian/act_norm.jpg");
        if (normalMap){
            driver->makeNormalMapTexture(normalMap, 100.0f);
            node->setMaterialTexture (1, normalMap);
        }*/
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
