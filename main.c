#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>

#define RED PB1 // power-on LED
#define OUT PB2 // output pin
#define BUT PB3 // "start transmitting" button

#define BITS 271 // number of bits to transmit from data array

// current bit; doesn't need to be volatile, because it's being modified only in interrupts
uint16_t bit = 0;

const uint8_t data[34] PROGMEM = {
    0b00000000,
    0b10101010,
    0b10101010,
    0b10101010,
    0b00000000,
    0b01001001,
    0b00100100,
    0b11010010,
    0b01001001,
    0b10100100,
    0b10011010,
    0b01101101,
    0b00100110,
    0b10011010,
    0b01001101,
    0b00100100,
    0b10011010,
    0b01101001,
    0b10110110,
    0b10011010,
    0b01101101,
    0b10110100,
    0b11011011,
    0b01101101,
    0b10110110,
    0b11011010,
    0b01101101,
    0b10110100,
    0b11011010,
    0b01101000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};

int main() {
    DDRB |= _BV(OUT) | _BV(RED); // OUT and RED as outputs

    TCCR0A |= _BV(WGM01); // clear timer on compare match
    TIMSK |= _BV(OCIE0A); // enable timer interrupt

    // 2 kbps (CPU @ 1 MHz)
    TCCR0B |= _BV(CS01); // prescaler: 8
    OCR0A = 62; // timer counts to 62 instead of 255

    sei();

    PORTB |= _BV(RED); // source the RED LED

    while (1) {
        sleep_mode();
    }
}

ISR (TIMER0_COMPA_vect) {
    if (!(PINB & _BV(BUT))) { // don't transmit unless the button is pressed
        PORTB &= ~_BV(OUT);
        bit = 0;
    } else {
        if (pgm_read_byte(&(data[bit / 8])) & (0x80 >> bit % 8)) { // read bit from PROGMEM
            PORTB |= _BV(OUT);
        } else {
            PORTB &= ~_BV(OUT);
        }

        if (bit == BITS - 1) {
            bit = 0;
        } else {
            bit++;
        }
    }
}