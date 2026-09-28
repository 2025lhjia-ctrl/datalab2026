/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int x_sign=x>>31;
    int y_sign=y>>31;
    if(!x&&!y){
        return 1;
    }
    if(x_sign&&y_sign){
        return 1;
    }
    if((x&&y)&&(!x_sign&&!y_sign)){
        return 1;
    }
    return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result=0;
    int check;
    check=(v>65535);
    v=v>>(check<<4);
    result=result|(check<<4);
    check=(v>255);
    v=v>>(check<<3);
    result=result|(check<<3);
    check=(v>15);
    v=v>>(check<<2);
    result=result|(check<<2);
    check=(v>3);
    v=v>>(check<<1);
    result=result|(check<<1);
    check=(v>1);
    v=v>>(check);
    result=result|(check);
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns=n<<3;
    int ms=m<<3;
    int n_byte=(x>>ns)&0xFF;
    int m_byte=(x>>ms)&0xFF;
    int mask=~((0xFF<<ns)|(0xFF<<ms));
    x=x&mask;
    x|=(n_byte<<ms)|(m_byte<<ns);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r=0;
    int i;
    for(i=32;i;i=i-1){
        r=(r<<1)|(v&1);
        v=v>>1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x=x>>n;
    int mask=~(((1<<31)>>n)<<1);
    x=x&mask;
    return x;
}

/*
 * leftBitCount - returns count of number of consecutive 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int inv=~x;
    int r=0;
    int b;
    
    b=!(inv>>16);
    r=r+(b<<4);
    inv=inv<<(b<<4);

    b=!(inv>>24);
    r=r+(b<<3);
    inv=inv<<(b<<3);

    b=!(inv>>28);
    r=r+(b<<2);
    inv=inv<<(b<<2);

    b=!(inv>>30);
    r=r+(b<<1);
    inv=inv<<(b<<1);

    b=!(inv>>31);
    r=r+b;

    return r+!inv;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign=0;
    unsigned ux=x;
    unsigned E,frac,g;

    if(x==0)return 0;
    if(x<0){
        sign=0x80000000;
        ux=~ux+1;
    }
    
    E=31;
    while(!(ux&0x80000000)){
        ux=ux<<1;
        E=E-1;
    }
    frac=(ux>>8)&0x7FFFFF;
    g=ux&0xFF;

    if(g>0x80){
        frac=frac+1;
    }else if(g==0x80){
        if(frac&1)frac=frac+1;
    }
    if(frac==0x800000){
        frac=0;
        E=E+1;
    }
    return sign|((E+127)<<23)|frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign=uf&0x80000000;
    unsigned exp=(uf>>23)&0xFF;
    if(exp==255){
        return uf;
    }
    if(exp==0){
        return sign|((uf<<1)&0x7FFFFFFF);
    }
    if(exp==254){
        return sign|0x7F800000;
    }
    return uf+(1<<23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s=uf2>>31;
    unsigned e=(uf2>>20)&0x7FF;
    int E=e-1023;
    unsigned top21=(uf2&0xFFFFF)|0x100000;
    unsigned result;

    if(e>=0x7FF) return 0x80000000;
    if(E<0) return 0;
    if(E>30) return 0x80000000;

    if(E<=20){
        result=top21>>(20-E);
    }
    else{
        result = (top21 << (E - 20)) | (uf1 >> (52 - E));
    }
    if (s) return ~result + 1;
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127){
        return 0xFF<<23;
    }
    if(x>=-126){
        return (x+127)<<23;
    }
    if(x>=-149){
        return 1<<(x+149);
    }
    return 0;
}
