#pragma once

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_MIN_X 0
#define SCREEN_MIN_Y 0
#define SCREEN_MAX_X 319
#define SCREEN_MAX_Y 239

#define BG_COLOR TFT_BLACK
#define LINE_COLOR TFT_LIGHTGREY
#define METER_BG_COLOR TFT_BLACK
#define SPEED_BG_COLOR TFT_BLACK
#define STEERING_COLOR (0x6bf1 >> 1 & 0xfbef)
#define ACCEL_COLOR (0x0397 >> 1 & 0xfbef)
#define BRAKE_COLOR (0xcacb >> 1 & 0xfbef)
#define RPM_COLOR (TFT_DARKGREY >> 1 & 0xfbef)

#define METER_HEIGHT 15
#define METER_SPACE 3
#define LINE_WIDTH 1
#define RPM_ORIGIN_X 0
#define RPM_ORIGIN_Y 0

#define STEERING_ORIGIN_X 159
#define STEERING_ORIGIN_Y (RPM_ORIGIN_Y + METER_HEIGHT + 25)
// #define STEERING_R 320
#define STEERING_R (320 / 2 * sqrt(3))
#define STEERING_WIDTH 30

#define BRAKE_ORIGIN_X 0
#define BRAKE_ORIGIN_Y (SCREEN_MAX_Y - METER_HEIGHT)
#define ACCEL_ORIGIN_X (159 - (int)(LINE_WIDTH / 2))
#define ACCEL_ORIGIN_Y (SCREEN_MAX_Y - METER_HEIGHT)

#define UNIT_FONT &fonts::Font2
#define UNIT_FONT_COLOR LINE_COLOR
#define UNIT_FONT_SIZE 1.0

#define SPEED_FONT &fonts::Font7
#define SPEED_FONT_COLOR (TFT_GREEN >> 1 & 0xfbef)
#define SPEED_FONT_SIZE 0.75

#define SHIFT_FONT &lgfxJapanGothicP_40
#define SHIFT_FONT_COLOR (TFT_LIGHTGREY >> 1 & 0xfbef)
#define SHIFT_FONT_SIZE 1.5
#define SHIFT_N_COLOR    (TFT_GREEN >> 1 & 0xfbef)
#define SHIFT_C_COLOR    (TFT_ORANGE >> 1 & 0xfbef)
