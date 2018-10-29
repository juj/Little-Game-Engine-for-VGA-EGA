/***********************
*  LITTLE GAME ENGINE  *
************************/
#include "n_engine.h"

SPRITE sprite_player;

int Scene = 0;

void Set_Platform(){
	MCGA_ClearScreen();
	printf("Loading...\n");
	Scene = 2;
	load_map("GFX/mario.tmx");
	load_tiles("GFX/mariotil.bmp");
	
	load_sprite("GFX/s_mario.bmp",&sprite_player,16);
	LT_Load_Music("music/platform.imf");
	LT_Start_Music(580);
	
	//animate colours
	LT_Set_Map(0,0);
	LT_Gravity = 1;
}

void Run_Platform(){
	Scene = 2;
	sprite_player.pos_x = 6*16;
	sprite_player.pos_y = 6*16;
	
	while(Scene == 2){
		MCGA_Scroll(SCR_X,SCR_Y);
		LT_scroll_follow(&sprite_player);
		
		LT_Draw_Sprite(&sprite_player);
		LT_scroll_map();
		
		LT_move_player(&sprite_player);

		if (LT_Keys[LT_RIGHT]) LT_Set_Sprite_Animation(&sprite_player,0,4,4);
		else if (LT_Keys[LT_LEFT]) LT_Set_Sprite_Animation(&sprite_player,6,4,4);
		else sprite_player.animate = 0;

		if (LT_Keys[LT_ESC]) Scene = -1; //esc exit
		
		
	}
	
	LT_unload_sprite(&sprite_player); //manually free sprites
}


void main(){
	
	system("cls");

	LT_Init();
	
	Set_Platform();
	Run_Platform();

	LT_ExitDOS(); //frees map, tileset, font and music.
	
	return;
}