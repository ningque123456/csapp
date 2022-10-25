#include<stdio.h>
typedef unsigned char *byte_pointer;
// 2.55 - 2.57
void show_bytes(byte_pointer start , size_t length){
    for (size_t i = 0; i < length; i++)
        printf("%.2x ",start[i]);
    printf("\n");
}
void show_short(short x ){ show_bytes((byte_pointer* ) &x , sizeof(short) ); }
void show_long(long x){ show_bytes((byte_pointer* ) &x , sizeof(long)); }
void show_float(float x){ show_bytes((byte_pointer* ) &x , sizeof(float)); }
void show_double(double x){ show_bytes((byte_pointer* ) &x , sizeof(double)); }

void test_show_bytes(int val){
    int ival = val;
    float fval = (float) ival;
    int* pval = &ival;
    show_float(fval);
    show_short((short)ival);
    show_long((long)ival);
    show_double((double)fval);
    
}
// 2.58 判断机器是大端机器还是小端机器
int is_letter_endian(){
    // 小端机器返回为1,因为最高位有效字节是01 ，大端机器返回0，因为最高有效位字节是00；
    int test = 0x1;
    byte_pointer byte_start = (byte_pointer) &test;
    return (int)byte_start[0];
}
// 2.59 生成一个字，由x的最低有效字节和y中剩下的字节组成
int mix_two_int(int x , int y){
    return (x & 0xff) + (y & 0xffffff00);
}

// 2.60 将x的第i个字节替换成b
unsigned replace_byte(unsigned x , int i , unsigned char b){
    unsigned char tb = b;
    unsigned tx = x;
    tx <<= (i*8);   
    // 构造2个掩码，分别处理
    unsigned mask_1 = (unsigned) ~(0xff << (i << 3));
    unsigned mask_2 = (unsigned) (b << (i << 3));

    return x & mask_1 | mask_2;


}
// 2.61 x全1 全0 最低有效字节全1 最高有效字节0 时返回1，否则返回0 
int func261(int x){
    int exp_1 = !~x;
    int exp_2 = !x;
    int exp_3 = !~(x | ~0xff); // 构造1111……00000000 , 
    int exp_4 =  !(( x >> (sizeof(int) - 1) << 3 ) & 0xff); //  x >> (sizeof(int) - 1) << 3  将最高有效字节移动到最低有效字节位置上
    return x & mask_1 || x & mask_2 || 
}
// 2.62 实现函数 在对int类型的数使用算数右移的机器上返回1，其他返回0
int int_shifts_are_arithmetic(){
    // 构造一个全1的二进制数，如-1或~0。
    int t = -1;
    // return t == (t<<1) 最简单的思路，但是要求不能使用==
    return  ! (t ^ (t << 1)); // 所以采用 异或 来替代==
}

int main(int argc, char const *argv[])
{
    /* code */
    int a = 328;
    int x = 0x89ABCDEF;
    int y = 0x76543210;
    int z = mix_two_int(x , y);
    printf("%.8x", replace_byte(0x12345678,0,0xab));
    // test_show_bytes(a);
    return 0;
}
