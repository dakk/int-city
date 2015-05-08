#include "ExampleApplication.h"
#include "WaterMesh.h"

class TestApp : public ExampleApplication
{
public:
    TestApp();
    ~TestApp();

protected:
    Entity* mWater;
    Entity *mWaterEntity;
    Plane mWaterPlane;

    void createScene();
};
