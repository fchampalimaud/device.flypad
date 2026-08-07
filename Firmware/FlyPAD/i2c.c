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
 * Full 8x8 bit-matrix transpose: out[col] bit (7-row) = in[row] bit col.
 * Row 0 becomes the MSB of every output byte, matching the MSB-first order
 * the AD7150 clocks bits out in.
 *
 * Inline asm because the algorithm needs the same hardware Carry flag
 * shared between two independent shifts (LSL on the row register, ROL on
 * the column accumulator) each step. C has no "reuse this shift's carry in
 * that other variable's shift" construct, so avr-gcc cannot generate this
 * from a portable C loop -- each of the 64 output bits costs exactly one
 * LSL + one ROL (2 single-cycle instructions) done this way.
 */
static void transpose8x8(const uint8_t *in, uint8_t *out)
{
    uint8_t r0,r1,r2,r3,r4,r5,r6,r7;
    uint8_t c0,c1,c2,c3,c4,c5,c6,c7;

    asm volatile(
        "ld  %[r0], %a[inp]+ \n\t"
        "ld  %[r1], %a[inp]+ \n\t"
        "ld  %[r2], %a[inp]+ \n\t"
        "ld  %[r3], %a[inp]+ \n\t"
        "ld  %[r4], %a[inp]+ \n\t"
        "ld  %[r5], %a[inp]+ \n\t"
        "ld  %[r6], %a[inp]+ \n\t"
        "ld  %[r7], %a[inp]  \n\t"

        "clr %[c0] \n\t clr %[c1] \n\t clr %[c2] \n\t clr %[c3] \n\t"
        "clr %[c4] \n\t clr %[c5] \n\t clr %[c6] \n\t clr %[c7] \n\t"

        "lsl %[r0] \n\t rol %[c7] \n\t  lsl %[r0] \n\t rol %[c6] \n\t"
        "lsl %[r0] \n\t rol %[c5] \n\t  lsl %[r0] \n\t rol %[c4] \n\t"
        "lsl %[r0] \n\t rol %[c3] \n\t  lsl %[r0] \n\t rol %[c2] \n\t"
        "lsl %[r0] \n\t rol %[c1] \n\t  lsl %[r0] \n\t rol %[c0] \n\t"

        "lsl %[r1] \n\t rol %[c7] \n\t  lsl %[r1] \n\t rol %[c6] \n\t"
        "lsl %[r1] \n\t rol %[c5] \n\t  lsl %[r1] \n\t rol %[c4] \n\t"
        "lsl %[r1] \n\t rol %[c3] \n\t  lsl %[r1] \n\t rol %[c2] \n\t"
        "lsl %[r1] \n\t rol %[c1] \n\t  lsl %[r1] \n\t rol %[c0] \n\t"

        "lsl %[r2] \n\t rol %[c7] \n\t  lsl %[r2] \n\t rol %[c6] \n\t"
        "lsl %[r2] \n\t rol %[c5] \n\t  lsl %[r2] \n\t rol %[c4] \n\t"
        "lsl %[r2] \n\t rol %[c3] \n\t  lsl %[r2] \n\t rol %[c2] \n\t"
        "lsl %[r2] \n\t rol %[c1] \n\t  lsl %[r2] \n\t rol %[c0] \n\t"

        "lsl %[r3] \n\t rol %[c7] \n\t  lsl %[r3] \n\t rol %[c6] \n\t"
        "lsl %[r3] \n\t rol %[c5] \n\t  lsl %[r3] \n\t rol %[c4] \n\t"
        "lsl %[r3] \n\t rol %[c3] \n\t  lsl %[r3] \n\t rol %[c2] \n\t"
        "lsl %[r3] \n\t rol %[c1] \n\t  lsl %[r3] \n\t rol %[c0] \n\t"

        "lsl %[r4] \n\t rol %[c7] \n\t  lsl %[r4] \n\t rol %[c6] \n\t"
        "lsl %[r4] \n\t rol %[c5] \n\t  lsl %[r4] \n\t rol %[c4] \n\t"
        "lsl %[r4] \n\t rol %[c3] \n\t  lsl %[r4] \n\t rol %[c2] \n\t"
        "lsl %[r4] \n\t rol %[c1] \n\t  lsl %[r4] \n\t rol %[c0] \n\t"

        "lsl %[r5] \n\t rol %[c7] \n\t  lsl %[r5] \n\t rol %[c6] \n\t"
        "lsl %[r5] \n\t rol %[c5] \n\t  lsl %[r5] \n\t rol %[c4] \n\t"
        "lsl %[r5] \n\t rol %[c3] \n\t  lsl %[r5] \n\t rol %[c2] \n\t"
        "lsl %[r5] \n\t rol %[c1] \n\t  lsl %[r5] \n\t rol %[c0] \n\t"

        "lsl %[r6] \n\t rol %[c7] \n\t  lsl %[r6] \n\t rol %[c6] \n\t"
        "lsl %[r6] \n\t rol %[c5] \n\t  lsl %[r6] \n\t rol %[c4] \n\t"
        "lsl %[r6] \n\t rol %[c3] \n\t  lsl %[r6] \n\t rol %[c2] \n\t"
        "lsl %[r6] \n\t rol %[c1] \n\t  lsl %[r6] \n\t rol %[c0] \n\t"

        "lsl %[r7] \n\t rol %[c7] \n\t  lsl %[r7] \n\t rol %[c6] \n\t"
        "lsl %[r7] \n\t rol %[c5] \n\t  lsl %[r7] \n\t rol %[c4] \n\t"
        "lsl %[r7] \n\t rol %[c3] \n\t  lsl %[r7] \n\t rol %[c2] \n\t"
        "lsl %[r7] \n\t rol %[c1] \n\t  lsl %[r7] \n\t rol %[c0] \n\t"

        : [r0] "=&r" (r0), [r1] "=&r" (r1), [r2] "=&r" (r2), [r3] "=&r" (r3),
          [r4] "=&r" (r4), [r5] "=&r" (r5), [r6] "=&r" (r6), [r7] "=&r" (r7),
          [c0] "=&r" (c0), [c1] "=&r" (c1), [c2] "=&r" (c2), [c3] "=&r" (c3),
          [c4] "=&r" (c4), [c5] "=&r" (c5), [c6] "=&r" (c6), [c7] "=&r" (c7),
          [inp] "+e" (in)
        :
        : "cc", "memory"
    );

    out[0]=c0; out[1]=c1; out[2]=c2; out[3]=c3;
    out[4]=c4; out[5]=c5; out[6]=c6; out[7]=c7;
}


