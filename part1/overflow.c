#include<stdio.h>
#include<limits.h>
#include<string.h>

/**
 * practice 2.25：
 * 一个存在bug的数组求和代码，当length为0时，会爆出内存错误。
 * 原因：lengt是unsigned类型，length = 0 时，执行 length - 1会突破unsigned int的下界。
 * 此时length变成4294967295，循环次数过多，导致内存溢出。
 * 修改：i <= length - 1 修改为 i < length 
*/
float sum_elements(float a[] , unsigned length)
{
    int i = 0;
    float result = 0;
    for (int i = 0; i <= length - 1; i++)
    {
        result += a[i];
    }
    return result;
    
}
/**
 * practice 2.26：
 * 一个判断两个字符串哪个更长的函数，存在bug，解释原因并修改。
 * A：什么情况下会报错？ 串s长度小于t时。
 * B：为什么会报错？ strlen函数返回值为unsigned类型，无符号与有符号在计算时被默认转化为无符号，出现正数。
 * C：如何修改？ return strlen(s) > strlen(t)
 * 
 */
int str_longer(char *s,char *t){
    return strlen(s) - strlen(t) > 0;
}
/**
 * practice 2.27：
 * 写一个函数判断无符号整数相加是否发生溢出：
 * 不溢出的情况，两正数之和一定大于其中任意一个数，
 * 溢出之后， 结果为INT_MAX - (x + y)， 值一定小于x 
 *  
 */
int uadd_ok(unsigned x, unsigned y){
    return x + y < x;
}
/**
 * practtice 2.30 
 * 写一个函数判断有符号整数相加是否发生溢出：
 * 若溢出： 正数相加为负， 负数相加为正。
 * 异号相加不可能溢出。
 * 
 */
int tadd_ok(unsigned x, unsigned y){
    int sum = x + y;
    if( x >= 0 && y >= 0){
        return sum < 0 ;
    }
    if( x < 0 && y < 0)
    {
        return sum >= 0;  
    }
    return 0 ;
    
}
/* 答案版本 */
int tadd_ok(unsigned x, unsigned y){
    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x >= 0 && y>= 0 && sum < 0;
    return !neg_over && !pos_over;
}
/**
 * practice 2.32：
 * 以下代码当y取何值时会出现bug？ 
 *  y取INT_MIN时，-y也等于INT_MIN，此时调用tadd_ok，若x为正数，则还会溢出。
 */
int tsub_ok(int x, int y){
    return tadd_ok(x,-y);
}
/* 正确版本 */
int tsub_ok(int x, int y){
    if ( x == INT_MIN || y == INT_MIN)
    {
        /* code */
        
    }
    
}
/**
 * practice 2.35：
 * 证明tmult_ok函数的逻辑正确性：
 * 1. x=0时，返回0，不会溢出，结果正确。
 * 2. 由于x与y都是w位2进制，两者乘积最大需要2w位二进制来表示，设p为x与y补码乘法的结果，则p最大为w位，
 *    想达到2w位，只需要再加上2^w即可。
 *    即 x * y = p + t2^w
 * 3. 无论x*y的值p是否发生溢出，最终结果一定是个整数，一个整数一定能表示为 乘数 * 乘数 + 余数 的形式，
 *    即 p = x * q + r 
 * 4. 显然，当且仅当 r = t = 0 是， q = y 成立。
 */
int tmult_ok(int x, int y){
    int p = x * y;
    return !x || p/x == y;
}
/**
 * practice 2.36：
 * 对于32位的数据，使用64位精度的方式实现2.35的函数，从而不使用除法。
 */
int tmult_ok(int x, int y){
    // 将乘积转化位64位整数，返回时进行截断，并比较
    // 如果不等，说明在高位[w , 2w]上存在数据，且被截断。
    // 如果相等，则未发生溢出。
    int64_t p = (int64_t)x * y;
    return p == (int) p;

}
/**
 * practice 2.42：
 * 实现函数div16，传入x，返回x/16的值，不能使用基本运算符
 */
int div16(int x){
    // 由于不能使用基本运算符，所以不能直接判断x的正负性
    // 因为x默认32位，可以通过右移31位的方式，判断出首位是0或1.
    // 首位被设置为“偏置”biasing即可。
    int bias = x >> 31 & 0xff;
    return (x + bias )>>4;
}
int main(int argc, char const *argv[])
{
    int x = 5 ;
    int y = 5 * 8;
    int z = x << 3;
    printf( " %d",y);
    printf( " %d",z);
    return 0;
}
