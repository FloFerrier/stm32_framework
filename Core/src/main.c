#include <stdint.h>

#define SIZE 20

uint32_t tmp[SIZE] = {0};

int main(void) {
    static uint32_t index = 0;
    while (1) {
        tmp[index] = index;
        ++index;
        if (index >= SIZE) {
            index = 0;
        }
    }
    return 0;
}