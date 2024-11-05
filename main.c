#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_PIN    16
#define BUZZER_PIN    17
#define SEGMENT_A     7
#define SEGMENT_B     6
#define SEGMENT_C     20
#define SEGMENT_D     19
#define SEGMENT_E     18
#define SEGMENT_F     8
#define SEGMENT_G     9
#define SEGEMENT_DP   21
static const unsigned int ALL_SEGMENTS[] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, SEGMENT_DP}

#define ALL_SEGMENTS_COUNT 8

int main() {
    alphabet_init();
    alphabet_off(); 
    int num = 27;
    alphabet_show(num);
    sleep_ms(500);
    alphabet_off();
    sleep_ms(500);
    return 0;
}
