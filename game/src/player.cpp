#include "player.h"

#include <src/level.h>
#include <src/tile_apple.h>
#include <string>
#include <src/util_draw.h>

Player::Player( const Int2 pos, Level* _level )
	: _level( _level )
{
	reset();

	_sound_grow = LoadSound( "resources/grow.wav" );
	_sound_ouch = LoadSound( "resources/ouch.wav" );
}

Player::~Player()
{
	clear_tiles();

	UnloadSound( _sound_grow );
	UnloadSound( _sound_ouch );
}

void Player::clear_tiles()
{
	for ( TileSnake* tile : _tiles )
	{
		delete tile;
	}
	_tiles.clear();
}

bool Player::try_set_move_dir( const Int2 new_move_dir )
{
	if ( new_move_dir.x == -_last_move_dir.x && new_move_dir.y == -_last_move_dir.y ) return false;

	_move_dir = new_move_dir;
	return true;
}

void Player::reset()
{
	clear_tiles();

	//  movement
	_current_move_time = MOVE_TIME;
	_move_dir = Int2 { 1, 0 };

	//  _tiles
	add_tile( _level->get_center_position() );
	increase_length();
	increase_length();

	//  game
	_score = 0;
	_is_game_running = true;
}

void Player::update( float dt )
{
	if ( !_is_game_running )
	{
		if ( IsKeyPressed( KEY_SPACE ) )
		{
			reset();
		}
		return;
	}

	//  input
	if ( IsKeyPressed( KEY_W ) || IsKeyPressed( KEY_UP ) )
	{
		try_set_move_dir( Int2 { 0, -1 } );
	}
	if ( IsKeyPressed( KEY_S ) || IsKeyPressed( KEY_DOWN ) )
	{
		try_set_move_dir( Int2 { 0, 1 } );
	}
	if ( IsKeyPressed( KEY_A ) || IsKeyPressed( KEY_LEFT ) )
	{
		try_set_move_dir( Int2 { -1, 0 } );
	}
	if ( IsKeyPressed( KEY_D ) || IsKeyPressed( KEY_RIGHT ) )
	{
		try_set_move_dir( Int2 { 1, 0 } );
	}

	//  movement
	if ( ( _current_move_time -= dt ) <= 0.0f )
	{
		//  reset timer
		_current_move_time += MOVE_TIME;

		//  get next pos
		Int2 next_pos = _tiles[0]->get_pos() + _move_dir;

		//  check out of bounds
		if ( !_level->is_in_bounds( next_pos ) )
		{
			die();
			return;
		}
		if ( _level->has_entity_at( next_pos ) )
		{
			TileEntity* tile = _level->get_entity_at( next_pos );

			//  check collision w/ its own body
			if ( dynamic_cast<TileSnake*>( tile ) )
			{
				die();
				return;
			}
			//  check collision w/ apple
			else if ( auto apple = dynamic_cast<TileApple*>( tile ) )
			{
				_score++;
				apple->eat();
				increase_length();

				_level->shake( 0.5f );

				//  play sound
				SetSoundPitch( _sound_grow, 1.0f + (float) GetRandomValue( 0, 100 ) / 100.0f * .5f );
				PlaySound( _sound_grow );
			}
		}

		//  move
		for ( TileSnake* tile : _tiles )
		{
			Int2 last_pos = tile->get_pos();
			tile->set_pos( next_pos );
			next_pos = last_pos;
		}

		//  set move dir
		_last_move_dir = _move_dir;
	}
}

void Player::draw()
{
	int font_size = 64;

	//  draw score
	const char* text = TextFormat( "%03d", _score );
	util::draw_centered_text( text, (float) SCREEN_WIDTH / 2, font_size * .75, font_size, WHITE );
	
	//  draw game over screen
	if ( !_is_game_running )
	{
		util::draw_centered_text( "GAME OVER", SCREEN_WIDTH / 2 - font_size, SCREEN_HEIGHT / 2, font_size * 2, WHITE );
		
		Color blink_color { 255, 255, 255, abs( sin( GetTime() * 4.0 ) ) * 255 };
		util::draw_centered_text( "Press 'SPACE' to restart!", SCREEN_WIDTH / 2 - font_size / 2, SCREEN_HEIGHT / 2 + font_size * 1.5f, font_size / 2, blink_color );
	}
}

void Player::increase_length()
{
	add_tile( _tiles[_tiles.size() - 1]->get_pos() + Int2 { -_move_dir.x, -_move_dir.y } );
}

void Player::add_tile( const Int2 pos )
{
	TileSnake* tile = new TileSnake( pos, _level, _tiles.size() );
	_tiles.push_back( tile );
}

void Player::die()
{
	printf( "dead\n" );
	_is_game_running = false;

	_level->shake( 1.5f );

	PlaySound( _sound_ouch );
}
