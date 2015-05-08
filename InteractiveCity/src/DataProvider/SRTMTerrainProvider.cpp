#include <DataProvider/SRTMTerrainProvider.h>
#include <Terrain.h>
#include <dirent.h>
#include <vector>
#include <iostream>

using namespace InteractiveCity;
using namespace DataProvider;




SRTMTerrainProvider::SRTMTerrainProvider(Ogre::SceneManager *smgr) : TerrainProvider(smgr)
{
}






Terrain *
SRTMTerrainProvider::loadFromPath(std::string path)
{
    std::vector<std::string> hgts;

    /* Get filenames of all hgt */
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir (path.c_str())) != NULL)
    {
        while((ent = readdir (dir)) != NULL)
        {
            if(ent->d_name[0] != '.')
                hgts.push_back(path+"/"+ent->d_name);

        }
        closedir(dir);
    }
    else
    {
        // Maybe use an exception?
        return NULL;
    }


    /* For each hgt file, load it in memory and put data in the Terrain->TerrainGroup */
    Terrain *ter = new Terrain(mSceneMgr); //, Ogre::Terrain::ALIGN_X_Z, 512, 12000.0f);
    ter->getTerrainGroup()->setTerrainSize(1025); //3602); // check!
    ter->getTerrainGroup()->setOrigin(Ogre::Vector3::ZERO);
    ter->getTerrainGroup()->setTerrainWorldSize(1025);


    for(int i = 0; i < hgts.size(); i++)
    {
        Ogre::Terrain::ImportData *data = loadHGT(hgts.at(i));

        if(data)
        {
            ter->getTerrainGroup()->defineTerrain(0, 0, data);
            ter->getTerrainGroup()->loadTerrain(0, 0, false);

            //std::cout << "loaded\n";
        }
        else
            std::cout << hgts.at(i) << "error!\n";

        break;
    }

    //ter->getTerrainGroup()->loadAllTerrains(true);

    return ter;
}



/**
 * Open an hgt file and return an array of float
 *
 * @brief SRTMTerrainProvider::loadHGT
 * @param path
 * @return
 */
Ogre::Terrain::ImportData *
SRTMTerrainProvider::loadHGT(std::string path)
{
    Ogre::Terrain::ImportData *data_im = new Ogre::Terrain::ImportData();
    FILE *fp = fopen(path.c_str(), "rb");

    if(fp == NULL)
        return NULL;

    fseek(fp, 0L, SEEK_END);
    int64_t size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    void *data = (void *) malloc(size);
    fread(data, size, 1, fp);
    fclose(fp);


    int16_t *data_i = (int16_t *) data;
    float *data_f = (float *) malloc(sizeof(float) * 1025 * 1025); //(size / sizeof(int16_t)));

    /*for(int64_t i = 0; i < (size / sizeof(int16_t)); i++)
    {
        data_f[i] = (float) data_i[i] / 10000.0;


        // Skip 1 point over 5
        if(i % 5 == 0) i = i + 1;

        //if (data_i[i] != 0) std::cout << data_i[i] << std::endl;
    }*/
    for(int i = 0; i < 1025; i++)
        for(int j = 0; j < 1025; j++)
            data_f[i*1024+j] = (data_i[i*1201+j] >= 0) ? (float) data_i[i*1201+j] / 45000.0 : 0.0;

    data_im->terrainSize = 1025;
    //data_im->inputScale = 800;
    data_im->inputFloat = data_f;

    // Texturing
    data_im->layerList.resize(3);
    data_im->layerList[0].worldSize = 100;
    data_im->layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    data_im->layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    data_im->layerList[1].worldSize = 30;
    data_im->layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    data_im->layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    data_im->layerList[2].worldSize = 200;
    data_im->layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    data_im->layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");




    //std::cout << size << " " << (size / sizeof(int16_t)) << std::endl;
    return data_im;
}
