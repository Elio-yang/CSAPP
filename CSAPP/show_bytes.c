#include<stdio.h>
#include<string.h>
#include<limits.h>


//each time the pointer with type unsigned char* will move 1 Byte.
typedef unsigned char *byte_pointer;

typedef long long int64_t;

void show_bytes(byte_pointer star, size_t len);

void show_int(int x);

void show_float(float x);

void show_pointer(void *x);

void fun1(unsigned w);

void fun2(unsigned w);

int bool_xor(int x, int y);

int uadd_ok(unsigned x, unsigned y);

int tadd_ok(int x, int y);

int tsub_ok(int x, int y);

int tmult_ok(int x, int y);

int tmult_ok_2(int x, int y);

int div_16(int x);

int main() {
	int ival = 12345;
	float fval = (float)ival;
	int *pval = &ival;
	show_int(ival);
	show_float(fval);
	show_pointer(pval);
	putchar('\n');
/*
	output 1:
	39 30 00 00
	00 e4 40 46
	58 4a b8 c5 ff 7f 00 00

	for number 12345 the hex is 0x3039
	in this system,the lower address has
	the lowest-effective-bit 39, so this
	machine is a little endian.
*/
	int val = 0x87654321;
	byte_pointer valp = (byte_pointer)&val;
	show_bytes(valp, 1);
	show_bytes(valp, 2);
	show_bytes(valp, 3);
	show_bytes(valp, sizeof(int));
	int i;
	for (i = 0; i < 4; i++) {
		printf("%.2x ", valp [i]);
	}
	printf("%.2d %c signed val=%d  unsigned val=%u", *valp, *valp, val, val);
	//valp has cast to unsigned char*
	//so *valp=the first memory cell which placed 0x21=33(dec)='!'
	putchar('\n');
/*
	output2:
	21
	21 43
	21 43 65
	21 43 65 87
	21 43 65 87 33 ! signed val=-2023406815  unsigned val=2271560481

	val=0x87654321
	when size_t len=1 output 1 byte when in little endian
	the byte is lowest_effective-bit 21
*/
	const char *s = "abcdef";
	show_bytes((byte_pointer)s, strlen(s));
	const char *s_2 = "abcdef";
	show_bytes((byte_pointer)s_2, 7);
	putchar('\n');
/*
	output3:
	61 62 63 64 65 66
	61 62 63 64 65 66 00
 */


	short x = 12345;
	short mx = -x;
	short mx_2 = -12345;
	show_bytes((byte_pointer)&x, sizeof(short));
	show_bytes((byte_pointer)&mx, sizeof(short));
	show_bytes((byte_pointer)&mx_2, sizeof(short));
	putchar('\n');
/*
	output4:
	39 30
	c7 cf
	c7 cf

	this is an little endian machine
	12345=30 39(hex)
	the two's complement of -12345 is 1100 1111 1100 0111(cf c7 hex)


*/
	int x2 = 12345;
	int mx2 = -x2;
	show_bytes((byte_pointer)&x2, sizeof(int));
	show_bytes((byte_pointer)&mx2, sizeof(int));
	putchar('\n');
/*
	output5:
	39 30 00 00
	c7 cf ff ff
*/
	char ch = -128;
	char ch2 = ch - 1;
	show_bytes((byte_pointer)&ch, sizeof(char));
	printf("%d\n", ch);
	printf("%d\n", ch2);
	printf("%u\n", ch2);
	show_bytes((byte_pointer)&ch2, sizeof(char));
	putchar('\n');
/*
	output6:
	80
	-128
	127
	127
	7f

	80=b1000 0000
	ch-1=0x80+0xff=b1 0111 1111
	so ch2=b0111 1111=0x7f=127(dec)

*/
	int sx = -1;
	unsigned u = 1 << 31;
	printf("sx=%u=%d\n", sx, sx);
	printf("u=%u=%d\n", u, u);
	putchar('\n');

/*
	output7:
	sx=4294967295=-1
	u=2147483648=-2147483648

	int sx=-1;
	sx here is complement form 0xffffffff
	if we print this in unsigned form 
	the answer is 0xffffffff=1<<32 -1=4294967295
	unsigned u=2147483648=2<<31=0x80000000
	when print in signed form is -(1<<31)=-2147483648
*/
 
//    int j;
//    for (j = 100; j - sizeof(char) >= 0; j--) {
//        printf("%2d\n", j);
//    }
//    sizeof made the expression unsigned 
//    so this is an endless loop


	short sx_2 = -12345;
	unsigned short usx = sx_2;
	int x_2 = sx_2;
	unsigned ux_2 = usx;

	printf("sx=%d\n", sx_2);
	show_bytes((byte_pointer)&sx_2, sizeof(short));
	printf("usx=%u\n", usx);
	show_bytes((byte_pointer)&usx, sizeof(unsigned short));
	printf("x=%d\n", x_2);
	show_bytes((byte_pointer)&x_2, sizeof(int));
	printf("ux=%u\n", ux_2);
	show_bytes((byte_pointer)&ux_2, sizeof(unsigned int));
	putchar('\n');
/*
	output8:
	sx=-12345
	c7 cf

	usx=53191
	c7 cf

	x=-12345
	c7 cf ff ff

	ux=12345
	c7 cf 00 00

	for unsigned the extension is 0
	for signed the extension is signal bit
*/

	short sx_3 = -12345;
	unsigned uy_2 = sx_3;
	printf("%u \n", uy_2);
	show_bytes((byte_pointer)&uy_2, sizeof(unsigned int));
	putchar('\n');
/*
	output9:
	4294954951
	c7 cf ff ff

	when expand an signed short to unsigned int
	first changed the size and then the type.

	unsigned uy_2==(unsigned )(int)uy_2---->4294954951=[ff ff cf c7]
	!= (unsigned) (short int) which will get 53191 [cf c7]

*/

	unsigned val1 = 0x00000076;
	fun1(val1);
	putchar('\n');
	fun2(val1);
	putchar('\n');

	/*
	fun1 logic shift: <<24--->0x76000000 >>24--->(be fulled with 0)0x00000076
	fun2 aithm shift: <<24--->0x76000000 signal bit is 0
	*/
	unsigned val2 = 0x87654321;
	fun1(val2);
	putchar('\n');
	fun2(val2);
	putchar('\n');
	/*
	fun1 logic shift: <<24--->0x21000000 >>24--->(be fulled with 0)0x00000021
	fun2 aithm shift: <<24--->0x21000000 signal bit is 0
	*/
	unsigned val3 = 0x000000c9;
	fun1(val3);
	putchar('\n');
	fun2(val3);
	putchar('\n');
	/*
	fun1 logic shift: <<24--->0xc9000000 >>24--->(be fulled with 0)0x000000c9
	fun2 aithm shift: <<24--->0xc9000000 signal bit is 1  c=1100  negative number
	*/
	unsigned val4 = 0xedcba987;
	fun1(val4);
	putchar('\n');
	fun2(val4);
	putchar('\n');
	/*
	fun1 logic shift: <<24--->0x87000000 >>24--->(be fulled with 0)0x00000087
	fun2 aithm shift: <<24--->0x87000000 signal bit is 1  8=1000   negative number
	*/

	int dat1 = 0x10101010;
	int dat2 = 0x11111111;
	int res = bool_xor(dat1, dat2);
	printf("%x\n", res);
	/*
	we can use OR and AND to achive XOR:
	a^b=
	1.(a&~b)|(~a&b)
	2.~(~a&~b)|~(a&b)
	3.(a&~b)|(~a&b)
	*/

	return 0;
}


