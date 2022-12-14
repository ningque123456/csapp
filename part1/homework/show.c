#include <stdio.h>
#include <assert.h>
#include <limits.h>
typedef unsigned char *byte_pointer;
typedef unsigned packed_t;
typedef unsigned float_bits;

// 2.55 - 2.57
void show_bytes(byte_pointer start, size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%.2x ", start[i]);
    printf("\n");
}
void show_short(short x) { show_bytes((byte_pointer *)&x, sizeof(short)); }
void show_long(long x) { show_bytes((byte_pointer *)&x, sizeof(long)); }
void show_float(float x) { show_bytes((byte_pointer *)&x, sizeof(float)); }
void show_double(double x) { show_bytes((byte_pointer *)&x, sizeof(double)); }

void test_show_bytes(int val)
{
    int ival = val;
    float fval = (float)ival;
    int *pval = &ival;
    show_float(fval);
    show_short((short)ival);
    show_long((long)ival);
    show_double((double)fval);
}
// 2.58 判断机器是大端机器还是小端机器
int is_letter_endian()
{
    // 小端机器返回为1,因为最高位有效字节是01 ，大端机器返回0，因为最高有效位字节是00；
    int test = 0x1;
    byte_pointer byte_start = (byte_pointer)&test;
    return (int)byte_start[0];
}
// 2.59 生成一个字，由x的最低有效字节和y中剩下的字节组成
int mix_two_int(int x, int y)
{
    return (x & 0xff) + (y & 0xffffff00);
}

// 2.60 将x的第i个字节替换成b
unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    unsigned char tb = b;
    unsigned tx = x;
    tx <<= (i * 8);
    // 构造2个掩码，分别处理
    unsigned mask_1 = (unsigned)~(0xff << (i << 3));
    unsigned mask_2 = (unsigned)(b << (i << 3));

    return x & mask_1 | mask_2;
}
// 2.61 x全1 全0 最低有效字节全1 最高有效字节0 时返回1，否则返回0
int func261(int x)
{
    int exp_1 = !~x;
    int exp_2 = !x;
    int exp_3 = !~(x | ~0xff);                           // 构造1111……00000000 ,
    int exp_4 = !((x >> (sizeof(int) - 1) << 3) & 0xff); //  x >> (sizeof(int) - 1) << 3  将最高有效字节移动到最低有效字节位置上
    return 0;
}
// 2.62 实现函数 在对int类型的数使用算数右移的机器上返回1，其他返回0
int int_shifts_are_arithmetic()
{
    // 构造一个全1的二进制数，如-1或~0。
    int t = -1;
    // return t == (t<<1) 最简单的思路，但是要求不能使用==
    return !(t ^ (t << 1)); // 所以采用 异或 来替代==
}
// 2.63 srl函数：算术右移完成逻辑右移 ， sra函数：逻辑右移完成算术右移
unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int)x >> k; // perform shift arithmetically
    int w = sizeof(int) * 8;
    int mask = (int)-1 << (w - k);
    return xsra & (~mask);
}

