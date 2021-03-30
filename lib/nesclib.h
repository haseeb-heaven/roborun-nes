/*
NESCLIB - NES-C-Library is helper library for original NES library by Shiru this includes more functionality
over neslib and include utilities made by Doug Fraker,i have updated Shiru's library to version 280221 see changelogs on header

FEATURES :
** Print logs on NES screen for debugging use 'nes_text_log()'.
** Print HUD text on NES screen for scores lives etc use 'nes_text_hud()'.
** Palette randomizer fill your palette both bg and spr with random colors use 'nes_palette_rand()'.
** Load RLE packed Titles,Intros,Outros using 'nes_load_title()' or 'nes_load_title_a()'.
** Clears nametable,buffers vram/oam cleanly using 'nes_clear_nametable()' and 'nes_exit_cleanup()'
** Show specific video region errors using 'nes_show_region_error()' and fade transitions fade in/out.
NOTE : You need to use original 'nes.lib' file to compile this because it uses standard/console I/O libraries.

Version 1.0.0 : 
[+] Added version 1.0 included neslib by Shiru and utils made by Doug Fraker.
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
#define NES_SPR_SZ_8PX_8PX oam_size(0);  //8x8 Sprite size.
#define NES_SPR_SZ_8PX_16PX oam_size(1); //8x16 Sprite size.
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
void gotoxy(uint8_t, uint8_t);
uint8_t wherex(void);
uint8_t wherey(void);
#endif

//Stuff for HUD text buffers and Nametable updaters.
uint8_t gpit, rda, update_index = 0;
unsigned int gp_addr;
#define UPDATE_LIST_SIZE 30
static uint8_t update_list[UPDATE_LIST_SIZE * 3 + 1];
#define UPDATE_NT_BUF update_list[update_index++]

void _update_nt_text(uint8_t x, uint8_t y, uint8_t l, char *s);
static void _vram_text(const char *, int, int);
void nes_load_title(char *, unsigned int);
void nes_load_title_a(char *);
void nes_load_title_b(char *);
void nes_hud_update();
void nes_fade_transition_fg();
void nes_fade_transition_bg();
void nes_show_region_error(uint8_t region_type);
void nes_exit_cleanup(void);
void nes_fade_out(void);
void nes_fade_in(void);

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
void nes_palette_rand(uint8_t paletteType)
{
    uint8_t bgPalette[16] = {NULL}, sprPalette[16] = {NULL};
    uint8_t i = 0;

    for (i = 0; i < 16; ++i)
    {
        bgPalette[i] = (i + rand8() + (i * 2)) % 0x3F;
        sprPalette[i] = (i + rand8() + (i * 1)) % 0x3F;
    }

    if (paletteType == PALETTE_TYPE_BG)
        pal_bg(bgPalette);

    else if (paletteType == PALETTE_TYPE_SPR)
        pal_spr(sprPalette);
    else
    {
        pal_bg(bgPalette);
        pal_spr(sprPalette);
    }
}

/**
 * @brief Prints text log on screen - Useful for printing text while debugging.
 * define #NES_DEBUG to use it.
 *
 * @param  text Formatted text to print on screen
 */

#ifdef NES_DEBUG
void nes_text_log(const char *format, ...)
{
    char textBuf[0x32] = {NULL};
    va_list args;
    va_start(args, format);
    vsprintf(textBuf, format, args);

    if (wherex() > TILES_X)
    {
        yText++;
        xText = 0;

        if (yText > TILES_Y)
            yText = 1;
    }

    gotoxy(xText, yText);
    _vram_text(textBuf, xText++, yText);

    if (textBuf[strlen(textBuf) - 1] == '\n')
    {
        yText++;
        xText = 0;
    }
    if (textBuf[strlen(textBuf) - 1] == '\t')
        xText += strlen(textBuf) + 4;

    va_end(args);
}
#endif

/**
 * @brief Print formatted text on HUD screen
 * Remember to call nes_hud_update() method to show text on screen.
 *
 * @param  text Formatted text to print on HUD screen
 */
void nes_text_hud(const char *format, ...)
{
    char textBuf[32] = {NULL};
    va_list args;
    va_start(args, format);
    vsprintf(textBuf, format, args);

    _update_nt_text(xText, yText, strlen(textBuf), textBuf);

    if (textBuf[strlen(textBuf) - 1] == '\n')
    {
        yText++;
        xText = 0;
    }
    if (textBuf[strlen(textBuf) - 1] == '\t')
        xText += strlen(textBuf) + 4;

#ifdef NES_HUD_UPDATE
    nes_hud_update();
#endif
    va_end(args);
}

/**
 * @brief Update text printed on HUD screen
 * 
 * NOTE : This is disabled by default so define 'NES_HUD_UPDATE' to automatically update your text.
 */
void nes_hud_update()
{
    update_list[update_index] = NT_UPD_EOF;
    update_index = 0; // Reset update list
}

/**
 * @brief Load RLE data into nametable can be used for loading Titles,Intros,Outros.
 * 
* @param  nametable nametable type like NAMETABLE_A or NAMETABLE_B .
 */
