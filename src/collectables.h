#ifndef _COLLECTABLES_H
#define _COLLECTABLES_H

void set_generic(GenericBase *, Collectable *, int, int);
void spr_collectable_collision(Player *player, Collectable *collectable);
void add_collectable(Collectable *, int, int, uint8_t);

Collectable star1 = {NULL}, star2 = {NULL}, star3 = {NULL};
Collectable coin1 = {NULL}, coin2 = {NULL}, coin3 = {NULL}, coin4 = {NULL}, coin5 = {NULL};
Collectable life1 = {NULL}, life2 = {NULL}, life3 = {NULL};

//Initialize collectable list.
void init_collectables()
{
    collectable_index = 0;
    if (game_level == 1)
    {
        add_collectable(&coin1, 0x2000, 0x2200, COLLECTABLE_COIN);
        add_collectable(&coin2, 0x1800, 0x5200, COLLECTABLE_COIN);
        add_collectable(&coin3, 0x1200, 0x9200, COLLECTABLE_STAR);
        add_collectable(&coin4, 0x5000, 0x9200, COLLECTABLE_COIN);
        add_collectable(&coin5, -0x1900, 0x1900, COLLECTABLE_COIN);
        max_coins = 4;
    }
    else if (game_level == 2)
    {
        add_collectable(&coin1, 0x2000, 0x2000, COLLECTABLE_COIN);
        add_collectable(&coin2, 0x1800, 0x5200, COLLECTABLE_COIN);
        add_collectable(&coin3, -0x1600, 0x7200, COLLECTABLE_COIN);
        add_collectable(&life1, 0x4000, 0x9200, COLLECTABLE_STAR);
        add_collectable(&life2, -0x1900, 0x1900, COLLECTABLE_LIFE);
        max_coins = 3, max_lives = 2;
    }
    else if (game_level == 3)
    {
        add_collectable(&coin1, 0x2000, 0x1500, COLLECTABLE_COIN);
        add_collectable(&coin2, 0x1800, 0x5200, COLLECTABLE_COIN);
        add_collectable(&coin3, -0x1600, 0x7200, COLLECTABLE_COIN);
        add_collectable(&life1, 0x4500, 0x9200, COLLECTABLE_LIFE);
        add_collectable(&star1, -0x2F00, 0xD400, COLLECTABLE_STAR);
        max_coins = 3, max_lives = 1, max_stars = 1;
    }

    else if (game_level == 4)
    {
        add_collectable(&coin1, 0x2000, 0x1500, COLLECTABLE_COIN);
        add_collectable(&coin2, 0x1800, 0x4700, COLLECTABLE_COIN);
        add_collectable(&coin3, 0x7000, 0x3700, COLLECTABLE_COIN);
        add_collectable(&life1, -0x1600, 0x7200, COLLECTABLE_LIFE);
        add_collectable(&star1, 0x3F00, 0xD400, COLLECTABLE_STAR);
        max_coins = 3, max_lives = 1, max_stars = 1;
    }
    else if (game_level == 5)
    {
        add_collectable(&coin1, 0x3F00, 0xD400, COLLECTABLE_COIN);
        add_collectable(&coin2, 0x1800, 0x4700, COLLECTABLE_COIN);
        add_collectable(&coin3, 0x5000, 0x3700, COLLECTABLE_COIN);
        add_collectable(&life1, -0x1600, 0x6800, COLLECTABLE_LIFE);
        add_collectable(&star1, 0x99A0, 0xD400, COLLECTABLE_STAR);
        max_coins = 3, max_lives = 1, max_stars = 1;
    }
    collectables_item_count = collectable_index;
}

void add_collectable(Collectable *item, int x, int y, uint8_t type)
{
    item->x = x;
    item->y = y;
    item->state = STATE_ALIVE;
    item->type = type;
    collectable_list[collectable_index++] = *item;
}

void reset_collectables()
{
    lives = old_lives = 3;
    score = old_score = total_score = 0;
    stars = old_stars = 0;
    coins = old_coins = total_coins = 0;
    game_level = 1;
    life_timer = LIFE_TIMER_MAX;
    star_timer = STAR_TIMER_MAX;
    invincible_state = half_dead_state = FALSE;
}

void check_invincible_state()
{
    if (star_timer == 0)
    {
        star_timer = STAR_TIMER_MAX;
        invincible_state = FALSE;
        stars--;
        music_pause(FALSE);
        nes_hud_update();
        pal_spr(palette_spr);
    }
    else
    {
        if (invincible_state && !half_dead_state && get_frame_count() % 2 == 0)
        {
            if (blink_cycle == 0)
            {
                pal_col(17, NES_COLOR_CYAN_BLUE);
                pal_col(18, NES_COLOR_YELLOW);
                //pal_col(19, NES_COLOR_PALE_ORANGE);
            }

            else if (blink_cycle == 1)
            {
                pal_col(17, NES_COLOR_PALE_ORANGE);
                pal_col(18, NES_COLOR_LIGHT_BLUE);
                //pal_col(19, NES_COLOR_YELLOW);
            }

            else if (blink_cycle == 2)
            {
                pal_col(17, NES_COLOR_AQUA);
                pal_col(18, NES_COLOR_LIGHT_BLUE);
                //pal_col(19, NES_COLOR_BLACK);
            }
            blink_cycle = (blink_cycle > 2) ? 0 : (blink_cycle+1);
        }

        if (invincible_state && !half_dead_state && get_frame_count() % (1 << 5) == 0)
        {
            blink_life = !blink_life;
            music_pause(TRUE);
            sfx_play(SFX_STAR, 0);

            NES_GOTOXY(16, 0);
            nes_text_hud("%c%c%0.2d ", (blink_life) ? 0x20 : 0x21, 0x25, star_timer--);
            nes_hud_update();
        }
    }
}

void spr_collectable_collision(Player *player, Collectable *collectable)
{
    set_generic(&genericBase1, player, PLAYER_WIDTH, PLAYER_HEIGHT);
    set_generic(&genericBase2, collectable, COLLECTABLE_WIDTH, COLLECTABLE_HEIGHT);

    if (check_collision(&genericBase1, &genericBase2))
    {
        collectable->state = STATE_DEAD;
        HIGH_BYTE(collectable->y) = TURN_OFF;

        switch (collectable->type)
        {
        case COLLECTABLE_COIN:
            sfx_play(SFX_COIN, 0);
            score += 50;
            coins++;
            break;
        case COLLECTABLE_LIFE:
            sfx_play(SFX_LIFE, 0);
            lives++;
            life_timer = LIFE_TIMER_MAX; //Reset life timer.
            half_dead_state = FALSE;
            break;
        case COLLECTABLE_STAR:
            sfx_play(SFX_STAR, 0);
            stars++;
            score += 30;
            //Activate invincible state.
            if (!half_dead_state && lives > 1)
            {
                invincible_state = TRUE;
                star_timer = STAR_TIMER_MAX;
                nes_hud_update();
            }
            else
            {
                sfx_play(SFX_WRONG, 0);
                invincible_state = FALSE;
            }
            break;
        }
    }
}
#endif
