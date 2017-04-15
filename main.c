#include <Iskra.h>

int (*fw)(char);

int write(char x){
    return x; //<-- функции для предачи через RS-232 8 битов данных
}

int main()
{
    fw = write;
    int TRK_No = 0x01;
    int CMD = 0x31;
    int Price = 1234;
    int Volume = 123456;
    int Status = 0x00;
    writeBuffer(TRK_No, CMD, Price, Volume, Status, fw);
    return 0;
}

