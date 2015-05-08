#ifndef __CORE_H
#define __CORE_H

#include <string>
#include <ExampleApplication.h>

#include <Terrain.h>

namespace InteractiveCity
{
    class Core : public ExampleApplication
    {
    public:
        static const std::string    VERSION;
        static const std::string    VERSION_CODENAME;

                                    Core();
                                    ~Core();
        static Core *               loadFromFile(std::string basePath, std::string file);

        bool                        setTerrain(std::string dataPath, std::string type = "srtm");
        bool                        addLayer(std::string name, std::string dataPath,
                                             std::string materialsPath = NULL, std::string type = "osm");


        void                        go();

    protected:
        void                        createScene();

        Terrain *                   mTerrain;

    };
}

#endif
