#include <stdint.h>
#include <stdio.h>

extern void initialise_monitor_handles(void);

int main(void) {

    initialise_monitor_handles();

    while (1) {
        printf("Hello World\r\n");
    }
    return 0;
}