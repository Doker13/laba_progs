#include <stdio.h>

int main(){
    printf("%x \n", (0xabcd|0x5432)&(0xfdeb >> 1));
    return 0;
}
