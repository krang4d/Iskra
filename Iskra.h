#ifndef ISKRA_H
#define ISKRA_H

typedef unsigned char byte;

typedef struct{
    byte SOH;               //Маркер начала сообщения
    byte TRK_No[2];         //Номер ТРК. *Только для команды "Общий останов"
    byte CMD;               //Код команды управления
    byte STX;               //Маркер начала поля данных
    byte Price[6];          //Цена топлива, коп.
    byte Volume[6];         //Доза налива, мл.
    byte Status[4];         //Код состояния/ошибки и параметры ТРК
    byte ETX;               //Маркер окончания поля данных
    byte CRC;               //Контрольная сумма
} Buffer_TypeDef;

int writeBuffer(int TRK_No, int CMD, int Price, int Volume, int Code, int (*_write)(char)); //Функцию отправки данных от ККМ в контроллер ТРК.

void setTRK_No(Buffer_TypeDef *buff, int *trk_no);
void setCMD(Buffer_TypeDef *buff, int *cmd);
void setPrice(Buffer_TypeDef *buff, int *price);
void setVolume(Buffer_TypeDef *buff, int *valume);
void setStatus(Buffer_TypeDef *buff, int *status);
void setCRC(Buffer_TypeDef *buff);	//Подсчет  байта контрольной суммы сообщения
void sendBuffer(Buffer_TypeDef *buff, int (*_write)(char));

byte toHex(int *i);
byte toDec(int *i);
void sortBuff(Buffer_TypeDef *p, int s, int e);
#endif // ISKRA_H
