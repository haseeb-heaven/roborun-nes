#ifndef _CONST_H
#define _CONST_H

#define ACCEL 0x20
#define GRAVITY 0x60
#define MAX_SPEED 0x250
#define JUMP_VEL -0x500
#define PLAYER_WIDTH 7
#define PLAYER_HEIGHT 9
#define ENEMY_WIDTH 7
#define ENEMY_HEIGHT 9
#define COLLECTABLE_WIDTH 7
#define COLLECTABLE_HEIGHT 9
#define TURN_OFF 0xFF
#define MAX_ENEMY 5
#define MAX_LEVELS 7
#define MAX_COLLECTABLES 5
#define ANIM_FRAME_OFFSET 5
#define LIFE_TIMER_MAX 30
#define STAR_TIMER_MAX 15

uint8_t enemy_direction, old_enemy_direction;
const uint8_t palette_spr[16] = {0x00, 0x11, 0x26, 0x36, 0x00, 0x01, 0x21, 0x31, 0x00, 0x06, 0x16, 0x26, 0x00, 0x38, 0x19, 0x29};
const uint8_t palette_title[16] = {0x21, 0x00, 0x10, 0x30, 0x21, 0x01, 0x21, 0x31, 0x21, 0x06, 0x16, 0x26, 0x21, 0x38, 0x19, 0x29};
const uint8_t palette_bg1[16] = {0x20, 0x2, 0x17, 0x16, 0x0a, 0x12, 0x22, 0x32, 0x0a, 0x13, 0x15, 0x33, 0x0a, 0x14, 0x07, 0x34};
const uint8_t palette_bg2[16] = {0x20, 0x17, 0x21, 0x4, 0x22, 0x17, 0x21, 0x31, 0x22, 0x06, 0x15, 0x06, 0x22, 0x07, 0x17, 0x3c};
const uint8_t palette_bg3[16] = {0x20, 0x04, 0x1c, 0x4, 0x22, 0x17, 0x21, 0x31, 0x22, 0x06, 0x15, 0x06, 0x22, 0x07, 0x17, 0x3c};

#pragma bss-name(push, "ZEROPAGE")
uint8_t index, collision, collision_L, collision_R, collision_U, collision_D;
uint8_t object_L, object_R, object_U, object_D, map_coords;
const uint8_t *p_maps;
uint8_t eject_L, eject_R, eject_D, eject_U, map;
uint8_t lowX, highX, lowY, temp4, L_R_switch, enemy_index = 0, collectable_index = 0;
unsigned int old_x, upperLeft, up_l_back;
int score, old_score, total_score;
unsigned int scroll_x = 0, scroll_y = 0;
uint8_t lives, stars, game_level = 1, coins, total_coins, max_coins = 5, max_stars = 3, max_lives = 3;
uint8_t old_lives, old_stars, old_level = 1, old_coins, player_anim = 0;
uint8_t enemy_item_count = 0, collectables_item_count = 0, blink_life = 0,blink_cycle = 0,menu_select = 0;
uint8_t life_timer = LIFE_TIMER_MAX,star_timer = STAR_TIMER_MAX;
uint8_t half_dead_state = FALSE, invincible_state = 0,hit_dead = FALSE;
uint8_t level_offset = 1, game_mode, player_vel_state;

enum GAME_MODES
{
	MODE_TITLE,
	MODE_START,
	MODE_HELP,
	MODE_GAME,
	MODE_PAUSE,
	MODE_END,
	MODE_GAME_OVER
};

enum PLAYER_STATES
{
	STATE_DEAD,
	STATE_ALIVE,
	STATE_UNDEF,
	STATE_JUMP_AIR,
	STATE_JUMP_FALL,
};

enum PLAYER_DIR
{
	LEFT = 11,
	RIGHT = 0,
	UP,
	DOWN
};

enum PLAYER_ANIMS
{
	PLAYER_ANIM_IDLE = 0,
	PLAYER_ANIM_PUSH = 4,
	PLAYER_ANIM_JUMP = 7,
	PLAYER_ANIM_FALL,
	PLAYER_ANIM_VICTORY,
	PLAYER_ANIM_DEAD,
};

