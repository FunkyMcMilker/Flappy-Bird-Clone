
#include <sstream>
#include "PauseState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>

namespace Kaiah
{
    PauseState::PauseState(GameDataRef data) : _data( data )
    {
        
    }

    void PauseState::Init()
    {
        this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_STATE_BACKGROUND_FILEPATH);
         this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
 
        _background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
       _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        
       _pausedText.setFont(this->_data->assets.GetFont("Flappy Font"));

              _pausedText.setString("PAUSED");
       
              _pausedText.setCharacterSize(128);

              _pausedText.setFillColor(sf::Color::White);

              _pausedText.setOrigin(sf::Vector2f(_pausedText.getGlobalBounds().width / 2, _pausedText.getGlobalBounds().height / 2));

        _pausedText.setPosition(sf::Vector2f(_data->window.getSize().x / 2, _data->window.getSize().y / 5));
        
        
        _playButton.setPosition( (SCREEN_WIDTH / 2) - _playButton.getGlobalBounds().width / 2 , (SCREEN_HEIGHT / 2 ) - _playButton.getGlobalBounds().height / 4);
    }

    void PauseState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            
            if( this->_data->input.IsSpriteClicked(_playButton , sf::Mouse::Left, this->_data->window ) )
            {
                this->_data->machine.RemoveState();
            }
               
        }
    }

    void PauseState::Update(float dt)
    {
        
    }

    void PauseState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);

        this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_playButton );
        this->_data->window.draw( this->_pausedText );

        this->_data->window.display();
    }
}
