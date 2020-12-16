#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace Kaiah
{

    Land::Land( GameDataRef data ) : _data( data )
    {
        sf::Sprite sprite ( this->_data->assets.GetTexture("Land"));
        sf::Sprite sprite2 ( this->_data->assets.GetTexture("Land"));

        sprite.setPosition( 0 , _data->window.getSize().y - sprite.getGlobalBounds().height );
        sprite2.setPosition( sprite.getGlobalBounds().width , _data->window.getSize().y - sprite.getGlobalBounds().height );
        
        _landSprites.push_back( sprite );
        _landSprites.push_back( sprite2 );
            
        _clock.restart();
        
        _timeFactor = PIPE_MOVEMENT_SPEED;
        
    }

    void Land::MoveLand(float dt)
    {
        
        for ( unsigned short int x = 0 ; x < _landSprites.size() ; x++)
        {
            
            float movment = PIPE_MOVEMENT_SPEED * dt ;
            
            _landSprites.at ( x ).move( - movment , 0.0f );
            
            if ( _landSprites.at ( x ).getPosition().x < 0 - _landSprites.at ( x ).getGlobalBounds().width)
            {
                sf::Vector2f position( _data->window.getSize().x , _landSprites.at( x ).getPosition().y );
                
                _landSprites.at( x ).setPosition( position );
            }
           
        }
    }
   void Land::DrawLand()
    {
        for ( unsigned short int x = 0 ; x < _landSprites.size() ; x++ )
        {
            this->_data->window.draw(_landSprites.at ( x ) );
        }
    }

    const std::vector<sf::Sprite> &Land::GetSprites ( ) const
    {
        return _landSprites;  
    }
}