int sra(int x, int k)
{
    int xsrl = (unsigned)x >> k; // perform shift logically
    int w = sizeof(int) * 8;
    int mask = (int)-1 << (w - k);

    int mask_2 = 1 << (w - 1);
    // 如果x首位为1，要求mask结果不变； 否则 mask需要变为前k位为0.
    mask &= !(x & mask_2) - 1;
    return xsrl | mask;
}
// 2.64 Return 1 when any odd bit of x equals 1 ; 0 otherwise.
int any_odd_one(unsigned x)
{
    return !!(0xaaaaaaaa & x);
}
// 2.65 Return 1 when x contains an odd number if 1s ; 0 otherwise .
// ref: https://stackoverflow.com/questions/21617970
int odd_ones(unsigned x)
{
    /**
     * 32bits太长，我们以8bits举例，假设8bits分别是a b c d e f g h .
     * 由于是8bits，所以跳过step1和step2
     * step3 x ^= (x >> 4) -> x ^ 0 0 0 0 a b c d -> a b c d ae bf cg dh
     * step4 x ^= (x >> 2) -> x ^ 0 0 a b c d ae bf -> a b ac bd ace bdf aceg bdfh
     * 可以发现，经过不断的 XOR + shifts 运算 ，我们把每一位都参与到了 XOR　运算中。
     * 最终计算后变成 a ab abc abcd abcde abcdef abcdefg abcdefgh
     * 当存在偶数个1时，则也存在偶数个0 ，最终abcdefgh XOR 的结果一定为 0 , 否则其结果一定为 1
     *
     *
     */
    x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    return ~(x & 1);
}
// 2.66 Generate mask indicating leftmost 1 in x . (保留最左边的1)
int leftmost_one(unsigned x)
{
    // 个人思路：保留最高位的1，所以不能 << ，因为 << 操作会丢失高位。
    // 设最高位的1为第k位，则经过下列操作后，x结构为[31~k)位为0，[k,0]位为1.
    x |= (x >> 16);
    x |= (x >> 8);
    x |= (x >> 4);
    x |= (x >> 2);
    x |= (x >> 1);
    // 正常情况下 右移1位，加1即可，但考虑到全0情况，所以加 (x&1);
    return (x >> 1) + (x & 1);
}
// 2.67 写一个函数，当在一个int32位的机器上返回1，否则返回0，不允许sizeof
int int_size_is_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 15;
    beyond_msb <<= 15;
    beyond_msb <<= 2;
    return set_msb && !beyond_msb;
}
// 2.68 Mask with least signficant n bits set to 1 (把后n位变成全1)
int lower_one_mask(int n)
{
    int w = sizeof(int) << 3;
    return ~((~0) << n);
}
// 2.69 Do rotating left shift .
unsigned rotate_left(unsigned x, int n)
{
    // 个人思路：x左移n位，同时保留w-n位，用于|计算。
    int w = sizeof(int) << 3;
    // int mask = 0xffffffff << (w - n);
    // int left  = (mask & x) >> (w - n) ;
    // x <<= n;
    // return x | left;

    // 一行版本
    return x << n | ((-1 << (w - n)) & x) >> (w - n);
}
// 2.70 Return 1 when x can be represented as an n-bit, 2's-complement
int fits_bits(int x, int n)
{
    // 看不懂题目，抄
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}
// 2.71 抽取指定的字节，并拓展为一个32位的int
int xbyte(packed_t word, int bytenum)
{
    // old version
    // return (word >> (bytenum << 3)) & 0xff;
    // 问题：当bytenum为负数时，位移操作失败
    int maxnum = 3;
    return (int)word << ((maxnum - bytenum) << 3) >> (maxnum << 3);
}
// 2.72 将整数val复制到缓冲区buf，只有当buf有足够空间时，才执行。
void copy_int(int val, void *buf, int maxbytes)
{
    // if (maxbytes - sizeof(val) >= 0)
    // {
    //     memcpy(buf,(void*) &val, sizeof(val));
    // }
    // 问题：sizeof的返回值类型为size_t，是个unsigned类型，maxbytes - sizeof(val) 本质上
    // 是一个有符号与无符号的运算，最终结果会被转化为无符号，永远大于0.
    // solution：size_t转为int
    if (maxbytes - (int)sizeof(val) >= 0)
    {
        memcpy(buf, (void *)val, sizeof(val));
    }
}
// 2.73 Addition that saturates to Tmin or Tmax
int saturating_add(int x, int y)
{
    int sum = x + y;
    int mask = INT_MIN;
    // 一共会出现2种溢出情况：
    // x正y正，sum负，此时发生正溢出
    // x负y负，sum正，此时发生负溢出
    int pos_over = !(x & mask) && !(y & mask) && (sum & mask);
    int neg_over = (x & mask) && (y & mask) && !(sum & mask);
    // 不能使用if分支，只能通过逻辑运算
    (pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN));
    return sum;
}
// 2.74 Determine whether arguments can be subtracted without overflow (x - y 不溢出则返回1)
int tsub_ok(int x, int y)
{
    // x与y同号则不会overflow，异号时，若sub与x异号则发生overflow
    // 异号： x ^ y & mask != 0 ,
    int mask = INT_MIN;
    int sub = x - y;
    int overflow = (!!(x ^ y & mask)) && (!!(x ^ sub & mask));
    return !overflow;
}
// 2.75 在w位的机器上，计算x*y的高w位
unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int sig_x = x >> 31;
    int sig_y = y >> 31;
    int signed_prod = signed_high_prod(x, y);
    return signed_high_prod + x * sig_y + y * sig_x;
}
int signed_high_prod(int x, int y)
{
    off64_t mul = x * y;
    return mul >> 32;
}
// 2.76 实现calloc库函数，实在不知道不用if - else 怎么写了
void *calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
    {
        return NULL;
    }
    size_t total = nmemb * size;
    // 说明没溢出
    if (nmemb == total / size)
    {
        void *ptr = malloc(total);
        if (ptr != NULL)
        {
            memset(ptr, 0, total);
        }
        return ptr;
    }
    return NULL;
}
// 2.77 使用+ - << 运算，代替乘法
void replce_mul(int x)
{
    // K = 17
    (x << 4) - x;
    // K = -7
    x - (x << 3);
    // K = 60
    (x << 6) - (x << 2);
    // K = -112
    (x << 4) - (x >> 7);
}
// 2.78 Divide by power of 2
int divide_power2(int x, int k)
{
    // 判断符号，正数直接右移k位
    // 负数 需要使用偏置位 x + ( 1 << k ) - 1
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1));
    return x >> k;
}
// 2.79 实现函数mul3div4，计算3*x/4
int mul3div4(int x)
{
    int mul3 = (x << 1) + x;
    int is_neg = x & INT_MIN;
    is_neg && (x = x + (1 << 2) - 1);
    return x >> 2;
}
// 2.80 计算3/4x的值，向零舍入，不允许溢出
int threefourths(int x)
{
    int is_neg = x & INT_MIN;
    int f = x & ~0x3;
    int l = x & 0x3;

    int fd4 = f >> 2;
    int fd4m3 = (fd4 << 1) + fd4;

    int lm3 = (l << 1) + l;
    int bias = (1 << 2) - 1;
    (is_neg && (lm3 += bias));
    int lm3d4 = lm3 >> 2;

    return fd4m3 + lm3d4;
}
// 2.81 使用位运算表示下列数据
// 1^(w-k)*0^k  ->  -1 << k;
// 0^(w-k-j)*1^k*0^j   -> ~(-1 << k) << j
// 2.82 判断以下表达式是否恒为1，否则举出反例
void solution281()
{
    int x = rand();
    int y = rand();
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;
    // (x < y) == (-x > -y)  0 : x = INT_MIN y = 100
    // ((x+y)<<4)+y-x == 17*y+15*x  true
    // ~x + ~y + 1 == ~(x + y)  true
    // (ux - uy) == -(unsigned)(y-x) true
    // ((x>>2) << 2) true
}
// 2.83
/*
    证明
    n = 0.yyyyy
    n << k = yy.yyyyy = Y + n
    n << k - n = Y
    n = Y / (2^k - 1)

*/
// 2.84 补全程序的返回值，该程序测试它的第一个参数是否小于等于第二个参数
int float_le(float x, float y)
{
    unsigned ux = (unsigned)f2u(x);
    unsigned uy = (unsigned)f2u(y);
    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    /* Give an expression using only ux, uy, sx, and sy */
    return (ux << 1 == 0 && uy << 1 == 0) || /* both zeros */
           (sx && !sy) ||                    /* x < 0, y >= 0 or x <= 0, y > 0 */
           (!sx && !sy && ux <= uy) ||       /* x > 0, y >= 0 or x >= 0, y > 0 */
           (sx && sy && ux >= uy);           /* x < 0, y <= 0 or x <= 0, y < 0 */
}
// 2.85
// Given a floating-point format with a k-bit exponent and an n-bit fraction, write
// formulas for the exponent E, the significand M, the fraction f , and the value V
// for the quantities that follow. In addition, describe the bit representation.
// A. The number 7.0
// B. The largest odd integer that can be represented exactly
// C. The reciprocal of the smallest positive normalized value
// ------------------------------------------------------------------------
// bias = 2^(k-1) - 1 , float -> k = 8 , bias = 127
// E = e - bias , V = (-1)^s * M * 2^E
// 7.0 -> 111.000000 . M = 1.11 , f = 0.11 , E = 2(11) , e = 129 ,
// 最大的偶数，则M = 1.11111…… . f = 0.11111…… , E = n , bits:0 bias+n 11111

