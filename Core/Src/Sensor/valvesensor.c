/*
 * adc.c
 *
 *  Created on: Oct 25, 2022
 *      Author: CBT
 */


#include "main.h"
#include "sensor.h"

extern ADC_HandleTypeDef hadc1;

int ValveCheck(){
    const uint8_t samples = 4;
    uint32_t total = 0;
    for (uint8_t i = 0; i < samples; i++) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        total += HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
    }
    uint32_t value = total / samples;
    if(value>50){
        return 1;
    }
    else{
    	return 0;
    }
}
