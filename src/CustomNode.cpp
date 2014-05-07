#include "CustomNode.h"
CustomNode::CustomNode(scene::ISceneManager* mgr, video::IVideoDriver* driver, IrrlichtDevice* device){
    smgr = mgr;
    //scene::IAnimatedMesh* mesh = smgr->getMesh("../librarian/Librarian.3ds");
    //node = smgr->addAnimatedMeshSceneNode( mesh );
    node = smgr->addSphereSceneNode(50, 64);

    node->getMaterial(0).Shininess = 100.f;
    node->getMaterial(0).AmbientColor = irr::video::SColor(255, 255, 255, 255);
    node->getMaterial(0).DiffuseColor = irr::video::SColor(255, 255, 0, 0);
    //node = smgr->addCubeSceneNode(50);
    //node->setRotation(core::vector3df(0.f, 45.f, 0.f));
    if (node){
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        video::ITexture* texture = driver->getTexture("../textures/earthmap1k.jpg");
        if(texture){
            node->setMaterialTexture(0, texture);
        }

        video::ITexture* normalMap = driver->getTexture("../textures/earthnormal1k.jpg");
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

    clouds = smgr->addSphereSceneNode(51, 64, node);
    video::ITexture* cloudsTexture = driver->getTexture("../textures/earthclouds2k.jpg");
    if(cloudsTexture){
        clouds->setMaterialTexture(0, cloudsTexture);
    }

    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
    s32 defaultShader = 0;

    BasicShaderCallBack* mc = new BasicShaderCallBack(device);
    if (gpu){
       defaultShader = gpu->addHighLevelShaderMaterialFromFiles(
                   "../shaders/clouds.vert",
                   "../shaders/clouds.frag",
                   mc, video::EMT_TRANSPARENT_ALPHA_CHANNEL, 0);
    }
    mc->drop();

    clouds->setMaterialType((video::E_MATERIAL_TYPE)defaultShader);
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

irr::scene::IMeshSceneNode* CustomNode::getNode(){
    return node;
}
