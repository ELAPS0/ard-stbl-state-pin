#include "StableStatePin.h"

StableStatePin::StableStatePin(){
	pin = 0xff;
	strcpy(name, "noname");
	stbl_state = STBLPIN_OFF; 
    pin_state_candidate = STBLPIN_OFF;
    pin_state_candidate_ts = 0;
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
	stbl_state = STBLPIN_OFF; 
    pin_state_candidate = STBLPIN_OFF;
    pin_state_candidate_ts = 0;
	strncpy(name, _name,MAX_NAME_LEN);
	name[MAX_NAME_LEN-1] = '\0';
	period = _period;
	pinMode (pin, INPUT);
	get_state();
}

STBLPIN_STATE StableStatePin::get_state(){
    uint8_t actual_pin_state;

    Serial.print(pin_state_candidate_ts);
    if (pin_state_candidate_ts){
        //отсчет запущен, состояние-кандидат актуально
        actual_pin_state = digitalRead(pin);
        if(actual_pin_state != pin_state_candidate){
            //состояние изменилось, перезапускаем таймер
            pin_state_candidate_ts = millis();
        }else if (millis() - pin_state_candidate_ts > period){
                //период прошел, состояние не изменилось. Считаем, что стабильно
                stbl_state = pin_state_candidate;
                pin_state_candidate_ts = 0;
            }
    }else{
        pin_state_candidate = digitalRead(pin);
        if (pin_state_candidate != stbl_state){
            pin_state_candidate_ts = millis();
        }
    }
    return stbl_state;


}

