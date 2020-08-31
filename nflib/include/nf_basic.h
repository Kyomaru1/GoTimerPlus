#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NF_BASIC_H__
#define __NF_BASIC_H__





// NightFox LIB - Include de funciones basicas
// Requiere DevkitARM
// Codigo por Cesar Rincon "NightFox"
// http://www.nightfoxandco.com/
// Version 20140413



// Includes devKitPro
#include <nds.h>


// Define la variable global NF_ROOTFOLDER
extern char NF_ROOTFOLDER[32];



// Function NF_Error();
// Generates an error and stops program execution, showing on the screen the error.
// This command it’s internaly used by the lib to generate debug messages and rarely will
// be used in you code.
void NF_Error(u16 code, const char* text, u32 value);
// Errors for debug. Stops the system and reports the error
// 101: File not found
// 102: Out of memory
// 103: There are no free slots
// 104: Background not found
// 105: Background not created
// 106: Out of range
// 107: Insufficient contiguous blocks in VRAM (Tiles)
// 108: Insufficient contiguous blocks in VRAM (Maps)
// 109: Id busy (already in use)
// 110: Id not loaded (in RAM)
// 111: Id not in VRAM
// 112: Sprite not created
// 113: Insufficient VRAM memory
// 114: Text layer does not exist
// 115: Unsupported background measurements (not multiples of 256)
// 116: File too large
// 117: Incorrect affine fund measurements
// 118: Wrong affine background creation layer



// Function NF_SetRootFolder();
/*
Defines the root folder of your project then inits the filesystem (FAT or NitroFS).
This makes easy change the name of folder that contains all files of your project afterit’s compiled. 
It’s imperative the use of this function before load any file from FAT.
If you want to use NitroFS, use “NITROFS” as root folder name. 
You must copy the right MAKEFILE on the root of your project to enable NitroFS usage. 
Also you has to put all files you want to load in “nitrofiles” folder.
*/
void NF_SetRootFolder(const char* folder);



// Function NF_DmaMemCopy();
/*
Function to fast copy blocks of memory from RAM to VRAM (because it’s the kind of copy where DMA copy it’s most effective). 
The function checks if data it’s aligned for DMA copy, if not, uses memcpy(); command insead.
*/
void NF_DmaMemCopy(void* destination, const void* source, u32 size);


// Function NF_GetLanguage();
/*
Returns the user language ID.
0 : Japanese
1 : English
2 : French
3 : German
4 : Italian
5 : Spanish
6 : Chinese
*/
extern u8 NF_GetLanguage(void);






#endif

#ifdef __cplusplus
}
#endif
