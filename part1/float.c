#include<stdio.h>
#include<math.h>
#include<fp2bin.h>
const int MAX_LEN = 10;
/**
 * @brief 浮点数的二进制表示
 * 
 * @param dec 整数部分 
 * @param decp 小数部分
 * @param ans 转换后的字符串地址
 */
void float2blob(long dec , float decp , char* bin_dec, char* bin_decp ){
    // 先将整数部分正常转化
    long s = dec ;
    int rem = 0;
    int p = 0;
    char ans_dec[65];
    while (s > 0)
    {
        rem = s % 2 ;
        // rem = ( s & 0x01);
        ans_dec[p++] = rem + '0';
        s /= 2; 
        // s <<= 1;
    }
    p--;
    int pp = 0;
    while ( p > 0)
    {
        bin_dec[pp++] = ans_dec[p--];
    }
    // 小数部分转化 ， 乘2取整并设置最大长度。
    pp = 0;
    int cur_len = 0;
    float ss = decp;
    int qz = 0; //取整的结果
    while ( ss > 0 )
    {
        qz = (int) (ss * 2);
        bin_decp[pp++] = qz + '0';
        ss *= 2 ;
        if (ss >= 1)
        {
            ss -= 1;
        }

        if (cur_len == MAX_LEN) break;
    }
    // 防止出现安全问题，在指针最后设置一个终止符。
    bin_decp[pp] = '\0';
    
}

/**
 * @brief 比较官方的写法
 * 
 */
void fp2bin_i(double fp_int , char* binString){
    int bitCount = 0 ;
    int i ;
    char binString_tmp[FP2BIN_STRING_MAX];
    do
    {
        binString_tmp[bitCount++] = (int)fmod(fp_int , 2) + '0';
        fp_int = floor(fp_int / 2);
    } while (fp_int > 0);
    // 逆序赋值
    for ( i = 0; i < bitCount; i++)
    {
        binString[i] = binString_tmp[bitCount - i - 1];
    }
    binString[bitCount] = 0;
    
}

void fp2bin_f(double fp_frac, char* binString){
    int bitCount = 0;
    double fp_int;
    while (fp_frac > 0)
    {
        fp_frac *= 2;
        // modf函数，取fp_frac的整数部分，赋值给fp_int指向的内存
        fp_frac = modf(fp_frac , &fp_int);
        binString[bitCount++] = (int)fp_int + '0';        
    }
    binString[bitCount] = 0;

}

void fp2bin(double fp , char* binString){
double fp_int, fp_frac;

 // 拆分整数与小数部分
 fp_frac = modf(fp,&fp_int);

 
 if (fp_int != 0)
   fp2bin_i(fp_int,binString);
 else
   strcpy(binString,"0");

 strcat(binString,"."); // Radix point

 if (fp_frac != 0)
   fp2bin_f(fp_frac,binString+strlen(binString)); //Append
 else
   strcpy(binString+strlen(binString),"0");
}


int main(int argc, char const *argv[])
{
    /* code */
    float f = 123.25f;
    float f2 = 123.2f;
    char s1[101] , s2[101];
    float2blob((long)f2 , f2 - (long)f ,s1 ,s2 );
    printf( " %s.%s",s1,s2);
    return 0;
}
