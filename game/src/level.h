#pragma once
#include "level.fwd.h"

#include <raylib.h>
#include <unordered_map>

#include <src/ientity.h>
#include <src/tile_entity.h>
#include <src/screen.h>
#include <src/int2.h>

class Level : public IEntity
{
public:
	const int WIDTH = 16;
	const int HEIGHT = 16;
	const int PADDING = 127;
	const int TILE_MARGIN = 4;
	const int TILE_SIZE = ( SCREEN_HEIGHT - TILE_MARGIN * HEIGHT - PADDING ) / HEIGHT;
private:
	Camera2D _camera;

	std::unordered_map<Int2, TileEntity*, Int2Hasher> _entities;

	float _shake_intensity = 0.0f;

	int _x = 0, _y = 0;
	int _x_margin = 0, _y_margin = 0;
public:
	Level();

	void update( float dt ) override;
	void draw() override;

	void draw_rectangle( Color color );

	void push_view() { BeginMode2D( _camera ); }
	void pop_view() { EndMode2D(); }
	void shake( float intensity );

	bool add_entity( TileEntity* entity );
	bool remove_entity( TileEntity* entity );
	bool has_entity_at( const Int2 pos );
	TileEntity* get_entity_at( const Int2 pos );

	bool is_in_bounds( const Int2 pos );
	Int2 get_random_free_position();
	Int2 get_center_position();
};

