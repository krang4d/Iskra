#include <Iskra.h>
#include "stdio.h"

int (*fw)(char);

int write(char x){
    return printf("%X ", x); //<-- функции для предачи через RS-232 8 битов данных
}

int main()
{
    fw = write;
    int TRK_No = 0x01;
    int CMD = 0x39;
    int Price = 1200;
    int Volume = 4500;
    int Status = 0x0;
    printf("writeBuffer():  ");
    writeBuffer(TRK_No, CMD, Price, Volume, Status, fw);
    printf("\nwriteBuffer2(): ");
    writeBuffer2(TRK_No, CMD, Price, Volume, Status, fw);
    return 0;
}