/*
    DISCLAIMER: the way the capacitances are calculated is suboptimal, but 
    calculating them in the same function makes execution time increase beyond 
    the harp core allowed timeout limit
*/
// ~110us
/*void calculate_capacitance_1()
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
}*/

// ~100us
/*void calculate_capacitance_1()
{
	uint16_t c0 = 0, c2 = 0, c4 = 0, c6 = 0;
	for (uint8_t i = 0; i < 16; i++) {
		uint8_t b = bytes_d[i];
		c0 = (c0 << 1) | ((b >> 0) & 0x01);
		c2 = (c2 << 1) | ((b >> 1) & 0x01);
		c4 = (c4 << 1) | ((b >> 2) & 0x01);
		c6 = (c6 << 1) | ((b >> 3) & 0x01);
	}

	uint16_t c1 = 0, c3 = 0, c5 = 0, c7 = 0;
	for (uint8_t i = 0; i < 16; i++) {
		uint8_t b = bytes_d[16 + i];
		c1 = (c1 << 1) | ((b >> 0) & 0x01);
		c3 = (c3 << 1) | ((b >> 1) & 0x01);
		c5 = (c5 << 1) | ((b >> 2) & 0x01);
		c7 = (c7 << 1) | ((b >> 3) & 0x01);
	}

	app_regs.REG_CAPACITANCE_VALUES[0] = c0;
	app_regs.REG_CAPACITANCE_VALUES[2] = c2;
	app_regs.REG_CAPACITANCE_VALUES[4] = c4;
	app_regs.REG_CAPACITANCE_VALUES[6] = c6;
	app_regs.REG_CAPACITANCE_VALUES[1] = c1;
	app_regs.REG_CAPACITANCE_VALUES[3] = c3;
	app_regs.REG_CAPACITANCE_VALUES[5] = c5;
	app_regs.REG_CAPACITANCE_VALUES[7] = c7;
}*/

