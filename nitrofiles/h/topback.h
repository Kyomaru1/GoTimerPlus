
//{{BLOCK(topback)

//======================================================================
//
//	topback, 256x256@4, 
//	Transparent color : FF,00,BB
//	+ palette 16 entries, not compressed
//	+ 15 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 480 + 2048 = 2560
//
//	Time-stamp: 2020-08-29, 23:35:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TOPBACK_H
#define GRIT_TOPBACK_H

#define topbackTilesLen 480
extern const unsigned int topbackTiles[120];

#define topbackMapLen 2048
extern const unsigned short topbackMap[1024];

#define topbackPalLen 32
extern const unsigned short topbackPal[16];

#endif // GRIT_TOPBACK_H

//}}BLOCK(topback)
