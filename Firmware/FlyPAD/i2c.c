#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "app_ios_and_regs.h"

extern AppRegs app_regs;

#define _1_CLOCK_CYCLES asm ( "nop \n")
#define _2_CLOCK_CYCLES _1_CLOCK_CYCLES; _1_CLOCK_CYCLES
#define _4_CLOCK_CYCLES _2_CLOCK_CYCLES; _2_CLOCK_CYCLES
#define _8_CLOCK_CYCLES _4_CLOCK_CYCLES; _4_CLOCK_CYCLES
#define _16_CLOCK_CYCLES _8_CLOCK_CYCLES; _8_CLOCK_CYCLES
#define _32_CLOCK_CYCLES _16_CLOCK_CYCLES; _16_CLOCK_CYCLES
#define _48_CLOCK_CYCLES _32_CLOCK_CYCLES; _16_CLOCK_CYCLES 
#define _64_CLOCK_CYCLES _32_CLOCK_CYCLES; _32_CLOCK_CYCLES

void init_ios2()
{
    *((&PORTD.PIN0CTRL)+0) = (*((&PORTD.PIN0CTRL)+0) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+0) &= ~0x7;
    *((&PORTD.PIN0CTRL)+1) = (*((&PORTD.PIN0CTRL)+1) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+1) &= ~0x7;
    *((&PORTD.PIN0CTRL)+2) = (*((&PORTD.PIN0CTRL)+2) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+2) &= ~0x7;
    *((&PORTD.PIN0CTRL)+3) = (*((&PORTD.PIN0CTRL)+3) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+3) &= ~0x7;
    *((&PORTD.PIN0CTRL)+4) = (*((&PORTD.PIN0CTRL)+4) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+4) &= ~0x7;
    *((&PORTD.PIN0CTRL)+5) = (*((&PORTD.PIN0CTRL)+5) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+5) &= ~0x7;
    *((&PORTD.PIN0CTRL)+6) = (*((&PORTD.PIN0CTRL)+6) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+6) &= ~0x7;
    *((&PORTD.PIN0CTRL)+7) = (*((&PORTD.PIN0CTRL)+7) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTD.PIN0CTRL)+7) &= ~0x7;
    *((&PORTE.PIN0CTRL)+4) = (*((&PORTE.PIN0CTRL)+4) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTE.PIN0CTRL)+4) &= ~0x7;
    *((&PORTE.PIN0CTRL)+5) = (*((&PORTE.PIN0CTRL)+5) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTE.PIN0CTRL)+5) &= ~0x7;
    *((&PORTE.PIN0CTRL)+6) = (*((&PORTE.PIN0CTRL)+6) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTE.PIN0CTRL)+6) &= ~0x7;
    *((&PORTE.PIN0CTRL)+7) = (*((&PORTE.PIN0CTRL)+7) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTE.PIN0CTRL)+7) &= ~0x7;
    *((&PORTF.PIN0CTRL)+4) = (*((&PORTF.PIN0CTRL)+4) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTF.PIN0CTRL)+4) &= ~0x7;
    *((&PORTF.PIN0CTRL)+5) = (*((&PORTF.PIN0CTRL)+5) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTF.PIN0CTRL)+5) &= ~0x7;
    *((&PORTF.PIN0CTRL)+6) = (*((&PORTF.PIN0CTRL)+6) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTF.PIN0CTRL)+6) &= ~0x7;
    *((&PORTF.PIN0CTRL)+7) = (*((&PORTF.PIN0CTRL)+7) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTF.PIN0CTRL)+7) &= ~0x7;
    *((&PORTH.PIN0CTRL)+4) = (*((&PORTH.PIN0CTRL)+4) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTH.PIN0CTRL)+4) &= ~0x7;
    *((&PORTH.PIN0CTRL)+5) = (*((&PORTH.PIN0CTRL)+5) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTH.PIN0CTRL)+5) &= ~0x7;
    *((&PORTH.PIN0CTRL)+6) = (*((&PORTH.PIN0CTRL)+6) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTH.PIN0CTRL)+6) &= ~0x7;
    *((&PORTH.PIN0CTRL)+7) = (*((&PORTH.PIN0CTRL)+7) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTH.PIN0CTRL)+7) &= ~0x7;
    *((&PORTJ.PIN0CTRL)+0) = (*((&PORTJ.PIN0CTRL)+0) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTJ.PIN0CTRL)+0) &= ~0x7;
    *((&PORTJ.PIN0CTRL)+1) = (*((&PORTJ.PIN0CTRL)+1) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTJ.PIN0CTRL)+1) &= ~0x7;
    *((&PORTJ.PIN0CTRL)+2) = (*((&PORTJ.PIN0CTRL)+2) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTJ.PIN0CTRL)+2) &= ~0x7;
    *((&PORTJ.PIN0CTRL)+3) = (*((&PORTJ.PIN0CTRL)+3) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTJ.PIN0CTRL)+3) &= ~0x7;
    *((&PORTA.PIN0CTRL)+0) = (*((&PORTA.PIN0CTRL)+0) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTA.PIN0CTRL)+0) &= ~0x7;
    *((&PORTA.PIN0CTRL)+1) = (*((&PORTA.PIN0CTRL)+1) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTA.PIN0CTRL)+1) &= ~0x7;
    *((&PORTA.PIN0CTRL)+2) = (*((&PORTA.PIN0CTRL)+2) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTA.PIN0CTRL)+2) &= ~0x7;
    *((&PORTA.PIN0CTRL)+3) = (*((&PORTA.PIN0CTRL)+3) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTA.PIN0CTRL)+3) &= ~0x7;
    *((&PORTB.PIN0CTRL)+4) = (*((&PORTB.PIN0CTRL)+4) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTB.PIN0CTRL)+4) &= ~0x7;
    *((&PORTB.PIN0CTRL)+5) = (*((&PORTB.PIN0CTRL)+5) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTB.PIN0CTRL)+5) &= ~0x7;
    *((&PORTB.PIN0CTRL)+6) = (*((&PORTB.PIN0CTRL)+6) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTB.PIN0CTRL)+6) &= ~0x7;
    *((&PORTB.PIN0CTRL)+7) = (*((&PORTB.PIN0CTRL)+7) & 0xC0) | OUT_IO_DIGITAL | PULL_IO_TRISTATE | SENSE_IO_EDGES_BOTH;
    *((&PORTB.PIN0CTRL)+7) &= ~0x7;
}

