#include <Core.h>
#include <Terrain.h>
#include <DataProvider/TerrainProvider.h>
#include <DataProvider/SRTMTerrainProvider.h>

#include <Procedural.h>
#include <SdkTrays.h>

#include <iostream>
#include <tinyxml.h>
#include <stdio.h>


using namespace InteractiveCity;


/* Consts */
const std::string Core::VERSION = "0.1";
const std::string Core::VERSION_CODENAME = "unknown";


/**
 * Core constructor
 *
 * @brief Core::Core
 */
Core::Core() : ExampleApplication()
{
    std::cout << "InteractiveCity " << Core::VERSION << " (" << Core::VERSION_CODENAME << ")" << std::endl;

    mTerrain = NULL;
}


/**
 * @brief Core::~Core
 */
Core::~Core()
{
    if(mTerrain)
        delete mTerrain;
}


/**
 * Create an Core object reading data from XML file
 *
 * @brief Core::loadFromFile
 * @param path
 * @return
 */
Core *
Core::loadFromFile(std::string basePath, std::string file)
{
    /* Create the core and run setup() */
    Core *it = new Core();

    if(!it->setup())
        return NULL;

    /* Load XML file */
    TiXmlDocument doc(basePath+file);

    std::cout << "Loading from file: "<< basePath+file << "... ";

    if(!doc.LoadFile())
    {
        std::cout << "Failed" << std::endl;;
        return NULL;
    }

    std::cout << "Ok" << std::endl;;
    TiXmlElement *root = doc.RootElement();

    // Terrain
    TiXmlElement *terrain = root->FirstChildElement("terrain");

    if(terrain)
    {
        std::string ttype = terrain->Attribute("type");
        std::string tpath = terrain->Attribute("path");

        // Set terrain
        std::cout << "\tSetting terrain (" << tpath << ")... ";
        if(it->setTerrain(basePath+tpath, ttype))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "Failed" << std::endl;
    }

    // Layers
    TiXmlElement *layers = root->FirstChildElement("layers");

    if(layers)
    {
        TiXmlElement *layer = layers->FirstChildElement();

        while(layer)
        {
            std::string ltype = layer->Attribute("type");
            std::string lpath = layer->Attribute("path");
            std::string lname = layer->Attribute("name");
            std::string lmat = layer->Attribute("materials");

            // Add layer
            std::cout << "\tAdding layer (" << lpath << ")... ";
            if(it->addLayer(lname, basePath+lpath, lmat, ltype))
                    std::cout << "Ok" << std::endl;
                else
                    std::cout << "Failed" << std::endl;

            layer = layer->NextSiblingElement();
        }
    }

    return it;
}


/**
 * Replace standard go() method, because setup is already done.
 *
 * @brief Core::go
 */
void
Core::go()
{
    mRoot->startRendering();
}


/**
 * Create the scene
 * @brief Core::createScene
 */
void
Core::createScene()
{
    // Camera setting
    mCamera->setNearClipDistance(0.1);
    mCamera->setFarClipDistance(5000000);


    // Infinite far clip plane
    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
        mCamera->setFarClipDistance(0);


    // Set ambient lighting
    mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));


    // Set ambient skybox and fog to simulate simple clouds
    /*Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 300, 600);
    mWindow->getViewport(0)->setBackgroundColour(fadeColour);

    Ogre::Plane plane;
    plane.d = 100;
    plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;

    mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true, 0.5, 150, 150);*/


    // Sea
#if 0
    Ogre::Plane oceanSurface;
    oceanSurface.normal = Ogre::Vector3::UNIT_Y;
    oceanSurface.d = 200;
    Ogre::MeshManager::getSingleton().createPlane("OceanSurface",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        oceanSurface,
        1000, 1000, 50, 50, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

    Ogre::Entity *mOceanSurfaceEnt = mSceneMgr->createEntity( "OceanSurface", "OceanSurface" );
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mOceanSurfaceEnt);
#endif

    // Testing procedural
    Procedural::SphereGenerator().setRadius(15.f).setUTile(.5f).realizeMesh("mySphere");
    Ogre::Entity *sphere = mSceneMgr->createEntity("mySphere");
    mSceneMgr->getRootSceneNode()->attachObject(sphere);
}


/**
 * Set the terrain source, replacing the existing istance if any
 *
 * @brief Core::setTerrain
 * @param dataPath
 * @param type
 * @return
 */
bool
Core::setTerrain(std::string dataPath, std::string type)
{
    if(mTerrain != NULL)
        delete mTerrain;

    mTerrain = NULL;

    DataProvider::TerrainProvider *tp;

    if(type == "srtm")
        tp = new DataProvider::SRTMTerrainProvider(mSceneMgr);
    else
        return NULL;


    mTerrain = tp->loadFromPath(dataPath);


    return (mTerrain);
}


/**
 * @brief Core::addLayer
 * @param dataPath
 * @param materialsPath
 * @param type
 * @return
 */
bool
Core::addLayer(std::string name, std::string dataPath, std::string materialsPath, std::string type)
{
    return true;
}
