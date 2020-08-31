
//{{BLOCK(botback)

//======================================================================
//
//	botback, 256x256@8, 
//	Transparent color : FF,00,BB
//	+ palette 256 entries, not compressed
//	+ 3 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 192 + 2048 = 2752
//
//	Time-stamp: 2020-08-30, 00:17:33
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOTBACK_H
#define GRIT_BOTBACK_H

#define botbackTilesLen 192
extern const unsigned int botbackTiles[48];

#define botbackMapLen 2048
extern const unsigned short botbackMap[1024];

#define botbackPalLen 512
extern const unsigned short botbackPal[256];

#endif // GRIT_BOTBACK_H

//}}BLOCK(botback)
