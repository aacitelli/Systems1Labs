
#include <stdio.h>

struct exp{
    char name[21];
    short results[10];
    short vcount;
};

long count( struct exp *ptr, long lower, long upper);

int main()
{
        struct exp example = { "at twenty characters",
                { 5, 2, 3, 4, 5, 6, 7, 5, 6, 6 },
                6 };
        long G = count(&example, 4, 7);

        printf("countmain: %ld found.\n", G);
}
