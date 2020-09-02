
//{{BLOCK(botback)

//======================================================================
//
//	botback, 256x256@8, 
//	Transparent color : FF,00,BB
//	+ palette 256 entries, not compressed
//	+ 5 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 320 + 2048 = 2880
//
//	Time-stamp: 2020-09-01, 21:00:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOTBACK_H
#define GRIT_BOTBACK_H

#define botbackTilesLen 320
extern const unsigned int botbackTiles[80];

#define botbackMapLen 2048
extern const unsigned short botbackMap[1024];

#define botbackPalLen 512
extern const unsigned short botbackPal[256];

#endif // GRIT_BOTBACK_H

//}}BLOCK(botback)
