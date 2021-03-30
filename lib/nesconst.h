/*NES Constants and Macros binded together in one place.
* These include macros for Memory Read Write,Colors,GamePad,PPU,NameTable,Palette and Other constants.
* Haseeb Mir - 02-25-2021
*/

#ifndef _NES_CONST_H_
#define _NES_CONST_H_
#include <stdint.h>

//Macros for NULL & Bools.
#define NULL 0
enum NES_BOOL
{
    FALSE,
    TRUE
};

/*NES standard data types defined 
NOTE : 64-bit datatype not supported.*/
#ifndef _STDDEF_H
typedef unsigned long size_t;
#endif

//Macros for Video Region.
enum NES_REGION
{
    REGION_NTSC,
    REGION_PAL,
    REGION_DENDY
};


//Constants & Macros for Read & Write data.
#define NES_WRITE(addr, val) (*(uint8_t *)(addr) = (val))
#define NES_READ(addr) (*(uint8_t *)(addr))
#define HIGH_BYTE(c) *((uint8_t *)&c + 1)
#define LOW_BYTE(c) *((uint8_t *)&c)

//Constants for Color emphasis.
#define COL_EMP_BLUE 0x80
#define COL_EMP_GREEN 0x40
#define COL_EMP_RED 0x20
#define COL_EMP_NORMAL 0x00
#define COL_EMP_DARK 0xe0

//Macros for Joypad.
typedef enum NES_PAD
{
    PAD_RIGHT = (1 << 0),
    PAD_LEFT = (1 << 1),
    PAD_DOWN = (1 << 2),
    PAD_UP = (1 << 3),
    PAD_START = (1 << 4),
    PAD_SELECT = (1 << 5),
    PAD_B = (1 << 6),
    PAD_A = (1 << 7)
};

#define OAM_FLIP_V 0x80
#define OAM_FLIP_H 0x40
#define OAM_BEHIND 0x20

#define MASK_SPR 0x10
#define MASK_BG 0x08
#define MASK_EDGE_SPR 0x04
#define MASK_EDGE_BG 0x02

#define NAMETABLE_A 0x2000
#define NAMETABLE_B 0x2400
#define NAMETABLE_C 0x2800
#define NAMETABLE_D 0x2c00

#define NT_UPD_HORZ 0x40
#define NT_UPD_VERT 0x80
#define NT_UPD_EOF 0xff

//macro to calculate nametable address from X,Y in compile time

#define NTADR_A(x, y) (NAMETABLE_A | (((y) << 5) | (x)))
#define NTADR_B(x, y) (NAMETABLE_B | (((y) << 5) | (x)))
#define NTADR_C(x, y) (NAMETABLE_C | (((y) << 5) | (x)))
#define NTADR_D(x, y) (NAMETABLE_D | (((y) << 5) | (x)))

//macro to get MSB and LSB

#define MSB(x) (((x) >> 8))
#define LSB(x) (((x)&0xff))

//Define tiles and screen size.
#define TILES_X 30
#define TILES_Y 28
#define SCREEN_H 256
#define SCREEN_V 240

//NES Color palettes generated using NESDev reference https://wiki.nesdev.com/w/index.php/PPU_palettes.

/*****************************************************************
First block of Palette ranging from (0x00 - 0x0F) --> DARK COLORS.
*****************************************************************/
typedef enum NES_COLORS_DARK
{
    NES_COLOR_GRAY,
    NES_COLOR_DARK_BLUE,
    NES_COLOR_PURE_BLUE,
    NES_COLOR_PURPLE,
    NES_COLOR_DARK_MAGENTA,
    NES_COLOR_DARK_PINK,
    NES_COLOR_MAROON,
    NES_COLOR_BROWN,
    NES_COLOR_DARK_BROWN,
    NES_COLOR_DARK_GREEN,
    NES_COLOR_LIME_GREEN,
    NES_COLOR_DARK_LIME_GREEN,
    NES_COLOR_DARK_CYAN,
    NES_COLOR_BLACK
    //(0x0D - 0x0F) Black shades not defined in NESDev reference.
};

