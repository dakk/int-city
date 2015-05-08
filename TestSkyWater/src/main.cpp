#include "TestApp.h"

 
int main()
{
    try
    {
        TestApp ta;
        ta.go();
    }
    catch ( Ogre::Exception &error )
    {
    }
    return 0;
}
