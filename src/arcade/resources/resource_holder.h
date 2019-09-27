#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../util/non_copyable.h"
#include "../util/non_moveable.h"
#include "resource_manager.h"

class ResourceHolder : public NonCopyable, public NonMovable {
  public:
    static ResourceHolder &get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::SoundBuffer> soundBuffers;

  private:
    ResourceHolder();
};