void nes_load_title(char *title, unsigned int nametable)
{
    vram_adr(nametable);
    vram_unrle(title);
}

/**
 * @brief Load Title data into nametable A.
 */
void nes_load_title_a(char *title)
{
    vram_adr(NAMETABLE_A);
    vram_unrle(title);
}

/**
 * @brief Load Title data into nametable B.
 */
void nes_load_title_b(char *title)
{
    vram_adr(NAMETABLE_B);
    vram_unrle(title);
}


/**
 * @brief Clears specified nametable.
 * 
* @param  nametable nametable type like NAMETABLE_A or NAMETABLE_B .
 */

void nes_clear_nametable(unsigned int nametable)
{
    ppu_off();
    vram_adr(nametable);
    vram_fill(0, 1024);
    ppu_on_all();
}

/**
 * @brief Show error regarding to selected video region.
 *
 * @param  region_type Type of region NTSC/PAL use Enum REGION_NTSC or REGION_PAL
 */

void nes_show_region_error(uint8_t region_type)
{
    ppu_region = REGION_DENDY + 1; //Error set initial.
    if (ppu_system() && region_type == REGION_NTSC)
    {
        NES_GOTOXY(3, 15);
        nes_text_hud("WRONG VIDEO REGION SELECTED\n");

        NES_GOTOXY(3, 17);
        nes_text_hud("PLEASE SWITCH TO PAL OR DENDY");
        ppu_region = REGION_NTSC;
    }
    else if (!ppu_system() && region_type == REGION_PAL || region_type == REGION_DENDY)
    {
        NES_GOTOXY(3, 15);
        nes_text_hud("WRONG VIDEO REGION SELECTED\n");

        NES_GOTOXY(3, 17);
        nes_text_hud("PLEASE SWITCH TO NTSC");
        ppu_region = REGION_PAL;
    }

    if (ppu_region <= REGION_DENDY)
    {
        nes_clear_nametable(NAMETABLE_A);
        nes_hud_update();
        set_vram_update(update_list);
        ppu_on_all();

        while (TRUE)
        {
            ppu_wait_nmi();
            //Fading effect for title.
            nes_fade_transition_fg();
        }
    }
}

/**
 * @brief Fade transition for foreground.
 * 
 */

void nes_fade_transition_fg()
{
    if (get_frame_count() % (1 << 4) == 0)
    {
        pal_col(1, rand8() & 4);
        pal_col(3, rand8() & 4);
        delay(10);
    }
}

/**
 * @brief Fade transition for background.
 * 
 */
void nes_fade_transition_bg()
{
    if (get_frame_count() % (1 << 4) == 0)
    {
        pal_col(0, rand8() & 4);
        pal_col(2, rand8() & 4);
        delay(10);
    }
}

/**
 * @brief Exit cleanly by clearing buffers vram/oam and music.
 * remember to turn on ppu like ppu_on_all().
 */
void nes_exit_cleanup(void)
{
    set_vram_buffer();
    clear_vram_buffer();
    oam_clear();
    music_stop();
    nes_fade_out();
    ppu_off();
}

/**
 * @brief Transition type fade out.
 */
void nes_fade_out(void)
{
    for (fade_index = 4; fade_index > 0; fade_index--)
    {
        pal_bright(fade_index);
        delay(FADE_DELAY);
    }
}

/**
 * @brief Transition type fade in.
 */
void nes_fade_in(void)
{
    for (fade_index = 0; fade_index < 5; fade_index++)
    {
        pal_bright(fade_index);
        delay(FADE_DELAY);
    }
}

/***************************************
 * Private Methods - Dont use directly.
 **************************************/
#ifndef NES_TEXT_TILE_INDEX
#warning Text tile index is not defined.
#define NES_TEXT_TILE_INDEX 0 //Point to blank character 0x20 (ASCII).
#endif

//Print text directly on nametable instead of PPU.

void _print_nt_text(uint8_t x, uint8_t y, uint8_t *s)
{
    vram_adr(NAMETABLE_A + (y << 5) + x);
    while (rda = *s++)
        vram_put(rda - +NES_TEXT_TILE_INDEX - 0x20);
}

//Print text directly on nametable and update it. UPDATE_NT_BUF = Update NameTable Buffer.
void _update_nt_text(uint8_t x, uint8_t y, uint8_t l, char *s)
{
    gp_addr = NAMETABLE_A + (y << 5) + x;
    UPDATE_NT_BUF = MSB(gp_addr) | NT_UPD_HORZ; // Horizontal type text. change to NT_UPD_VERT for Vertical text
    UPDATE_NT_BUF = LSB(gp_addr);
    UPDATE_NT_BUF = l; //l - length of text.
    gpit = l;
    while (gpit--)
        UPDATE_NT_BUF = *s++ + NES_TEXT_TILE_INDEX - 0x20;
}

#ifdef NES_DEBUG
static void _vram_text(const char *text, int textX, int textY)
{
    vram_adr(NTADR_A(textX, textY));

    while (*text)
        vram_put((*text++) + NES_TEXT_TILE_INDEX - 0x20);
}
#endif

#endif //_NES_CLIB_