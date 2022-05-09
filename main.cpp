#include "header.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char ** argv)
{
        // 
        // Classic Date and Time
        //

        clock_t clocks = clock();
        cout << "Program has been running for " << clocks << " clocks." << endl;
        cout << "That is equivalent to " <<  (double) clocks / CLOCKS_PER_SEC << " seconds with " 
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
        // Basic time/date stuff in C++
        //
        
        using day_t = duration<long, std::ratio<3600 * 24>>;
        auto start  = system_clock::now();
        std::this_thread::sleep_for(seconds(1));
        auto end = system_clock::now();
        auto dur = end - start;
        auto d = duration_cast<day_t>(dur);
        auto h = duration_cast<hours>(dur -= d);
        auto m = duration_cast<minutes>(dur -= h);
        auto s = duration_cast<seconds>(dur -= m);
        auto ms = duration_cast<seconds>(dur -= s);
        std::cout << d.count() << " days, "
                << h.count() << " hours, "
                << m.count() << " minutes, "
                << s.count() << " seconds, "
                << ms.count() << " milliseconds\n";

        //
        // Durations in C++
        //
       
        time_t result = time(nullptr);
        cout << ctime(&result);
        
        auto t1 = high_resolution_clock::now();
        this_thread::sleep_for(seconds(1));
        auto t2 = high_resolution_clock::now();

        //cout << format("%D", t2) << endl;

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
        
        // Get the the number of milliseconds elapsed since the epoch until now
        
        auto msclockOnTheWall = time_point_cast<milliseconds>(system_clock::now());        
        auto millis_since_utc_epoch = msclockOnTheWall.time_since_epoch();
                
        // Year, Month, Day types
        
        constexpr year  thisYear(2022);
        constexpr month thisMonth(May);
        constexpr day   thisDay(8);
        
        //cout << "Year: " << thisYear << " , Month: " << thisMonth << ", Day: " << thisDay << " isLeap: " << std::noboolalpha << thisYear.is_leap() << endl;
        
        static_assert(thisYear == 2022y);
        
        year_month thisYearMonth(thisYear, thisMonth);        
        year_month_day today(thisYear, thisMonth, thisDay);
        
        constexpr year_month_day_last lastDayOfThisMonthV1 =  2022y / May / last;
        constexpr year_month_day_last lastDayOfThisMonthV2 =  last / May / 2022y;        
        constexpr year_month_day_last lastDayOfThisMonthV3 =  May / last / 2022y;
        
        static_assert(lastDayOfThisMonthV1 == lastDayOfThisMonthV2 and lastDayOfThisMonthV2 == lastDayOfThisMonthV3);
        
        const year_month_day ymd { floor<days>(system_clock::now()) };
        
        //
        // Integer limits
        //        

        size_t min_int = numeric_limits<int>::min();
        size_t max_int = numeric_limits<int>::max();
        cout << "Int Min: " << min_int << ", Max: " << max_int << endl;

        double min_double = numeric_limits<double>::min();
        double max_double = numeric_limits<double>::min();

        cout << "Double Min: " << min_double << ", Max: " << max_double << endl;

        size_t min_byte = numeric_limits<uint8_t>::min();
        size_t max_byte = numeric_limits<uint8_t>::max();

        cout << "Byte Min: " << min_byte << ", Max: " << max_byte << endl;

        // What we can say about type sizes in C:
        //
        // char, signed char, and unsigned char are at least 8 bits
        
        static_assert(sizeof(char) >= 1);
        static_assert(sizeof(char) == sizeof(signed char) and sizeof(signed char) == sizeof(unsigned char));
        
        // signed short, unsigned short, signed int, and unsigned int are at least 16 bits
                
        static_assert(sizeof(short) >= 2);
        static_assert(sizeof(short) == sizeof(signed short) and sizeof(signed short) == sizeof(unsigned short));
                
        // signed long and unsigned long are at least 32 bits
        
        static_assert(sizeof(long) >= 4);
        static_assert(sizeof(long) == sizeof(signed long) and sizeof(signed long) == sizeof(unsigned long));
        
        // signed long long and unsigned long long are at least 64 bits        

        static_assert(sizeof(long long) >= 8);
        static_assert(sizeof(long long) == sizeof(signed long long) and sizeof(signed long long) == sizeof(unsigned long long));

        // Sometimes we don't know the actual size, because of the "at least" stuff
        // intmax_t is the largest type that your compiler and lib can deal with                
        
        static_assert(sizeof(intmax_t) >= sizeof(uint64_t));
        
        intmax_t maxt = 0xdeadbeefbaadf00d;
        printf("num64 as MaxSizeType == %jd\n", maxt);

        // Printing 64 bit quantities properly

        uint64_t num64;
        num64 = 1LLU<<63;
        printf("2^63 == %llu\n", num64);
        cout << "2^63 == " << num64 << endl;
        
        num64 = 0xdeadbeefbaadf00d;
        printf("0xdeadbeefbaadf00d == %llx\n", num64);
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
        cout << format("Hello") << endl;

        // Printing arguments out of order:
        
        // Should print: "a, b, c"
        cout << format("{}, {}, {}", 'a', 'b', 'c') << endl;
        
        // Should print: "c, b, a"
        cout << format("{2}, {1}, {0}", 'a', 'b', 'c') << endl;

        // Dyamic and static Width
        cout << format("{:<{}}", "left aligned", 30)  << endl;          // Width as argument
        cout << format("{:>30}", "right aligned") << endl;              // Width in format 
        
        // Dyanmic and static precision
        
        cout << format("{:.{}f}", 3.14159265, 3) << endl;
        cout << format("{:.3f}", 3.14159265) << endl;

        // Handling the sign
        
        // Expect: "+3.140000; -3.140000"
        cout << format("{:+f}; {:+f}", 3.14, -3.14) << endl;  // show it always

        // Expect: " 3.140000; -3.140000"
        cout << format("{: f}; {: f}", 3.14, -3.14) << endl;  // show a space for positive numbers

        // Expect: "3.140000; -3.140000"
        cout << format("{:-f}; {:-f}", 3.14, -3.14) << endl;  // show only the minus -- same as '{:f}; {:f}'
        
        // Converting to different number bases

        // Expect: "int: 42;  hex: 2a;  oct: 52; bin: 101010"
        // with 0x or 0 or 0b as prefix:
                
        cout << format("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42) << endl;

        // Expect: "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010"fmt::format("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        // Expect: "int: 42;  hex: 2a;  oct: 52; bin: 101010"
        // with 0x or 0 or 0b as prefix:

        cout << format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42) << endl;

        // Expect: "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010"

        cout << format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42) << endl;
        
        return 0;
}
