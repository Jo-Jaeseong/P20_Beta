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
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    if(value>50){
        return 1;
    }
    else{
    	return 0;
    }
}
