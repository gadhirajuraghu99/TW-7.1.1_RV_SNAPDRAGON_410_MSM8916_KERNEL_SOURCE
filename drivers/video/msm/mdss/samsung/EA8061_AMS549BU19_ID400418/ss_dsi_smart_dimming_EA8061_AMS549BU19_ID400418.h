/*
 * =================================================================
 *
 *
 *	Description:  samsung display panel file
 *
 *	Author: jb09.kim
 *	Company:  Samsung Electronics
 *
 * ================================================================
 */
/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2012, Samsung Electronics. All rights reserved.

*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#ifndef _SS_DSI_SMART_MTP_MAGNA_EA8061_SDC__H_
#define _SS_DSI_SMART_MTP_MAGNA_EA8061_SDC__H_

#include "../ss_dsi_panel_common.h"
#include "../ss_dsi_smart_dimming_common.h"

/*
*	From 4.8 inch model use AID function
*	CASE#1 is used for now.
*/
#define AID_OPERATION

enum {
	GAMMA_CURVE_1P9 = 0,
	GAMMA_CURVE_2P0,
	GAMMA_CURVE_2P15,
	GAMMA_CURVE_2P2,
};

#define REV_A	0x00
#define REV_C	0x01

#define LUMINANCE_MAX 62
#define GAMMA_SET_MAX 33
#define BIT_SHIFT 22
/*
	it means BIT_SHIFT is 22.  pow(2,BIT_SHIFT) is 4194304.
	BIT_SHIFT is used for right bit shfit
*/
#define BIT_SHFIT_MUL 4194304

#define GRAY_SCALE_MAX 256

/* 5.8 * 4194304 */
#define VREG0_REF_5P8 24326963
/* 5.6 * 4194304 */
#define VREG0_REF_5P6 23488102

/*V0,V3,V11,V23,V35,V51,V87,V151,V203,V255*/
#define ARRAY_MAX 11

/* PANEL DEPENDENT THINGS */
#define MIN_CANDELA	5

/*
*	ID 0x20
*/
#define V255_300CD_R_MSB_20 0x01
#define V255_300CD_R_LSB_20 0x00

#define V255_300CD_G_MSB_20 0x01
#define V255_300CD_G_LSB_20 0x00

#define V255_300CD_B_MSB_20 0x01
#define V255_300CD_B_LSB_20 0x00

#define V203_300CD_R_20 0x80
#define V203_300CD_G_20 0x80
#define V203_300CD_B_20 0x80

#define V151_300CD_R_20 0x80
#define V151_300CD_G_20 0x80
#define V151_300CD_B_20 0x80

#define V87_300CD_R_20 0x80
#define V87_300CD_G_20 0x80
#define V87_300CD_B_20 0x80

#define V51_300CD_R_20 0x80
#define V51_300CD_G_20 0x80
#define V51_300CD_B_20 0x80

#define V35_300CD_R_20 0x80
#define V35_300CD_G_20 0x80
#define V35_300CD_B_20 0x80

#define V23_300CD_R_20 0x80
#define V23_300CD_G_20 0x80
#define V23_300CD_B_20 0x80

#define V11_300CD_R_20 0x80
#define V11_300CD_G_20 0x80
#define V11_300CD_B_20 0x80

#define V3_300CD_R_20 0x80
#define V3_300CD_G_20 0x80
#define V3_300CD_B_20 0x80

#define VT_300CD_R_20 0x00
#define VT_300CD_G_20 0x00
#define VT_300CD_B_20 0x00


/* PANEL DEPENDENT THINGS END*/

enum {
	V1_INDEX = 0,
	V3_INDEX = 1,
	V11_INDEX = 2,
	V23_INDEX = 3,
	V35_INDEX = 4,
	V51_INDEX = 5,
	V87_INDEX = 6,
	V151_INDEX = 7,
	V203_INDEX = 8,
	V255_INDEX = 9,
};

struct GAMMA_LEVEL {
	int level_0;
	int level_1;
	int level_3;
	int level_11;
	int level_23;
	int level_35;
	int level_51;
	int level_87;
	int level_151;
	int level_203;
	int level_255;
} __packed;

