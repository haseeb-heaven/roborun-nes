/* RoboRun-NES - is platform single room game for nes created as a homebrew project to learn the the basics of NES game dev
and compiler and other tools used . Whole game was coded in plain C not Assembly to check limitations of C in NES coding.

Game design info:
Graphics : CHR converted from NES Sprite convertor (My own tool https://github.com/haseeb-heaven/NES-Sprite-Convertor)
Sound : Famitracker and Famitone2 (By Shiru).
Level design : Using Tiled and my custom scripts in scripts folder and Metatiles convertor using meta2c by Doug fraker.  
Animations : SpriteMixer library by Mojon-Twins.
All credits given to desired authors as they have contributed alot for open source nes projects.

CopyLeft@2021 - Haseeb Mir.
Dated : 30-03-2021
*/

//Include all game files.
//#define DEBUG_MODE //For debugging levels.
#include "src\game.h"

void draw_sprites(void);
void print_hud();

//Main method for game loop with player/enemy/sprites sections.
void main()
{
    //Disable PPU to stop rendering.
    ppu_off();
    pal_bg(palette_title);
    pal_spr(palette_spr);
    NES_BANK_BG_1;  //First set for background.
    NES_BANK_SPR_2; //Second set for sprites.
    NES_SPR_SZ_8PX_8PX; // 8x8 Sprites.

    //Set vram buff and load title.
    set_vram_buffer();
    clear_vram_buffer();
    nes_show_region_error(REGION_NTSC);

    //If PAL is selected.
    nes_load_title(game_title, NAMETABLE_A);
    music_play(SONG_TITLE);
    game_mode = MODE_TITLE;
    ppu_on_all();

    //Main game loop.
    while (TRUE)
    {
        while (game_mode == MODE_TITLE)
        {
            ppu_wait_nmi();
            oam_clear();

            //Automatic start/help selection loop.
            while (TRUE)
            {
                ppu_wait_nmi();
                //Fading effect for title.
                nes_fade_transition_fg();
                if (get_frame_count() % 12 == 0)
                    menu_select = !menu_select;

                if (menu_select)
                {
                    //Alternate of oam_spr() method just add +0x20 to tile number to print tiles.
                    NES_GOTOXY(13, 18);
                    nes_text_hud("%c%c", 0x71, 0x72);
                    NES_GOTOXY(13, 20);
                    nes_text_hud("%c%c", 0x20, 0x20);
                    game_mode = MODE_START;
                }
                else
                {
                    NES_GOTOXY(13, 18);
                    nes_text_hud("%c%c", 0x20, 0x20);
                    NES_GOTOXY(13, 20);
                    nes_text_hud("%c%c", 0x71, 0x72);
                    game_mode = MODE_HELP;
                }
                nes_hud_update();
                //Update list every 12th frame.
                if (get_frame_count() % 12 == 0)
                    set_vram_update(update_list);

                if (NES_PAD1(PAD_START))
                {
                    sfx_play(SFX_START, 0);
                    nes_exit_cleanup();
                    break;
                }
            }

            if (game_mode == MODE_START)
            {
                sfx_play(SFX_LIFE, 0);
                delay(50);
                nes_fade_out();
                ppu_off();

                //Load current level.
                load_level();

                draw_sprites();
                init_player(0x2FD0, 0xC200, 10, 8, LEFT);
                init_enemy();
                reset_collectables();
                init_collectables();
                set_vram_update(update_list);

                pal_bg(palette_bg1);
                pal_spr(palette_spr);
                //Print HUD text.
                print_hud();

                ppu_on_all();
                nes_fade_in();
                game_mode = MODE_GAME;
            }
            //Show Help page.
            else if (game_mode == MODE_HELP)
            {
                nes_fade_out();
                oam_clear();
                nes_clear_nametable(NAMETABLE_A);
                nes_exit_cleanup();
                pal_spr(palette_title);
                nes_load_title(game_help_title, NAMETABLE_A);
                ppu_on_all();
                nes_fade_in();
            }
        }

        while (game_mode == MODE_GAME)
        {
            ppu_wait_nmi();
            clear_vram_buffer();
            // clear all sprites from sprite buffer
            oam_clear();

            player_movement();
            enemy_movement();
            draw_sprites();
            check_invincible_state();
            enemy_sprite_collision();
            collectable_sprite_collision();

            //Update HUD text if values gets updated during game.
            if (old_score != score || old_lives != lives || old_stars != stars || old_coins != coins)
            {
                if (!half_dead_state && !invincible_state)
                    print_hud();

                old_score = score;
                old_lives = lives;
                old_stars = stars;
                old_coins = coins;
            }


            #ifdef DEBUG_MODE
            if(NES_PAD1(PAD_B)){coins = max_coins; score = max_coins * 50;}
            #endif

            //Player win state.
            if (coins == max_coins && score > 0)
            {
                music_pause(TRUE);
                sfx_play(SFX_STAR, 0);
                oam_clear();
                oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[PLAYER_ANIM_VICTORY]);
                delay(70);

                nes_clear_nametable(NAMETABLE_A);
                nes_exit_cleanup();
                nes_fade_out();
                nes_fade_in();
                total_coins += coins;        //Add up level coins
                total_score += score;        //Add up level score
                life_timer = LIFE_TIMER_MAX; //Reset life timer.
                star_timer = STAR_TIMER_MAX;
                invincible_state = FALSE;

                if (lives == 1 || game_level == 4)
                {
                    nes_hud_update();
                    set_vram_update(update_list);
                    life_timer = LIFE_TIMER_MAX;
                    half_dead_state = TRUE;
                }

                //Change palette for higher levels.
                if (game_level < 3)
                {
                    pal_bg(palette_bg2);
                    pal_spr(palette_spr);
                }
                else
                {
                    pal_bg(palette_bg3);
                    pal_spr(palette_spr);
                }

                //Load title and music.
                nes_load_title(level_clear_title, NAMETABLE_A);
                NES_GOTOXY(0, 1);nes_text_hud("%c", 0x77);
                NES_GOTOXY(18, 13);nes_text_hud("%0.5d", score);
                NES_GOTOXY(18, 15);nes_text_hud("%0.2d", lives);
                
                //Setup for bonus level.
                if(game_level == 4){
                NES_GOTOXY(10, 8);
                nes_text_hud("BONUS LEVEL");
                life_timer = 30;
                half_dead_state = TRUE;
                }

                nes_hud_update();
                set_vram_update(update_list);
                music_play(SONG_LEVEL_CLEAR);
                ppu_on_all();

                while (TRUE)
                {
                    ppu_wait_nmi();
                    nes_fade_transition_fg();
                    if (NES_PAD1(PAD_START))
                    {
                        nes_fade_in();
                        pal_spr(palette_spr);
                        break;
                    }
                }
                nes_exit_cleanup();

                //Advance level and reset coins.
                game_level++;
                coins = stars = score = 0;

                //Init player,enemy and collectables.
                if (game_level <= 3)
                    init_player(0x2FD0, 0xC200, 12, 8, RIGHT);
                else
                    init_player(-0x2FD0, 0xC200, 12, 8, LEFT);

                init_enemy();
                init_collectables();

                //Load room with fade effect.
                load_level();
                print_hud();
                ppu_on_all();
                nes_fade_in();
                set_vram_update(update_list);
                music_pause(FALSE);
            }

            //Game over state.
            if (playerRobo.state == STATE_DEAD || lives == 0 || life_timer == 0 || game_level > MAX_LEVELS)
            {
                game_mode = MODE_GAME_OVER;
                sfx_play(SFX_DEAD, 0);
                oam_clear();
                if (game_level < MAX_LEVELS)
                {
                    oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[PLAYER_ANIM_DEAD]);
                    delay(50);
                }
                nes_clear_nametable(NAMETABLE_A);
                nes_exit_cleanup();

                nes_fade_out();
                nes_fade_in();
                pal_spr(palette_title);
                nes_load_title(game_over_title, NAMETABLE_A);

                //Show total coins and total score.
                NES_GOTOXY(0, 0);nes_text_hud("%c", 0x77);
                NES_GOTOXY(18, 13);nes_text_hud("%0.5d", total_score);
                NES_GOTOXY(18, 15);nes_text_hud("%0.2d", total_coins);

                nes_hud_update();
                set_vram_update(update_list);
                music_play(SONG_LEVEL_CLEAR);
                ppu_on_all();
            }

            //Pause game state.
            if (NES_PAD1(PAD_START))
            {
                music_pause(TRUE);
                game_mode = MODE_PAUSE;
                sfx_play(SFX_PAUSE, 0);
                color_emphasis(COL_EMP_DARK);
                NES_GOTOXY(9, 1);
                nes_text_hud("GAME PAUSED");
                nes_hud_update();
            }
        }

        while (game_mode == MODE_PAUSE)
        {
            oam_clear();
            ppu_wait_nmi();
            clear_vram_buffer();

            if (NES_PAD1(PAD_START))
            {
                sfx_play(SFX_PAUSE, 0);
                game_mode = MODE_GAME;
                color_emphasis(COL_EMP_NORMAL);
                music_pause(FALSE);
                
                //Clear game paused text.
                NES_GOTOXY(9, 1);
                nes_text_hud("              ");
                nes_hud_update();
            }
        }

        while (game_mode == MODE_GAME_OVER || game_mode == MODE_HELP)
        {
            ppu_wait_nmi();
            nes_fade_transition_fg();

            //Restart game.
            if (NES_PAD1(PAD_START))
            {
                game_mode = MODE_TITLE;
                reset_collectables();
                oam_clear();
                nes_clear_nametable(NAMETABLE_A);
                nes_exit_cleanup();

                nes_fade_out();
                nes_fade_in();
                pal_bg(palette_title);
                nes_load_title(game_title, NAMETABLE_A);
                ppu_on_all();
                music_play(SONG_TITLE);
                break;
            }
        }
    }
}

void draw_sprites(void)
{
    for (index = 0; index < collectables_item_count; ++index)
        oam_meta_spr(HIGH_BYTE(collectable_list[index].x), HIGH_BYTE(collectable_list[index].y), collectables_spr_list[collectable_list[index].type]);

    for (index = 0; index < enemy_item_count; ++index)
        oam_meta_spr(HIGH_BYTE(enemy_list[index].x), HIGH_BYTE(enemy_list[index].y), enemy_spr_list[enemy_list[index].type]);
}

void print_hud()
{
    NES_GOTOXY(0, 0);
    nes_text_hud("%c%c%0.2d%c%d    %c%c%0.2d    %c%c%0.2d    %c%c%0.5d\n", 0x6D, 0x25, coins, 0x23, max_coins, 0x2D, 0x25, lives, 0x21, 0x25, stars, 0x22, 0x25, score);
    nes_text_hud("%c", 0x7D);
    nes_hud_update();
}
