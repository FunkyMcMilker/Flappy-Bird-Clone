
#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include "PauseState.hpp"

#include <iostream>

namespace Kaiah
{
    GameState::GameState(GameDataRef data) : _data( data )
    {

    }

    void GameState::Init()
    {
        
        _hitSoundBuffer.loadFromFile("HIT_SOUND_FILEPATH ");
        _wingSoundBuffer.loadFromFile("WIND_SOUND_FILEPATH ");
        _pointSoundBuffer.loadFromFile("POINT_SOUND_FILEPATH ");
        
        _hitSound.setBuffer( _hitSoundBuffer );
        _wingSound.setBuffer( _wingSoundBuffer );
        _pointSound.setBuffer( _pointSoundBuffer );

       
        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
        this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FILEPATH_1);
        this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FILEPATH_2);
        this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FILEPATH_3);
        this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FILEPATH_4);
        this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
        this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

        pipe = new Pipe ( _data ) ;
        land = new Land ( _data ) ;
        bird = new Bird ( _data ) ;
        flash = new Flash ( _data ) ;
        hud = new HUD ( _data );
 
        _background.setTexture(this->_data->assets.GetTexture("Game Background"));
        
        _pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getGlobalBounds().width, this->_data->window.getSize().y - _pauseButton.getGlobalBounds().height ) ;
        
        _gameState = GameStates::eReady;
        
        _score = 0;
        hud->UpdateScore( _score );
        
        _timeFactor = 1.0f;
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }
            
            if( this->_data->input.IsSpriteClicked( _background, sf::Mouse::Left , this->_data->window))
            {
                if( GameStates::eGameOver != _gameState)
                {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();
                    
                    _wingSound.play();
                }
            }
            
            if ( this->_data->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left , this->_data->window))
            {
                if(GameStates::eGameOver != _gameState)
                {
                    this->_data->machine.AddState(StateRef ( new PauseState( _data ) ) , false );
                    _gameState = GameStates::ePlaying;
                }
            }
           
        }
        
    }

    void GameState::Update(float dt)
    {
        if ( _clock2.getElapsedTime().asSeconds() > 5)
        {
            _timeFactor = _timeFactor - 0.1f ;
            _clock2.restart();
            if ( _timeFactor < 0.7f)
            {
                _timeFactor = 0.7f; 
            }
        }
        if( GameStates::eGameOver != _gameState)
        {
        bird->Animante( dt );
        land->MoveLand( dt );
        }
        if ( GameStates::ePlaying == _gameState)
        {
            pipe->MovePipes( dt );
            if ( clock.getElapsedTime().asSeconds() > ( PIPE_SPAWN_FREQUENCY * _timeFactor ) )
            {
            pipe->RandomisePipeOffset();
            pipe->SpawnBottomPipe();
            pipe->SpawnTopPipe();
            pipe->SpawnInvisiblePipe();
            pipe->SpawnScoringPipes();
            
            clock.restart(); 
            }
        
            bird->Update( dt );
            
            std::vector<sf::Sprite> landSprites = land->GetSprites();
            
            for ( int x = 0; x < landSprites.size() ; x ++ )
            {
                if( Collision().CheckSpriteCollision(bird->GetSprite(), landSprites.at( x )))
                {
                    _gameState = GameStates::eGameOver;
                    
                    clock.restart();
                    
                    _hitSound.play();

                }
            }
            
            std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();

            for ( int x = 0; x < pipeSprites.size() ; x ++ )
            {
                if( Collision().CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at( x ), 1.0f ) )
                {
                    _gameState = GameStates::eGameOver;
                    
                    clock.restart();
                    
                    _hitSound.play();
                    
                }
            }
            
            if ( GameStates::ePlaying == _gameState)
            {
            std::vector<sf::Sprite> &scoringSprites = pipe->GetScoringSprites();

            for ( int x = 0; x < scoringSprites.size() ; x ++ )
            {
                if( Collision().CheckSpriteCollision(bird->GetSprite(), 0.7f, scoringSprites.at( x ), 1.0f ) )
                {
                    _score++;
                    hud->UpdateScore(_score );
                    
                    _gameState = GameStates::ePlaying;
                    
                    scoringSprites.erase( scoringSprites.begin() + x );
                    
                    _pointSound.play();
                }
            }
        }
    }
        
        if ( GameStates::eGameOver == _gameState)
        {
            flash->Show( dt );
            
            if ( clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
            {
                _data->machine.AddState(StateRef ( new GameOverState ( _data , _score) ), true );
            }
        }
        
    }

    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);

        this->_data->window.draw( this->_background );
        
        pipe->DrawPipes();
        land->DrawLand();
        bird->Draw();
        hud->Draw();
        flash->Draw();
        
        this->_data->window.draw( this->_pauseButton );

        this->_data->window.display();
    }
}
