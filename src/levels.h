//Load room with current level , levels created using Tiled.
void load_level(void)
{
    uint8_t x, y;

    set_data_pointer(level_list[game_level-1]);
    set_mt_pointer(metatiles_bg);
    for (y = 0;; y+= 0x20) //0x20 = 32 (4 x 8 metatiles).
    {
        for (x = 0; ;x += 0x20)
        {
            clear_vram_buffer();                                      
            buffer_4_mt(get_ppu_addr(0, x, y), (y & 0xf0) + (x >> 4)); 
            flush_vram_update_nmi();
            if (x == SCREEN_V - 16)
                break;
        }
        if (y == SCREEN_V - 16)
            break;
    }
    music_play(game_level % 2);
    memcpy(c_map,level_list[game_level-1], 240);
}