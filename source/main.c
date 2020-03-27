/*---------------------------------------------------------------------------------

	GoTimerPlus:
		Stylized Go Game Timer for playing the game of Go;
		Top Screen will show timer outputs for each side:
					  | 00:00 |
					  ---------
			-------------   -------------
			| 000:00:00 |   | 000:00:00 |
			|===========|   |===========|

		underneath the numbers in the timer display is a line, that flashes to 
		indicate the current active timer display. each blink should correspond to 
		1 (one) second

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
				888:88:88   888:88:88

		Application will have the ability to save the user's settings for later use
		including setting 3 custom timer options. Will also include built in the
		standard time settings for a game of go

			* Japanese byo-yomi
				- <Maintime> + <Number of periods> of <amount of overtime per period>
				-example:
					- 30 minutes + 10 periods of 60 seconds
					- once in overtime, a player has n number of seconds to
					  make a move.
						- If a move is not made within that amount of time, the
						  period is lost, and the next period is started.
		v				- making a move before the time runs out resets the period
						- If no periods are left, that player loses on time.
			* Canadian byo-yomi
				- <Maintime> + <Number of moves> moves in <amount of overtime>
			s	- example:
					- 60 minutes + 20 moves in 5 minutes
						- Player has n seconds/minutes to make x number of moves
							- If player makes all those moves within n time,
							  time resets, and another x moves must be made
							- If player fails to make x moves in n time, they lose
							  on time.


		GRAPHICS NEEDED:
			- Segmented Display Sprites


		AUDIO NEEDED:
			- Timer Beep
			- Button Click
			- Switch Flip

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	
	// consoleDebugInit(DebugDevice_NOCASH);
	// consoleDemoInit();
	consoleInit(
		NULL,
		0,
		BgType_Bmp16,
		BgSize_B16_256x256,
		0,
		0,
		true,
		true
	);

	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_TIMER_BEEP);
	
	mm_sound_effect timer_beep = {
		{SFX_TIMER_BEEP},
		(int)(1.0f*(1<<10)),
		0,
		255,
		0,
	};

	

	iprintf("\x1b[2J");
	iprintf("\x1b[0;8HMaxMod Audio Demo");
	iprintf("\x1b[3;0HPress any key for beep");

	mm_sfxhand amb = 0;

	do {
		int keys_pressed, keys_released;

		swiWaitForVBlank();
		scanKeys();
		keys_pressed = keysDown();
		keys_released = keysUp();

		if (keys_pressed & KEY_A){
			amb = mmEffectEx(&timer_beep);
			iprintf("\x1b[4;0HKey Pressed");
		}
		if (keys_released & KEY_A){
			mmEffectCancel(amb);
			iprintf("\x1b[5:0HKey Released");
		}
		if(keys_pressed & KEY_START) break;
	} while(1);

	return 0;

}
