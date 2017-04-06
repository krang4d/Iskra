#include <stdio.h>
#include <Iskra.h>

int main()
{
    int TRK_No = 1;
    unsigned char CMD = 2;
    long long Price = 3;
    long long Volume = 4;
    int Code = 5;
    writeBuffer(TRK_No, CMD, Price, Volume, Code);
    return 0;
}
