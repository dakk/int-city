#ifndef __SRTM_TERRAIN_PROVIDER_H
#define __SRTM_TERRAIN_PROVIDER_H

#include <DataProvider/TerrainProvider.h>
#include <stdio.h>

namespace InteractiveCity
{
    namespace DataProvider
    {

        class SRTMTerrainProvider : public TerrainProvider
        {
        public:
                                    SRTMTerrainProvider(Ogre::SceneManager *smgr);
            virtual Terrain *       loadFromPath(std::string path);


            Ogre::Terrain::ImportData *loadHGT(std::string path);
        };
    }
}

#endif