enum COLLECTABLE_ANIMS
{
	COLLECTABLES_ANIM_COIN,
	COLLECTABLE_ANIM_STAR,
	COLLECTABLE_ANIM_LIFE,
	//Coin animations.
	COLLECTABLES_ANIM_COIN_M1,
	COLLECTABLES_ANIM_COIN_M2,
	COLLECTABLES_ANIM_COIN_M3,
	COLLECTABLES_ANIM_COIN_M4,
};

enum ENEMY_TYPE
{
	ENEMY_FIRE,
	ENEMY_FIRE_BALL,
	ENEMY_SWARS,
	ENEMY_GLOUT,
	ENEMY_BEAR,
	ENEMY_GORILLA,
	ENEMY_BAT,
	ENEMY_OCTA,
	ENEMY_THORN,
	ENEMY_TENTA,
	ENEMY_PUP,
	ENEMY_MUSH,
};

enum COLLECTABLES_TYPE
{
	COLLECTABLE_COIN,
	COLLECTABLE_STAR,
	COLLECTABLE_LIFE
};

enum SONG_TYPE
{
	SONG_TITLE,
	SONG_INGAME_A,
	SONG_INGAME_B,
	SONG_LEVEL_OVER,
	SONG_LEVEL_CLEAR,
};

enum SFX_TYPE
{
	SFX_DEAD,
	SFX_PAUSE,
	SFX_START,
	SFX_STAR,
	SFX_LIFE,
	SFX_COIN,
	SFX_HIT,
	SFX_JUMP,
	SFX_JUMP2,
	SFX_WRONG,
	SFX_HALF_DEAD,
};

#define COL_DOWN 0x80
#define COL_ALL 0x40
#define COL_NONE 0x0

const unsigned char is_solid[] = {
	COL_NONE,
	COL_ALL,  //Floor Brick1
	COL_ALL,  //Platform Brick1
	COL_NONE, //Decorations1
	COL_NONE, //Decorations2
	COL_NONE, //Decorations - Sky & Cloud
	COL_NONE, //Decorations - Sky
	COL_ALL,  //Exit level brick.
	COL_ALL,  //Platform Brick2
	COL_DOWN, //Platformer top1.
	COL_DOWN, //Platformer top1.
	COL_NONE, //Platformer bottom.
	COL_NONE, //Platformer bottom.
	COL_DOWN, //Platformer top2.
	COL_DOWN, //Platformer top2.
	COL_DOWN, //Platformer top2.
	COL_NONE, //Platformer bottom.
	COL_NONE, //Platformer bottom.
	COL_NONE, //Platformer bottom.
	COL_ALL,  //Platform Brick3
	COL_DOWN, //Round Bricks.
	COL_ALL,  //Round Bricks2.
	COL_DOWN, //Enemy block1 (Lava)
	COL_NONE, //Decorations - Sky
	COL_DOWN, //Platform Brick Curved
	COL_NONE, //Decorations - Background
	COL_DOWN, //Square blocks
	COL_DOWN, //Enemy block1 (Spider)
	COL_NONE, //Directional brick fixed.
	COL_NONE, //Platform block - Left.
	COL_ALL,  //Platform block = Mid.
	COL_NONE, //Platform block = Right.
	COL_ALL,  //Green Platform block - Left.
	COL_ALL,  //Green Platform block - Mid.
	COL_ALL,  //Green Platform block - Right.
	COL_DOWN, //Sand Platform block - Left.
	COL_DOWN, //Sand Platform block - Mid.
	COL_DOWN, //Sand Platform block - Right.
	COL_ALL,  //Green block.
	COL_ALL,  //Brown brick faced.
	COL_ALL,  //Ice Platform block - Left.
	COL_ALL,  //Ice Platform block - Mid.
	COL_ALL,  //Ice Platform block - Right.
};

//Colliion map for colliion detection.
#pragma bss-name(push, "BSS")
uint8_t c_map[240];

//Structures for Player and Enemy
typedef struct Base
{
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
} GenericBase;

GenericBase genericBase1, genericBase2;

typedef struct Sprite
{
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
	uint8_t direction;
	uint8_t state;
	uint8_t type;
} Player, Enemy, Collectable;

Player playerRobo = {0x2FDF, 0xc200, 10, 8, RIGHT, STATE_ALIVE, -1};

#pragma bss-name(push, "ZEROPAGE")
Enemy enemy_list[MAX_ENEMY] = {NULL};
Collectable collectable_list[MAX_COLLECTABLES] = {NULL};
#endif
