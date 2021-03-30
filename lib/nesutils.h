//NES Utils Written by Doug Fraker 2018
// v 1.01
#ifndef _NES_UTILS_H
#define _NES_UTILS_H
void set_vram_buffer(void);
void __fastcall__ one_vram_buffer(unsigned char data, int ppu_address);
void __fastcall__ multi_vram_buffer_horz(const char * data, unsigned char len, int ppu_address);
void __fastcall__ multi_vram_buffer_vert(const char * data, unsigned char len, int ppu_address);
void clear_vram_buffer(void);
unsigned char __fastcall__ get_pad_new(unsigned char pad);
unsigned char __fastcall__ get_frame_count(void);
void __fastcall__ set_music_speed(unsigned char tempo);
unsigned char __fastcall__ check_collision(void * object1, void * object2);
void __fastcall__ pal_fade_to(unsigned char from, unsigned char to);
void __fastcall__ set_scroll_x(unsigned int x);
void __fastcall__ set_scroll_y(unsigned int y);
int __fastcall__ add_scroll_y(unsigned char add, unsigned int scroll);
int __fastcall__ sub_scroll_y(unsigned char sub, unsigned int scroll);
int __fastcall__ get_ppu_addr(char nt, char x, char y);
int __fastcall__ get_at_addr(char nt, char x, char y);
void __fastcall__ set_data_pointer(const char * data);
void __fastcall__ set_mt_pointer(const char * metatiles);
void __fastcall__ buffer_1_mt(int ppu_address, char metatile);
void __fastcall__ buffer_4_mt(int ppu_address, char index);
void flush_vram_update_nmi(void);
void __fastcall__ color_emphasis(char color);
void __fastcall__ xy_split(unsigned int x, unsigned int y);
void gray_line(void);
void seed_rng(void);
#endif


