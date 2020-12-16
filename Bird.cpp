#include "DEFINITIONS.hpp"
#include "Bird.hpp"

namespace Kaiah
{
    Bird::Bird( GameDataRef data) : _data( data )
    {
        _animationIterator = 0;
        
        _animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1" ) );
        _animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2" ) );
        _animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3" ) );
        _animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4" ) );
        
        _birdSprite.setTexture( _animationFrames.at(_animationIterator) );
       _birdSprite.setPosition( (_data->window.getSize().x / 4 ) - (_birdSprite.getGlobalBounds().width / 2 ) , _data->window.getSize().y / 2 );
        
        _birdState = BIRD_STATE_STILL;
        
        sf::Vector2f origon = sf::Vector2f( _birdSprite.getGlobalBounds().width / 2 , _birdSprite.getGlobalBounds().height / 2 );
        
        _birdSprite.setOrigin( origon);
        
        _rotaion = 0;
    }

    Bird::~Bird()
    {
        
    }

    void Bird::Draw()
    {
        _data->window.draw( _birdSprite );
    }

    void Bird::Animante( float dt )
    {
        if( _clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_RATE / _animationFrames.size())
        {
            if( _animationIterator < _animationFrames.size() - 1)
            {
                _animationIterator++;
            }
            else
            {
                _animationIterator = 0;
            }
            
            _birdSprite.setTexture(_animationFrames.at( _animationIterator));
            
            _clock.restart();
        }
    }

    void Bird::Update( float dt )
    {
        if( BIRD_STATE_FALLING == _birdState)
        {
            _birdSprite.move( 0 , GRAVITY * dt );
            
            _rotaion += ( ROTATION_SPEED * dt );
            
            if( _rotaion > 25.0f)
            {
                _rotaion = 25.0f;
            }
            
            _birdSprite.setRotation( _rotaion );
        }
        else if( BIRD_STATE_FLYING == _birdState)
        {
            _birdSprite.move( 0 , - FLYING_SPEED * dt );
            
            _rotaion -= ( ROTATION_SPEED * dt );
            
            if( _rotaion < -25.0f)
            {
                _rotaion =  -25.0f;
            }
            
            _birdSprite.setRotation( _rotaion );
        }
        
        if ( _movmentClock.getElapsedTime().asSeconds() > FLYING_DURATION)
        {
            _movmentClock.restart();
            _birdState = BIRD_STATE_FALLING;
        }
    }

    void Bird::Tap( )
    {
        _movmentClock.restart();
        _birdState = BIRD_STATE_FLYING;
    }

    const sf::Sprite &Bird::GetSprite ( ) const
    {
    return _birdSprite;
    }

}
