#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NF_2D_H__
#define __NF_2D_H__





// NightFox LIB - Include common 2D functions
// Requires DevkitARM
// Code by Cesar Rincon "NightFox"
// http://www.nightfoxandco.com/
// Version 20140413



// Includes devKitPro
#include <nds.h>





// Function NF_Set2D();
// Starts the selected 2D mode on the desired screen
void NF_Set2D(u8 screen, u8 mode);




// Function NF_ShowBg();
// Make the background of the given layer and screen visible
void NF_ShowBg(u8 screen, u8 layer);



// Function NF_HideBg();
// Hide the background of the given layer and screen
void NF_HideBg(u8 screen, u8 layer);




// Function NF_ScrollBg();
// Move the background to the specified coordinates.
// You must indicate the screen, layer, and X and Y coordinates
// If the map is greater than 512 in some measure, you must keep the background in RAM
void NF_ScrollBg(u8 screen, u8 layer, s16 x, s16 y);


// Function NF_MoveSprite();
// Move the Sprite to the specified coordinates
// You must indicate the screen, sprite id and coordinates
void NF_MoveSprite(u8 screen, u8 id, s16 x, s16 y);



// Function NF_SpriteLayer();
// Define the layer on which the sprite will be drawn
// You must indicate the screen, id of the sprite and layer
void NF_SpriteLayer(u8 screen, u8 id, u8 layer);



// Function NF_ShowSprite();
// Show or hide the sprite
// You must specify the screen, sprite id and state (true, false)
void NF_ShowSprite(u8 screen, u8 id, bool show);



// Function NF_HflipSprite();
// Flip the Sprite horizontally
// You must specify the screen, sprite id and state (true, false)
void NF_HflipSprite(u8 screen, u8 id, bool hflip);



// Function NF_GetSpriteHflip();
// Returns the state of the horizontal flip of a sprite
// You must specify the screen and the id of the sprite
extern bool NF_GetSpriteHflip(u8 screen, u8 id);


// Function NF_VflipSprite();
// Flip the Sprite vertically
// You must specify the screen, sprite id and state (true, false)
void NF_VflipSprite(u8 screen, u8 id, bool vflip);


// Function NF_GetSpriteVflip();
// Returns the state of the vertical flip of a sprite
// You must specify the screen and the id of the sprite
extern bool NF_GetSpriteVflip(u8 screen, u8 id);


// Function NF_SpriteFrame();
// Change the frame of a Sprite
// You must specify the screen, the id of the sprite and the frame
void NF_SpriteFrame(u8 screen, u8 id, u16 frame);


// Function NF_EnableSpriteRotScale();
// Enable the sprite as rotatable and scalable.
// You must specify the screen, sprite number, rotation id and if the doublesize (size x2) has to be activated
void NF_EnableSpriteRotScale(u8 screen, u8 sprite, u8 id, bool doublesize);


// Function NF_DisableSpriteRotScale();
// Disable a sprite as rotatable and scalable
// You must specify the screen and the sprite number
void NF_DisableSpriteRotScale(u8 screen, u8 sprite);


// Function NF_SpriteRotScale();
// Define the rotation angle and scale of the Sprites associated with the Id.
// The range of the angle is from -512 to 512, with 0 being the central value
// The scaling range is from 0 to 512, 256 being the normal value (100%)
void NF_SpriteRotScale(u8 screen, u8 id, s16 angle, u16 sx, u16 sy);





#endif

#ifdef __cplusplus
}
#endif
