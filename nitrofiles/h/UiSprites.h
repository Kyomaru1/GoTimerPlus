
//{{BLOCK(UiSprites)

//======================================================================
//
//	UiSprites, 256x256@4, 
//	Transparent color : FF,00,BB
//	+ palette 256 entries, not compressed
//	+ 43 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 16x16 
//	Metatiled by 2x2
//	Total size: 512 + 1376 + 144 + 512 = 2544
//
//	Time-stamp: 2020-08-28, 21:39:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_UISPRITES_H
#define GRIT_UISPRITES_H

#define UiSpritesTilesLen 1376
extern const unsigned int UiSpritesTiles[344];

#define UiSpritesMetaTilesLen 144
extern const unsigned short UiSpritesMetaTiles[72];

#define UiSpritesMetaMapLen 512
extern const unsigned short UiSpritesMetaMap[256];

#define UiSpritesPalLen 512
extern const unsigned short UiSpritesPal[256];

#endif // GRIT_UISPRITES_H

//}}BLOCK(UiSprites)
