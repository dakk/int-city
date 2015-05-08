#include <iostream>
#include <InteractiveCity.h>

using namespace std;

int main()
{
    InteractiveCity::Core *it = InteractiveCity::Core::loadFromFile("/home/dak/Dropbox/IntCity/Repo/Data/", "data.xml");

    try
    {
        it->go();
    }
    catch (Ogre::Exception &error)
    {
        std::cout << error.getFullDescription().c_str() << std::endl;
    }

    return 0;
}

