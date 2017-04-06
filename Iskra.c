#include "Iskra.h"

byte CheckSumma(byte TRK_No, byte CMD, byte STX, byte Price, byte Volume, byte Status, byte ETX)
{
   return (0x11U);
}

int writeBuffer(int TRK_No, byte CMD, llong Price, llong Volume, int Status)
{
    Buffer_TypeDef buff;

    buff.SOH = 0x01U;
    buff.TRK_No[0] = ((byte*)&TRK_No)[0];
    buff.TRK_No[1] = ((byte*)&TRK_No)[1];
    buff.CMD = CMD;
    buff.STX = 0x02U;
    buff.Price[0] = ((byte*)&Price)[0];
    buff.Price[1] = ((byte*)&Price)[1];
    buff.Price[2] = ((byte*)&Price)[2];
    buff.Price[3] = ((byte*)&Price)[3];
    buff.Price[4] = ((byte*)&Price)[4];
    buff.Price[5] = ((byte*)&Price)[5];

    buff.Volume[0] = ((byte*)&Volume)[0];
    buff.Volume[1] = ((byte*)&Volume)[1];
    buff.Volume[2] = ((byte*)&Volume)[2];
    buff.Volume[3] = ((byte*)&Volume)[3];
    buff.Volume[4] = ((byte*)&Volume)[4];
    buff.Volume[5] = ((byte*)&Volume)[5];

    buff.Status[0] = ((byte*)&Status)[0];
    buff.Status[1] = ((byte*)&Status)[1];
    buff.Status[2] = ((byte*)&Status)[2];
    buff.Status[3] = ((byte*)&Status)[3];

    buff.ETX = 0x03U;
    buff.CRC = CheckSumma(&buff.TRK_No, buff.CMD, buff.STX, &buff.Price, &buff.Volume, &buff.Status, buff.ETX);


//    printf("SOH = %X\nTRK_No[0] = %X\nTRK_No[1] = %X\nCMD = %X\nSTX = %X\nPrice = %X\nVolume = %X\nStatus = %X\nETX = %X\nCRC = %X\n",
//           buff.SOH, buff.TRK_No[0], buff.TRK_No[1], buff.CMD, buff.STX, buff.Price, buff.Volume, buff.Status, buff.ETX, buff.CRC);

    for(int i =0;  i < (sizeof(Buffer_TypeDef)/sizeof(byte)); i++)
    {
        //printf("%X\n", ((byte*)&buff)[i]);
        // write((byte*)&buff)[i]) пишем в порт по 8 бит данных
    }

    //printf("sizeof(23) = %d\n", sizeof(llong));
    return 0;
}
