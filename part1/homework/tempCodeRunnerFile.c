#include<limits.h>
#include<assert.h>
int main(int argc, char const *argv[])
{
    /* code */
    int x = INT_MIN;
    int y = 100;
    
    printf(" %d ---" ,sizeof(int));

    printf("%d --\n", (x == -x)); // 1
    printf("%d --\n", (x < y)); // 1
    printf("%d %d %d %d \n", x, y, -x, -y);
    printf("%d --\n", ((-x) > (-y))); // 1

    // assert(!tsub_ok(0x00, INT_MIN));
    // assert(tsub_ok(0x00, 0x00));
    // printf("%.4x", leftmost_one((unsigned) y));
    // test_show_bytes(a);
    return 0;
}