#include "header.h"

using namespace std::chrono;
using namespace std; 

int main(int argc, char ** argv)
{

        
        // 
        // Classic Date and Time
        //

        // Program duration (estimate of how long program has been running)

        clock_t clocks = clock();
        cout << "Program has been running for " << clocks << " clocks." << endl;
        cout << "Which is equivalent to " <<  (double) clocks / CLOCKS_PER_SEC << " seconds with " 
             <<  CLOCKS_PER_SEC << " clocks per second." << endl;

        // Current date and time

        time_t ttime = time(0);
        char * dt = ctime(&ttime);
        cout << "The current local date and time is: " << dt;
        
        tm * gmt_time = gmtime(&ttime);
        dt = asctime(gmt_time);
        cout << "The current UTC date and time is:" << dt;

        // Localtime and parsing it out

        tm *local_time = localtime(&ttime);
    
        cout << "Year: "  << 1900 + local_time->tm_year << endl;        // Year is 1900-based
        cout << "Month: " << 1 + local_time->tm_mon<< endl;             // Month is 0-based
        cout << "Day: "   << local_time->tm_mday << endl;               // Day is 1-based
        cout << "Time: "  << local_time->tm_hour << ":";            // Hour is zero based
                     cout << local_time->tm_min << ":";                    
                     cout << local_time->tm_sec << endl;

        //
        // Durations in C++
        //
       
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
        
        //
        // Integer limits
        //        

        size_t min_int = numeric_limits<int>::min();
        size_t max_int = numeric_limits<int>::max();
        cout << "Int Min: " << min_int << ", Max: " << max_int << endl;

        double min_double = numeric_limits<double>::min();
        double max_double = numeric_limits<double>::min();

        cout << "Double Min: " << min_double << ", Max: " << max_double << endl;

        double min_byte = numeric_limits<uint8_t>::min();
        double max_byte = numeric_limits<uint8_t>::max();

        cout << "Byte Min: " << min_byte << ", Max: " << max_byte << endl;

        // What we can say about type sizes in C:
        //
        // char, signed char, and unsigned char are at least 8 bits
        // signed short, unsigned short, signed int, and unsigned int are at least 16 bits
        // signed long and unsigned long are at least 32 bits
        // signed long long and unsigned long long are at least 64 bits        
        // Sometimes we don't know the actual size, because of the "at least" stuff
        // intmax_t is the largest type that your compiler and lib can deal with

        static_assert(sizeof(intmax_t) >= sizeof(uint64_t));
        intmax_t maxt = 0xdeadbeefbaadf00d;
        printf("num64 as MaxSizeType == %jd\n", maxt);

        // Printing 64 bit quantities properly

        uint64_t num64;
        num64 = 1LLU<<63;
        printf("2^63 == %lu\n", num64);

        num64 = 0xdeadbeefbaadf00d;
        printf("0xdeadbeefbaadf00d == %lx\n", num64);
        printf("0xdeadbeefbaadf00d as signed decimal == %" PRId64 "\n", num64);
        printf("0xdeadbeefbaadf00d as unsigned decimal == %" PRIu64 "\n", num64);
        cout << "num64 streamed to cout == " << num64 << endl;
        
        // __uint128_t num128 = 0;
        // cout << "num128 streamed out == " << num128 << endl;

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
