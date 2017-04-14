#include "Iskra.h"

void sortBuff(Buffer_TypeDef *p, int s, int e){
    e+=1;
    byte *b, b1;
    b = (byte*)p;
    for(int i=0; i<(e-s)/2; i++)
    {
        b1 = b[s+i];
        b[s+i]=b[e-1-i];
        b[e-1-i] = b1;
    }
}

byte toHex(int *i){
    switch((*i) % 16){
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

byte toDec(int *i){
    switch((*i) % 10){
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
void setCMD(Buffer_TypeDef *buff, int *cmd){
    buff->CMD = toHex(cmd);
}
void setStatus(Buffer_TypeDef *buff, int *status){
    for(int i = 0; i < 4; i++){
        buff->Status[i] = toHex(status);
        (*status) /= 16;
    }
    sortBuff(buff, 17, 20);
}
void setTRK_No(Buffer_TypeDef *buff, int *trk_no){
    for(int i = 0; i < 2; i++){
        buff->TRK_No[i] = toHex(trk_no);
        (*trk_no) /= 16;
    }
    sortBuff(buff, 1, 2);
}
void setPrice(Buffer_TypeDef *buff, int *price){
    for(int i = 0; i < 6; i++){
        buff->Price[i] = toDec(price);
        (*price) /= 10;
    }
    sortBuff(buff, 5, 10);
}
void setVolume(Buffer_TypeDef *buff, int *valume)
{
    for(int i = 0; i < 6; i++){
        buff->Volume[i] = toDec(valume);
        (*valume) /= 10;
    }
    sortBuff(buff, 11, 16);
}
void setCRC(Buffer_TypeDef *buff){
    byte* b = (byte*)buff;
    b[22]=0; for (int i=1; i<22; i++) b[22]^= b[i];
}
void sendBuffer(Buffer_TypeDef *buff,int (*_write)(char)){
    int n = sizeof(Buffer_TypeDef)/sizeof(byte);
    byte* px;
    px = (byte*)buff;
    for(int i=0;  i < n; i++){
        _write(px[i]);
    }
}
int writeBuffer(int TRK_No, int CMD, int Price, int Volume, int Status, int(*_write)(char)){
    Buffer_TypeDef buff = {0};
    buff.SOH = 0x01U;
    buff.STX = 0x02U;
    buff.ETX = 0x03U;
    setTRK_No(&buff, &TRK_No);
    setCMD(&buff, &CMD);
    setPrice(&buff, &Price);
    setVolume(&buff, &Volume);
    setStatus(&buff, &Status);
    setCRC(&buff);
    sendBuffer(&buff, _write);
    return 0;
}
 int writeBuffer2(int TRK_No, int CMD, int Price, int Volume, int Status, int(*_write)(char)){
     for(int i = 0; i < 23; i++)
     {
         if(i==0) {buff[i] = 0x01U; continue;}
         else if(i<3) {buff[i] = toHex(&TRK_No); TRK_No /= 16; continue;}
         else if(i==3) {buff[i] = toHex(&CMD); continue;}
         else if(i==4) {buff[i] = 0x02U; continue;}
         else if(i<11) {buff[i] = toDec(&Price); Price /= 10; continue;}
         else if(i<17) {buff[i] = toDec(&Volume); Volume /= 10; continue;}
         else if(i<21) {buff[i] = toHex(&Status); Status /= 16; continue;}
         else if(i==21) {buff[i] = 0x03U; continue;}
         else if(i==22) {buff[22]=0; for (int i=1; i<22; i++) buff[22]^= buff[i]; continue;}
     }
     for(unsigned int i=0;  i < sizeof(buff); i++){
         _write(buff[i]);
    }
    return 0;
}
