#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "constants.h"
#include "collision.h"

void init_player(int x, int y, uint8_t vel_x, uint8_t vel_y, uint8_t direction)
{
    //Player robo data.
    playerRobo.x = x;
    playerRobo.y = y;
    playerRobo.vel_x = vel_x;
    playerRobo.vel_y = vel_y;
    playerRobo.direction = direction;
    playerRobo.state = STATE_ALIVE;
    playerRobo.type = -1;
}

void player_movement(void)
{
    old_x = playerRobo.x;

    if (NES_PAD1(PAD_LEFT))
    {
        playerRobo.direction = LEFT;

        playerRobo.vel_x -= ACCEL;
        if (playerRobo.vel_x < -MAX_SPEED)
            playerRobo.vel_x = -MAX_SPEED;
    }
    else if (NES_PAD1(PAD_RIGHT))
    {
        playerRobo.direction = RIGHT;

        playerRobo.vel_x += ACCEL;
        if (playerRobo.vel_x > MAX_SPEED)
            playerRobo.vel_x = MAX_SPEED;
    }
    else
    {
        if (playerRobo.vel_x >= 0x100)
            playerRobo.vel_x -= ACCEL;
        else if (playerRobo.vel_x < -0x100)
            playerRobo.vel_x += ACCEL;
        else
            playerRobo.vel_x = 0;
    }

    playerRobo.x += playerRobo.vel_x;

    L_R_switch = 1; // head and feet collisions

    //Enable Collision
    enable_bg_collision(&playerRobo, PLAYER_WIDTH, PLAYER_HEIGHT);

    if (collision_R && collision_L)
    {
        playerRobo.x = old_x;
        playerRobo.vel_x = 0;
    }
    else if (collision_L)
    {
        playerRobo.vel_x = 0;
        HIGH_BYTE(playerRobo.x) = HIGH_BYTE(playerRobo.x) - eject_L;
    }
    else if (collision_R)
    {
        playerRobo.vel_x = 0;
        HIGH_BYTE(playerRobo.x) = HIGH_BYTE(playerRobo.x) - eject_R;
    }

    // gravity section
    if (playerRobo.vel_y < 0x300)
        playerRobo.vel_y += GRAVITY;
    else
        playerRobo.vel_y = 0x300;

    playerRobo.y += playerRobo.vel_y;

    L_R_switch = 0;
    genericBase1.x = HIGH_BYTE(playerRobo.x);
    genericBase1.y = HIGH_BYTE(playerRobo.y);
    bg_collision(&genericBase1);

    if (collision_U)
    {
        HIGH_BYTE(playerRobo.y) = HIGH_BYTE(playerRobo.y) - eject_U;
        playerRobo.vel_y = 0;
    }
    else if (collision_D)
    {
        HIGH_BYTE(playerRobo.y) = HIGH_BYTE(playerRobo.y) - eject_D;
        playerRobo.y &= 0xff00;
        if (playerRobo.vel_y > 0)
        {
            playerRobo.vel_y = 0;
        }
    }

    // check collision down a little lower than player
    genericBase1.y = HIGH_BYTE(playerRobo.y);
    bg_check_low(genericBase1);
    if (collision_D)
    {
        if (NES_PAD1(PAD_A))
        {
            playerRobo.vel_y = JUMP_VEL; // JUMP
            sfx_play(SFX_JUMP, 0);
            player_vel_state = STATE_JUMP_AIR;
        }
    }

    //Player Sprites render section.
    if (lives == 1 && !invincible_state)
        half_dead_state = TRUE;

    //Just skip drawing to blink player and life sprite.
    if (half_dead_state && !invincible_state && get_frame_count() % (1 << 5) == 0)
    {
        blink_life = !blink_life;
        sfx_play(SFX_HALF_DEAD, 0);
        NES_GOTOXY(9, 0);
        nes_text_hud("%c%c%0.2d ", (blink_life) ? 0x26 : 0x2D, 0x25, life_timer--);
        nes_hud_update();
    }

    //Draw jump sprite.
    else if (player_vel_state == STATE_JUMP_AIR)
        oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction + PLAYER_ANIM_JUMP]);
    else if (player_vel_state == STATE_JUMP_FALL)
    {
        oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction + PLAYER_ANIM_FALL]);
        if (collision_D)
            player_vel_state = STATE_UNDEF;
    }

    //Draw idle sprite.
    else if (playerRobo.vel_x == 0 && !NES_PAD1(PAD_B))
        oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction]);

    //Draw walking sprite.
    else
    {
        oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction]);
        if (get_frame_count() % 4 == 0)
            oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction + 1]);
        if (get_frame_count() % 7 == 0)
            oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction + 2]);
        if (get_frame_count() % 13 == 0)
            oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[playerRobo.direction + 3]);
    }

    if (!collision_D)
        player_vel_state = STATE_JUMP_FALL;

    if (life_timer == 0)
    {
        lives--;
        half_dead_state = FALSE;
    }
}

#endif