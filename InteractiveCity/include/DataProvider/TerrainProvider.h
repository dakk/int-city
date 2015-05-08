#ifndef __TERRAIN_PROVIDER_H
#define __TERRAIN_PROVIDER_H

#include <Terrain.h>
#include <stdio.h>

namespace InteractiveCity
{
    namespace DataProvider
    {

        class TerrainProvider
        {
        public:
                                    TerrainProvider(Ogre::SceneManager *smgr);
            virtual Terrain *       loadFromPath(std::string path) = 0;

        protected:
            Ogre::SceneManager *    mSceneMgr;
        };
    }
}

#endif
