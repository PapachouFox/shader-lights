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
            node->setMaterialTexture (1, normalMap);
        }

        video::ITexture* specularMap = driver->getTexture("../textures/earthspec1k.jpg");
        if (specularMap){
            node->setMaterialTexture (2, specularMap);
        }

        video::ITexture* nightMap = driver->getTexture("../textures/earthlights1k.jpg");
        if (nightMap){
            node->setMaterialTexture (3, nightMap);
        }
    }
}

void CustomNode::addAnimator(irr::scene::ISceneNodeAnimator* anim){
    node->addAnimator(anim);
}

CustomNode::~CustomNode(){
    node->removeAll();
}

void CustomNode::SetMaterial(s32 material){
    node->setMaterialType((video::E_MATERIAL_TYPE)material);
}
