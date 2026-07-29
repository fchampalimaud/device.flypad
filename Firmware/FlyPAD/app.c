#include "hwbp_core.h"
#include "hwbp_core_regs.h"
#include "hwbp_core_types.h"

#include "app.h"
#include "app_funcs.h"
#include "app_ios_and_regs.h"

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;
extern uint8_t app_regs_type[];
extern uint16_t app_regs_n_elements[];
extern uint8_t *app_regs_pointer[];
extern void (*app_func_rd_pointer[])(void);
extern bool (*app_func_wr_pointer[])(void*);

#define _1_CLOCK_CYCLES asm ( "nop \n")
#define _2_CLOCK_CYCLES _1_CLOCK_CYCLES; _1_CLOCK_CYCLES
#define _4_CLOCK_CYCLES _2_CLOCK_CYCLES; _2_CLOCK_CYCLES
#define _8_CLOCK_CYCLES _4_CLOCK_CYCLES; _4_CLOCK_CYCLES
#define _16_CLOCK_CYCLES _8_CLOCK_CYCLES; _8_CLOCK_CYCLES
#define _32_CLOCK_CYCLES _16_CLOCK_CYCLES; _16_CLOCK_CYCLES
#define _64_CLOCK_CYCLES _32_CLOCK_CYCLES; _32_CLOCK_CYCLES
#define _128_CLOCK_CYCLES _64_CLOCK_CYCLES; _64_CLOCK_CYCLES

/************************************************************************/
/* Initialize app                                                       */
/************************************************************************/
static const uint8_t default_device_name[] = DEVICE_NAME;

void hwbp_app_initialize(void)
{   
   	/* Start core */
   	core_func_start_core_V2(
   	    WHO_AM_I,
   	    MAJOR_HW_VERSION, MINOR_HW_VERSION, PATCH_HW_VERSION,
   	    MAJOR_FW_VERSION, MINOR_FW_VERSION, PATCH_FW_VERSION,
   	    (uint8_t*)(&app_regs),
   	    APP_NBYTES_OF_REG_BANK,
   	    APP_REGS_ADD_MAX - APP_REGS_ADD_MIN + 1,
   	    default_device_name,
   	    false,	// The device is _not_ able to repeat the harp timestamp clock
   	    false,	// The device is _not_ able to generate the harp timestamp clock
   	    0		// Default timestamp offset
   	);
}

/************************************************************************/
/* Handle if a catastrophic error occur                                 */
/************************************************************************/
void core_callback_catastrophic_error_detected(void)
{
	
}

/************************************************************************/
/* User functions                                                       */
/************************************************************************/
void read_capacitance()
{
	uint16_t ch1 = 0;
	uint16_t ch2 = 0;
	uint16_t ch3 = 0;
	uint16_t ch4 = 0;
	
	
	// Start condition
	set_SDA11;
	set_SDA12;
	set_SDA13;
	set_SDA14;
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	clr_SCL;
	
	uint8_t device_address = 0x90;
	// _8_CLOCK_CYCLES;
	for (uint8_t i = 0; i < 8; i++) 
	{
		if ((device_address<<i) & 0x80) {
			set_SDA11;
			set_SDA12;
			set_SDA13;
			set_SDA14;
		}
		else {
			clr_SDA11;
			clr_SDA12;
			clr_SDA13;
			clr_SDA14;
		}
		set_SCL;
		_32_CLOCK_CYCLES;
		clr_SCL;
		_8_CLOCK_CYCLES;
	}

	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
    // io_pin2in(&PORTD, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 1, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 2, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 3, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
	set_SCL;
	_32_CLOCK_CYCLES;
	// read_SDA11; // Read acknowledge bit
	// read_SDA12; // Read acknowledge bit
	// read_SDA13; // Read acknowledge bit
	// read_SDA14; // Read acknowledge bit
	clr_SCL;
	// io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);

	uint8_t command_byte = 0x01; // CH1 MSB
	
	_8_CLOCK_CYCLES;
	for (uint8_t i = 0; i < 8; i++) 
	{
		if ((command_byte<<i) & 0x80) {
			set_SDA11;
			set_SDA12;
			set_SDA13;
			set_SDA14;
		}
		else {
			clr_SDA11;
			clr_SDA12;
			clr_SDA13;
			clr_SDA14;
		}
		set_SCL;
		_32_CLOCK_CYCLES;
		clr_SCL;
		_8_CLOCK_CYCLES;
	}
	
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	// io_pin2in(&PORTD, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 1, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 2, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    // io_pin2in(&PORTD, 3, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
	set_SCL;
	_32_CLOCK_CYCLES;
	// read_SDA11; // Read acknowledge bit
	// read_SDA12; // Read acknowledge bit
	// read_SDA13; // Read acknowledge bit
	// read_SDA14; // Read acknowledge bit
	clr_SCL;
	// io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);
    // io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);
	
	// Start condition
	_8_CLOCK_CYCLES;
	set_SDA11;
	set_SDA12;
	set_SDA13;
	set_SDA14;
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	clr_SCL;
	
	device_address = 0x91;
	
	_8_CLOCK_CYCLES;
	for (uint8_t i = 0; i < 8; i++) 
	{
		if ((device_address<<i) & 0x80) {
			set_SDA11;
			set_SDA12;
			set_SDA13;
			set_SDA14;
		}
		else {
			clr_SDA11;
			clr_SDA12;
			clr_SDA13;
			clr_SDA14;
		}
		set_SCL;
		_32_CLOCK_CYCLES;
		clr_SCL;
		_8_CLOCK_CYCLES;
	}
	
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	set_SCL;
	_32_CLOCK_CYCLES;
	// read_SDA11; // Read acknowledge bit
	// read_SDA12; // Read acknowledge bit
	// read_SDA13; // Read acknowledge bit
	// read_SDA14; // Read acknowledge bit
	clr_SCL;

	io_pin2in(&PORTD, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 1, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 2, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 3, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
	
	// _8_CLOCK_CYCLES;
	for (uint8_t i = 8; i > 0; i--) // read register 
	{
		set_SCL;
		ch1 = (read_SDA11 << (i-1 + 8)) | ch1;
		ch2 = (read_SDA12 << (i-2 + 8)) | ch2;
		ch3 = (read_SDA13 << (i-3 + 8)) | ch3;
		ch4 = (read_SDA14 << (i-4 + 8)) | ch4;
		_1_CLOCK_CYCLES;
		clr_SCL;
		_16_CLOCK_CYCLES;
	}

	io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);
		
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;

	io_pin2in(&PORTD, 0, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 1, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 2, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
    io_pin2in(&PORTD, 3, PULL_IO_UP, SENSE_IO_EDGES_BOTH);
	
	// _8_CLOCK_CYCLES;
	for (uint8_t i = 8; i > 0; i--) // read register 
	{
		set_SCL;
		ch1 = (read_SDA11 << (i-1)) | ch1;
		ch2 = (read_SDA12 << (i-2)) | ch2;
		ch3 = (read_SDA13 << (i-3)) | ch3;
		ch4 = (read_SDA14 << (i-4)) | ch4;
		// _4_CLOCK_CYCLES;
		clr_SCL;
		_16_CLOCK_CYCLES;
	}

	io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);
    io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);

	set_SDA11;
	set_SDA12;
	set_SDA13;
	set_SDA14;
	set_SCL;
	_32_CLOCK_CYCLES;
	clr_SCL;
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;
	
	_32_CLOCK_CYCLES;
	set_SCL;
	set_SDA11; 
	set_SDA12; 
	set_SDA13; 
	set_SDA14; 
	_32_CLOCK_CYCLES;
	clr_SCL;
	clr_SDA11;
	clr_SDA12;
	clr_SDA13;
	clr_SDA14;

	app_regs.REG_CAPACITANCE_VALUES[0] = ch1;
	app_regs.REG_CAPACITANCE_VALUES[2] = ch2;
	app_regs.REG_CAPACITANCE_VALUES[4] = ch3;
	app_regs.REG_CAPACITANCE_VALUES[6] = ch4;

	if (app_regs.REG_CAPACITANCE_VALUES[3] == 0) {
		app_regs.REG_CAPACITANCE_VALUES[3] = 1;
	} else {
		app_regs.REG_CAPACITANCE_VALUES[3] = 0;
	}
}

