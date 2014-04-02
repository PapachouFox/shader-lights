#include "CustomNode.h"
CustomNode::CustomNode(scene::ISceneManager* mgr, video::IVideoDriver* driver){
    smgr = mgr;
    //scene::IAnimatedMesh* mesh = smgr->getMesh("../librarian/Librarian.3ds");
    //node = smgr->addAnimatedMeshSceneNode( mesh );
    node = smgr->addSphereSceneNode(50, 128);
    if (node){
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        video::ITexture* texture = driver->getTexture("../textures/earthmap1k.jpg");
        if(texture){
            node->setMaterialTexture(0, texture);
        }

        video::ITexture* normalMap = driver->getTexture("../textures/earthbump1k.jpg");
        if (normalMap){
            driver->makeNormalMapTexture(normalMap, 10.0f);
            node->setMaterialTexture (1, normalMap);
        }
    }

    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.0f, 0.3f, 0.0f));
    if(anim){
        node->addAnimator(anim);
        anim->drop();
    }
}

CustomNode::~CustomNode(){
    node->removeAll();
}

void CustomNode::SetMaterial(s32 material){
    node->setMaterialType((video::E_MATERIAL_TYPE)material);
}