struct RGB_OUTPUT_VOLTARE {
	struct GAMMA_LEVEL R_VOLTAGE;
	struct GAMMA_LEVEL G_VOLTAGE;
	struct GAMMA_LEVEL B_VOLTAGE;
} __packed;

struct GRAY_VOLTAGE {
	/*
		This voltage value use 14bit right shit
		it means voltage is divied by 16384.
	*/
	int R_Gray;
	int G_Gray;
	int B_Gray;
} __packed;

struct GRAY_SCALE {
	struct GRAY_VOLTAGE TABLE[GRAY_SCALE_MAX];
	struct GRAY_VOLTAGE VT_TABLE;
} __packed;

/*V0,V1,V3,V11,V23,V35,V51,V87,V151,V203,V255*/

struct MTP_SET {
	char OFFSET_255_MSB;
	char OFFSET_255_LSB;
	char OFFSET_203;
	char OFFSET_151;
	char OFFSET_87;
	char OFFSET_51;
	char OFFSET_35;
	char OFFSET_23;
	char OFFSET_11;
	char OFFSET_3;
	char OFFSET_1;
} __packed;

struct MTP_OFFSET {
	struct MTP_SET R_OFFSET;
	struct MTP_SET G_OFFSET;
	struct MTP_SET B_OFFSET;
} __packed;

struct illuminance_table {
	int lux;
	char gamma_setting[GAMMA_SET_MAX];
} __packed;

struct SMART_DIM {
	struct MTP_OFFSET MTP_ORIGN;

	struct MTP_OFFSET MTP;
	struct RGB_OUTPUT_VOLTARE RGB_OUTPUT;
	struct GRAY_SCALE GRAY;

	/* Because of AID funtion, below members are added*/
	int lux_table_max;
	int *plux_table;
	struct illuminance_table gen_table[LUMINANCE_MAX];

	int brightness_level;
	int ldi_revision;
	int vregout_voltage;
} __packed;

#define AOR_DIM_BASE_CD_REVA	115
#define AOR_DIM_BASE_CD_REVE	113

#define CANDELA_MAX_TABLE 61
#define RGB_COMPENSATION 24

static int candela_table[][2] = {
	{5, 0},
	{6, 1},
	{7, 2},
	{8, 3},
	{9, 4},
	{10, 5},
	{11, 6},
	{12, 7},
	{13, 8},
	{14, 9},
	{15, 10},
	{16, 11},
	{17, 12},
	{19, 13},
	{20, 14},
	{21, 15},
	{22, 16},
	{24, 17},
	{25, 18},
	{27, 19},
	{29, 20},
	{30, 21},
	{32, 22},
	{34, 23},
	{37, 24},
	{39, 25},
	{41, 26},
	{44, 27},
	{47, 28},
	{50, 29},
	{53, 30},
	{56, 31},
	{60, 32},
	{64, 33},
	{68, 34},
	{72, 35},
	{77, 36},
	{82, 37},
	{87, 38},
	{93, 39},
	{98, 40},
	{105, 41},
	{111, 42},
	{119, 43},
	{126, 44},
	{134, 45},
	{143, 46},
	{152, 47},
	{162, 48},
	{172, 49},
	{183, 50},
	{195, 51},
	{207, 52},
	{220, 53},
	{234, 54},
	{249, 55},
	{265, 56},
	{282, 57},
	{300, 58},
	{316, 59},
	{333, 60},
	{350, 61},
};
static int base_luminance_revA[][2] = {
	{5, 113,},
	{6, 113,},
	{7, 113,},
	{8, 113,},
	{9, 113,},
	{10, 113,},
	{11, 113,},
	{12, 113,},
	{13, 113,},
	{14, 113,},
	{15, 113,},
	{16, 113,},
	{17, 113,},
	{19, 113,},
	{20, 113,},
	{21, 113,},
	{22, 113,},
	{24, 113,},
	{25, 113,},
	{27, 113,},
	{29, 113,},
	{30, 113,},
	{32, 113,},
	{34, 113,},
	{37, 113,},
	{39, 113,},
	{41, 113,},
	{44, 113,},
	{47, 113,},
	{50, 113,},
	{53, 113,},
	{56, 113,},
	{60, 113,},
	{64, 113,},
	{68, 113,},
	{72, 118,},
	{77, 126,},
	{82, 135,},
	{87, 141,},
	{93, 151,},
	{98, 158,},
	{105, 170,},
	{111, 180,},
	{119, 191,},
	{126, 201,},
	{134, 214,},
	{143, 229,},
	{152, 240,},
	{162, 256,},
	{172, 256,},
	{183, 256,},
	{195, 256,},
	{207, 256,},
	{220, 256,},
	{234, 256,},
	{249, 256,},
	{265, 272,},
	{282, 285,},
	{300, 303,},
	{316, 318,},
	{333, 338,},
	{350, 350,},
};

