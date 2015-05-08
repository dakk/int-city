#ifndef __LAYER_H
#define __LAYER_H

#include <string>
#include <OgreSceneNode.h>

namespace InteractiveCity
{
    /**
     * A layer
     *
     * @brief The Layer class
     */
    class Layer : public Ogre::SceneNode
    {
    public:
                                    Layer(Ogre::SceneManager *sm);
                                    ~Layer();
    };
}

#endif
