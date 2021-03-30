#ifndef _GENERIC_H
#define _GENERIC_H
void set_generic(GenericBase *, Player *, int, int);

void set_generic(GenericBase *gBase, Player *player, int width, int height)
{
    gBase->x = HIGH_BYTE(player->x);
    gBase->y = HIGH_BYTE(player->y);
    gBase->width = width;
    gBase->height = height;
}

#endif