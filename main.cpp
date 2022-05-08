#include "header.h"

int main(int argc, char ** argv)
{
        // What we can say about type sizes in C:
        //
        // char, signed char, and unsigned char are at least 8 bits
        // signed short, unsigned short, signed int, and unsigned int are at least 16 bits
        // signed long and unsigned long are at least 32 bits
        // signed long long and unsigned long long are at least 64 bits        

        printf("Hello World\n");

        // When we know the variable type size

        int x = 3;
        printf("x = %d\n", x);

        // Sometimes we don't know the actual size, becasue of the "at least" stuff
        // intmax_t is the largest type that your compiler and lib can deal with

        intmax_t maxt = 0xdeadbeef;
        printf("num64 as MaxSizeType == %jd\n", maxt);

        // Printing 64 bit quantities properly

        static_assert(sizeof(intmax_t) >= sizeof(uint64_t));

        uint64_t num64;
        num64 = 1LLU<<63;
        printf("2^63 == %lu\n", num64);

        num64 = 0xdeadbeefbaadf00d;
        printf("0xdeadbeefbaadf00d == %lx\n", num64);
        printf("0xdeadbeefbaadf00d as signed decimal == %" PRId64 "\n", num64);
        printf("0xdeadbeefbaadf00d as unsigned decimal == %" PRIu64 "\n", num64);

        using namespace std;      
        cout << "num64 streamed to cout == " << num64 << endl;
        
        // __uint128_t num128 = 0;
        // cout << "num128 streamed out == " << num128 << endl;
        
        //
        // Durations in C++
        //

        using namespace std::chrono;
        
        time_t result = time(nullptr);
        cout << ctime(&result);
        
        auto t1 = high_resolution_clock::now();
        sleep(1);
        auto t2 = high_resolution_clock::now();

        // floating-point duration: no duration_cast needed

        duration<double, std::milli> fp_ms = t2 - t1;
        
        // Integer duration will need a duration_cast

        duration<uint32_t, std::micro> iMicrosec = duration_cast<microseconds>(t2 - t1);
        
        // Convert to micrososeconds with a duration_cast

        duration<uint32_t, std::micro> cMicrosec = duration_cast<microseconds>(t2 - t1);

        // integral duration: requires duration_cast

        milliseconds int_ms = duration_cast<milliseconds>(t2 - t1);
        
        // Convert duration to different unit

        microseconds dur_usec  = duration_cast<microseconds>(int_ms);
        milliseconds dur_mssec = duration_cast<milliseconds>(int_ms);
        nanoseconds  dur_nsec  = duration_cast<nanoseconds>(int_ms);

        size_t       count_usec  = dur_usec.count();
        size_t       count_mssec = dur_mssec.count();
        size_t       count_nsec  = dur_nsec.count();
        
        std::cout << "Sleeping for one second took " << fp_ms.count() << " ms, " << endl
                  << "or " << count_mssec << " milliseconds" << endl
                  << "or " << count_usec  << " microseconds" << endl 
                  << "or " << count_nsec  << " nanoseconds" << endl;               

        //
        // Clocks
        //

        auto clockOnTheWall = system_clock::now();
        auto monotonicNow   = steady_clock::now();
        auto highResNow     = high_resolution_clock::now();
        
        hh_mm_ss = 
        // Integer limits
        
        int min_int = INT_MIN;
        int max_int = INT_MAX;

        min_int = numeric_limits<int>::min();
        max_int = numeric_limits<int>::max();
        cout << "Min: " << min_int << ", Max: " << max_int << endl;

        // Formatting
        //
        // cmake CMakeLists.txt
        // make -j 64
        // sudo make install
        // use clang++
        // add -lfmt to compiler command line

        using namespace fmt::v8;

        cout << format("Hello");

        return 0;
}
