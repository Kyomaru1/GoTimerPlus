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
#include <maxmod9.h>
#include "common/nitrofs.h"

#include "soundbank.h"
#include "soundbank_bin.h"
// #include "SmallFontSprites.h"
#include "UiSprites.h"
#include "LargeNumberSprites.h"
#include "font.h"
#include "font6x8.h"
#include "TimerSystem.h"
#include "TopBackground.h"
#include "graphics.h"

#define POS2IDX(x, y)    (x + (y*32))
#define TIMER_SPEED (BUS_SPEED/1024)
#define TILE_FLIP_NONE    (0 << 10)
#define TILE_FLIP_X       (1 << 10)
#define TILE_FLIP_Y       (2 << 10)
#define TILE_FLIP_XY      (TILE_FLIP_X | TILE_FLIP_Y)
#define TILE_PAL(n) ((n) << 12)


const int32 TWENTYFOUR_HOURS_IN_MS = 0x5265C00;
//---------------------------------------------------------------------------------
//static const int DMA_CHANNEL = 3;
uint16 blank_count = 0;
Time p1mainTime = Time(0, 29, 10);
Time p2mainTime = Time(0, 30, 0);
// uint16 mainTime_P1 = 15;
// uint16 mainTime_P2 = 15;
// uint8 consumedVblank_P1 = blank_count,
// 	  consumedVblank_P2 = blank_count;

int8 playerTurn = -1;
bool beepPlaying = false;
bool timePause = true;
bool leftIsP1 = false;
uint8 turnNumber = 1;

typedef struct 
{
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8* frame_gfx;

	int state;
	int anim_frame;
	
} Sprite;

enum SpriteStateDigit {
	S_ZERO  = 0,
	S_ONE   = 1,
	S_TWO   = 2,
	S_THREE = 3,
	S_FOUR  = 4,
	S_FIVE  = 5,
	S_SIX   = 6,
	S_SEVEN = 7,
	S_EIGHT = 8,
	S_NINE  = 9
};

void animateMainTimeDigit(Sprite *digit){
	int frame = digit -> anim_frame + digit -> state;
	u8* offset = digit-> frame_gfx + frame * 16*32;
	dmaCopy(offset, digit->sprite_gfx_mem, 16*32);
}

void initMainTimeDigit(Sprite *digit, u8* gfx){
	digit -> sprite_gfx_mem = oamAllocateGfx(
		&oamMain, 
		SpriteSize_16x32, 
		SpriteColorFormat_256Color
	);

	digit -> frame_gfx = (u8*)gfx;
}

void initBackgrounds(){
	// REG_BG3CNT = BG_BMP16_256x256 |
	// 			 BG_BMP_BASE(0) |
	// 			 BG_PRIORITY(3);

	// REG_BG3PA = 1 << 8;
	// REG_BG3PB = 0;
	// REG_BG3PC = 0;
	// REG_BG3PD = 1 << 8;

	// REG_BG3X = 0;
	// REG_BG3Y = 0;
	bgInit(3, BgType_ExRotation, BgSize_ER_256x256, true, false);
	bgInit(2, BgType_Rotation, BgSize_R_256x256, true, false);
	bgInit(0, BgType_Text8bpp, BgSize_T_256x256, true, false);

	// bgInitSub(3, BgType_ExRotation, BgSize_ER_256x256, true, false);
	// bgInitSub(2, BgType_Rotation, BgSize_R_256x256, true, false);
	// bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, true, false);

}

