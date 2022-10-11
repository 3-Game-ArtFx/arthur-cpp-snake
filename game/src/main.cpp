#include <raylib.h>

#include <iostream>

#include <src/level.h>
#include <src/player.h>
#include <src/tile_apple.h>

static Level level;
static Player* player;
static TileApple* apple;

void init()
{
	player = new Player( Int2 { 5, 5 }, &level );
	apple = new TileApple( level.get_random_free_position(), &level );
}

void update( float dt )
{
	player->update( dt );
	level.update( dt );
}

void draw()
{
	BeginDrawing();
	ClearBackground( GRAY );

	level.push_view();
	level.draw();
	level.pop_view();

	player->draw();

	//  draw screen diagonals
	//DrawLine( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, RED );
	//DrawLine( SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, RED );

	EndDrawing();
}

void release()
{
	delete player;
	delete apple;
}


int main()
{
	InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE );
	SetTargetFPS( 60 );

	InitAudioDevice();

	init();

	while ( !WindowShouldClose() )
	{
		float dt = GetFrameTime();
		update( dt );
		draw();
	}

	release();

	CloseWindow();
	CloseAudioDevice();

	return 0;
}