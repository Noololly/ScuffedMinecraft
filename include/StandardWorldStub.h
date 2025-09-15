#pragma once

#include <WillowVox/world/World.h>
#include <WillowVox/rendering/Camera.h>
#include <iostream>

using namespace WillowVox;

namespace ScuffedMinecraft {
    class StandardWorld : public World
    {
    public:
        StandardWorld(Camera* player)
        {
            std::cout << "StandardWorld: Creating with camera" << std::endl;
            m_mainCamera = player;
            // Create a dummy chunk manager to prevent null pointer access
            m_chunkManager = reinterpret_cast<ChunkManager*>(1);
            std::cout << "StandardWorld: Created successfully" << std::endl;
        }

        ~StandardWorld()
        {
            std::cout << "StandardWorld: Destroying" << std::endl;
        }
    };
}