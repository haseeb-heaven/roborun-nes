#include "metatiles_bg.h"


/*Enemy metasprites list*/
const unsigned char enemy_spr_0_data[]={

	- 8,- 8,0x0a,1,
	- 8,  0,0x1a,1,
	  0,- 8,0x0a,1|OAM_FLIP_H,
	  0,  0,0x1a,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_1_data[]={

	- 8,- 8,0x45,1,
	- 8,  0,0x55,1,
	  0,- 8,0x45,1|OAM_FLIP_H,
	  0,  0,0x55,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_2_data[]={

	- 8,- 8,0x40,1,
	- 8,  0,0x50,1,
	  0,- 8,0x40,1|OAM_FLIP_H,
	  0,  0,0x50,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_3_data[]={

	- 8,- 8,0x0e,2,
	- 8,  0,0x1e,2,
	  0,- 8,0x0e,2|OAM_FLIP_H,
	  0,  0,0x1e,2|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_4_data[]={

	- 8,- 8,0x0f,1,
	- 8,  0,0x1f,1,
	  0,- 8,0x0f,1|OAM_FLIP_H,
	  0,  0,0x1f,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_5_data[]={

	- 8,- 8,0x07,1,
	- 8,  0,0x17,1,
	  0,- 8,0x07,1|OAM_FLIP_H,
	  0,  0,0x17,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_6_data[]={

	- 8,- 8,0x41,1,
	- 8,  0,0x51,1,
	  0,- 8,0x41,1|OAM_FLIP_H,
	  0,  0,0x51,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_7_data[]={

	- 8,- 8,0x0b,1,
	- 8,  0,0x1b,1,
	  0,- 8,0x0b,1|OAM_FLIP_H,
	  0,  0,0x1b,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_8_data[]={

	- 8,- 8,0x0c,1,
	- 8,  0,0x1c,1,
	  0,- 8,0x0c,1|OAM_FLIP_H,
	  0,  0,0x1c,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_9_data[]={

	- 8,- 8,0x42,1,
	- 8,  0,0x52,1,
	  0,- 8,0x42,1|OAM_FLIP_H,
	  0,  0,0x52,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_10_data[]={

	- 8,- 8,0x43,1,
	- 8,  0,0x53,1,
	  0,- 8,0x43,1|OAM_FLIP_H,
	  0,  0,0x53,1|OAM_FLIP_H,
	128

};

const unsigned char enemy_spr_11_data[]={

	- 8,- 8,0x46,1,
	- 8,  0,0x56,1,
	  0,- 8,0x46,1|OAM_FLIP_H,
	  0,  0,0x56,1|OAM_FLIP_H,
	128

};

const unsigned char* const enemy_spr_list[]={

	enemy_spr_0_data,
	enemy_spr_1_data,
	enemy_spr_2_data,
	enemy_spr_3_data,
	enemy_spr_4_data,
	enemy_spr_5_data,
	enemy_spr_6_data,
	enemy_spr_7_data,
	enemy_spr_8_data,
	enemy_spr_9_data,
	enemy_spr_10_data,
	enemy_spr_11_data

};


//Robo player sprites and animations.
const unsigned char player_robo_spr_0_data[]={

	- 8,- 8,0x80,0,
	  0,- 8,0x81,0,
	- 8,  0,0x90,0,
	  0,  0,0x91,0,
	128

};

const unsigned char player_robo_spr_1_data[]={

	- 8,- 8,0x86,0,
	  0,- 8,0x87,0,
	- 8,  0,0x96,0,
	  0,  0,0x97,0,
	128

};

const unsigned char player_robo_spr_2_data[]={

	- 8,- 8,0x88,0,
	  0,- 8,0x89,0,
	- 8,  0,0x98,0,
	  0,  0,0x99,0,
	128

};

const unsigned char player_robo_spr_3_data[]={

	- 8,- 8,0x8a,0,
	  0,- 8,0x8b,0,
	- 8,  0,0x9a,0,
	  0,  0,0x9b,0,
	128

};

const unsigned char player_robo_spr_4_data[]={

	- 8,- 8,0xa0,0,
	  0,- 8,0xa1,0,
	- 8,  0,0xb0,0,
	  0,  0,0xb1,0,
	128

};

const unsigned char player_robo_spr_5_data[]={

	- 8,- 8,0xa2,0,
	  0,- 8,0xa3,0,
	- 8,  0,0xb2,0,
	  0,  0,0xb3,0,
	128

};

const unsigned char player_robo_spr_6_data[]={

	- 8,- 8,0xa4,0,
	  0,- 8,0xa5,0,
	- 8,  0,0xb4,0,
	  0,  0,0xb5,0,
	128

};

const unsigned char player_robo_spr_7_data[]={

	- 8,- 8,0x82,0,
	  0,- 8,0x83,0,
	- 8,  0,0x92,0,
	  0,  0,0x93,0,
	128

};

const unsigned char player_robo_spr_8_data[]={

	- 8,- 8,0x84,0,
	  0,- 8,0x85,0,
	- 8,  0,0x94,0,
	  0,  0,0x95,0,
	128

};

const unsigned char player_robo_spr_9_data[]={

	- 8,- 8,0x8c,0,
	  0,- 8,0x8d,0,
	- 8,  0,0x9c,0,
	  0,  0,0x9d,0,
	128

};

const unsigned char player_robo_spr_10_data[]={

	- 8,  0,0x9e,0,
	  0,  0,0x9f,0,
	128

};

const unsigned char player_robo_spr_11_data[]={

	  0,- 8,0x80,0|OAM_FLIP_H,
	- 8,- 8,0x81,0|OAM_FLIP_H,
	  0,  0,0x90,0|OAM_FLIP_H,
	- 8,  0,0x91,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_12_data[]={

	  0,- 8,0x86,0|OAM_FLIP_H,
	- 8,- 8,0x87,0|OAM_FLIP_H,
	  0,  0,0x96,0|OAM_FLIP_H,
	- 8,  0,0x97,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_13_data[]={

	  0,- 8,0x88,0|OAM_FLIP_H,
	- 8,- 8,0x89,0|OAM_FLIP_H,
	  0,  0,0x98,0|OAM_FLIP_H,
	- 8,  0,0x99,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_14_data[]={

	  0,- 8,0x8a,0|OAM_FLIP_H,
	- 8,- 8,0x8b,0|OAM_FLIP_H,
	  0,  0,0x9a,0|OAM_FLIP_H,
	- 8,  0,0x9b,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_15_data[]={

	  0,- 8,0xa0,0|OAM_FLIP_H,
	- 8,- 8,0xa1,0|OAM_FLIP_H,
	  0,  0,0xb0,0|OAM_FLIP_H,
	- 8,  0,0xb1,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_16_data[]={

	  0,- 8,0xa2,0|OAM_FLIP_H,
	- 8,- 8,0xa3,0|OAM_FLIP_H,
	  0,  0,0xb2,0|OAM_FLIP_H,
	- 8,  0,0xb3,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_17_data[]={

	  0,- 8,0xa4,0|OAM_FLIP_H,
	- 8,- 8,0xa5,0|OAM_FLIP_H,
	  0,  0,0xb4,0|OAM_FLIP_H,
	- 8,  0,0xb5,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_18_data[]={

	  0,- 8,0x82,0|OAM_FLIP_H,
	- 8,- 8,0x83,0|OAM_FLIP_H,
	  0,  0,0x92,0|OAM_FLIP_H,
	- 8,  0,0x93,0|OAM_FLIP_H,
	128

};

const unsigned char player_robo_spr_19_data[]={

	  0,- 8,0x84,0|OAM_FLIP_H,
	- 8,- 8,0x85,0|OAM_FLIP_H,
	  0,  0,0x94,0|OAM_FLIP_H,
	- 8,  0,0x95,0|OAM_FLIP_H,
	128

};

const unsigned char* const player_robo_spr_list[]={

	player_robo_spr_0_data,
	player_robo_spr_1_data,
	player_robo_spr_2_data,
	player_robo_spr_3_data,
	player_robo_spr_4_data,
	player_robo_spr_5_data,
	player_robo_spr_6_data,
	player_robo_spr_7_data,
	player_robo_spr_8_data,
	player_robo_spr_9_data,
	player_robo_spr_10_data,
	player_robo_spr_11_data,
	player_robo_spr_12_data,
	player_robo_spr_13_data,
	player_robo_spr_14_data,
	player_robo_spr_15_data,
	player_robo_spr_16_data,
	player_robo_spr_17_data,
	player_robo_spr_18_data,
	player_robo_spr_19_data

};


//Collectables items.
const unsigned char collectables_spr_0_data[]={

	- 8,- 8,0x60,2,
	- 8,  0,0x70,2,
	  0,- 8,0x60,2|OAM_FLIP_H,
	  0,  0,0x70,2|OAM_FLIP_H,
	128

};

const unsigned char collectables_spr_1_data[]={

	- 8,- 8,0x44,1,
	- 8,  0,0x54,1,
	  0,- 8,0x44,1|OAM_FLIP_H,
	  0,  0,0x54,1|OAM_FLIP_H,
	128

};

const unsigned char collectables_spr_2_data[]={

	- 8,- 8,0x47,1,
	- 8,  0,0x57,1,
	  0,  0,0x57,1|OAM_FLIP_H,
	  0,- 8,0x47,1,
	128

};

const unsigned char collectables_spr_3_data[]={

	- 8,- 8,0x60,2,
	- 8,  0,0x70,2,
	  0,- 8,0x60,2|OAM_FLIP_H,
	  0,  0,0x70,2|OAM_FLIP_H,
	128

};

const unsigned char collectables_spr_4_data[]={

	- 8,- 8,0x61,2,
	- 8,  0,0x71,2,
	  0,- 8,0x62,2,
	  0,  0,0x72,2,
	128

};

const unsigned char collectables_spr_5_data[]={

	- 8,- 8,0x63,2,
	- 8,  0,0x73,2,
	  0,- 8,0x64,2,
	  0,  0,0x74,2,
	128

};

const unsigned char collectables_spr_6_data[]={

	- 8,- 8,0x65,2,
	- 8,  0,0x75,2,
	  0,- 8,0x66,2,
	  0,  0,0x76,2,
	128

};

const unsigned char* const collectables_spr_list[]={

	collectables_spr_0_data,
	collectables_spr_1_data,
	collectables_spr_2_data,
	collectables_spr_3_data,
	collectables_spr_4_data,
	collectables_spr_5_data,
	collectables_spr_6_data

};




