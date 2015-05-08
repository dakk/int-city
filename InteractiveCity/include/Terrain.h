#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <string>
#include <Terrain/OgreTerrainGroup.h>


namespace InteractiveCity
{
    class Terrain
    {
    public:
                                    Terrain(Ogre::SceneManager *sm);
                                    ~Terrain();
        Ogre::TerrainGroup *        getTerrainGroup();

    protected:
        Ogre::TerrainGroup *        mTerrainGroup;
        Ogre::TerrainGlobalOptions *mTerrainGlobals;
    };
}

#endif
