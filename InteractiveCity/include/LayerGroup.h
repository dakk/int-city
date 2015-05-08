#ifndef __LAYERGROUP_H
#define __LAYERGROUP_H

#include <string>
#include <OgreSceneNode.h>

namespace InteractiveCity
{
    /**
     * Container for handling layers
     *
     * @brief The LayerGroup class
     */
    class LayerGroup : public Ogre::SceneNode
    {
    public:
                                    LayerGroup(Ogre::SceneManager *sm);
                                    ~LayerGroup();
    };
}

#endif
