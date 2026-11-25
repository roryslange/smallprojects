#include <stdint.h>
#include <stdio.h>

typedef int8_t i8;
typedef int8_t i16;
typedef int8_t i32;
typedef int8_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct {
    u8 *str;
    u64 size;
} string8;

string8 read_file(const char* path);
void print_string(string8 input);

string8 read_file(const char* path) {
    string8 out = { 0 };
    FILE *f = fopen(path);

    fseek(f, 0, SEEK_END);
    out.size = ftell(f);
    out.str = malloc(out.size);
    fseek(f, 0, SEEK_SET);
    fread(out.str, 1, out.size, f);

    fclose(f);
    return out;
}

void print_string(string8 input) {
    for (u64 i = 0; i < input.size; i++) {
        printf("%c", (char)input.str[i]);
    }
}
