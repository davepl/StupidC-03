#include <stdio.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

// If on old C, define __STDC_FORMAT_MACROS before including inttypes.h

#include <inttypes.h>



int main(int argc, char ** argv)
{

        printf("Hello World\n");

        intmax_t maxt = 0xdeadbeef;
        printf("num64 as MaxSizeType == %jd\n", maxt);
                
        uint64_t num64;
        
        num64 = 1LLU<<63;
        printf("2^63 == %llu\n", num64);

        num64 = 0xdeadbeefbaadf00d;
        printf("num64 == %llx\n", num64);

        printf("num64 as signed == %" PRId64 "\n", num64);

        printf("num64 as unsigned == %" PRIu64 "\n", num64);

        using namespace std;
                        
        cout << "num64 streamed out == " << num64 << endl;
        
        // __uint128_t num128 = 0;
        // cout << "num128 streamed out == " << num128 << endl;
        
        using namespace std::chrono;
        
        time_t result = time(nullptr);
        cout << ctime(&result);
        
        auto t1 = std::chrono::high_resolution_clock::now();
        sleep(1);
        auto t2 = std::chrono::high_resolution_clock::now();

        // floating-point duration: no duration_cast needed
        std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

        // integral duration: requires duration_cast
        auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        // converting integral duration to integral duration of shorter divisible time unit:
        // no duration_cast needed
        
        std::chrono::duration<long, std::micro> int_usec = int_ms;

        std::cout << "sleepine one seconds took " << fp_ms.count() << " ms, "
                  << "or " << int_ms.count() << " whole milliseconds "
                  << "(which is " << int_usec.count() << " whole microseconds)" << std::endl;
                  
        return 0;
}
