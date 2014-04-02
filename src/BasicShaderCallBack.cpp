#include "BasicShaderCallBack.h"

BasicShaderCallBack::BasicShaderCallBack(IrrlichtDevice *irrDevice){
    this->device = irrDevice;
}

void BasicShaderCallBack::OnSetConstants(video::IMaterialRendererServices* services, s32 userData){
    video::IVideoDriver* driver = services->getVideoDriver();

    // set inverted world matrix
    // if we are using highlevel shaders (the user can select this when
    // starting the program), we must set the constants by name.

    core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
    invWorld.makeInverse();

    services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);

    // set clip matrix

    core::matrix4 worldViewProj;
    worldViewProj = driver->getTransform(video::ETS_PROJECTION);
    worldViewProj *= driver->getTransform(video::ETS_VIEW);
    worldViewProj *= driver->getTransform(video::ETS_WORLD);

    services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

    // set camera position
    core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();

    services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&pos), 3);

    // set light color

    video::SColorf col(0.0f,1.0f,1.0f,0.0f);

    services->setVertexShaderConstant("mLightColor", reinterpret_cast<f32*>(&col), 4);

    // set transposed world matrix

    core::matrix4 world = driver->getTransform(video::ETS_WORLD);
    world = world.getTransposed();

    services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);

    // set texture, for textures you can use both an int and a float setPixelShaderConstant interfaces (You need it only for an OpenGL driver).
    s32 TextureLayerID = 0;
    services->setPixelShaderConstant("myTexture", &TextureLayerID, 1);
}

