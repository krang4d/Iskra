#ifndef ISKRA_H
#define ISKRA_H

typedef unsigned char byte;

//Перечень команд управления (HEX)
#define SHOT    (0x31U)     //Задание дозы налива для ТРК и установка готовности ТРК к пуску
#define SET     (0x33U)     //Установка параметров ТРК
#define TEST    (0x34U)     //Опрос состояния ТРК
#define START   (0x35U)     //Запуск ТРК
#define STOP    (0x36U)     //Останов ТРК
#define RESET   (0x37U)     //Сброс состояния ТРК
#define FULL    (0x39U)     //Заправка до полного бака

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

void setTRK_No(Buffer_TypeDef *buff, int *trk_no);
void setCMD(Buffer_TypeDef *buff, int *cmd);
void setPrice(Buffer_TypeDef *buff, int *price);
void setVolume(Buffer_TypeDef *buff, int *valume);
void setStatus(Buffer_TypeDef *buff, int *status);
void setCRC(Buffer_TypeDef *buff);	//Подсчет  байта контрольной суммы сообщения
int writeBuffer(int TRK_No, int CMD, int Price, int Volume, int Code, int (*_write)(unsigned char)); //Функцию отправки данных от ККМ в контроллер ТРК.
void sendBuffer(Buffer_TypeDef *buff, int (*_write)(unsigned char));

byte toHex(int *i);
byte toDec(int *i);

#endif // ISKRA_H