/************************************************************************/
/* Initialization Callbacks                                             */
/************************************************************************/
void core_callback_define_clock_default(void) {}
void core_callback_initialize_hardware(void)
{
	/* Initialize IOs */
	/* Don't delete this function!!! */
	init_ios();
	
	/* Initialize hardware */
	
}

void core_callback_reset_registers(void)
{
	/* Initialize registers */
	
}

void core_callback_registers_were_reinitialized(void)
{
	/* Update registers if needed */
	
}

/************************************************************************/
/* Callbacks: Visualization                                             */
/************************************************************************/
void core_callback_visualen_to_on(void) {}
void core_callback_visualen_to_off(void) {}

/************************************************************************/
/* Callbacks: Change to the operation mode                              */
/************************************************************************/
void core_callback_device_to_standby(void) {}
void core_callback_device_to_active(void) {}
void core_callback_device_to_enchanced_active(void) {}
void core_callback_device_to_speed(void) {}

/************************************************************************/
/* Callbacks: 1 ms timer                                                */
/************************************************************************/
void core_callback_t_before_exec(void) {}
void core_callback_t_after_exec(void) {}
void core_callback_t_new_second(void) {}
void core_callback_t_500us(void) {}
void core_callback_t_1ms(void) {
	read_capacitance();
}

/************************************************************************/
/* Callbacks: clock control                                             */
/************************************************************************/
void core_callback_clock_to_repeater(void) {}
void core_callback_clock_to_generator(void) {}
void core_callback_clock_to_unlock(void) {}
void core_callback_clock_to_lock(void) {}

/************************************************************************/
/* Callbacks: uart control                                              */
/************************************************************************/
void core_callback_uart_rx_before_exec(void) {}
void core_callback_uart_rx_after_exec(void) {}
void core_callback_uart_tx_before_exec(void) {}
void core_callback_uart_tx_after_exec(void) {}
void core_callback_uart_cts_before_exec(void) {}
void core_callback_uart_cts_after_exec(void) {}

/************************************************************************/
/* Callbacks: Read app register                                         */
/************************************************************************/
bool core_read_app_register(uint8_t add, uint8_t type)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;
	
	/* Receive data */
	(*app_func_rd_pointer[add-APP_REGS_ADD_MIN])();	

	/* Return success */
	return true;
}

/************************************************************************/
/* Callbacks: Write app register                                        */
/************************************************************************/
bool core_write_app_register(uint8_t add, uint8_t type, uint8_t * content, uint16_t n_elements)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;

	/* Check if the number of elements matches */
	if (app_regs_n_elements[add-APP_REGS_ADD_MIN] != n_elements)
		return false;

	/* Process data and return false if write is not allowed or contains errors */
	return (*app_func_wr_pointer[add-APP_REGS_ADD_MIN])(content);
}