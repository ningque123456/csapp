#include <stdio.h>
#include <string.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len)
{
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}
void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }
void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }
void show_pointer(void *x)
{
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void swap_bits(int *x, int *y)
{
    /**
     * 为什么要使用指针：引用传递
     * Tips：该方式并没有性能优势
     *
     */
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
/**
 * practice 2.11 ：
 * 1.cnt = 2k + 1 时，最后一次循环的l与r分别是什么？ l与r一样，都指向中间的元素。
 * 2.为什么中间元素会是0？
 * 3.如何通过小改动解决该问题？ l <= r  修改为 l < r 即可，长度为奇数时，反转之后中间位置元素不必改变。
 *
 */

void reverse_array(int a[], int cnt)
{
    /**
     * 书中demo，当a[]长度为奇数时，会导致中间的元素值变为0，
     * 当循环中执行最后一次交换时，*x与*y指向同一个元素。
     * 第一行执行完之后，*y = 0 ， 此时由于两者指向同一个元素，所以*y的变化会直接导致*x的变化
     * 导致后续所有操作的*x与*y都是0。
     *
     */
    for (int l = 0, r = cnt - 1; l <= r; l++, r--)
    {
        swap_bits(&a[l], &a[r]);
    }
}
/**
 * practice 2.12：已知x=0x87654321
 * 1.除x最低有效字节，其他均为0.  与0x000000ff 进行 与 运算
 * 2.除x最低有效字节，其他均取补。 与0xffffff00 进行 异或 运算
 * 3.x最低有效字节设置全1，其他保持不变。 与0x876543ff 进行 或 运算
 */
void mask_bits(int *x)
{
    int mask_1 = 0x000000ff;
    int mask_2 = 0xffffff00;
    int mask_3 = 0x876543ff;
    printf(" %x \n", *x & mask_1);
    printf(" %x \n", *x ^ mask_2);
    printf(" %x \n", *x | mask_3);
}
/**
 * practice 2.13 ：
 * 有以下两个指令，接收2个输入x与m，输出一个结果z。
 * bis指令：m为1的位置上，将z设置为1。
 * bic指令：m为1的位置上，将z设置为0。
 * 
 */
/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m);
int bic(int x, int m);
/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y)
{
    int result = bis(x , y);
        ;
    return result;
}
/* Compute x^y using only calls to functions bis and bic */ 
int bool_xor(int x, int y)
{
    int result =  bis(bic(x , y) , bic( x , y));
        ;
    return result;
}
/**
 * practice 2.15：
 * 编写一个只用位运算的函数，实现判断x == y的效果。
 */
int equal_func(int x, int y)
{
    return x ^ y == 0 ;
}

int main(int argc, char const *argv[])
{
    int val = 0x87654321;
    byte_pointer valp = (byte_pointer)&val;
    show_bytes(valp, 1);
    show_bytes(valp, 2);
    show_bytes(valp, 3);
    const char *s = "abcdefg";
    show_bytes((byte_pointer)s, strlen(s));
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4, 5};
    reverse_array(a, 4);
    reverse_array(b, 5);
    for (size_t i = 0; i < 4; i++)
    {
        printf("%d ", a[i]);
    }
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", b[i]);
    }
    int x = 0x87654321;
    mask_bits(&x);

    return 0;
}