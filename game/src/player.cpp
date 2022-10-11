#include "player.h"

#include "level.h"
#include <src/tile_apple.h>
#include <string>
#include <src/util_draw.h>

Player::Player( const Int2 pos, Level* level )
	: level( level )
{
	reset();
}

Player::~Player()
{
	clear_tiles();
}

void Player::clear_tiles()
{
	for ( TileSnake* tile : tiles )
	{
		delete tile;
	}
	tiles.clear();
}

bool Player::try_set_move_dir( const Int2 new_move_dir )
{
	if ( new_move_dir.x == -move_dir.x && new_move_dir.y == -move_dir.y ) return false;

	move_dir = new_move_dir;
	return true;
}

void Player::reset()
{
	clear_tiles();
	add_tile( level->get_center_position() );

	current_move_time = MOVE_TIME;
	move_dir = Int2 { 1, 0 };

	is_game_running = true;
}

void Player::update( float dt )
{
	if ( !is_game_running )
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
	if ( ( current_move_time -= dt ) <= 0.0f )
	{
		//  reset timer
		current_move_time += MOVE_TIME;

		//  get next pos
		Int2 next_pos = tiles[0]->get_pos() + move_dir;

		//  check out of bounds
		if ( !level->is_in_bounds( next_pos ) )
		{
			die();
			return;
		}
		if ( level->has_entity_at( next_pos ) )
		{
			TileEntity* tile = level->get_entity_at( next_pos );

			//  check collision w/ its own body
			if ( dynamic_cast<TileSnake*>( tile ) )
			{
				die();
				return;
			}
			//  check collision w/ apple
			else if ( auto apple = dynamic_cast<TileApple*>( tile ) )
			{
				apple->eat();
				increase_length();
			}
		}

		//  move
		for ( TileSnake* tile : tiles )
		{
			Int2 last_pos = tile->get_pos();
			tile->set_pos( next_pos );
			next_pos = last_pos;
		}
	}
}

void Player::draw()
{
	//  draw score
	int font_size = 64;

	const char* text = TextFormat( "%03d", tiles.size() - 1 );
	util::draw_centered_text( text, (float) SCREEN_WIDTH / 2, font_size * .75, font_size, LIGHTGRAY );
	
	//  draw game over screen
	if ( !is_game_running )
	{
		util::draw_centered_text( "GAME OVER", SCREEN_WIDTH / 2 - font_size, SCREEN_HEIGHT / 2, font_size * 2, WHITE );
		
		Color blink_color { 255, 255, 255, abs( sin( GetTime() * 4.0 ) ) * 255 };
		util::draw_centered_text( "Press 'SPACE' to restart!", SCREEN_WIDTH / 2 - font_size / 2, SCREEN_HEIGHT / 2 + font_size * 1.5f, font_size / 2, blink_color );
	}
}

void Player::increase_length()
{
	add_tile( tiles[tiles.size() - 1]->get_pos() + Int2 { -move_dir.x, -move_dir.y } );
}

void Player::add_tile( const Int2 pos )
{
	TileSnake* tile = new TileSnake( pos, level, tiles.size() );
	tiles.push_back( tile );
}

void Player::die()
{
	printf( "dead\n" );
	is_game_running = false;
}
