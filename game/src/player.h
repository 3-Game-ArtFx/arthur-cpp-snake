#pragma once

#include <vector>

#include <src/level.fwd.h>
#include <src/ientity.h>
#include <src/tile_snake.h>

class Player : public IEntity
{
public:
	const float MOVE_TIME = .25f;
private:
	Level* _level;
	std::vector<TileSnake*> _tiles;

	float _current_move_time;
	Int2 _move_dir, _last_move_dir;

	int _score = 0;
	bool _is_game_running = true;

	Sound _sound_ouch;
	Sound _sound_grow;
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

