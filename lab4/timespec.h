/* since gcc screws this up, include this file
* to use nanosleep.  Be sure to include <time.h>
*/
struct timespec {
        time_t   tv_sec;        /* seconds */
        long     tv_nsec;       /* nanoseconds */
};
