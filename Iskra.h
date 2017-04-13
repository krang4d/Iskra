#ifndef ISKRA_H
#define ISKRA_H

char buff[23];

void writeBuffer(int TRK_No, int CMD, int Price, int Volume, int Status, int (*_write)(char)); //функцию отправки данных от ККМ в контроллер ТРК.

char toHex(int *i);
char toDec(int *i);

#endif // ISKRA_H
