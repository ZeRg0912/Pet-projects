#ifndef _SOFTSPI_H
#define _SOFTSPI_H

#if (ARDUINO >= 100) 
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

//#include <SPI.h>

#if !defined(SPI_CLOCK_DIV2)
#define SPI_CLOCK_DIV2   2
#define SPI_CLOCK_DIV4   4
#define SPI_CLOCK_DIV8   8
#define SPI_CLOCK_DIV16  16
#define SPI_CLOCK_DIV32  32
#define SPI_CLOCK_DIV64  64
#define SPI_CLOCK_DIV128 128
#endif

class SoftSPI {
    private:
        int _cke;
        int _ckp;
        int _delay;
        int _miso;
        int _mosi;
        int _sck;
        int _order;

    public:
        SoftSPI(int mosi, int miso, int sck);
        void begin();
        void end();
        void setBitOrder(int);
        void setDataMode(int);
        void setClockDivider(int);
        int transfer(int);
        int transfer16(int data);
        long long transferBits(long long, long long);
};
#endif