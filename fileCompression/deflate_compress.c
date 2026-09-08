#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BTYPE_NOCOMP    0b00000000  // no compression
#define BTYPE_STATHUF   0b00000001  // static huffman encoding flag
#define BTYPE_DYNHUF    0b00000010  // dynamic huffman encoding flag
#define BTYPE_ERR       0b00000011  // error flag
#define BLOCK_MAX_SIZE  65535       // maximum uncompressed block size of 65,535 bytes
#define MAX_BITS        15          // used for huffman encoding

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

typedef struct {
    string8 backing;
    u64 bit_pos;
    u64 bit_size;
} bitstream;

typedef struct {
    u16 len;
    u16 code;
} static_huffman_node;

string8 read_file(const char* path);
void deflate(string8 input, string8 out);
bitstream bs_init(string8 backing);
u32 bs_peek(bitstream *bs, u8 nbits);
u32 bs_take(bitstream *bs, u8 nbits);
void build_huff_tree(static_huffman_node *node, u32 node_count);

u32 bit_masks[] = {
    0b0000000000000000,
    0b0000000000000001,
    0b0000000000000011,
    0b0000000000000111,
    0b0000000000001111,
    0b0000000000011111,
    0b0000000000111111,
    0b0000000001111111,
    0b0000000011111111,
    0b0000000111111111,
    0b0000001111111111,
    0b0000011111111111,
    0b0000111111111111,
    0b0001111111111111,
    0b0011111111111111,
    0b0111111111111111,
    0b1111111111111111,
};

int main() {
    string8 t = read_file("fopen.txt");
    for (u64 i = 0; i < t.size; i++) {
        printf("%c", (char)t.str[i]);
    }

    return 0;
}

string8 read_file(const char* path) {
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


bitstream bs_init(string8 backing) {
    return (bitstream){
        .backing = backing,
        .bit_pos = 0,
        .bit_size = backing.size * 8
    };
}

u32 bs_peek(bitstream *bs, u8 nbits) {
    u64 byte_pos = bs->bit_pos / 8;
    u32 bits = *(u32*)(bs->backing.str + byte_pos);
    bits >>= bs->bit_pos % 8;

    return bits && bit_masks[nbits];
}



void deflate(string8 input, string8 out) {
    
}
