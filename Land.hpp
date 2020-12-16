#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace Kaiah
{
    
    class Land
    {
    public:
        Land ( GameDataRef data );
        
        void MoveLand( float dt );
        void DrawLand();
        void DeleteLand( );
        
        const std::vector<sf::Sprite> &GetSprites ( ) const;
        
    private:
        GameDataRef _data;
        
        sf::Clock _clock;
        
        float _timeFactor;
        std::vector<sf::Sprite> _landSprites;
        
    };
}
