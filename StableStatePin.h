/*
Обертка для input digital pin, невелирующая кратковременные изменения сотояния входа.
*/
#ifndef STBLSTATEPIN_LIB
#define STBLSTATEPIN_LIB

#include <Arduino.h>

#define MAX_NAME_LEN	64

//состояние входа  
enum STBLPIN_STATE {
      STBLPIN_ON,
      STBLPIN_OFF
    };


class StableStatePin
{
	//стабильное состояние
	STBLPIN_STATE	stbl_state;

	//текущее состояни входае
	STBLPIN_STATE	pin_state;
	//время изменения текущего состояния
	uint32_t	pin_state_ts;

	uint8_t 	pin; 
	char 		name[MAX_NAME_LEN];

	//период, в течении которого состояние входа не должно меняться
    //задается в миллисекундах
	uint32_t 	period;
	
public:
	StableStatePin();
	StableStatePin(uint8_t _pin, const char * _name,  uint32_t _period);
	void init(uint8_t _pin, const char * _name,  uint32_t _period);
   	STBLPIN_STATE get_state();
};


#endif
