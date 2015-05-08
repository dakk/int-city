#include "TestApp.h"
#include "WaterMesh.h"

TestApp::TestApp()
{
  //no implementation yet
}


TestApp::~TestApp()
{

}



void TestApp::createScene()
{
    mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");


    mWaterPlane.normal = Vector3::UNIT_Y;
    mWaterPlane.d = -1.5;
    MeshManager::getSingleton().createPlane(
        "WaterPlane",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        mWaterPlane,
        8000, 8000,
        20, 20,
        true, 1,
        10, 10,
        Vector3::UNIT_Z);


    mWaterEntity = mSceneMgr->createEntity("water", "WaterPlane");
    //mWaterEntity->setMaterialName("Examples/TextureEffect1");
    SceneNode *waterNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("WaterNode");
    waterNode->attachObject(mWaterEntity);
    waterNode->translate(4000, 50, 4000);


    Light* pLight = mSceneMgr->createLight("MainLight");
    pLight->setType( Light::LT_DIRECTIONAL );
    pLight->setDirection( 0, -100, 0 );

}
