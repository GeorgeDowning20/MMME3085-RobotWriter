#pragma once

#include <stdio.h>
#include <stdlib.h>

#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#else
#include <Windows.h>
#define sleep(x) Sleep(x)
#endif

#include "../lib/rs232.h"
#include "../lib/serial.h"

#define bdrate 115200               /* 115200 baud */
