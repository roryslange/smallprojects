#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// need two primes these are to be kept secret (usually)
// factoring makes no sense if numbers are betweeen 2^1023 and 2^1024
#define KEY_P 11
#define KEY_Q 23

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
    u8 *str;
    u64 size;
} string8;

string8 read_file(char *path);
u32 gcd(u32 a, u32 b);

/*
*
* four steps
* 1. key generation
* 2. key distribution (not relevant here but could do example)
* 3. public key operation
* 4. private key operation
*
*/

int main() {
    string8 test = read_file("text.txt");

    u32 n = KEY_P * KEY_Q;
    u32 etf = (KEY_P - 1) * (KEY_Q - 1);    // should be 220, Euler Totient Function (two primes)
    u32 encrypt_exp = 131;                  // gcd(encrypt_exp, etf) should be 1
    u32 decrypt_exp = 1 % etf;
    
    printf("%d\n", decrypt_exp);
}

string8 read_file(char *path) {
    string8 out = { 0 };
    FILE* f = fopen(path, "rb");

    fseek(f, 0, SEEK_END);
    out.size = ftell(f);
    out.str = malloc(out.size);
    fseek(f, 0, SEEK_SET);

    fread(out.str, 1, out.size, f);
    fclose(f);

    return out;
}

u32 gcd(u32 a, u32 b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}



