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
    services->setVertexShaderConstant("u_WorldMatrixInv", invWorld.pointer(), 16);

    // set clip matrix
    core::matrix4 worldViewProj;
    worldViewProj = driver->getTransform(video::ETS_PROJECTION);
    worldViewProj *= driver->getTransform(video::ETS_VIEW);
    worldViewProj *= driver->getTransform(video::ETS_WORLD);
    services->setVertexShaderConstant("u_ProjectionMatrix", worldViewProj.pointer(), 16);

    // set camera position
    core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
    services->setVertexShaderConstant("u_LightPosition", reinterpret_cast<f32*>(&pos), 3);

    // set ambient light color (r g b a)
    video::SColorf ambientCol(1.0f,1.0f,1.0f,1.0f);
    services->setVertexShaderConstant("u_AmbientLightColor", reinterpret_cast<f32*>(&ambientCol), 4);
    video::SColorf diffuseCol(1.0f,1.0f,1.0f,1.0f);
    services->setVertexShaderConstant("u_DiffuseLightColor", reinterpret_cast<f32*>(&diffuseCol), 4);

    // set texture, for textures you can use both an int and a float setPixelShaderConstant interfaces (You need it only for an OpenGL driver).
    s32 TextureLayerID = 0;
    services->setPixelShaderConstant("u_texture", (float*)&TextureLayerID, 1);
}