void writeToConsole(){
	printf("\x1b[2J");
		// printf("%d\n",mainTime_P1);
		// printf("%d\n",mainTime_P2);
		printf("Player 1:\n");
		printf("%02d:%02d:%02d\n", p1mainTime.hours, p1mainTime.minutes, p1mainTime.seconds);
		printf("\nPlayer 2:\n");
		printf("%02d:%02d:%02d\n", p2mainTime.hours, p2mainTime.minutes, p2mainTime.seconds);
		printf("\n\nPlayerTurn: %d", playerTurn);
		if(timePause){
			printf("\nTime is Paused");
			printf("\nTurn Number: %03d\n", turnNumber);
		}
		else
			printf("\n\nTurn Number: %03d\n", turnNumber);
		printf("\nP1 Consumed Vblank: %d\n", p1mainTime.vblankConsumed);
		printf("P2 Consumed Vblank: %d\n", p2mainTime.vblankConsumed);
		printf("%d\n", blank_count);
		if(leftIsP1 && playerTurn != -1)
			printf("Player 1 is D-Pad Side");
		else if(!leftIsP1 && playerTurn != -1)
			printf("Player 1 is ABXY Side");
}

void displayTopScreenTimerBackground() {
	// tiles for top screen background

	// memcpy((void*) BG_TILE_RAM(1), TopBackgroundBitmap, TopBackgroundBitmapLen);
	// memcpy((void*) BG_PALETTE, TopBackgroundPal, TopBackgroundPalLen );
	
}

void displayTopScreenTextLayer(){

}

void initVideo(){
	vramSetPrimaryBanks(
		VRAM_A_MAIN_BG_0x06000000,
		VRAM_B_MAIN_BG_0x06040000,
		VRAM_C_MAIN_BG_0x06060000,
		VRAM_D_LCD);

	videoSetMode(
		MODE_2_2D |
		DISPLAY_BG2_ACTIVE |
		DISPLAY_BG3_ACTIVE |
		DISPLAY_BG0_ACTIVE
	);

	videoSetModeSub(
		MODE_2_2D |
		DISPLAY_BG2_ACTIVE
	);
	oamInit(&oamMain, SpriteMapping_Bmp_1D_256, false);
}

void dsi_callback_quitToMenu(){

}



