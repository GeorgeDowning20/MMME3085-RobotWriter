#pragma once

#include "../../lib/rs232.h"
#include "../../lib/serial.h"
#include "../font/fontChar.h"
#include "../misc/error.h"
#include "cursor.h"


#define MAX_X_VALUE_MM 100.0
#define MAX_Y_VALUE_MM 0
#define MIN_X_VALUE_MM 0
#define MIN_Y_VALUE_MM -1000.0

#define HOME_X_VALUE_MM 0.0
#define HOME_Y_VALUE_MM 0.0

#define CHARACTER_SPACE_MM 18.0
#define LINE_SPACE_MM 5.0

#define MINIMUM_TEXT_HEIGHT_MM 4.0
#define MAXIMUM_TEXT_HEIGHT_MM 10.0

#define FONT_FILE "SingleStrokeFont.txt"



errorCode_t StartUpRobot(void);

errorCode_t SendStoke(const cursor_t *const cursor, const stroke_t stroke);

errorCode_t HomeRobot(void);
