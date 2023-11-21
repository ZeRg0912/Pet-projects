#include "SoftSPI.h"

// Создание Софт SPI:
// Pin 6 = MOSI,
// Pin 7 = MISO,
// Pin 8 = SCK
SoftSPI mySPI(6, 7, 8);
SoftSPI mySPI2(9, 10, 11);

void setup() {
  // Старт и присваивание пинов 
  mySPI.begin();
  mySPI2.begin();
  // Порядок MSBFIRST или LSBFIRST
  mySPI.setBitOrder(MSBFIRST);
  mySPI2.setBitOrder(MSBFIRST);
  // Устанавливаем скорость работы
  mySPI.setClockDivider(SPI_CLOCK_DIV128);
  mySPI2.setClockDivider(SPI_CLOCK_DIV128);
  // Клок работает по ВОЗВРАСТАЮЩЕМУ ФРОНТУ SPI_MODE2 || ПОНИЖАЮЩЕМУСЯ ФРОНТУ SPI_MODE1
  mySPI.setDataMode(SPI_MODE2);
  mySPI2.setDataMode(SPI_MODE2);
  // Стоп и присваивание пинам значение вход
  //mySPI.end();
  //mySPI2.end();
}

void loop() {
  // Значение регистра
  int v = 0x51;
  // Размер в битах необходимый для передачи значения регистра
  int sizeOfV = 8;
  // Считывание значения тип данных меняем вплоть до long long
	mySPI.transferBits(v, sizeOfV);
  mySPI2.transferBits(v, sizeOfV);
	delay(1000);
}