int main(void) {
//---------------------------------------------------------------------------------
	powerOn(POWER_ALL_2D);

	// consoleDebugInit(DebugDevice_NOCASH);
	// consoleDemoInit();
	// consoleInit(
	// 	NULL,
	// 	0,
	// 	BgType_Text8bpp,
	// 	BgSize_T_256x256,
	// 	0,
	// 	0,
	// 	true,
	// 	true
	// );

	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_TIMER_BEEP);
	
	mm_sound_effect timer_beep = {
		{SFX_TIMER_BEEP},
		(int)(1.0f*(1<<10)),
		0,
		255,
		255/2,
	};

	mm_sfxhand beep = 0;
	// int bg3 = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	// dmaCopyHalfWords(DMA_CHANNEL, topscreentimerBitmap, bgGetGfxPtr(bg3), topscreentimerBitmapLen);
	// initVideo();
	//initBackgrounds();
	
	bool graphicsInited = false;

	if(!graphicsInited){
		graphicsInit();
		graphicsInited = true;
	}

	// displayTopScreenTextLayer();
	//uint64 ticks= 0;

	// setPowerButtonCB(dsi_callback_quitToMenu);
	do {
		int keys_pressed, keys_released;
		swiWaitForVBlank();
		if(!timePause){
			blank_count++;
		}
		scanKeys();
		keys_pressed = keysDown();
		keys_released = keysUp();

		// if(blank_count == 60){
		// 	if(playerTurn == 0){
		// 		// mainTime_P1--;
		// 	}

		// 	if(playerTurn == 1){
		// 		// mainTime_P2--;
		// 	}
		// 	blank_count = 0;
		// }
		if(!timePause){
			if(playerTurn == 0 && blank_count <= 60){
				p1mainTime.tickTimeDown1Vblank(blank_count);
				if(blank_count == 60)
					blank_count = 0;
			}
			else if(playerTurn == 1 && blank_count <= 60){
				p2mainTime.tickTimeDown1Vblank(blank_count);
				if(blank_count == 60)
					blank_count = 0;
			}
		}

		//right side player controls
		//right side player is player 1;
		if ((
			keys_pressed & KEY_A ||
			keys_pressed & KEY_B ||
			keys_pressed & KEY_X ||
			keys_pressed & KEY_Y
			) && playerTurn == 0
			&& !leftIsP1){
			playerTurn = 1;
			// consumedVblank_P1 = blank_count;
			// blank_count = consumedVblank_P2;
			p1mainTime.setVblankConsumed(blank_count);
			blank_count = p2mainTime.vblankConsumed;
			turnNumber++;	
		}
		//right side player is player 2;
		else if((
			keys_pressed & KEY_A ||
			keys_pressed & KEY_B ||
			keys_pressed & KEY_X ||
			keys_pressed & KEY_Y
			) && playerTurn == 1
			&& leftIsP1){
			playerTurn = 0;
			// consumedVblank_P1 = blank_count;
			// blank_count = consumedVblank_P2;
			p2mainTime.setVblankConsumed(blank_count);
			blank_count = p1mainTime.vblankConsumed;
			turnNumber++;
		}

		//Left side player controls;
		//Left side player is player 1
		if ((
			keys_pressed & KEY_LEFT ||
			keys_pressed & KEY_UP ||
			keys_pressed & KEY_RIGHT ||
			keys_pressed & KEY_DOWN
			) && playerTurn == 0
			&& leftIsP1){
			playerTurn = 1;
			// consumedVblank_P2 = blank_count;
			// blank_count = consumedVblank_P1;
			p1mainTime.setVblankConsumed(blank_count);
			blank_count = p2mainTime.vblankConsumed;
			turnNumber++;
		}
		//Left side player is player 2
		if ((
			keys_pressed & KEY_LEFT ||
			keys_pressed & KEY_UP ||
			keys_pressed & KEY_RIGHT ||
			keys_pressed & KEY_DOWN
			) && playerTurn == 1
			&& !leftIsP1){
			playerTurn = 0;
			// consumedVblank_P2 = blank_count;
			// blank_count = consumedVblank_P1;
			p2mainTime.setVblankConsumed(blank_count);
			blank_count = p1mainTime.vblankConsumed;
			turnNumber++;
		}
		
		if(playerTurn == -1){
			if(
				keys_pressed & KEY_LEFT ||
				keys_pressed & KEY_UP ||
				keys_pressed & KEY_RIGHT ||
				keys_pressed & KEY_DOWN
			){
				//first player to press button will determine who is player 1
				//This is how real chess/go clocks operate, so emulate here.
				//The player who presses the button first is player 2
				playerTurn = 0;
				timePause = false;
				leftIsP1 = false;
			}
			else if(
				keys_pressed & KEY_A ||
				keys_pressed & KEY_B ||
				keys_pressed & KEY_X ||
				keys_pressed & KEY_Y
			){
				//first player to press button will determine who is player 1
				//This is how real chess/go clocks operate, so emulate here.
				//The player who presses the button first is player 2
				playerTurn = 0;
				timePause = false;
				leftIsP1 = true;
			}
		}

		// if((mainTime_P1<= 10) || 
		// 	  (mainTime_P2 <= 10)
		// 	  && blank_count == 60)
		// {
		// 	beep = mmEffectEx(&timer_beep);
			
			
		// }

		// if(mainTime_P1 == 0 || mainTime_P2 == 0){
		// 	mainTime_P1 = 999;
		// 	mainTime_P2 = 999;
		// }

		// if (keys_pressed & KEY_A){
		// 	amb = mmEffectEx(&timer_beep);
		// 	iprintf("\x1b[4;0HKey Pressed");
		// }
		// if (keys_released & KEY_A){
		// 	mmEffectCancel(amb);
		// 	iprintf("\x1b[5:0HKey Released");
		// }
		if(keys_pressed & KEY_START && !timePause) 
			timePause = true;
		
		else if(keys_pressed & KEY_START && timePause && playerTurn != -1)
			timePause = false;

		//debug: SELECT is to break for now;
		if(keys_pressed & KEY_SELECT)
			break;

	
		// printf("P1 Current VBlank Count: %d\n", consumedVblank_P1);
		// printf("P2 Current VBlank Count: %d\n", consumedVblank_P2);
		// mmEffectCancel(beep);
		// writeToConsole();
		
	} while(1);

	return 0;

}