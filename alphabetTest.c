#include <stdio.h>
#include "pico/stdlib.h"

uint8_t alphValues[] = {
    0b11101110, //A
    0b00111111, //B
    0b10011101, //C
    0b01111011, //D
    0b10011111, //E
    0b10001110, //F
    0b11110111, //G
    0b01101110, //H
    0b00001100, //I
    0b01111001, //J
    0b01101110, //K
    0b00011101, //L
    0b10101000, //M
    0b00101010, //N
    0b11111101, //O
    0b11001110, //P
    0b11100110, //Q
    0b00001010, //R
    0b10110110, //S
    0b00011110, //T
    0b01111100, //V
    0b00111000, //U
    0b01010100, //W
    0b01101110, //X
    0b01110110, //Y
    0b11011010, //Z
    0b11111111, //8
}

void alphabet_init() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }
}

void alphabet_off() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], true);
    }
}

unsigned int alphabet_show(unsigned int number) {
    if (number > 27) return 1;
    unsigned int segmentBit = 1 << (7 - i);
    bool illuminateSegment = (segmentBit & values[number]); 
    gpio_put(
            ALL_SEGMENTS[i],
            !illuminateSegment
        );
    printf("%d \n", number);
    return 0;
}