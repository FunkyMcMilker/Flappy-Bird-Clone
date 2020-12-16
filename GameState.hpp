#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace Kaiah
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);
        
        void Init();
        
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );
    
    private:
        GameDataRef _data;
                
        sf::Sprite _background;
       
        Pipe *pipe;
        Land *land;
        Bird *bird; 
        Collision collision;
        Flash *flash;
        HUD *hud;
        
        sf::Sprite _pauseButton;
        
        sf::Clock clock; 
        sf::Clock _clock2;
        
        int _gameState;
        
        int _score;
        
        float _timeFactor;
        
        sf::SoundBuffer _hitSoundBuffer;
        sf::SoundBuffer _wingSoundBuffer;
        sf::SoundBuffer _pointSoundBuffer;
        
        sf::Sound _hitSound;
        sf::Sound _wingSound;
        sf::Sound _pointSound;
        

    };

}
