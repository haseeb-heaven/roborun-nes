#ifndef _COLLISION_H
#define _COLLISION_H
void bg_collision(GenericBase *);
void bg_collision_x(GenericBase *);
void bg_collision_y(GenericBase *);
void spr_enemy_collision(Player *, Player *);
void set_generic(GenericBase *, Player *, int, int);
void spr_collectable_collision(Player *player, Collectable *collectable);

void enable_bg_collision(Player *player, int width, int height)
{
    set_generic(&genericBase1, player, width, height);
    bg_collision(&genericBase1);
}

void enable_bg_collision_x(Player *player, int width, int height)
{
    set_generic(&genericBase1, player, width, height);
    bg_collision_x(&genericBase1);
}

void enable_bg_collision_y(Player *player, int width, int height)
{
    set_generic(&genericBase1, player, width, height);
    bg_collision_y(&genericBase1);
}

void enemy_sprite_collision()
{
    for (index = 0; index < MAX_ENEMY; ++index)
    {
        spr_enemy_collision(&playerRobo, &enemy_list[index]);
    }
}

void collectable_sprite_collision()
{
    for (index = 0; index < MAX_COLLECTABLES; ++index)
    {
        spr_collectable_collision(&playerRobo, &collectable_list[index]);
    }
}

void bg_collision_sub(void)
{
    map_coords = (lowX >> 4) + (lowY & 0xf0);
    collision = c_map[map_coords];
    collision = is_solid[collision];
}

void bg_check_low(GenericBase basePlayer)
{
    // floor collisions
    collision_D = 0;

    upperLeft = basePlayer.x + scroll_x; //left
    lowX = upperLeft & 0xff;             //low byte
    highX = upperLeft >> 8;              //high byte

    lowY = basePlayer.y + basePlayer.height + 1; // bottom

    if (lowY >= 0xf0)
        return;

    bg_collision_sub();

    if (collision & (COL_DOWN | COL_ALL))
    {
        ++collision_D;
    }

    //upperLeft = right
    upperLeft += basePlayer.width;
    lowX = upperLeft & 0xff; //low byte
    highX = upperLeft >> 8;  //high byte

    //lowY is unchanged
    bg_collision_sub();

    if (collision & (COL_DOWN | COL_ALL))
    {
        ++collision_D;
    }

    if ((lowY & 0x0f) > 3)
        collision_D = 0; // for platforms, only collide with the top 3 pixels
}

void bg_collision(GenericBase *basePlayer)
{
    collision_L = collision_R = collision_U = collision_D = 0;

    if (basePlayer->y >= 0xf0)
        return;

    up_l_back = upperLeft = basePlayer->x + scroll_x;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    eject_L = lowX | 0xf0;
    lowY = basePlayer->y;
    eject_U = lowY | 0xf0;

    if (L_R_switch)
        lowY += 5;

    bg_collision_sub();

    if (collision & COL_ALL)
    {
        ++collision_L;
        ++collision_U;
    }

    // upper right
    upperLeft += basePlayer->width;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    eject_R = (lowX + 1) & 0x0f;

    bg_collision_sub();

    if (collision & COL_ALL)
    {
        ++collision_R;
        ++collision_U;
    }

    lowY = basePlayer->y + basePlayer->height;

    if (L_R_switch)
        lowY -= 2;
    eject_D = (lowY + 1) & 0x0f;

    if (lowY >= 0xf0)
        return;

    bg_collision_sub();

    if (collision & COL_ALL)
    {
        ++collision_R;
    }
    if (collision & (COL_DOWN | COL_ALL))
    {
        ++collision_D;
    }

    // bottom left
    lowX = up_l_back & 0xff;
    highX = up_l_back >> 8;

    //lowY, y is unchanged
    bg_collision_sub();

    if (collision & COL_ALL)
    {
        ++collision_L;
    }
    if (collision & (COL_DOWN | COL_ALL))
    {
        ++collision_D;
    }

    if ((lowY & 0x0f) > 3) //top 3 pixels
        collision_D = 0; 
}

void bg_collision_x(GenericBase *basePlayer)
{
    collision_L = collision_R = 0;

    if (basePlayer->y >= 0xf0)
        return;

    up_l_back = upperLeft = basePlayer->x + scroll_x;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    eject_L = lowX | 0xf0;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    lowY = basePlayer->y; // y top

    bg_collision_sub();

    if (collision & COL_ALL)
    {
        ++collision_L;
    }

    // upper right
    upperLeft += basePlayer->width;
    lowX = upperLeft & 0xff; // low byte x
    highX = upperLeft >> 8;  // high byte x

    eject_R = (lowX + 1) & 0x0f;
    bg_collision_sub();

    if (collision & COL_ALL)
        ++collision_R;
}

void bg_collision_y(GenericBase *basePlayer)
{
    collision_U = collision_D = 0;

    if (basePlayer->y >= 0xf0)
        return;

    up_l_back = upperLeft = basePlayer->x + scroll_x;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    lowY = basePlayer->y;
    eject_U = lowY | 0xf0;

    if (L_R_switch)
        lowY += 5; 

    bg_collision_sub();

    if (collision & COL_ALL)
        ++collision_U;
    
    // upper right
    upperLeft += basePlayer->width;
    lowX = upperLeft & 0xff;
    highX = upperLeft >> 8;

    lowY = basePlayer->y + basePlayer->height;

    if (L_R_switch)
        lowY -= 2;
    eject_D = (lowY + 1) & 0x0f;

    if (lowY >= 0xf0)
        return;

    bg_collision_sub();

    if (collision & (COL_DOWN | COL_ALL))
    {
        ++collision_D;
    }

    if ((lowY & 0x0f) > 3) //top 3 pixels
        collision_D = 0;  
}

#endif