void set_sda()
{
    PORTD.OUTSET = 0xFF;
    PORTE.OUTSET = 0xF0;
    PORTF.OUTSET = 0xF0;
    PORTH.OUTSET = 0xF0;
    PORTJ.OUTSET = 0x0F;
    PORTA.OUTSET = 0x0F;
    PORTB.OUTSET = 0xF0;
}

void clr_sda()
{
    PORTD.OUTCLR = 0xFF;
    PORTE.OUTCLR = 0xF0;
    PORTF.OUTCLR = 0xF0;
    PORTH.OUTCLR = 0xF0;
    PORTJ.OUTCLR = 0x0F;
    PORTA.OUTCLR = 0x0F;
    PORTB.OUTCLR = 0xF0;
}

void sda_to_out()
{
    PORTD.DIR |= 0xFF;
    PORTE.DIR |= 0xF0;
    PORTF.DIR |= 0xF0;
    PORTH.DIR |= 0xF0;
    PORTJ.DIR |= 0x0F;
    PORTA.DIR |= 0x0F;
    PORTB.DIR |= 0xF0;
}

void sda_to_in()
{
    PORTD.DIR &= ~0xFF;
    PORTE.DIR &= ~0xF0;
    PORTF.DIR &= ~0xF0;
    PORTH.DIR &= ~0xF0;
    PORTJ.DIR &= ~0x0F;
    PORTA.DIR &= ~0x0F;
    PORTB.DIR &= ~0xF0;
}

void write_byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if ((byte << i) & 0x80) {
			set_sda();
		}
		else {
            clr_sda();
		}
		
		set_SCL;
		_32_CLOCK_CYCLES; // ~1us (spec 0.6us)
		clr_SCL;
		_48_CLOCK_CYCLES; // set/clr_SDA takes around ~1.5us - add 250ns margin (spec 1.3us)
	}
}

uint8_t bytes_d[32];
uint8_t bytes_e[32];
uint8_t bytes_f[32];
uint8_t bytes_h[32];
uint8_t bytes_j[32];
uint8_t bytes_a[32];
uint8_t bytes_b[32];

