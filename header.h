#pragma once

#ifdef _WIN32
  #define NOMINMAX 1
  #define _CRT_SECURE_NO_DEPRECATE 1
  #include <Windows.h>
  #include <corecrt_math_defines.h>
  #include <format>
#else
  #include <unistd.h>
  #include <fmt/format.h>
#endif

#include <stdio.h>
#include <stddef.h>

#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <limits>
#include <thread>

#include <limits.h>
#include <math.h>

// If on old C, define __STDC_FORMAT_MACROS before including inttypes.h

#include <inttypes.h>
