#include <Terrain.h>
#include <Terrain/OgreTerrainGroup.h>

using namespace InteractiveCity;


Terrain::Terrain(Ogre::SceneManager *sm)
{
    mTerrainGroup = new Ogre::TerrainGroup(sm);
    mTerrainGlobals = new Ogre::TerrainGlobalOptions();

    //mTerrainGlobals->setCompositeMapAmbient(sm->getAmbientLight());
    mTerrainGlobals->setMaxPixelError(8);
    //mTerrainGlobals->setCompositeMapDistance(300000);

    /*Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_TRILINEAR);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();

    Ogre::Light* light = sm->createLight("tstLight");
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(sm->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
    */
    Ogre::TerrainGlobalOptions::getSingleton().setCastsDynamicShadows(false);

}


Terrain::~Terrain()
{
    delete mTerrainGroup;
    delete mTerrainGlobals;
}


Ogre::TerrainGroup *
Terrain::getTerrainGroup()
{
    return mTerrainGroup;
}