/*******************************************************************
Second block of Palette ranging from (0x10 - 0x1F) --> MEDIUM COLORS
********************************************************************/
typedef enum NES_COLORS_MEDIUM
{
    _NES_BLANK_MEDIUM = 0xF,
    NES_COLOR_MEDIUM_GRAY,
    NES_COLOR_CYAN_BLUE,
    NES_COLOR_BLUE,
    NES_COLOR_VIOLET,
    NES_COLOR_MEDIUM_VIOLET,
    NES_COLOR_PINK,
    NES_COLOR_RED,
    NES_COLOR_DARK_ORANGE,
    NES_COLOR_OLIVE,
    NES_COLOR_FOREST_GREEN,
    NES_COLOR_MEDIUM_GREEN,
    NES_COLOR_CYAN_GREEN,
    NES_COLOR_MEDIUM_CYAN
    //(0x1D - 0x1F) - Gray shades not defined in NESDev reference.
};

/*****************************************************************
Third block of Palette ranging from (0x20 - 0x2F) --> LIGHT COLORS
******************************************************************/
typedef enum NES_COLORS_LIGHT
{
    _NES_BLANK_LIGHT = 0x1E,
    NES_COLOR_MEDIUM_BLUE,
    NES_COLOR_LIGHT_BLUE,
    NES_COLOR_LIGHT_VIOLET,
    NES_COLOR_MAGENTA,
    NES_COLOR_LIGHT_MAGENTA,
    NES_COLOR_ORANGE,
    NES_COLOR_DARK_YELLOW,
    NES_COLOR_YELLOW,
    NES_COLOR_LIGHT_ORANGE,
    NES_COLOR_GREEN,
    NES_COLOR_TURQUOISE,
    NES_COLOR_AQUA
    //(0x2D - 0x2F) - Gray shades not defined in NESDev reference.
};

/**********************************************************************
Fourth block of Palette ranging from (0x30 - 0x3F) --> VERY LIGHT COLORS
***********************************************************************/

typedef enum NES_COLORS_VERY_LIGHT
{
    NES_COLOR_WHITE = 0x30,
    NES_COLOR_PALE_BLUE,
    NES_COLOR_PALE_VIOLET,
    NES_COLOR_PALE_MAGENTA,
    NES_COLOR_VERY_LIGHT_MAGENTA,
    NES_COLOR_PALE_RED,
    NES_COLOR_PALE_ORANGE,
    NES_COLOR_LIGHT_YELLOW,
    NES_COLOR_VERY_LIGHT_YELLOW,
    NES_COLOR_LIGHT_GREEN,
    NES_COLOR_LIGHT_LIME_GREEN,
    NES_COLOR_LIGHT_TURQUOISE,
    NES_COLOR_LIGHT_AQUA
    //(0x3D - 0x3F)  White shades not defined in NESDev reference.
};

//Palette informations Background,CHR types etc.
#define PALETTE_NUMS 8    // (4x4 = 8) 4 Background Palette and 4 CHR Palette for sprites
#define PALETTE_GROUPS 4  /* Each palette has 4 groups. 0 to 1 = Background control color,text. \
 2 to 3 = Foreground control color,text*/
#define PALETTE_BG_NUMS 4 //4 Background palettes.
#define PALETTE_FG_NUMS 4 //4 Foreground palettes.

typedef enum PALETTE_TYPES
{
    PALETTE_TYPE_BG,      //Background palette for Objects only.
    PALETTE_TYPE_SPR,     //Foreground palette for Sprites only.
    PALETTE_TYPE_ALL = -1 //Both Objects and Sprites.
};

//Macros for writing binary.
#define bin(h, g, f, e, d, c, b, a) (a | b << 1 | c << 2 | d << 3 | e << 4 | f << 5 | g << 6 | h << 7)
#define bin8(h, g, f, e, d, c, b, a) (a | b << 1 | c << 2 | d << 3 | e << 4 | f << 5 | g << 6 | h << 7)
#define bin7(g, f, e, d, c, b, a) (a | b << 1 | c << 2 | d << 3 | e << 4 | f << 5 | g << 6)
#define bin6(f, e, d, c, b, a) (a | b << 1 | c << 2 | d << 3 | e << 4 | f << 5)
#define bin5(e, d, c, b, a) (a | b << 1 | c << 2 | d << 3 | e << 4)
#define bin4(d, c, b, a) (a | b << 1 | c << 2 | d << 3)
#define bin3(c, b, a) (a | b << 1 | c << 2)
#define bin2(b, a) (a | b << 1)

#endif