typedef unsigned char byte;
typedef unsigned long long llong;

#define SHOT    (0x31U) /*Задание дозы налива для ТРК и установка готовности ТРК к пуску*/
#define SET     (0x32U) /*Установка параметров ТРК*/
#define TEST    (0x34U) /*Опрос состояния ТРК*/
#define START   (0x35U) /*Запуск ТРК*/
#define STOP    (0x36U) /*Останов ТРК*/
#define RESET   (0x37U) /*Сброс состояния ТРК*/
#define FULL    (0x39U) /*Заправка до полного бака*/

//typedef struct
//{
//    byte Error[2];          /*Код ошибки протокола*/
//    byte Code[2];          /*Код состояния ТРК*/
//} ErrorStatus;


typedef struct
{
    byte SOH;               /*Маркер начала сообщения*/
    byte TRK_No[2];         /*Номер ТРК. *Только для команды "Общий останов"*/
    byte CMD;               /*Код команды управления*/
    byte STX;               /*Маркер начала поля данных*/
    byte Price[6];          /*Цена топлива, коп.*/
    byte Volume[6];         /*Доза налива, мл.*/
    byte Status[4];         /*Код состояния/ошибки и параметры ТРК*/
    byte ETX;               /*Маркер окончания поля данных*/
    byte CRC;               /*Контрольная сумма*/
} Buffer_TypeDef;

byte CheckSumma(byte TRK_No, byte CMD, byte STX, byte Price, byte Volume, byte Status, byte ETX);
//int writeBuff(Buffer_TypeDef _buff);
int writeBuff(int TRK_No, byte CMD, llong Price, llong Volume, int Code);
