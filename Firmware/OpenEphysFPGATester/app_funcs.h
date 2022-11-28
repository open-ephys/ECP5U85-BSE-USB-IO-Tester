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
void app_read_REG_TEST_STARTED(void);
void app_read_REG_FAIL_EVENT(void);
void app_read_REG_J1_2V5_7(void);
void app_read_REG_J1_3V3_9(void);
void app_read_REG_J1_3V3_11(void);
void app_read_REG_J1_3V3_13(void);
void app_read_REG_J1_5V_1(void);
void app_read_REG_J1_5V_3(void);
void app_read_REG_J1_5V_5(void);
void app_read_REG_J1_RAMVDD_4(void);
void app_read_REG_J1_RAMVDD_6(void);
void app_read_REG_J2_3V3_2(void);
void app_read_REG_J2_3V3_4(void);
void app_read_REG_J2_3V3_6(void);

bool app_write_REG_TEST_STARTED(void *a);
bool app_write_REG_FAIL_EVENT(void *a);
bool app_write_REG_J1_2V5_7(void *a);
bool app_write_REG_J1_3V3_9(void *a);
bool app_write_REG_J1_3V3_11(void *a);
bool app_write_REG_J1_3V3_13(void *a);
bool app_write_REG_J1_5V_1(void *a);
bool app_write_REG_J1_5V_3(void *a);
bool app_write_REG_J1_5V_5(void *a);
bool app_write_REG_J1_RAMVDD_4(void *a);
bool app_write_REG_J1_RAMVDD_6(void *a);
bool app_write_REG_J2_3V3_2(void *a);
bool app_write_REG_J2_3V3_4(void *a);
bool app_write_REG_J2_3V3_6(void *a);


#endif /* _APP_FUNCTIONS_H_ */