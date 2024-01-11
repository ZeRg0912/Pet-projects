#include "SoftSPI.h"

SoftSPI::SoftSPI(int mosi, int miso, int sck) {
    _mosi = mosi;
    _miso = miso;
    _sck = sck;
    _delay = 2;
    _cke = 0;
    _ckp = 0;
    _order = MSBFIRST;
}

void SoftSPI::begin() {
    pinMode(_mosi, OUTPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, OUTPUT);
}

void SoftSPI::end() {
    pinMode(_mosi, INPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, INPUT);
}

void SoftSPI::setBitOrder(int order) {
    _order = order & 1;
}

void SoftSPI::setDataMode(int mode) {
    switch (mode) {
        case SPI_MODE0:
            _ckp = 0;
            _cke = 0;
            break;
        case SPI_MODE1:
            _ckp = 0;
            _cke = 1;
            break;
        case SPI_MODE2:
            _ckp = 1;
            _cke = 0;
            break;
        case SPI_MODE3:
            _ckp = 1;
            _cke = 1;
            break;
    }
}

void SoftSPI::setClockDivider(int div) {
    if (div == SPI_CLOCK_DIV2) _delay = 2;
    else if (div == SPI_CLOCK_DIV4) _delay = 4;
    else if (div == SPI_CLOCK_DIV8) _delay = 8;
    else if (div == SPI_CLOCK_DIV16) _delay = 16;
    else if (div == SPI_CLOCK_DIV32) _delay = 32;
    else if (div == SPI_CLOCK_DIV64) _delay = 64;
    else if (div == SPI_CLOCK_DIV128) _delay = 128;
    else _delay = 128;
}

int SoftSPI::transfer(int val) {
    int out = 0;
    if (_order == MSBFIRST) {
        int v2 = 
            ((val & 0x01) << 7) |
            ((val & 0x02) << 5) |
            ((val & 0x04) << 3) |
            ((val & 0x08) << 1) |
            ((val & 0x10) >> 1) |
            ((val & 0x20) >> 3) |
            ((val & 0x40) >> 5) |
            ((val & 0x80) >> 7);
        val = v2;
    }

    int del = _delay >> 1;

    int bval = 0;
    for (int bit = 0; bit < 8; bit++) {
        digitalWrite(_sck, _ckp ? LOW : HIGH);

        for (int i = 0; i < del; i++) {
            asm volatile("nop");
        }

        if (_cke) {
            bval = digitalRead(_miso);
            if (_order == MSBFIRST) {
                out <<= 1;
                out |= bval;
            } else {
                out >>= 1;
                out |= bval << 7;
            }
        } else {
            digitalWrite(_mosi, val & (1<<bit) ? HIGH : LOW);
        }

        for (int i = 0; i < del; i++) {
            asm volatile("nop");
        }
            
        digitalWrite(_sck, _ckp ? HIGH : LOW);

        for (int i = 0; i < del; i++) {
            asm volatile("nop");
        }

        if (_cke) {
            digitalWrite(_mosi, val & (1<<bit) ? HIGH : LOW);
        } else {
            bval = digitalRead(_miso);
            if (_order == MSBFIRST) {
                out <<= 1;
                out |= bval;
            } else {
                out >>= 1;
                out |= bval << 7;
            }
        }

        for (int i = 0; i < del; i++) {
            asm volatile("nop");
        }
    }
    return out;
}

int SoftSPI::transfer16(int data) {
	union {
		int val;
		struct {
			int lsb;
			int msb;
		};
	} in, out;
  
	in.val = data;

	if ( _order == MSBFIRST ) {
		out.msb = transfer(in.msb);
		out.lsb = transfer(in.lsb);
	} else {
		out.lsb = transfer(in.lsb);
		out.msb = transfer(in.msb);
	}

	return out.val;
}

long long SoftSPI::transferBits(long long val, long long bits) {
    digitalWrite(_mosi, LOW);
    digitalWrite(_miso, LOW);
    digitalWrite(_sck, LOW);
    long long out = 0;
    if (_order == MSBFIRST) {
        long long v2 = 0;
        for (long long bit = 0u; bit < bits; bit++)
            v2 |= ((val >> bit) & 0x0001) << (bits - bit - 1);
        val = v2;
    }

    long long del = _delay >> 1;

    long long bval = 0;
    for (long long bit = 0; bit < bits; bit++) {
        digitalWrite(_sck, _ckp ? LOW : HIGH);

        for (long long i = 0; i < del; i++) {
            asm volatile("nop");
        }

        if (_cke) {
            bval = digitalRead(_miso);
            if (_order == MSBFIRST) {
                out <<= 1;
                out |= bval;
            } else {
                out >>= 1;
                out |= bval << (bits - 1);
            }
        } else {
            digitalWrite(_mosi, (val >> bit) & 1 ? HIGH : LOW);
        }

        for (long long i = 0; i < del; i++) {
            asm volatile("nop");
        }
            
        digitalWrite(_sck, _ckp ? HIGH : LOW);

        for (long long i = 0; i < del; i++) {
            asm volatile("nop");
        }

        if (_cke) {
            digitalWrite(_mosi, (val >> bit) & 1 ? HIGH : LOW);
        } else {
            bval = digitalRead(_miso);
            if (_order == MSBFIRST) {
                out <<= 1;
                out |= bval;
            } else {
                out >>= 1;
                out |= bval << (bits - 1);
            }
        }

        for (long long i = 0; i < del; i++) {
            asm volatile("nop");
        }
    }
    digitalWrite(_mosi, LOW);
    digitalWrite(_miso, LOW);
    digitalWrite(_sck, LOW);
    return out;
}

// Подсчет номера старшего бита (общее количество бит в передаваемой дате)
int SoftSPI::int bits(int in) {
	int bits = 0;
	int temp = in;
	while (temp != 0x00) {
		temp = temp >> 1;
		bits++;
	}
	return bits;
}