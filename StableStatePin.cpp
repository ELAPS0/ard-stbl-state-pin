#include "StableStatePin.h"

StableStatePin::StableStatePin(){
	pin = 0xff;
	strcpy(name, "noname");
	stbl_state = STBLPIN_OFF; 
	pin_state = STBLPIN_OFF; 
	pin_state_ts = 0;
}

StableStatePin::StableStatePin(uint8_t _pin, const char * _name,  uint32_t _period){
	init (_pin, _name, _period);
}

/*
@pin 		- номер выхода, состоянием которого будет управлять экземпляр класса  
@name 		- имя, отображаемое в логе
@state 		- начальное состояние выхода
*/
void StableStatePin::init(uint8_t _pin, const char * _name,  uint32_t _period){
	pin = _pin;
	strncpy(name, _name,MAX_NAME_LEN);
	name[MAX_NAME_LEN-1] = '\0';
	period = _period;

	pinMode (pin, INPUT);
	get_state();
}

STBLPIN_STATE StableStatePin::get_state(){
    char s[256];
    if(pin_state != digitalRead(pin))
    {
        pin_state != pin_state;
        sprintf("%ud: %s pin state changed form %d to %d\n",millis(), name, !pin_state, pin_state);
        Serial.print(s);
        if (millis() - pin_state_ts > period){
            sprintf("%ud: %s stable state changed form %d to %d\n",millis(), name, stbl_state, pin_state);
            Serial.print(s);
            stbl_state = pin_state;
        }
        pin_state_ts = millis();
    }
	return pin_state;
}

