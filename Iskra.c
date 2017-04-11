#include "Iskra.h"

void setCMD(Buffer_TypeDef *buff, int cmd){
    switch(cmd % 16){
        case 0 : buff->CMD = '0'; break;
        case 1 : buff->CMD = SHOT; break;
        case 2 : buff->CMD = '2'; break;
        case 3 : buff->CMD = SET; break;
        case 4 : buff->CMD = TEST; break;
        case 5 : buff->CMD = START; break;
        case 6 : buff->CMD = STOP; break;
        case 7 : buff->CMD = RESET; break;
        case 8 : buff->CMD = '8'; break;
        case 9 : buff->CMD = FULL; break;
        case 10 : buff->CMD = 'A'; break;
        case 11 : buff->CMD = 'B'; break;
        case 12 : buff->CMD = 'C'; break;
        case 13 : buff->CMD = 'D'; break;
        case 14 : buff->CMD = 'E'; break;
        case 15 : buff->CMD = 'F'; break;}
}

void setStatus(Buffer_TypeDef *buff, int status){
    for(int i = 0; i < 4; i++){
        switch(status % 16){
            case 0 : buff->Status[i] = '0'; break;
            case 1 : buff->Status[i] = '1'; break;
            case 2 : buff->Status[i] = '2'; break;
            case 3 : buff->Status[i] = '3'; break;
            case 4 : buff->Status[i] = '4'; break;
            case 5 : buff->Status[i] = '5'; break;
            case 6 : buff->Status[i] = '6'; break;
            case 7 : buff->Status[i] = '7'; break;
            case 8 : buff->Status[i] = '8'; break;
            case 9 : buff->Status[i] = '9'; break;
            case 10 : buff->Status[i] = 'A'; break;
            case 11 : buff->Status[i] = 'B'; break;
            case 12 : buff->Status[i] = 'C'; break;
            case 13 : buff->Status[i] = 'D'; break;
            case 14 : buff->Status[i] = 'E'; break;
            case 15 : buff->Status[i] = 'F'; break;
        }
        status = status / 16;
    }
}

void setTRK_No(Buffer_TypeDef *buff, int trk_no){
    for(int i = 0; i < 2; i++){
        switch(trk_no % 16){
            case 0 : buff->TRK_No[i] = '0'; break;
            case 1 : buff->TRK_No[i] = '1'; break;
            case 2 : buff->TRK_No[i] = '2'; break;
            case 3 : buff->TRK_No[i] = '3'; break;
            case 4 : buff->TRK_No[i] = '4'; break;
            case 5 : buff->TRK_No[i] = '5'; break;
            case 6 : buff->TRK_No[i] = '6'; break;
            case 7 : buff->TRK_No[i] = '7'; break;
            case 8 : buff->TRK_No[i] = '8'; break;
            case 9 : buff->TRK_No[i] = '9'; break;
            case 10 : buff->TRK_No[i] = 'A'; break;
            case 11 : buff->TRK_No[i] = 'B'; break;
            case 12 : buff->TRK_No[i] = 'C'; break;
            case 13 : buff->TRK_No[i] = 'D'; break;
            case 14 : buff->TRK_No[i] = 'E'; break;
            case 15 : buff->TRK_No[i] = 'F'; break;

        }
        trk_no = trk_no / 16;
    }
}

void setPrice(Buffer_TypeDef *buff, int price){
    for(int i = 0; i < 6; i++){
        switch(price % 10){
            case 0 : buff->Price[i] = '0'; break;
            case 1 : buff->Price[i] = '1'; break;
            case 2 : buff->Price[i] = '2'; break;
            case 3 : buff->Price[i] = '3'; break;
            case 4 : buff->Price[i] = '4'; break;
            case 5 : buff->Price[i] = '5'; break;
            case 6 : buff->Price[i] = '6'; break;
            case 7 : buff->Price[i] = '7'; break;
            case 8 : buff->Price[i] = '8'; break;
            case 9 : buff->Price[i] = '9'; break;
        }
        price = price / 10;
    }
}

void setVolume(Buffer_TypeDef *buff, int valume)
{
    for(int i = 0; i < 6; i++){
        switch(valume % 10){
            case 0 : buff->Volume[i] = '0'; break;
            case 1 : buff->Volume[i] = '1'; break;
            case 2 : buff->Volume[i] = '2'; break;
            case 3 : buff->Volume[i] = '3'; break;
            case 4 : buff->Volume[i] = '4'; break;
            case 5 : buff->Volume[i] = '5'; break;
            case 6 : buff->Volume[i] = '6'; break;
            case 7 : buff->Volume[i] = '7'; break;
            case 8 : buff->Volume[i] = '8'; break;
            case 9 : buff->Volume[i] = '9'; break;
        }
        valume = valume / 10;
    }
}

byte setCRC(Buffer_TypeDef buff){
    unsigned int n = sizeof(Buffer_TypeDef)/sizeof(byte);
    for(unsigned int i=2; i < (n-2); i++){
       ((byte*)&buff)[1] ^= ((byte*)&buff)[i];
    }
    return ((byte*)&buff)[1];
}

 void sendBuffer(Buffer_TypeDef *buff){
    unsigned int n = sizeof(Buffer_TypeDef)/sizeof(byte);
    byte* px;
    px = (byte*)buff;
    for(unsigned int i =0;  i < n; i++){
        //_write(px[i]) <-- функции для предачи через RS-232 8 битов данных
        printf("byte[%i]: %X\n", i, px[i]);
    }
}

int writeBuffer(int TRK_No, byte CMD, int Price, int Volume, int Status){

    Buffer_TypeDef buff = {0};
    buff.SOH = 0x01U;
    setTRK_No(&buff, TRK_No);
    setCMD(&buff, CMD);
    buff.STX = 0x02U;
    setPrice(&buff, Price);
    setVolume(&buff, Volume);
    setStatus(&buff, Status);
    buff.ETX = 0x03U;
    buff.CRC = setCRC(buff);
    sendBuffer(&buff);
    return 0;
}
