/*
NESCLIB - NES-C-Library is helper library for original NES library by Shiru this includes more functionality
over neslib and include utilities made by Doug Fraker,i have updated Shiru's library to version 280221 see changelogs on header

FEATURES :
** Print logs on NES screen for debugging use 'nes_text_log()'.
** Print HUD text on NES screen for scores lives etc use 'nes_text_hud()'.
** Palette randomiser fill your palette both bg and spr with random colors use 'nes_palette_rand()'.
** Load RLE packed Titles,Intros,Outros using 'nes_load_title()' or 'nes_load_title_a()'.
** Clears nametable,buffers vram/oam cleanly using 'nes_clear_nametable()' and 'nes_exit_cleanup()'
** Show specific video region errors using 'nes_show_region_error()' and fade transitions fade in/out.
NOTE : You need to use original 'nes.lib' file to compile this because it uses standard/console I/O libraries.

Version 1.0.0 : 
[+] Added version 1.0 included neslib by Shiru and utilities made by Doug Fraker.
[+] Added useful Macros and constants for Colors,Joypads etc.
[+] Added documentation on methods to understand them better.
Dated : 07/03/2021

@Copyleft 2021 - Haseeb Mir
*/

#ifndef _NES_CLIB_
#define _NES_CLIB_

#include "neslib.h"   //Original lib by Shiru version 280221
#include "nesutils.h" //Utilities by Doug Fraker Originally called nesdoug.h
#include "nesconst.h" //NES Constants defined.
#include <stdarg.h>   //Standard args for vsprintf.

int xText = 0, yText = 0;
uint8_t ppu_region, fade_index;

//Some useful macros defined.
#define NES_PAD1(key) (pad_poll(0 & 1) & key)
#define NES_PAD2(key) (pad_poll(1 & 1) & key)
#define NES_SPR_COLOR(color) pal_col(3, color)
#define NES_BG_COLOR(color) pal_col(0, color)
#define NES_BANK_SPR_1 bank_spr(0); //Bank sprite 1
#define NES_BANK_SPR_2 bank_spr(1); //Bank sprite 2
#define NES_BANK_BG_1 bank_bg(0); //Bank background 1
#define NES_BANK_BG_2 bank_bg(1); //Bank background 2
#define NES_SPR_SZ_8_8 oam_size(0);  //8x8 Sprite size.
#define NES_SPR_SZ_8_16 oam_size(1); //8x16 Sprite size.
#define NES_GOTOX(x) (xText = x)
#define NES_GOTOY(y) (yText = y)
#define NES_GOTOXY(x, y) (xText = x, yText = y)
#define FADE_DELAY 4

//Include prototypes from standard libs.
#ifndef _STDIO_H
int vsprintf(char *, const char *, va_list);
#endif

#ifndef _STRING_H
size_t strlen(const char *);
#endif

#ifndef _CONIO_H
void __fastcall__ gotoxy(uint8_t, uint8_t);
uint8_t wherex(void);
uint8_t wherey(void);
#endif

//Stuff for HUD text buffers and Nametable updaters.
#define UPDATE_LIST_SIZE 30
static uint8_t update_list[UPDATE_LIST_SIZE * 3 + 1];
#define UPDATE_NT_BUF update_list[update_index++]

/***************************************
 * Public Methods - Check documentation.
 **************************************/

/**
 * @brief Fill palette with random colors
 *
 * @param  paletteType 
 *  PALETTE_TYPE_BG for Background objects. 
 *  PALETTE_TYPE_SPR for Sprite objects.
 *  PALETTE_TYPE_ALL for both.
 */
void __fastcall__ nes_palette_rand(uint8_t paletteType);

/**
 * @brief Prints text log on screen - Useful for printing text while debugging.
 *
 * @param  text Formatted text to print on screen
 */

void nes_text_log(const char *format, ...);

/**
 * @brief Print formatted text on HUD screen
 * Remember to call nes_hud_update() method to show text on screen.
 *
 * @param  text Formatted text to print on HUD screen
 */
void  nes_text_hud(const char *format, ...);

/**
 * @brief Update text printed on HUD screen
 * 
 * NOTE : This is disabled by default so define 'NES_HUD_UPDATE' to automatically update your text.
 */
void __fastcall__ nes_hud_update();
/**
 * @brief Load RLE data into nametable can be used for loading Titles,Intros,Outros.
 * 
* @param  nametable nametable type like NAMETABLE_A or NAMETABLE_B .
 */
void __fastcall__ nes_load_title(char *title, unsigned int nametable);

/**
 * @brief Load Title data into nametable A.
 */
void __fastcall__ nes_load_title_a(char *title);

/**
 * @brief Load Title data into nametable B.
 */
void __fastcall__ nes_load_title_b(char *title);


/**
 * @brief Clears specified nametable.
 * 
* @param  nametable nametable type like NAMETABLE_A or NAMETABLE_B .
 */

void __fastcall__ nes_clear_nametable(unsigned int nametable);

/**
 * @brief Show error regarding to selected video region.
 *
 * @param  region_type Type of region NTSC/PAL use Enum REGION_NTSC or REGION_PAL
 */

void __fastcall__ nes_show_region_error(uint8_t region_type);

/**
 * @brief Fade transition for foreground.
 * 
 */

void __fastcall__ nes_fade_transition_fg();

/**
 * @brief Fade transition for background.
 * 
 */
void __fastcall__ nes_fade_transition_bg();

/**
 * @brief Exit cleanly by clearing buffers vram/oam and music.
 * remember to turn on ppu like ppu_on_all().
 */
void __fastcall__ nes_exit_cleanup(void);

/**
 * @brief Transition type fade out.
 */
void __fastcall__ nes_fade_out(void);

/**
 * @brief Transition type fade in.
 */
void __fastcall__ nes_fade_in(void);

/***************************************
 * Private Methods - Dont use directly.
 **************************************/
#ifndef NES_TEXT_TILE_INDEX
#warning Text tile index is not defined.
#define NES_TEXT_TILE_INDEX 0 //Point to blank character 0x20 (ASCII).
#endif

//Print text directly on nametable instead of PPU.

void __fastcall__ _print_nt_text(uint8_t x, uint8_t y, uint8_t *s);

//Print text directly on nametable and update it. UPDATE_NT_BUF = Update NameTable Buffer.
void __fastcall__ _update_nt_text(uint8_t x, uint8_t y, uint8_t l, char *s);

static void __fastcall__ _vram_text(const char *text, int textX, int textY);

#endif //_NES_CLIB_