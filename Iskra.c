#include "Iskra.h"

void setCMD(Buffer_TypeDef *buff, int cmd){
    buff->CMD = toHex(cmd);
}

void setStatus(Buffer_TypeDef *buff, int status){
    for(int i = 0; i < 4; i++){
        buff->Status[i] = toHex(status);
        status /= 16;
    }
}

void setTRK_No(Buffer_TypeDef *buff, int trk_no){
    for(int i = 0; i < 2; i++){
        buff->TRK_No[i] = toHex(trk_no);
        trk_no /= 16;
    }
}

void setPrice(Buffer_TypeDef *buff, int price){
    for(int i = 0; i < 6; i++){
        buff->Price[i] = toDec(price);
        price /= 10;
    }
}

void setVolume(Buffer_TypeDef *buff, int valume)
{
    for(int i = 0; i < 6; i++){
        buff->Volume[i] = toDec(valume);
        valume /=  10;
    }
}

void setCRC(Buffer_TypeDef *buff){
    byte *b = (byte*)buff;
    for(int i=1; i < 22; i++){
       b[22] ^= b[i];
    }
}

 void sendBuffer(Buffer_TypeDef *buff,int (*_write)(unsigned char)){
    unsigned int n = sizeof(Buffer_TypeDef)/sizeof(byte);
    byte* px;
    px = (byte*)buff;
    for(unsigned int i =0;  i < n; i++){
        _write(px[i]); //<-- функции для предачи через RS-232 8 битов данных
    }
}

int writeBuffer(int TRK_No, byte CMD, int Price, int Volume, int Status, int (*_write)(unsigned char ch)){

    Buffer_TypeDef buff = {0};
    buff.SOH = 0x01U;
    setTRK_No(&buff, TRK_No);
    setCMD(&buff, CMD);
    buff.STX = 0x02U;
    setPrice(&buff, Price);
    setVolume(&buff, Volume);
    setStatus(&buff, Status);
    buff.ETX = 0x03U;
    setCRC(&buff);
    sendBuffer(&buff, _write);
    return 0;
}

byte toHex(int i){
    switch(i % 16){
        case 0 : return '0';
        case 1 : return '1';
        case 2 : return '2';
        case 3 : return '3';
        case 4 : return '4';
        case 5 : return '5';
        case 6 : return '6';
        case 7 : return '7';
        case 8 : return '8';
        case 9 : return '9';
        case 10 : return 'A';
        case 11 : return 'B';
        case 12 : return 'C';
        case 13 : return 'D';
        case 14 : return 'E';
        case 15 : return 'F';
        default: return '0';
    }
}

byte toDec(int i){
    switch(i % 10){
        case 0 : return '0';
        case 1 : return '1';
        case 2 : return '2';
        case 3 : return '3';
        case 4 : return '4';
        case 5 : return '5';
        case 6 : return '6';
        case 7 : return '7';
        case 8 : return '8';
        case 9 : return '9';
        default: return '0';
    }
}
