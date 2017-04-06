#include "Iskra.h"

byte CheckSumma(byte* TRK_No, byte CMD, byte STX, byte* Price, byte* Volume, byte* Status, byte ETX)
{
   return (0x11U);
}

int writeBuffer(byte* TRK_No, byte CMD, byte* Price, byte* Volume, byte* Status)
{
    Buffer_TypeDef buff;

    buff.SOH = 0x01U;
    buff.TRK_No[0] = *(TRK_No);
    buff.TRK_No[1] = *(TRK_No+1);
    buff.CMD = CMD;
    buff.STX = 0x02U;
    buff.Price[0] = *(Price);
    buff.Price[1] = *(Price+1);

    buff.Volume[0] = *(Volume);
    buff.Volume[1] = *(Volume+1);
    buff.Volume[2] = *(Volume+2);
    buff.Volume[3] = *(Volume+3);
    buff.Volume[4] = *(Volume+4);
    buff.Volume[5] = *(Volume+5);

    buff.Status[0] = *(Status);
    buff.Status[1] = *(Status+1);
    buff.Status[2] = *(Status+2);
    buff.Status[3] = *(Status+3);

    buff.ETX = 0x03U;
    buff.CRC = CheckSumma(&buff.TRK_No, buff.CMD, buff.STX, &buff.Price, &buff.Volume, &buff.Status, buff.ETX);


    printf("SOH = %X\nTRK_No = %X\nCMD = %X\nSTX = %X\nPrice = %X\nVolume = %X\nStatus = %X\nETX = %X\nCRC = %X\n",
           buff.SOH, buff.TRK_No, buff.CMD, buff.STX, buff.Price, buff.Volume, buff.Status, buff.ETX, buff.CRC);


    printf("sizeof(23) = %d\n", sizeof(Buffer_TypeDef)/sizeof(byte));
    return 0;
}
