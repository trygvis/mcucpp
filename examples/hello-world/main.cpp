#include <cstdio>

#include "stm32f10x.h"
#include "core_cm3.h"

int main() {
    printf("Hello World!");

    while(true) {
        __NOP();
    }

    return 0;
}
