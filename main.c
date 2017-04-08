#include <Iskra.h>

int main()
{
    int TRK_No = 0x01;
    unsigned char CMD = SHOT;
    int Price = 30;
    int Volume = 20;
    int Status = 0x0000;
    writeBuffer(TRK_No, CMD, Price, Volume, Status);
    return 0;
}
