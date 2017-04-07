#include <stdio.h>
#include <Iskra.h>

int main()
{
    int TRK_No = 0x01U;
    unsigned char CMD = SHOT;
    int Price = 3;
    int Volume = 4;
    int Error = 5;
    writeBuffer(TRK_No, CMD, Price, Volume, Error);
    return 0;
}