// 25us
void calculate_capacitance_1()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_d[0],  hi0);
	transpose8x8(&bytes_d[8],  lo0);
	transpose8x8(&bytes_d[16], hi1);
	transpose8x8(&bytes_d[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[0] = ((uint16_t)hi0[0] << 8) | lo0[0];
	app_regs.REG_CAPACITANCE_VALUES[2] = ((uint16_t)hi0[1] << 8) | lo0[1];
	app_regs.REG_CAPACITANCE_VALUES[4] = ((uint16_t)hi0[2] << 8) | lo0[2];
	app_regs.REG_CAPACITANCE_VALUES[6] = ((uint16_t)hi0[3] << 8) | lo0[3];
	app_regs.REG_CAPACITANCE_VALUES[1] = ((uint16_t)hi1[0] << 8) | lo1[0];
	app_regs.REG_CAPACITANCE_VALUES[3] = ((uint16_t)hi1[1] << 8) | lo1[1];
	app_regs.REG_CAPACITANCE_VALUES[5] = ((uint16_t)hi1[2] << 8) | lo1[2];
	app_regs.REG_CAPACITANCE_VALUES[7] = ((uint16_t)hi1[3] << 8) | lo1[3];
}

void calculate_capacitance_2()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_d[0],  hi0);
	transpose8x8(&bytes_d[8],  lo0);
	transpose8x8(&bytes_d[16], hi1);
	transpose8x8(&bytes_d[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[8]  = ((uint16_t)hi0[4] << 8) | lo0[4];
	app_regs.REG_CAPACITANCE_VALUES[10] = ((uint16_t)hi0[5] << 8) | lo0[5];
	app_regs.REG_CAPACITANCE_VALUES[12] = ((uint16_t)hi0[6] << 8) | lo0[6];
	app_regs.REG_CAPACITANCE_VALUES[14] = ((uint16_t)hi0[7] << 8) | lo0[7];
	app_regs.REG_CAPACITANCE_VALUES[9]  = ((uint16_t)hi1[4] << 8) | lo1[4];
	app_regs.REG_CAPACITANCE_VALUES[11] = ((uint16_t)hi1[5] << 8) | lo1[5];
	app_regs.REG_CAPACITANCE_VALUES[13] = ((uint16_t)hi1[6] << 8) | lo1[6];
	app_regs.REG_CAPACITANCE_VALUES[15] = ((uint16_t)hi1[7] << 8) | lo1[7];
}

void calculate_capacitance_3()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_e[0],  hi0);
	transpose8x8(&bytes_e[8],  lo0);
	transpose8x8(&bytes_e[16], hi1);
	transpose8x8(&bytes_e[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[16] = ((uint16_t)hi0[4] << 8) | lo0[4];
	app_regs.REG_CAPACITANCE_VALUES[18] = ((uint16_t)hi0[5] << 8) | lo0[5];
	app_regs.REG_CAPACITANCE_VALUES[20] = ((uint16_t)hi0[6] << 8) | lo0[6];
	app_regs.REG_CAPACITANCE_VALUES[22] = ((uint16_t)hi0[7] << 8) | lo0[7];
	app_regs.REG_CAPACITANCE_VALUES[17] = ((uint16_t)hi1[4] << 8) | lo1[4];
	app_regs.REG_CAPACITANCE_VALUES[19] = ((uint16_t)hi1[5] << 8) | lo1[5];
	app_regs.REG_CAPACITANCE_VALUES[21] = ((uint16_t)hi1[6] << 8) | lo1[6];
	app_regs.REG_CAPACITANCE_VALUES[23] = ((uint16_t)hi1[7] << 8) | lo1[7];
}

void calculate_capacitance_4()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_f[0],  hi0);
	transpose8x8(&bytes_f[8],  lo0);
	transpose8x8(&bytes_f[16], hi1);
	transpose8x8(&bytes_f[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[24] = ((uint16_t)hi0[4] << 8) | lo0[4];
	app_regs.REG_CAPACITANCE_VALUES[26] = ((uint16_t)hi0[5] << 8) | lo0[5];
	app_regs.REG_CAPACITANCE_VALUES[28] = ((uint16_t)hi0[6] << 8) | lo0[6];
	app_regs.REG_CAPACITANCE_VALUES[30] = ((uint16_t)hi0[7] << 8) | lo0[7];
	app_regs.REG_CAPACITANCE_VALUES[25] = ((uint16_t)hi1[4] << 8) | lo1[4];
	app_regs.REG_CAPACITANCE_VALUES[27] = ((uint16_t)hi1[5] << 8) | lo1[5];
	app_regs.REG_CAPACITANCE_VALUES[29] = ((uint16_t)hi1[6] << 8) | lo1[6];
	app_regs.REG_CAPACITANCE_VALUES[31] = ((uint16_t)hi1[7] << 8) | lo1[7];
}

void calculate_capacitance_5()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_h[0],  hi0);
	transpose8x8(&bytes_h[8],  lo0);
	transpose8x8(&bytes_h[16], hi1);
	transpose8x8(&bytes_h[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[32] = ((uint16_t)hi0[4] << 8) | lo0[4];
	app_regs.REG_CAPACITANCE_VALUES[34] = ((uint16_t)hi0[5] << 8) | lo0[5];
	app_regs.REG_CAPACITANCE_VALUES[36] = ((uint16_t)hi0[6] << 8) | lo0[6];
	app_regs.REG_CAPACITANCE_VALUES[38] = ((uint16_t)hi0[7] << 8) | lo0[7];
	app_regs.REG_CAPACITANCE_VALUES[33] = ((uint16_t)hi1[4] << 8) | lo1[4];
	app_regs.REG_CAPACITANCE_VALUES[35] = ((uint16_t)hi1[5] << 8) | lo1[5];
	app_regs.REG_CAPACITANCE_VALUES[37] = ((uint16_t)hi1[6] << 8) | lo1[6];
	app_regs.REG_CAPACITANCE_VALUES[39] = ((uint16_t)hi1[7] << 8) | lo1[7];
}

void calculate_capacitance_6()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_j[0],  hi0);
	transpose8x8(&bytes_j[8],  lo0);
	transpose8x8(&bytes_j[16], hi1);
	transpose8x8(&bytes_j[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[40] = ((uint16_t)hi0[0] << 8) | lo0[0];
	app_regs.REG_CAPACITANCE_VALUES[42] = ((uint16_t)hi0[1] << 8) | lo0[1];
	app_regs.REG_CAPACITANCE_VALUES[44] = ((uint16_t)hi0[2] << 8) | lo0[2];
	app_regs.REG_CAPACITANCE_VALUES[46] = ((uint16_t)hi0[3] << 8) | lo0[3];
	app_regs.REG_CAPACITANCE_VALUES[41] = ((uint16_t)hi1[0] << 8) | lo1[0];
	app_regs.REG_CAPACITANCE_VALUES[43] = ((uint16_t)hi1[1] << 8) | lo1[1];
	app_regs.REG_CAPACITANCE_VALUES[45] = ((uint16_t)hi1[2] << 8) | lo1[2];
	app_regs.REG_CAPACITANCE_VALUES[47] = ((uint16_t)hi1[3] << 8) | lo1[3];
}

void calculate_capacitance_7()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_a[0],  hi0);
	transpose8x8(&bytes_a[8],  lo0);
	transpose8x8(&bytes_a[16], hi1);
	transpose8x8(&bytes_a[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[48] = ((uint16_t)hi0[0] << 8) | lo0[0];
	app_regs.REG_CAPACITANCE_VALUES[50] = ((uint16_t)hi0[1] << 8) | lo0[1];
	app_regs.REG_CAPACITANCE_VALUES[52] = ((uint16_t)hi0[2] << 8) | lo0[2];
	app_regs.REG_CAPACITANCE_VALUES[54] = ((uint16_t)hi0[3] << 8) | lo0[3];
	app_regs.REG_CAPACITANCE_VALUES[49] = ((uint16_t)hi1[0] << 8) | lo1[0];
	app_regs.REG_CAPACITANCE_VALUES[51] = ((uint16_t)hi1[1] << 8) | lo1[1];
	app_regs.REG_CAPACITANCE_VALUES[53] = ((uint16_t)hi1[2] << 8) | lo1[2];
	app_regs.REG_CAPACITANCE_VALUES[55] = ((uint16_t)hi1[3] << 8) | lo1[3];
}

void calculate_capacitance_8()
{
	uint8_t hi0[8], lo0[8], hi1[8], lo1[8];
	transpose8x8(&bytes_b[0],  hi0);
	transpose8x8(&bytes_b[8],  lo0);
	transpose8x8(&bytes_b[16], hi1);
	transpose8x8(&bytes_b[24], lo1);

	app_regs.REG_CAPACITANCE_VALUES[56] = ((uint16_t)hi0[4] << 8) | lo0[4];
	app_regs.REG_CAPACITANCE_VALUES[58] = ((uint16_t)hi0[5] << 8) | lo0[5];
	app_regs.REG_CAPACITANCE_VALUES[60] = ((uint16_t)hi0[6] << 8) | lo0[6];
	app_regs.REG_CAPACITANCE_VALUES[62] = ((uint16_t)hi0[7] << 8) | lo0[7];
	app_regs.REG_CAPACITANCE_VALUES[57] = ((uint16_t)hi1[4] << 8) | lo1[4];
	app_regs.REG_CAPACITANCE_VALUES[59] = ((uint16_t)hi1[5] << 8) | lo1[5];
	app_regs.REG_CAPACITANCE_VALUES[61] = ((uint16_t)hi1[6] << 8) | lo1[6];
	app_regs.REG_CAPACITANCE_VALUES[63] = ((uint16_t)hi1[7] << 8) | lo1[7];
}

/*

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
}*/