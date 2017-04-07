#include "Iskra.h"

void setCMD(Buffer_TypeDef *buff, int cmd){
    switch(cmd % 16){
        case 0 : buff->CMD = SHOT; break;
        case 1 : buff->CMD = '1'; break;
        case 2 : buff->CMD = SET; break;
        case 3 : buff->CMD = '3'; break;
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
    int i = 0;
    while ((status >= 15) && (i < 4))
        {
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
            case 15 : buff->Status[i] = 'F'; break;}
        }
    status = status - (status / 16); i++;
}

void setTRK_No(Buffer_TypeDef *buff, int trk_no){
    int i = 0;
    while ((trk_no >= 15) && (i < 2))
        {
        switch(trk_no % 14){
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
            case 15 : buff->TRK_No[i] = 'F'; break;}
        }
    trk_no = trk_no - (trk_no / 16); i++;
}

void setPrice(Buffer_TypeDef *buff, int price){
    int i = 0;
    while ((price >= 9) && (i < 6)){
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
            case 9 : buff->Price[i] = '9'; break;}
        }
    price = price - (price / 10); i++;
}

void setVolume(Buffer_TypeDef *buff, int valume)
{
    int i = 0;
    while ((valume >= 9) && (i < 6)){
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
            case 9 : buff->Volume[i] = '9'; break;}
        }
    valume = valume - (valume / 10); i++;
}

void setCRC(Buffer_TypeDef *buff){
    for(unsigned int i=1; i < ((sizeof(Buffer_TypeDef)/sizeof(byte))-3); i++){
       ((byte*)buff)[i] ^= ((byte*)buff)[i+1];
    }
}

 void sendBuffer(Buffer_TypeDef _buff){
    for(unsigned int i =0;  i < (sizeof(Buffer_TypeDef)/sizeof(byte)); i++){
        //write((byte*)&_buff)[i]) пишем в порт по 8 бит данных
    }
}

int writeBuffer(int TRK_No, byte CMD, int Price, int Volume, int Status){

    Buffer_TypeDef buff;
    buff.SOH = 0x01U;
    setTRK_No(&buff, TRK_No);
    setCMD(&buff, CMD);
    buff.STX = 0x02U;
    setVolume(&buff, Volume);
    setPrice(&buff, Price);
    setStatus(&buff, Status);
    buff.ETX = 0x03U;
    setCRC(&buff);
    sendBuffer(buff);

//    printf("SOH = %X\nTRK_No[0] = %X\nTRK_No[1] = %X\nCMD = %X\nSTX = %X\nPrice = %X\nVolume = %X\nStatus = %X\nETX = %X\nCRC = %X\n",
//    buff.SOH, buff.TRK_No[0], buff.TRK_No[1], buff.CMD, buff.STX, buff.Price, buff.Volume, buff.Status, buff.ETX, buff.CRC);
//    printf("sizeof(23) = %d\n", sizeof(llong));
    return 0;
}