void read_byte(uint8_t index)
{
    uint8_t *arr_d = &bytes_d[index];
    uint8_t *arr_e = &bytes_e[index];
    uint8_t *arr_f = &bytes_f[index];
    uint8_t *arr_h = &bytes_h[index];
    uint8_t *arr_j = &bytes_j[index];
    uint8_t *arr_a = &bytes_a[index];
    uint8_t *arr_b = &bytes_b[index];
    
	for (uint8_t i = 0; i < 8; i++)
	{
		set_SCL;
        arr_d[i] = PORTD.IN;
        arr_e[i] = PORTE.IN;
        arr_f[i] = PORTF.IN;
        arr_h[i] = PORTH.IN;
        arr_j[i] = PORTJ.IN;
        arr_a[i] = PORTA.IN;
        arr_b[i] = PORTB.IN;
		clr_SCL;
		_48_CLOCK_CYCLES;

	}
}

void read_capacitance()
{
	// Start condition
    set_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_sda();
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Address AD7150 to write
	write_byte(0x90);
	
    // In theory, acknowledge bit should be read, but in practice we are just controlling the serial clock
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Write register from where we want to start the readings
	write_byte(0x01);

    // New fake acknowledge bit reading
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // New start condition, now for reading values
    set_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_sda();
	clr_SCL;
    _48_CLOCK_CYCLES;
	 
    // Address AD7150 to read
    write_byte(0x91);

    // New fake acknowledge bit reading
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Prepare to read byte
    sda_to_in();

    // Read first most significant byte of capacitance for channel 0
	read_byte(0);

    // Prepare to send acknowledge bit
    sda_to_out();

    // Send acknowledge bit
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Prepare to read byte
    sda_to_in();

    // Read first least significant byte of capacitance for channel 0
	read_byte(8);

    // Prepare to send acknowledge bit
    sda_to_out();

    // Send acknowledge bit
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Prepare to read byte
    sda_to_in();

    // Read first most significant byte of capacitance for channel 1
    read_byte(16);

    // Prepare to send acknowledge bit
    sda_to_out();

    // Send acknowledge bit
    clr_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	_48_CLOCK_CYCLES;

    // Prepare to read byte
    sda_to_in();

    // Read first least significant byte of capacitance for channel 1
    read_byte(24);

    // Prepare to send acknowledge bit
    sda_to_out();

    // Send not-acknowledge bit
    set_sda();
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
    clr_sda();
	_48_CLOCK_CYCLES;

    // Stop condition
	set_SCL;
    set_sda();
	_32_CLOCK_CYCLES;
	clr_SCL;
	clr_sda();
}


