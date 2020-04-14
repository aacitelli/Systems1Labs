/* lab 6 main - supplied code */
#include <stdio.h>

struct exp{
    char name[21];
    short results[10];
    short vcount;
};

/* OK, bad naming here.  These are actual structs */
struct exp A1 = { "at twenty characters", {1, 2, 3, 4, 5, 6, 5, 4, 0, 4 }, 8 };
char *junk1 = "Go Bucks!";
struct exp A2 = { "Test One", {1, 2, 3, 4, 5, 6, 5, 4, 0, 4 }, 10 };
char *junk2 = "Random stuff goes here.";
struct exp A3 = { "Run 2", {1, 2, 3, 4, 5, 6, 5, 4, 0, 4 }, 3 };
char *junk3 = "";
struct exp A4 = { "Run 3", {1, 2, 3, 4, 5, 6, 5, 4, 0, 4 }, 9 };
char *junk4 = "A really, really, really long string to move things.";
struct exp A5 = { "Neg 1", {-1, -2, -3, 0, 1, 2, 3, 4, 5, -4 }, 10 };

/* bad naming - it's an array of pointers, not of structs */
struct exp *structs[] = { &A1, &A2, &A3, &A4, &A5, NULL};

struct exp *search(struct exp *structs[], long scount, long lower, long upper);

main()
{
        struct exp *ptr;
        long lower = 3, upper = 5;
        long cnt = sizeof(structs) / sizeof(structs[0]) -1;


        lower = 3;
        upper = 5;
        ptr = search(structs, cnt, lower, upper);
printf("Lab6: '%s' has the most between %ld and %ld\n\n", ptr->name, lower, upper);

        lower = -2;
        upper = 2;
        ptr = search(structs, cnt, lower, upper);
printf("Lab6: '%s' has the most between %ld and %ld\n\n", ptr->name, lower, upper);

}





