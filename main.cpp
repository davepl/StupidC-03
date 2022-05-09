#include "header.h"

using namespace std;
using namespace std::chrono;
using namespace fmt::v8;

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

        // Sometimes we don't know the actual size, because of the "at least" stuff
        // intmax_t is the largest type that your compiler and lib can deal with

        intmax_t maxt = 0xdeadbeef;
        printf("num64 as MaxSizeType == %jd\n", maxt);

        // Printing 64 bit quantities properly

        static_assert(sizeof(intmax_t) >= sizeof(uint64_t), "Expecting at least 64 bits");

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
        
        // Integer limits
        
        size_t min_int = numeric_limits<int>::min();           // New way
        size_t max_int = numeric_limits<int>::max();
        cout << "Min: " << min_int << ", Max: " << max_int << endl;
                
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
        
         
        
        // Formatting
        //
        // cmake CMakeLists.txt
        // make -j 64
        // sudo make install
        // use clang++
        // add -lfmt to compiler command line

        cout << format("Hello");

        return 0;
}
