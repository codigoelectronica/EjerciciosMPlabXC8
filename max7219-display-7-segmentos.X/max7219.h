#ifndef MAX7219_H

#define	MAX7219_H

#define pinDIN_TRIS TRISCbits.TRISC5
#define pinCLK_TRIS TRISCbits.TRISC7
#define pinLOAD_TRIS TRISCbits.TRISC6

#define pinDIN_LAT PORTCbits.RC5
#define pinCLK_LAT PORTCbits.RC7
#define pinLOAD_LAT PORTCbits.RC6

// MAX7219 Registers
#define MAX7219_NOP   0x00
#define MAX7219_DIG1  0x01
#define MAX7219_DIG2  0x02
#define MAX7219_DIG3  0x03
#define MAX7219_DIG4  0x04
#define MAX7219_DIG5  0x05
#define MAX7219_DIG6  0x06
#define MAX7219_DIG7  0x07
#define MAX7219_DIG8  0x08
#define MAX7219_DECODE      0x09
#define MAX7219_INTENSITY   0x0A
#define MAX7219_SCAN_LIMIT  0x0B
#define MAX7219_SHUTDOWN    0x0C
#define MAX7219_TEST        0x0F

static const unsigned char digitos[10] = {
    // XABCDEFG
    0b01111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011 // 9
};

void max7219_Config(void);
void max7219_Intensity(unsigned char);
void max7219_WriteDigito(unsigned char, unsigned char);

void max7219_WriteBits(unsigned int);
void max7219_WriteComando(unsigned char, unsigned char);
void max7219_Clear();

void max7219_Config(void) {
    pinDIN_TRIS = 0;
    pinCLK_TRIS = 0;
    pinLOAD_TRIS = 0;

    pinDIN_LAT = 0;
    pinCLK_LAT = 0;
    pinLOAD_LAT = 1;

    max7219_WriteComando(MAX7219_SHUTDOWN, 0x00);
    max7219_WriteComando(MAX7219_TEST, 0x00);
    max7219_WriteComando(MAX7219_INTENSITY, 0x0F);
    max7219_WriteComando(MAX7219_SCAN_LIMIT, 0x07);
    max7219_WriteComando(MAX7219_SHUTDOWN, 0x01);

}

void max7219_WriteDigito(unsigned char digito, unsigned char valorDeDigito) {
    volatile unsigned int temporal = 0;
    if (digito > 7) {
        return;
    }
    temporal = digito + 1;
    temporal = temporal << 8;
    temporal = temporal & 0x0F00;
    temporal = temporal | digitos[valorDeDigito];
    max7219_WriteBits(temporal);
}

void max7219_Intensity(unsigned char value) {
    if (value < 16) {
        max7219_WriteComando(MAX7219_INTENSITY, value);
    }
}

void max7219_WriteBits(unsigned int valor) {
    volatile unsigned int temporal = 0;
    volatile unsigned char c = 0;
    pinLOAD_LAT = 0;
    for (c = 0; c < 16; c++) {
        temporal = 1;
        temporal = (temporal << (15 - c));
        if ((temporal & valor) != 0) {
            pinDIN_LAT = 1;
        } else {
            pinDIN_LAT = 0;
        }
        pinCLK_LAT = 1;
            __delay_us(1);
        pinCLK_LAT = 0;
    }
    pinLOAD_LAT = 1;
}

void max7219_WriteComando(unsigned char comando, unsigned char valorDeComando) {
    volatile unsigned int temporal = 0;
    temporal = comando;
    temporal = temporal << 8;
    temporal = temporal & 0x0F00;
    temporal = temporal | valorDeComando;
    max7219_WriteBits(temporal);
}

void max7219_Clear() {
    for (char i = 0; i < 8; i++) {
        max7219_WriteDigito(i, 0);
    }
}
#endif	/* MAX7219_H */