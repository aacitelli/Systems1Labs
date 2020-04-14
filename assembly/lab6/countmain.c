
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
                {1, 2, 3, 4, 5, 6, 5, 4, 0, 4 },
                8 };
        long G = count(&example, 3, 5);

        printf("countmain: %ld found.\n", G);
}
