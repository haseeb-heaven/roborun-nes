#ifndef _ENEMY_H
#define _ENEMY_H

void set_generic(GenericBase *, Player *, int, int);
void bg_collision(GenericBase *);
void bg_collision_x(GenericBase *);
void enable_bg_collision(Player *, int, int);
void bg_check_low(GenericBase);
void add_enemy(Enemy *, int, int,signed int,signed int, uint8_t, uint8_t);

Enemy enemy1 = {NULL}, enemy2 = {NULL}, enemy3 = {NULL};

//Initialize enemies list.
void init_enemy()
{
    enemy_index = 0;
    if (game_level == 1)
    {
        add_enemy(&enemy1, 0x7000, 0x3400, 0x150, 0x0, LEFT, ENEMY_FIRE);
        add_enemy(&enemy2, 0x9000, 0x8400, 0xEE, 0x0, LEFT, ENEMY_FIRE);
        add_enemy(&enemy3, 0x3000, 0xA400, 0x190, 0x0, LEFT, ENEMY_SWARS);
    }
    else if (game_level == 2)
    {
        add_enemy(&enemy1, 0x7000, 0x3400, 0x250, 0x0, LEFT, ENEMY_GLOUT);
        add_enemy(&enemy2, 0xB000, 0x8400, 0x122, 0x0, LEFT, ENEMY_BEAR);
        add_enemy(&enemy3, 0x5200, 0xA000, 0xD4, 0xE0, UP, ENEMY_BAT);
    }
    else if (game_level == 3)
    {
        add_enemy(&enemy1, 0x7000, 0x3400, 0x250, 0x0, LEFT, ENEMY_THORN);
        add_enemy(&enemy2, 0xB000, 0x8400, 0x0, 0xE0, DOWN, ENEMY_GLOUT);
        add_enemy(&enemy3, 0x5800, 0xA000, 0x0, 0xE0, UP, ENEMY_GORILLA);
    }
    else if (game_level == 4)
    {
        add_enemy(&enemy1, 0x7000, 0x3400, 0x220, 0x0, LEFT, ENEMY_MUSH);
        add_enemy(&enemy2, 0xB000, 0x8400, 0x0, 0xE0, DOWN, ENEMY_BEAR);
        add_enemy(&enemy3, 0x5200, 0xC800, 0x0, 0x170, UP, ENEMY_BAT);
    }
    else if (game_level == 5)
    {
        add_enemy(&enemy1, 0x2000, 0x6200, 0x150, 0x0, LEFT, ENEMY_OCTA);
        add_enemy(&enemy2, 0xB000, 0x8400, 0x0, 0x12C, DOWN, ENEMY_SWARS);
        add_enemy(&enemy3, 0x4800, 0x9800, 0x0, 0x110, UP, ENEMY_FIRE);
    }
    enemy_item_count = enemy_index;
}

void add_enemy(Enemy *enemy, int x, int y,signed int vel_x,signed int vel_y, uint8_t direction, uint8_t type)
{
    enemy->x = x;
    enemy->y = y;
    enemy->vel_x = vel_x;
    enemy->vel_y = vel_y;
    enemy->state = STATE_ALIVE;
    enemy->type = type;
    enemy->direction = direction;
    enemy_list[enemy_index++] = *enemy;
}

void enemy_movement_x(Player *enemyPlayer, uint8_t direction, signed int speed_x)
{
    enemy_direction = (enemyPlayer->direction == enemy_direction) ? enemy_direction : enemyPlayer->direction;

    if (enemy_direction == RIGHT)
    {
        enemyPlayer->x += enemyPlayer->vel_x;
    }
    else if (enemy_direction == LEFT)
    {
        enemyPlayer->x -= enemyPlayer->vel_x;
    }

    if (direction == LEFT || direction == RIGHT)
        enemyPlayer->vel_x = speed_x;

    //Enable Collision
    enable_bg_collision_x(enemyPlayer, ENEMY_WIDTH, ENEMY_HEIGHT);

    if (collision_L)
    {
        enemy_direction = RIGHT;
        HIGH_BYTE(enemyPlayer->x) = HIGH_BYTE(enemyPlayer->x) - eject_L;
    }
    else if (collision_R)
    {
        enemy_direction = LEFT;
        HIGH_BYTE(enemyPlayer->x) = HIGH_BYTE(enemyPlayer->x) - eject_R;
    }

    L_R_switch = 0;
    enemyPlayer->direction = (enemyPlayer->direction != enemy_direction) ? enemy_direction : enemyPlayer->direction;
}

void enemy_movement_y(Player *enemyPlayer, uint8_t direction, signed int speed_y)
{
    enemy_direction = (enemyPlayer->direction == enemy_direction) ? enemy_direction : enemyPlayer->direction;

    if (enemy_direction == UP)
    {
        enemyPlayer->y -= enemyPlayer->vel_y;
    }
    else if (enemy_direction == DOWN)
    {
        enemyPlayer->y += enemyPlayer->vel_y;
    }

    if (direction == UP || direction == DOWN)
        enemyPlayer->vel_y = speed_y;

    //Enable Collision
    enable_bg_collision_y(enemyPlayer, ENEMY_WIDTH, ENEMY_HEIGHT);

    if (collision_U)
    {
        enemy_direction = DOWN;
        HIGH_BYTE(enemyPlayer->y) = HIGH_BYTE(enemyPlayer->y) - eject_U;
    }
    else if (collision_D)
    {
        enemy_direction = UP;
        HIGH_BYTE(enemyPlayer->y) = HIGH_BYTE(enemyPlayer->y) - eject_D;
        enemyPlayer->y &= 0xff00;
    }

    L_R_switch = 0;
    enemyPlayer->direction = (enemyPlayer->direction != enemy_direction) ? enemy_direction : enemyPlayer->direction;
}

void enemy_movement()
{
    for (index = 0; index < MAX_ENEMY; ++index)
    {
        if (enemy_list[index].direction == LEFT || enemy_list[index].direction == RIGHT)
            enemy_movement_x(enemy_list + index, enemy_list[index].direction, enemy_list[index].vel_x);
        else if (enemy_list[index].direction == UP || enemy_list[index].direction == DOWN)
            enemy_movement_y(enemy_list + index, enemy_list[index].direction, enemy_list[index].vel_y);
    }
}

void spr_enemy_collision(Player *player, Enemy *enemy)
{
    set_generic(&genericBase1, player, PLAYER_WIDTH, PLAYER_HEIGHT);
    set_generic(&genericBase2, enemy, ENEMY_WIDTH, ENEMY_HEIGHT);

    if (check_collision(&genericBase1, &genericBase2))
    {
        enemy->vel_x = enemy->vel_y = 0;
        sfx_play(SFX_HIT, 0);
        enemy->state = STATE_DEAD;
        HIGH_BYTE(enemy->y) = TURN_OFF;

        //Add points in invincible state.
        if (invincible_state)
        {
            score = (score > 0) ? score + 100 : 0;
        }
        //Deduct points in normal state.
        else
        {
            score = (score > 0) ? score - 50 : 0;
            lives = (lives > 0) ? lives - 1 : 0;
        }

        //Play animation on dead and change state.
        if (lives <= 0)
        {
            oam_clear();
            player->state = STATE_DEAD;
            oam_meta_spr(HIGH_BYTE(playerRobo.x), HIGH_BYTE(playerRobo.y), player_robo_spr_list[PLAYER_ANIM_DEAD]);
            delay(50);
        }
    }
}
#endif
