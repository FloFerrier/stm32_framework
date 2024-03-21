#include "console.h"

void task_shell(void *params) {
    (void)params;

    console_init();

    for( ;; ) {
        static char character = 0;
        static bool isSuccess = true;
        isSuccess = console_receive(&character);
        if(isSuccess == true) {
            if(character >= 0x20  && character <= 0x7E) {
                console_send("%c", character);
            }
            else {
                switch (character)
                {
                case 0x0D: // CR: '\r'
                case 0x0A: // LF: '\n
                    console_send("\r\n");
                    break;
                default:
                    console_send(" 0%x ", character);
                    break;
                }
            }
        }
    }
}