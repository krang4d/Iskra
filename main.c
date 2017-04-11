#include <Iskra.h>
#include "stdio.h"

int (*fw)(unsigned char);

int write(unsigned char x){
        return printf("%X\n", x);
}

int main()
{
    fw = write;
    int TRK_No = 0x01;
    unsigned char CMD = SHOT;
    int Price = 30;
    int Volume = 20;
    int Status = 0x0000;
    writeBuffer(TRK_No, CMD, Price, Volume, Status, fw);
    return 0;
}

