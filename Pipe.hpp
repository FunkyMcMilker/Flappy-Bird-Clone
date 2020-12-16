#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace Kaiah
{
    
    class Pipe
    {
    public:
        Pipe ( GameDataRef data );
        
        void SpawnBottomPipe();
        void SpawnTopPipe();
        void SpawnInvisiblePipe();
        void SpawnScoringPipes();
        void MovePipes( float dt );
        void DrawPipes();
        void DeletePipes( );
        void RandomisePipeOffset( );
        
        const std::vector<sf::Sprite> &GetSprites ( ) const;
        std::vector<sf::Sprite> &GetScoringSprites ( );


    private:
        GameDataRef _data;
        std::vector<sf::Sprite> pipeSprites;
        std::vector<sf::Sprite> scoringSprites;
        
        sf::Clock _clock;
        
        float _timeFactor;
        
        int _landHeight;
        int _pipeSpawnYOffset;
    };
}
