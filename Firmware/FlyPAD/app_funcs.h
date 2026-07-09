#ifndef _APP_FUNCTIONS_H_
#define _APP_FUNCTIONS_H_
#include <avr/io.h>


/************************************************************************/
/* Define if not defined                                                */
/************************************************************************/
#ifndef bool
	#define bool uint8_t
#endif
#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif


/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/
void app_read_REG_ENABLE_ACQUISITION(void);
void app_read_REG_CAPACITANCE_VALUES(void);
void app_read_REG_DI0_STATE(void);
void app_read_REG_DI1_STATE(void);
void app_read_REG_DIGITAL_OUTPUT_SET(void);
void app_read_REG_DIGITAL_OUTPUT_CLEAR(void);
void app_read_REG_DIGITAL_OUTPUT_TOGGLE(void);
void app_read_REG_DIGITAL_OUTPUT_STATE(void);
void app_read_REG_ENABLE_EVENTS(void);

bool app_write_REG_ENABLE_ACQUISITION(void *a);
bool app_write_REG_CAPACITANCE_VALUES(void *a);
bool app_write_REG_DI0_STATE(void *a);
bool app_write_REG_DI1_STATE(void *a);
bool app_write_REG_DIGITAL_OUTPUT_SET(void *a);
bool app_write_REG_DIGITAL_OUTPUT_CLEAR(void *a);
bool app_write_REG_DIGITAL_OUTPUT_TOGGLE(void *a);
bool app_write_REG_DIGITAL_OUTPUT_STATE(void *a);
bool app_write_REG_ENABLE_EVENTS(void *a);


#endif /* _APP_FUNCTIONS_H_ */