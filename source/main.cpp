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

// Function Definitions.
void Initialize();
void InitBackgrounds();
void InitSprites();
void InitTimerDisplays(int player, int screen);
void InitIndicatorSprites();
void SetTimerStartupState(int player, int screen);

// Main
int main(void) {
	Initialize();
	consoleClear();
	setBrightness(3,0);
	
	InitBackgrounds();
	InitSprites();
	
	SetTimerStartupState(1, 0);
	SetTimerStartupState(2, 0);
	
	do{
		NF_SpriteOamSet(0);
		swiWaitForVBlank();
		oamUpdate(&oamMain);
	} while(true);

	return 0;
}


// Function Code
void Initialize(){
	consoleDemoInit();
	NF_Set2D(0,0);
	NF_SetRootFolder("NITROFS");
}

void InitTimerDisplays(int player, int screen){

	for(int i = 0; i < 9; i++){
		int id = 10 * player + i;
		NF_LoadSpriteGfx(
			"sprites/large_numbers",
			id,
			16,
			32);
		NF_LoadSpritePal(
			"sprites/large_numbers",
			id
		);
		NF_VramSpriteGfx(
			screen,
			id,
			id,
			true
		);
		NF_VramSpritePal(
			screen,
			id,
			10
		);
	}

	for(int i = 0; i < 9; i++){
		int id = 10 * player + i;
		int offset = 0;
		if(player == 2){
			offset = 32;
		}
		NF_CreateSprite(screen, id, id, 10, (16*(i+1)) + (1+i), 32 * player + offset);
	}
}

void InitBackgrounds(){
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
	
	NF_LoadTiledBg("backgrounds/topback2", "a", 256, 256);
	NF_LoadTiledBg("backgrounds/botback", "b", 256, 256);
	NF_CreateTiledBg(0,0,"a");
	NF_CreateTiledBg(1,0,"b");
}

void InitIndicatorSprites(){
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

	//ABXY Indicator
	NF_LoadSpriteGfx("sprites/topabxy", 2, 16, 16);
	NF_LoadSpritePal("sprites/topabxy", 2);
	NF_VramSpriteGfx(0, 2, 2, false);
	NF_VramSpritePal(0, 2, 2);
	
	//Cross Indicator
	NF_LoadSpriteGfx("sprites/topcross", 3, 16, 16);
	NF_LoadSpritePal("sprites/topcross", 3);
	NF_VramSpriteGfx(0, 3, 3, false);
	NF_VramSpritePal(0, 3, 3);

	s16 spritexy[4][2] = {
		{170,  32}, 
		{170,  48}, 
		{170,  96}, 
		{170, 112}
	};
	for(int i = 0; i < 4; i++){
		NF_CreateSprite(0, i, i, i, spritexy[i][0], spritexy[i][1]);
	}
}

void InitSprites(){
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);

	for(int i = 1; i <= 2; i++){
		InitTimerDisplays(i, 0);
	}

	InitIndicatorSprites();

}

void SetTimerStartupState(int player, int screen){
	for(int i = 0; i < 9; i++){
		int id = 10 * player + i;
		switch (i)
		{
		case 3:
		case 6:
			NF_SpriteFrame(screen, id, 10);
			break;
		
		default:
			NF_SpriteFrame(screen, id, 0);
			break;
		}
	}
}
