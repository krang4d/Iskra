#include <stdio.h>
#include <Iskra.h>

int main()
{
    byte TRK_No = 1;
    byte CMD = 1;
    byte Price = 1;
    byte Volume = 1;
    byte Code = 1;
    writeBuffer(&TRK_No, CMD, &Price, &Volume, &Code);
    return 0;
}
