/*---------------------------------------------------------------------------------

GoTimerPlus:
	Stylized Go Game Timer for playing the game of Go;
	Top Screen will show timer outputs for each side:

	-------------------------------
	|						 23:59|
	|  Player 1: O+               |
	|  88:88:88                   |
	|  ------------               |
	|							  |
	|  Player 2: O+               |
	|  88:88:88                   |
	|  ------------               |
	|  							  |
	|  Turn: 999               *  |
	-------------------------------

	underneath the numbers in the timer display is a line, that flashes to 
	indicate the current active timer display. each blink should correspond to 
	2 (two) seconds: 1 sec visible, 1 second not visible.

	bottom screen will have the controls for setting up the timer;

	buttons for indicating finishing a turn should be tactile. all 4 dpad buttons 
	will be used for the left side and the abxy buttons will be used for the 
	right side.

	center of top screen will show current turn, as well as an icon to indicate 
	timeout-warning sounds being active. Also, top center will be a display to
	show the current system clock time.

	Graphics for the top screen will be styled to try and match that of a real
	digital game timer; skeumorphic.
		- segmented digital LCD display graphics.
			888:88:88

	Application will have the ability to save the user's settings for later use
	including setting 3 custom timer options. Will also include built in the
	standard time settings for a game of go
		- Standard times include:
			- NHK time;
				- 30 sec main time
				- JBY: 10 periods of 1 minute each.
			- Blitz
				- 15 minutes default
				- No overtime
			- Absolute Timing
				- Time configurable
				- JBY, CBY, or No overtime
				- This one is basically what is used to create custom profiles
					- Once options selected, SAVE button can be used to save to
					  one of the memory slots.

		* Japanese byo-yomi (JBY)
			- <Maintime> + <Number of periods> of <amount of overtime per period>
			-example:
				- 30 minutes + 10 periods of 60 seconds
				- once in overtime, a player has n number of seconds to
					make a move.
					- If a move is not made within that amount of time, the
						period is lost, and the next period is started.
					- making a move before the time runs out resets the period
					- If no periods are left, that player loses on time.
		* Canadian byo-yomi (CBY)
			- <Maintime> + <Number of moves> moves in <amount of overtime>
			- example:
				- 60 minutes + 20 moves in 5 minutes
					- Player has n seconds/minutes to make x number of moves
						- If player makes all those moves within n time,
							time resets, and another x moves must be made
						- If player fails to make x moves in n time, they lose
							on time.


	GRAPHICS NEEDED:
		- Segmented Display Sprites
		- UI elements
			- Buttons
			- Check buttons
			- Up/Down buttons for adjusting time amounts.
		- Top Screen background tiles
		- Bottom screen background tiles



	AUDIO NEEDED:
		- Timer Beep
		- Button Click
		- Switch Flip

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>

void Initialize();

int main(void) {
	Initialize();
	consoleClear();
	setBrightness(3,0);
	NF_LoadTiledBg("backgrounds/topback2", "a", 256, 256);
	NF_LoadTiledBg("backgrounds/botback", "b", 256, 256);
	NF_CreateTiledBg(0,0,"a");
	NF_CreateTiledBg(1,0,"b");

	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);

	//ABXY Indicator
	NF_LoadSpriteGfx("sprites/topabxy", 0, 16, 16);
	NF_LoadSpritePal("sprites/topabxy", 0);
	NF_VramSpriteGfx(0, 0, 0, false);
	NF_VramSpritePal(0, 0, 0);
	
	//Cross Indicator
	NF_LoadSpriteGfx("sprites/topcross", 1, 16, 16);
	NF_LoadSpritePal("sprites/topcross", 1);
	NF_VramSpriteGfx(0, 1, 1, false);
	NF_VramSpritePal(0, 1, 1);

	//Player 1
	//Large number test
	//00:00:00
	//^
	NF_LoadSpriteGfx("sprites/large_numbers", 2, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 2);
	NF_VramSpriteGfx(0, 2, 2, true);
	NF_VramSpritePal(0, 2, 2);
	//00:00:00
	// ^
	NF_LoadSpriteGfx("sprites/large_numbers", 3, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 3);
	NF_VramSpriteGfx(0, 3, 3, true);
	NF_VramSpritePal(0, 3, 3);
	//00:00:00
	//  ^
	NF_LoadSpriteGfx("sprites/large_numbers", 4, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 4);
	NF_VramSpriteGfx(0, 4, 4, true);
	NF_VramSpritePal(0, 4, 4);
	//00:00:00
	//   ^
	NF_LoadSpriteGfx("sprites/large_numbers", 5, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 5);
	NF_VramSpriteGfx(0, 5, 5, true);
	NF_VramSpritePal(0, 5, 5);
	//00:00:00
	//    ^
	NF_LoadSpriteGfx("sprites/large_numbers", 6, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 6);
	NF_VramSpriteGfx(0, 6, 6, true);
	NF_VramSpritePal(0, 6, 6);

	//00:00:00
	//     ^
	NF_LoadSpriteGfx("sprites/large_numbers", 7, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 7);
	NF_VramSpriteGfx(0, 7, 7, true);
	NF_VramSpritePal(0, 7, 7);
	//00:00:00
	//      ^
	NF_LoadSpriteGfx("sprites/large_numbers", 8, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 8);
	NF_VramSpriteGfx(0, 8, 8, true);
	NF_VramSpritePal(0, 8, 8);
	//00:00:00
	//       ^
	NF_LoadSpriteGfx("sprites/large_numbers", 9, 16, 32);
	NF_LoadSpritePal("sprites/large_numbers", 9);
	NF_VramSpriteGfx(0, 9, 9, true);
	NF_VramSpritePal(0, 9, 9);

	s16 spritexy[3][2] = {{152, 64}, {152, 80}, {16, 32}};
	NF_CreateSprite(0, 0, 0, 0, spritexy[0][0], spritexy[0][1]);
	NF_CreateSprite(0, 1, 1, 1, spritexy[1][0], spritexy[1][1]);
	//0 0 : 0  0  : 0  0
	//6 7 8 9 10 11 12 13
	NF_CreateSprite(0, 6,  2, 2, 16,    64);  //0
	NF_CreateSprite(0, 7,  3, 3, 32+1,  64);  //0
	NF_CreateSprite(0, 8,  4, 4, 48+2,  64);  //:
	NF_CreateSprite(0, 9,  5, 5, 64+3,  64);  //0
	NF_CreateSprite(0, 10, 6, 6, 80+4,  64);  //0
	NF_CreateSprite(0, 11, 7, 7, 96+5,  64);  //:
	NF_CreateSprite(0, 12, 8, 8, 112+6, 64);  //0
	NF_CreateSprite(0, 13, 9, 9, 128+7, 64);  //0

	
	
	do{
		
		// for(int i = 0; i  < 8; i++){
		// 	NF_SpriteFrame(0, 6 + i, i);
		// 	NF_MoveSprite(0, 6, 32 + (32 * i/2), 64);
			
		// }

		NF_SpriteFrame(0,  6, 9);
		NF_SpriteFrame(0,  7, 9);
		NF_SpriteFrame(0,  8, 10);
		NF_SpriteFrame(0,  9, 9);
		NF_SpriteFrame(0, 10, 9);
		NF_SpriteFrame(0, 11, 10);
		NF_SpriteFrame(0, 12, 9);
		NF_SpriteFrame(0, 13, 9);
		NF_SpriteOamSet(0);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		
		
	}while(true);
	return 0;
}

void Initialize(){
	consoleDemoInit();
	NF_Set2D(0,0);
	NF_SetRootFolder("NITROFS");
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
}