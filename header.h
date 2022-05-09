#include <stdio.h>
#include <stddef.h>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

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
#include <fmt/format.h>

// If on old C, define __STDC_FORMAT_MACROS before including inttypes.h

#include <inttypes.h>
