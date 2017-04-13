#include "Iskra.h"

 void writeBuffer(int TRK_No, int CMD, int Price, int Volume, int Status, int(*_write)(char)){
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
}

 char toHex(int *i){
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

 char toDec(int *i){
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