static int base_luminance_revE[][2] = {
	{5, 113},
	{6, 113},
	{7, 113},
	{8, 113},
	{9, 113},
	{10, 113},
	{11, 113},
	{12, 113},
	{13, 113},
	{14, 113},
	{15, 113},
	{16, 113},
	{17, 113},
	{19, 113},
	{20, 113},
	{21, 113},
	{22, 113},
	{24, 113},
	{25, 113},
	{27, 113},
	{29, 113},
	{30, 113},
	{32, 113},
	{34, 113},
	{37, 113},
	{39, 113},
	{41, 113},
	{44, 113},
	{47, 113},
	{50, 113},
	{53, 113},
	{56, 113},
	{60, 113},
	{64, 113},
	{68, 113},
	{72, 113},
	{77, 121},
	{82, 129},
	{87, 136},
	{93, 145},
	{98, 153},
	{105, 162},
	{111, 171},
	{119, 183},
	{126, 192},
	{134, 202},
	{143, 216},
	{152, 229},
	{162, 242},
	{172, 255},
	{183, 255},
	{195, 255},
	{207, 255},
	{220, 255},
	{234, 255},
	{249, 255},
	{265, 269},
	{282, 286},
	{300, 308},
	{316, 321},
	{333, 336},
	{350, 350},
};
static int gradation_offset_revA[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 7, 13, 17, 18, 21, 22, 25, 27},
	{0, 7, 12, 15, 16, 22, 21, 23, 26},
	{0, 6, 11, 13, 14, 20, 20, 21, 24},
	{0, 6, 10, 12, 13, 18, 18, 20, 22},
	{0, 6, 9, 11, 12, 16, 16, 18, 20},
	{0, 5, 8, 9, 11, 12, 14, 16, 18},
	{0, 5, 8, 9, 11, 12, 13, 16, 18},
	{0, 5, 7, 9, 10, 11, 12, 15, 17},
	{0, 5, 7, 8, 9, 10, 12, 14, 16},
	{0, 5, 7, 8, 8, 10, 11, 13, 15},
	{0, 5, 6, 8, 8 , 9, 10, 13, 14},
	{0, 4, 6, 7, 7, 9, 9, 12, 13},
	{0, 4, 6, 7, 7, 8, 9, 12, 12},
	{0, 4, 6, 6, 6, 8, 9, 11, 12},
	{0, 4, 6, 6, 6, 7, 8, 11, 12},
	{0, 4, 6, 6, 6, 8, 8, 11, 12},
	{0, 4, 5, 6, 6, 7, 9, 12, 12},
	{0, 4, 5, 6, 5, 7, 9, 11, 12},
	{0, 4, 5, 6, 5, 7, 9, 11, 11},
	{0, 4, 5, 6, 5, 7, 8, 11, 11},
	{0, 4, 5, 6, 5, 7, 8, 10, 11},
	{0, 4, 5, 6, 5, 6, 8, 10, 10},
	{0, 3, 4, 6, 5, 6, 8, 10, 10},
	{0, 3, 4, 5, 4, 6, 7, 9, 8},
	{0, 3, 4, 4, 4, 6, 7, 9, 8},
	{0, 3, 4, 4, 4, 6, 7, 9, 8},
	{0, 3, 4, 4, 3, 5, 6, 8, 8},
	{0, 3, 4, 4, 3, 5, 6, 8, 8},
	{0, 3, 4, 4, 3, 4, 5, 8, 7},
	{0, 3, 4, 4, 3, 4, 5, 7, 6},
	{0, 3, 4, 4, 3, 4, 5, 7, 6},
	{0, 3, 3, 4, 2, 4, 5, 7, 6},
	{0, 3, 3, 4, 2, 3, 4, 6, 4},
	{0, 3, 3, 4, 2, 3, 4, 6, 6},
	{0, 3, 3, 3, 2, 3, 4, 5, 6},
	{0, 3, 3, 3, 2, 2, 4, 5, 6},
	{0, 3, 3, 3, 2, 2, 4, 5, 6},
	{0, 3, 3, 3, 2, 2, 4, 4, 6},
	{0, 3, 3, 3, 2, 2, 4, 4, 6},
	{0, 2, 3, 3, 2, 2, 3, 4, 6},
	{0, 2, 3, 3, 2, 2, 3, 4, 6},
	{0, 1, 3, 3, 2, 2, 3, 4, 6},
	{0, 1, 3, 3, 2, 2, 3, 4, 5},
	{0, 1, 3, 3, 2, 2, 3, 4, 5},
	{0, 1, 3, 3, 2, 2, 3, 4, 5},
	{0, 1, 3, 3, 2, 2, 3, 4, 4},
	{0, 1, 3, 3, 2, 2, 3, 3, 4},
	{0, 1, 3, 3, 2, 2, 3, 3, 4},
	{0, 2, 2, 3, 2, 2, 2, 3, 4},
	{0, 1, 2, 2, 1, 1, 2, 3, 4},
	{0, 1, 1, 2, 1, 1, 2, 3, 4},
	{0, 1, 1, 2, 1, 1, 1, 3, 3},
	{0, 1, 1, 2, 1, 1, 1, 2, 2},
	{0, 1, 0, 2, 0, 0, 0, 1, 2},
	{0, 0, 0, 1, 0, 0, 1, 1, 3},
	{0, 0, 0, 1, 0, 0, 0, 1, 2},
	{0, 0, 1, 1, 0, 0, 0, 1, 2},
	{0, 1, 1, 0, 0, 0, 1, 1, 3},
	{0, 0, 1, 1, 0, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static int gradation_offset_revE[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 6, 8, 13, 15, 16, 17, 18, 20},
	{0, 5, 8, 12, 14, 14, 15, 15, 18},
	{0, 5, 7, 11, 13, 13, 14, 14, 17},
	{0, 5, 7, 10, 11, 12, 13, 14, 16},
	{0, 5, 6, 9, 10, 11, 12, 13, 15},
	{0, 4, 6, 8, 9, 10, 10, 12, 14},
	{0, 4, 6, 8, 9, 9, 9, 11, 13},
	{0, 4, 6, 7, 8, 9, 9, 10, 12},
	{0, 4, 5, 6, 7, 8, 9, 10, 12},
	{0, 4, 5, 6, 6, 8, 8, 10, 12},
	{0, 4, 5, 6, 6, 7, 8, 9, 11},
	{0, 4, 5, 5, 5, 7, 7, 9, 11},
	{0, 4, 4, 5, 5, 6, 7, 9, 11},
	{0, 4, 4, 5, 5, 6, 7, 9, 11},
	{0, 4, 4, 5, 5, 6, 7, 9, 11},
	{0, 4, 4, 5, 5, 7, 8, 10, 12},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 5, 4, 6, 6, 8, 9, 11, 13},
	{0, 4, 4, 6, 6, 8, 9, 11, 12},
	{0, 4, 4, 6, 5, 7, 8, 10, 11},
	{0, 4, 4, 5, 5, 6, 7, 9, 10},
	{0, 4, 4, 5, 5, 5, 7, 9, 10},
	{0, 4, 4, 5, 5, 5, 6, 8, 9},
	{0, 4, 4, 5, 4, 4, 6, 8, 9},
	{0, 4, 4, 5, 4, 4, 5, 7, 8},
	{0, 4, 4, 4, 4, 4, 5, 6, 8},
	{0, 3, 4, 4, 4, 4, 5, 6, 7},
	{0, 3, 4, 4, 4, 3, 4, 5, 7},
	{0, 3, 4, 4, 4, 3, 4, 5, 7},
	{0, 3, 4, 4, 4, 3, 4, 5, 7},
	{0, 3, 4, 4, 4, 3, 4, 4, 6},
	{0, 3, 4, 4, 4, 3, 4, 4, 6},
	{0, 3, 4, 4, 4, 3, 4, 4, 6},
	{0, 3, 4, 4, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 4, 4, 6},
	{0, 3, 4, 5, 4, 3, 3, 4, 5},
	{0, 3, 4, 5, 4, 3, 3, 4, 5},
	{0, 3, 4, 5, 4, 3, 3, 4, 5},
	{0, 3, 4, 4, 3, 3, 3, 3, 4},
	{0, 3, 4, 4, 3, 3, 2, 3, 4},
	{0, 3, 4, 4, 3, 2, 2, 3, 3},
	{0, 3, 3, 3, 2, 2, 2, 2, 2},
	{0, 3, 3, 3, 2, 2, 2, 2, 2},
	{0, 3, 3, 3, 2, 2, 2, 2, 2},
	{0, 2, 3, 2, 1, 1, 1, 2, 2},
	{0, 2, 4, 2, 1, 1, 1, 0, 3},
	{0, 1, 3, 1, 2, 1, 1, 1, 0},
	{0, 0, 3, 0, 1, 0, 1, 1, 0},
	{0, 1, 2, 0, 1, 1, 1, 1, 0},
	{0, 0, 1, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static int rgb_offset_revA[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{-2, 0, -2, -3, 0, -2, -4, 0, -4, -11, 4, -9, -19, 5, -15, -20, 4, -10, -15, 4, -8, -18, 4, -20},
	{-2, 0, -1, -2, 0, -2, -4, 0, -4, -11, 4, -10, -13, 5, -12, -12, 4, -6, -9, 4, -10, -16, 4, -16},
	{-1, 0, -1, -2, 0, -2, -3, 0, -3, -10, 4, -9, -18, 5, -11, -8, 4, -5, -7, 4, -8, -13, 4, -13},
	{-1, 0, -1, -2, 0, -1, -2, 0, -2, -8, 3, -9, -10, 5, -11, -9, 4, -3, -7, 5, -7, -11, 4, -11},
	{-1, 0, 0, -2, 0, -3, -2, 0, -1, -7, 3, -7, -9, 5, -11, -11, 4, -3, -11, 3, -11, -11, 5, -10},
	{0, 0, 0, -2, 0, -2, -2, 0, -1, -9, 3, -9, -14, 5, -10, -15, 4, -7, -7, 4, -8, -11, 5, -11},
	{0, 0, 0, -2, 0, -2, -2, 0, -1, -8, 3, -8, -13, 5, -9, -13, 4, -7, -4, 4, -9, -10, 5, -11},
	{0, 0, 0, -1, 0, -1, -3, 0, -2, -8, 2, -8, -12, 5, -9, -12, 4, -7, -5, 4, -9, -10, 5, -11},
	{0, 0, 0, -1, 0, -1, -3, 0, -2, -6, 2, -8, -11, 5, -8, -14, 4, -7, -4, 4, -8, -10, 5, -10},
	{0, 0, 0, -1, 0, -1, -3, 0, -2, -6, 2, -7, -9, 4, -10, -9, 4, -4, -12, 4, -9, -10, 5, -10},
	{0, 0, 0, -1, 0, -1, -1, 0, -1, -6, 2, -6, -11, 4, -11, -9, 4, -5, -8, 4, -8, -10, 5, -9},
	{0, 0, 0, -1, 0, -1, -1, 0, -1, -6, 2, -6, -10, 4, -10, -9, 4, -4, -11, 4, -9, -10, 5, -10},
	{0, 0, 0, -1, 0, -1, -1, 0, -1, -5, 2, -5, -11, 5, -9, -10, 4, -4, -3, 4, -9, -8, 5, -10},
	{0, 0, 0, 0, 0, 0, -1, 0, -1, -5, 1, -5, -7, 4, -9, -4, 3, -2, -10, 4, -7, -7, 5, -11},
	{0, 0, 0, 0, 0, 0, -1, 0, -1, -4, 1, -6, -10, 4, -6, -10, 3, -6, -4, 4, -8, -7, 5, -11},
	{0, 0, 0, 0, 0, 0, -1, 0, -1, -4, 1, -6, -7, 4, -8, -6, 3, -3, -8, 4, -8, -6, 5, -13},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -4, 1, -5, -8, 4, -7, -12, 3, -7, -3, 4, -7, -6, 5, -12},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 1, -5, -8, 4, -8, -11, 3, -4, -2, 3, -7, -6, 5, -13},
	{0, 0, 0, 0, 0, 0, -1, 0, 0, -3, 1, -6, -7, 4, -7, -12, 2, -5, -1, 4, -6, -5, 5, -15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 1, -5, -7, 4, -8, -10, 2, -5, 1, 4, -9, -4, 4, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -6, -7, 4, -7, -11, 2, -5, 0, 4, -9, -5, 5, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -6, -8, 4, -8, -11, 2, -6, -4, 3, -11, -5, 6, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -3, 0, -6, -6, 4, -6, -10, 2, -5, -4, 3, -9, -5, 6, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -3, 0, -6, -4, 3, -8, -4, 2, -5, -7, 3, -10, -4, 5, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -2, 0, -5, -6, 3, -7, -7, 2, -2, 0, 3, -7, -3, 5, -18},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -2, 0, -5, -4, 3, -6, -2, 1, -3, -8, 3, -6, -3, 5, -19},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -2, 0, -4, -3, 3, -6, -3, 1, -4, -8, 3, -6, -3, 5, -18},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -2, 0, -4, -3, 3, -6, -3, 1, -3, -7, 2, -7, -5, 6, -18},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -2, 0, -4, -4, 3, -4, -8, 1, -4, 0, 2, -7, -1, 6, -13},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -1, 0, -3, -5, 3, -5, -7, 1, -3, 1, 2, -5, -1, 6, -16},
	{0, 0, 0, 0, 0, 0, 2, 0, 2, -2, 0, -4, -3, 3, -4, -3, 1, -2, -4, 2, -3, -1, 6, -13},
	{0, 0, 0, 1, 0, 1, 0, 0, 0, -3, 0, -4, -1, 2, -5, -2, 1, -1, -5, 2, -3, -1, 5, -13},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, -3, -2, 2, -5, -2, 1, -2, -5, 2, -4, -1, 5, -13},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -2, 0, -3, -1, 2, -4, -1, 1, -2, -4, 2, -2, -1, 5, -12},
	{0, 0, 0, 1, 0, 1, 0, 0, 0, -1, 0, -3, -2, 2, -3, 1, 1, 0, -4, 1, -3, -2, 5, -12},
	{0, 0, 0, -1, 0, -1, 1, 0, 1, -2, 0, -4, -3, 2, -4, -7, 1, 0, 2, 1, -4, 1, 5, -14},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -3, 0, -4, -3, 2, -3, -5, 0, -2, 2, 1, -4, -1, 6, -14},
	{0, 0, 0, 0, 0, 1, 1, 0, 0, -2, 0, -2, -3, 2, -3, -6, 1, -1, 4, 1, -2, -2, 5, -14},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, -2, -3, 1, -4, -4, 1, 0, 2, 1, -3, -1, 6, -12},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 2, -2, -2, 1, -1, -1, 1, -2, 1, 5, -11},
	{0, 0, 0, 1, 0, 1, 0, 0, 0, -1, 0, -2, -1, 1, -3, -1, 1, -1, -3, 1, -2, -1, 5, -16},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 1, -3, 0, 1, -2, -4, 1, -3, -1, 5, -14},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, -1, 0, -1, -1, 1, -3, -2, 1, -2, -5, 1, -1, -1, 4, -11},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 1, -3, -1, 1, -1, -3, 1, -2, -3, 4, -12},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, -1, -1, 0, -4, -1, 1, -1, -3, 1, -2, -3, 4, -14},
	{0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, -1, -2, 0, -4, -2, 1, -1, -6, 1, -3, -3, 4, -12},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, 0, -4, -1, 1, -2, -3, 1, -2, -4, 4, -14},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, -4, -1, 1, -1, -3, 1, -2, -3, 3, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -3, -1, 1, -1, -3, 0, -2, -2, 3, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -3, -2, 1, -1, -3, 1, -1, -2, 3, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -2, 1, 0, -2, 0, -2, -3, 3, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 1, 0, -1, 0, -1, -2, 2, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, -2, 1, 0, 0, 0, -1, 0, 2, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 1, -2, 0, 0, 0, 1, 2, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 1, 0, -2, 0, 0, 0, 0, 2, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static int rgb_offset_revE[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{-3, 0, -2, -4, 0, -3, -5, 1, -3, -12, 2, -9, -18, 2, -12, -13, 2, -9, -12, 3, -8, -1, 3, -3},
	{-3, 0, -1, -3, 0, -3, -5, 0, -4, -14, 0, -10, -16, 2, -12, -12, 2, -8, -16, 3, -9, -3, 3, -3},
	{-2, 0, -1, -2, 0, -2, -5, 0, -3, -12, 0, -9, -16, 2, -11, -10, 2, -7, -13, 3, -10, -5, 3, -4},
	{-2, 0, -1, -2, 0, -2, -5, 0, -3, -11, 0, -8, -14, 2, -10, -11, 2, -6, -13, 3, -8, -13, 3, -8},
	{-1, 0, 0, -2, 0, -2, -5, 0, -3, -11, 0, -8, -14, 2, -12, -11, 2, -5, -15, 3, -11, -15, 3, -8},
	{-1, 0, 0, -2, 0, -2, -4, 0, -2, -10, 0, -7, -12, 2, -10, -9, 2, -5, -15, 3, -11, -17, 3, -11},
	{-1, 0, 0, -2, 0, -2, -3, 0, -2, -9, 0, -6, -12, 2, -9, -9, 2, -4, -12, 3, -11, -17, 3, -11},
	{-1, 0, 0, -2, 0, -2, -3, 0, -2, -9, 0, -6, -12, 2, -11, -9, 2, -4, -12, 3, -9, -17, 3, -13},
	{-1, 0, 0, -2, 0, -2, -3, 0, -2, -7, 0, -5, -11, 2, -9, -9, 2, -4, -12, 3, -8, -17, 3, -15},
	{-1, 0, 0, -1, 0, -1, -3, 0, -2, -8, 0, -5, -8, 2, -9, -9, 2, -3, -11, 3, -9, -17, 3, -14},
	{-1, 0, 0, -1, 0, -1, -3, 0, -2, -6, 0, -4, -9, 2, -9, -8, 2, -3, -10, 3, -7, -17, 3, -14},
	{-1, 0, 0, -1, 0, -1, -1, 0, -1, -6, 0, -5, -11, 2, -10, -8, 2, -1, -10, 3, -8, -16, 3, -13},
	{-1, 0, 0, -1, 0, -1, -1, 0, -1, -6, 0, -5, -8, 2, -9, -8, 2, -3, -10, 3, -7, -16, 3, -13},
	{-1, 0, 0, -1, 0, -1, -1, 0, -1, -5, 0, -4, -7, 2, -9, -5, 2, -1, -7, 3, -4, -15, 3, -13},
	{-1, 0, 0, -1, 0, -1, -1, 0, -1, -5, 0, -4, -7, 2, -8, -5, 2, -1, -7, 3, -4, -13, 3, -13},
	{-1, 0, 0, -1, 0, -1, -1, 0, -1, -5, 0, -4, -4, 2, -7, -4, 2, -1, -8, 3, -3, -9, 3, -11},
	{-1, 0, 0, -1, 0, -1, -1, 0, -2, -5, 0, -4, -3, 2, -6, -6, 2, -2, -9, 3, -4, -9, 3, -13},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -5, 0, -4, -2, 2, -6, -4, 2, -1, -10, 3, -5, -9, 3, -13},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -4, 0, -4, -4, 2, -7, -6, 2, -2, -10, 3, -5, -9, 4, -15},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -4, 0, -4, -3, 2, -7, -5, 2, -2, -10, 3, -5, -12, 4, -17},
	{0, 0, 0, -1, 0, -2, -2, 0, -1, -4, 0, -4, -3, 2, -7, -6, 1, -3, -9, 3, -6, -12, 4, -19},
	{-1, 0, -1, -1, 0, -1, 0, 0, -1, -4, 0, -4, -4, 2, -7, -5, 1, -2, -11, 3, -8, -15, 5, -21},
	{0, 0, 0, -2, 0, -2, -1, 0, -2, -3, 0, -3, -3, 2, -6, -5, 1, -2, -11, 2, -7, -15, 4, -21},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -3, 0, -4, -2, 2, -5, -7, 1, -2, -8, 2, -7, -16, 4, -22},
	{0, 0, 0, -2, 0, -2, 0, 0, -1, -3, 0, -3, -2, 2, -6, -4, 1, -2, -10, 2, -8, -15, 4, -23},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -2, 0, -3, -2, 2, -6, -6, 1, -2, -11, 2, -6, -15, 4, -21},
	{0, 0, 0, -2, 0, -2, 0, 0, -1, -3, 0, -3, -1, 2, -5, -6, 1, -2, -10, 2, -7, -15, 5, -22},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -1, 0, -2, -3, 2, -5, -5, 1, -2, -6, 2, -5, -14, 5, -19},
	{0, 0, 0, -2, 0, -2, -1, 0, -1, -1, 0, -2, -2, 2, -4, -5, 1, -1, -6, 1, -7, -15, 6, -23},
	{0, 0, 0, -2, 0, -2, 0, 0, 0, -2, 0, -2, -1, 2, -3, -3, 1, 0, -5, 2, -4, -14, 4, -22},
	{0, 0, 0, -2, 0, -2, -1, 0, 0, -2, 0, -1, 0, 2, -4, -3, 1, 1, -4, 2, -3, -12, 4, -19},
	{0, 0, 0, -2, 0, -2, -1, 0, 0, -1, 0, -1, 0, 2, -3, -4, 1, 0, -5, 2, -5, -12, 4, -20},
	{0, 0, 0, -2, 0, -2, -1, 0, 0, -2, 0, -1, 2, 2, -2, -4, 1, 0, -4, 2, -4, -12, 4, -18},
	{0, 0, 0, -2, 0, -2, -1, 0, 0, -1, 0, -1, 1, 2, -2, -3, 1, 1, -4, 1, -4, -11, 4, -16},
	{0, 0, 0, -2, 0, -2, -1, 0, 0, -1, 0, 0, 2, 2, -2, -3, 1, 1, -3, 1, -3, -11, 4, -17},
	{0, 0, 0, 0, 0, -1, -2, 0, -1, -1, 0, 0, 1, 1, -3, -3, 1, 2, -3, 1, -3, -11, 3, -17},
	{0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 0, 0, 2, 1, -3, -3, 1, 2, -1, 1, 0, -11, 3, -17},
	{0, 0, 0, 0, 0, -1, -2, 0, -1, -1, 0, 0, 1, 1, -3, -3, 1, 1, -3, 1, -1, -9, 3, -15},
	{0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -4, -2, 1, 1, -3, 1, -1, -9, 3, -15},
	{1, 0, 1, -1, 0, -1, -1, 0, -1, 0, 0, 0, 1, 1, -2, -2, 1, 1, -5, 1, -1, -9, 3, -15},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 1, 1, -2, -2, 1, 1, -5, 1, -2, -9, 3, -15},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 1, 1, -2, -2, 1, 1, -3, 1, 1, -9, 3, -15},
	{0, 0, 0, -1, 0, -1, 0, 0, -1, -1, 0, 0, 1, 1, -2, -2, 1, 1, -3, 0, 0, -6, 2, -12},
	{0, 0, 0, -1, 0, -1, 1, 0, 0, 0, 0, -1, 0, 1, -2, -1, 1, 0, -5, 0, 0, -7, 2, -13},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, -2, -1, 1, 0, -4, 0, 0, -7, 2, -12},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 1, -2, -1, 1, 0, -4, 0, 0, -7, 2, -11},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 1, -1, 1, -2, 0, 1, 0, -4, 0, 0, -6, 2, -8},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -2, 0, -2, 0, 1, 0, -3, 0, 0, -6, 2, -8},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, 0, -2, 0, 1, 1, -4, 0, -1, -7, 2, -9},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, 0, -2, 1, 1, 1, -3, 0, -1, -7, 2, -9},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 1, 1, 1, -4, 0, -1, -5, 2, -8},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -2, 0, -1, 2, 1, 1, -3, 0, 0, -4, 2, -7},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, -1, 1, 1, 1, -4, 0, 1, -5, 1, -8},
	{0, 0, 0, 0, 0, 0, -1, 0, -1, -1, 0, -1, 0, 0, -1, 2, 1, 2, -3, 0, 0, -4, 1, -6},
	{0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, 0, -2, 3, 1, 2, -2, 0, 1, -2, 1, -5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 2, 0, 0, 0, 0, 3, -2, 0, -3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
#endif