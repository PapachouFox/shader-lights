#include "BasicShaderCallBack.h"

f32 model_shininess = 10;
core::vector3df LIGHT_SOURCE;

BasicShaderCallBack::BasicShaderCallBack(IrrlichtDevice *irrDevice){
    this->device = irrDevice;
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Model Shininess:", core::rect<s32>(0,0,200,10), false);
    guienv->getSkin()->setFont(guienv->getBuiltInFont(), gui::EGDF_DEFAULT);
    scrollbar = guienv->addScrollBar(true, core::rect<s32>(0, 10, 200, 25), 0, 3);
    scrollbar->setMin(0);
    scrollbar->setMax(50);
    scrollbar->setPos(10);

    LIGHT_SOURCE = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
}

void BasicShaderCallBack::OnSetConstants(video::IMaterialRendererServices* services, s32 userData){
    video::IVideoDriver* driver = services->getVideoDriver();

    // set inverted world matrix
    // if we are using highlevel shaders (the user can select this when
    // starting the program), we must set the constants by name.
    core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
    invWorld.makeInverse();
    services->setVertexShaderConstant("u_WorldMatrix", driver->getTransform(video::ETS_WORLD).pointer(), 16);
    services->setVertexShaderConstant("u_WorldMatrixInv", invWorld.pointer(), 16);

    // set clip matrix
    services->setVertexShaderConstant("u_ViewMatrix", device->getSceneManager()->getActiveCamera()->getViewMatrix().pointer(), 16);
    services->setVertexShaderConstant("u_ModelMatrix", driver->getTransform(video::ETS_WORLD).pointer(), 16);
    services->setVertexShaderConstant("u_ProjectionMatrix", device->getSceneManager()->getActiveCamera()->getProjectionMatrix().pointer(), 16);

    // set camera position
    core::vector3df cam = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();

    services->setVertexShaderConstant("u_LightPosition", reinterpret_cast<f32*>(&LIGHT_SOURCE), 3);
    services->setVertexShaderConstant("u_CameraPosition", reinterpret_cast<f32*>(&cam), 3);

    // set ambient light color (r g b a)
    video::SColorf ambientCol(0.1f,0.1f,0.1f,1.0f);
    services->setVertexShaderConstant("u_AmbientLightColor", reinterpret_cast<f32*>(&ambientCol), 4);
    video::SColorf diffuseCol(0.5f,0.5f,0.5f,1.0f);
    services->setVertexShaderConstant("u_DiffuseLightColor", reinterpret_cast<f32*>(&diffuseCol), 4);
    video::SColorf specularCol(0.8f,0.8f,0.8f,1.f);
    services->setVertexShaderConstant("u_SpecularLightColor", reinterpret_cast<f32*>(&specularCol), 4);

    services->setVertexShaderConstant("u_ModelShininess", &model_shininess, 1);

    // set texture, for textures you can use both an int and a float setPixelShaderConstant interfaces (You need it only for an OpenGL driver).
    s32 TextureLayerID = 0;
    services->setPixelShaderConstant("u_texture", &TextureLayerID, 1);
    s32 NormalLayerID = 1;
    services->setPixelShaderConstant("u_normal", &NormalLayerID, 1);
    s32 SpecularLayerID = 2;
    services->setPixelShaderConstant("u_specular", &SpecularLayerID, 1);
    s32 NightLayerID = 3;
    services->setPixelShaderConstant("u_night", &NightLayerID, 1);
}