// 2.90 补全代码 计算2^x
float fpwr2(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    // E = 1 - bias = 1 - 127 = -126 ; n = 23
    if (x < -149)
    {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    }
    else if (x < -126)
    {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (unsigned)(x - 126);
    }
    else if (x < 128)
    {
        /* Normalized result. */
        exp = x + 127;
        frac = 0;
    }
    else
    {
        /* Too big. Return +oo */
        exp = 0xff;
        frac = 0;
    }
    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
// 2.92 实现函数，对于浮点数f，计算-f，如果f=NaN，则简单的返回f
float_bits float_negate(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    int is_nan = (exp == 0xff) && (frac != 0);
    if (is_nan)
    {
        return f;
    }
    return (~sign << 31) | (exp << 23) | frac;
}
// 2.93 实现函数，对于浮点数f，计算|f|，如果f=NaN，则简单的返回f
float_bits float_absval(float_bits f)
{
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_nan = (exp == 0xFF) && (frac != 0);
    if (is_nan)
    {
        return f;
    }
    return (0 << 31) | exp << 23 | frac;
}
// 2.93 实现函数，对于浮点数f，计算2.0*f，如果f=NaN，则简单的返回f
float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    int is_nan_oo = (exp == 0xff);
    if (is_nan_oo)
    {
        return f;
    }
    // Denormalized
    if (exp == 0)
    {
        // 非规格化的情况，不能改阶码，所以需要将f整体左移。
        return f << 1;
    }
    else if (exp == 0xff - 1)
    {
        // 无穷大的情况，翻倍还是无穷大
        exp = 0xff;
        frac = 0;
    }
    else
    {
        // Normalized 规格化的情况，只需要修改 阶码 即可。
        exp += 1;
    }
    return sign << 31 | exp << 23 | frac;
}
// 2.93 实现函数，对于浮点数f，计算0.5*f，如果f=NaN，则简单的返回f
float_bits float_half(float_bits f)
{
    unsigned sig = f >> 31;
    unsigned rest = f & 0x7FFFFFFF;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NAN_or_oo = (exp == 0xFF);
    if (is_NAN_or_oo)
    {
        return f;
    }

    /*
     * round to even, we care about last 2 bits of frac
     *
     * 00 => 0 just >>1
     * 01 => 0 (round to even) just >>1
     * 10 => 1 just >>1
     * 11 => 1 + 1 (round to even) just >>1 and plus 1
     */
    int addition = (frac & 0x3) == 0x3;

    if (exp == 0)
    {
        /* Denormalized */
        frac >>= 1;
        frac += addition;
    }
    else if (exp == 1)
    {
        /* Normalized to denormalized */
        rest >>= 1;
        rest += addition;
        exp = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
    }
    else
    {
        /* Normalized */
        exp -= 1;
    }

    return sign << 31 | exp << 23 | frac;
}
int main(int argc, char const *argv[])
{
    /* code */
    int a = 328;
    int x = INT_MIN;
    int y = 100;
    printf("%d --\n", (x < y));
    printf("%d %d %d %d \n", x, y, -x, -y);
    printf("%d --\n", (-x > -y));
    int z = mix_two_int(x, y);
    assert((x < y) == (-x > -y));
    // assert(!tsub_ok(0x00, INT_MIN));
    // assert(tsub_ok(0x00, 0x00));
    // printf("%.4x", leftmost_one((unsigned) y));
    // test_show_bytes(a);
    return 0;
}