/*
    DISCLAIMER: the way the capacitances are calculated is suboptimal, but 
    calculating them in the same function makes execution time increase beyond 
    the harp core allowed timeout limit
*/
void calculate_capacitance_1()
{
    for (uint8_t i = 0; i < 8; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[0] |= (uint16_t)((bytes_d[i] >> 0) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[2] |= (uint16_t)((bytes_d[i] >> 1) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[4] |= (uint16_t)((bytes_d[i] >> 2) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[6] |= (uint16_t)((bytes_d[i] >> 3) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_d[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[0] |= (uint16_t)((bytes[i] >> 0) & 0x01) << (15 - i);
        reg[2] |= (uint16_t)((bytes[i] >> 1) & 0x01) << (15 - i);
        reg[4] |= (uint16_t)((bytes[i] >> 2) & 0x01) << (15 - i);
        reg[6] |= (uint16_t)((bytes[i] >> 3) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_2()
{
    for (uint8_t i = 8; i < 16; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[8] |= (uint16_t)((bytes_d[i] >> 4) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[10] |= (uint16_t)((bytes_d[i] >> 5) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[12] |= (uint16_t)((bytes_d[i] >> 6) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[14] |= (uint16_t)((bytes_d[i] >> 7) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_d[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[8] |= (uint16_t)((bytes[i] >> 4) & 0x01) << (15 - i);
        reg[10] |= (uint16_t)((bytes[i] >> 5) & 0x01) << (15 - i);
        reg[12] |= (uint16_t)((bytes[i] >> 6) & 0x01) << (15 - i);
        reg[14] |= (uint16_t)((bytes[i] >> 7) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_3()
{
    for (uint8_t i = 16; i < 24; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[16] |= (uint16_t)((bytes_e[i] >> 4) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[18] |= (uint16_t)((bytes_e[i] >> 5) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[20] |= (uint16_t)((bytes_e[i] >> 6) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[22] |= (uint16_t)((bytes_e[i] >> 7) & 0x01) << (15 - i);
    }

    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_e[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[16] |= (uint16_t)((bytes[i] >> 4) & 0x01) << (15 - i);
        reg[18] |= (uint16_t)((bytes[i] >> 5) & 0x01) << (15 - i);
        reg[20] |= (uint16_t)((bytes[i] >> 6) & 0x01) << (15 - i);
        reg[22] |= (uint16_t)((bytes[i] >> 7) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_4()
{
    for (uint8_t i = 24; i < 32; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[24] |= (uint16_t)((bytes_f[i] >> 4) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[26] |= (uint16_t)((bytes_f[i] >> 5) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[28] |= (uint16_t)((bytes_f[i] >> 6) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[30] |= (uint16_t)((bytes_f[i] >> 7) & 0x01) << (15 - i);
    }


    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_f[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[24] |= (uint16_t)((bytes[i] >> 4) & 0x01) << (15 - i);
        reg[26] |= (uint16_t)((bytes[i] >> 5) & 0x01) << (15 - i);
        reg[28] |= (uint16_t)((bytes[i] >> 6) & 0x01) << (15 - i);
        reg[30] |= (uint16_t)((bytes[i] >> 7) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_5()
{
    for (uint8_t i = 32; i < 40; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[32] |= (uint16_t)((bytes_h[i] >> 4) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[34] |= (uint16_t)((bytes_h[i] >> 5) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[36] |= (uint16_t)((bytes_h[i] >> 6) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[38] |= (uint16_t)((bytes_h[i] >> 7) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_h[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[32] |= (uint16_t)((bytes[i] >> 4) & 0x01) << (15 - i);
        reg[34] |= (uint16_t)((bytes[i] >> 5) & 0x01) << (15 - i);
        reg[36] |= (uint16_t)((bytes[i] >> 6) & 0x01) << (15 - i);
        reg[38] |= (uint16_t)((bytes[i] >> 7) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_6()
{
    for (uint8_t i = 40; i < 48; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[40] |= (uint16_t)((bytes_j[i] >> 0) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[42] |= (uint16_t)((bytes_j[i] >> 1) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[44] |= (uint16_t)((bytes_j[i] >> 2) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[46] |= (uint16_t)((bytes_j[i] >> 3) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_j[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[40] |= (uint16_t)((bytes[i] >> 0) & 0x01) << (15 - i);
        reg[42] |= (uint16_t)((bytes[i] >> 1) & 0x01) << (15 - i);
        reg[44] |= (uint16_t)((bytes[i] >> 2) & 0x01) << (15 - i);
        reg[46] |= (uint16_t)((bytes[i] >> 3) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_7()
{
    for (uint8_t i = 48; i < 56; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[48] |= (uint16_t)((bytes_a[i] >> 0) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[50] |= (uint16_t)((bytes_a[i] >> 1) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[52] |= (uint16_t)((bytes_a[i] >> 2) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[54] |= (uint16_t)((bytes_a[i] >> 3) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_a[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[48] |= (uint16_t)((bytes[i] >> 0) & 0x01) << (15 - i);
        reg[50] |= (uint16_t)((bytes[i] >> 1) & 0x01) << (15 - i);
        reg[52] |= (uint16_t)((bytes[i] >> 2) & 0x01) << (15 - i);
        reg[54] |= (uint16_t)((bytes[i] >> 3) & 0x01) << (15 - i);
    }
}

void calculate_capacitance_8()
{
    for (uint8_t i = 56; i < 64; i++) {
        app_regs.REG_CAPACITANCE_VALUES[i] = 0;
    }

    for (uint8_t i = 0; i < 16; i++)
	{
        app_regs.REG_CAPACITANCE_VALUES[56] |= (uint16_t)((bytes_b[i] >> 4) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[58] |= (uint16_t)((bytes_b[i] >> 5) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[60] |= (uint16_t)((bytes_b[i] >> 6) & 0x01) << (15 - i);
        app_regs.REG_CAPACITANCE_VALUES[62] |= (uint16_t)((bytes_b[i] >> 7) & 0x01) << (15 - i);
    }

    // Second channel
    uint16_t *reg = &app_regs.REG_CAPACITANCE_VALUES[1];
    uint8_t *bytes = &bytes_b[16];
    for (uint8_t i = 0; i < 16; i++)
	{
        reg[56] |= (uint16_t)((bytes[i] >> 4) & 0x01) << (15 - i);
        reg[58] |= (uint16_t)((bytes[i] >> 5) & 0x01) << (15 - i);
        reg[60] |= (uint16_t)((bytes[i] >> 6) & 0x01) << (15 - i);
        reg[62] |= (uint16_t)((bytes[i] >> 7) & 0x01) << (15 - i);
    }
}