void show_bytes(byte_pointer star, size_t len) {
	size_t i;
	for (i = 0; i < len; i++) {
		printf("%.2x ", star [i]);
	}
	printf("\n");
}

/*
	using unsigned char* star, the size of unsigned char is 1 Byte
	so when using for loop,each time will print a byte through hex
	with format .2. so for int type will get 4 input.
 */
void show_int(int x) {
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
	show_bytes((byte_pointer)&x, sizeof(void *));
}

void fun1(unsigned w) {
	int val = (int)((w << 24) >> 24);
	printf("(int)((%#8x<<24)>>24)=\t\t%#8x\t%8d\n", w, val, val);
}

void fun2(unsigned w) {
	int val = ((int)w << 24) >> 24;
	printf("((int)%#8x<<24)>>24=\t\t%#8x\t%8d\n", w, val, val);
}

int bool_xor(int x, int y) {
	return ((x&~y) | (~x & y));
}

int uadd_ok(unsigned x, unsigned y) {
	return ((x + y) < y) ? 0 : 1;
}

int tadd_ok(int x, int y) {   
	int sum = x + y;
	return ((x > 0 && y > 0 && sum <= 0) || (x < 0 && y < 0 && sum >= 0)) ? 0 : 1;
}

int tsub_ok(int x, int y) {
	return (y == INT_MIN) ? (!tadd_ok(x, -y)) : tadd_ok(x, -y);
}

int tmult_ok(int x, int y) {
	int p = x * y;
	return !x || p / x == y;
}

int tmult_ok_2(int x, int y) {
	int64_t tmp_result = (int64_t)(x*y);
	return tmp_result == (int)tmp_result;
}

int div_16(int x) {                             
	int bias = (x >> 31) & 0xF;
	return (x + bias) >> 4;
}
