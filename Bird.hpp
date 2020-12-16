#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>

namespace Kaiah
{
    class Bird
    {
    public:
        
        Bird( GameDataRef data );
        ~Bird();
        
        void Draw( );
        
        void Animante( float dt );
        
        void Update ( float dt );
        
        void Tap ( );

        const sf::Sprite &GetSprite ( ) const;
        
    private:
        GameDataRef _data;
        
        sf::Sprite _birdSprite;
        std::vector<sf::Texture> _animationFrames;
        
        unsigned int _animationIterator; 
        
        sf::Clock _clock;
        
        sf::Clock _movmentClock;
        
        int _birdState;
        
        float _rotaion;
        
    };
}
