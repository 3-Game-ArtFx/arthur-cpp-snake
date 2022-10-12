#pragma once

#include <vector>

#include <src/ientity.h>
#include <src/tile_snake.h>

class Player : public IEntity
{
public:
	const float MOVE_TIME = .25f;
private:
	Level* level;
	std::vector<TileSnake*> tiles;

	float current_move_time;
	Int2 move_dir, last_move_dir;

	int score = 0;
	bool is_game_running = true;

	Sound sound_ouch;
	Sound sound_grow;
public:
	Player( const Int2 pos, Level* level );
	~Player();

	bool try_set_move_dir( const Int2 move_dir );

	void reset();
	void clear_tiles();

	void update( float dt ) override;
	void draw() override;

	void increase_length();
	void add_tile( const Int2 pos );

	void die();
};

