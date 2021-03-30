//NES hardware-dependent functions by Shiru (shiru@mail.ru)
//Feel free to do anything you want with this code, consider it Public Domain

/*Versions history
280221 - Added methods for nesclock,and PPU control variable,moved all constants to nesconst.h file.
220919 - Changes removed sprid from oam functions, oam_spr 11% faster, meta 5% faster.
050517 - pad polling code optimized, button bits order reversed
280215 - fixed palette glitch caused by the active DMC DMA glitch
030914 - minor fixes in the VRAM update system
310814 - added vram_flush_update
120414 - removed adr argument from vram_write and vram_read,
  N/A  -  unrle_vram renamed to vram_unrle, with adr argument removed
060414 - many fixes and improvements, including sequental VRAM updates
previous versions were created since mid-2011, there were many updates*/

#ifndef _NES_LIB_H
#define _NES_LIB_H
void __fastcall__ pal_all(const char *data);
void __fastcall__ pal_bg(const char *data);
void __fastcall__ pal_spr(const char *data);
void __fastcall__ pal_col(unsigned char index,unsigned char color);
void __fastcall__ pal_clear(void);
void __fastcall__ pal_bright(unsigned char bright);
void __fastcall__ pal_spr_bright(unsigned char bright);
void __fastcall__ pal_bg_bright(unsigned char bright);
void __fastcall__ ppu_wait_nmi(void);
void __fastcall__ ppu_wait_frame(void);
void __fastcall__ ppu_off(void);
void __fastcall__ ppu_on_all(void);
void __fastcall__ ppu_on_bg(void);
void __fastcall__ ppu_on_spr(void);
void __fastcall__ ppu_mask(unsigned char mask);
unsigned char __fastcall__ ppu_system(void);
void __fastcall__ oam_clear(void);
void __fastcall__ oam_size(unsigned char size);
void __fastcall__ oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
void __fastcall__ oam_meta_spr(unsigned char x,unsigned char y,const unsigned char *data);
void __fastcall__ oam_hide_rest(void);
void __fastcall__ oam_set(unsigned char index);
unsigned char __fastcall__ oam_get(void);
void __fastcall__ music_play(unsigned char song);
void __fastcall__ music_stop(void);
void __fastcall__ music_pause(unsigned char pause);
void __fastcall__ sfx_play(unsigned char sound,unsigned char channel);
void __fastcall__ sample_play(unsigned char sample);
unsigned char __fastcall__ pad_poll(unsigned char pad);
unsigned char __fastcall__ pad_trigger(unsigned char pad);
unsigned char __fastcall__ pad_state(unsigned char pad);
void __fastcall__ scroll(unsigned int x,unsigned int y);
void __fastcall__ split(unsigned int x); //removed y, not used %%
void __fastcall__ bank_spr(unsigned char n);
void __fastcall__ bank_bg(unsigned char n);
unsigned char __fastcall__ rand8(void);
unsigned int  __fastcall__ rand16(void);
void __fastcall__ set_rand(unsigned int seed);
void __fastcall__ set_vram_update(const unsigned char *buf);
void __fastcall__ flush_vram_update(const unsigned char *buf);
void __fastcall__ vram_adr(unsigned int adr);
void __fastcall__ vram_put(unsigned char n);
void __fastcall__ vram_fill(unsigned char n,unsigned int len);
void __fastcall__ vram_inc(unsigned char n);
void __fastcall__ vram_read(unsigned char *dst,unsigned int size);
void __fastcall__ vram_write(const unsigned char *src,unsigned int size);
void __fastcall__ vram_unrle(const unsigned char *data);

#ifndef _STRING_H
void __fastcall__ memcpy(void *dst,void *src,unsigned int len);
void __fastcall__ memfill(void *dst,unsigned char value,unsigned int len);
#endif

void __fastcall__ delay(unsigned char frames);
unsigned char __fastcall__ nesclock(void);
unsigned char __fastcall__ get_ppu_ctrl_var(void);
void __fastcall__ set_ppu_ctrl_var(unsigned char var);
#endif

