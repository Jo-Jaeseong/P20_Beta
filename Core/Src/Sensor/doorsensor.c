/*
 * door_sensor.c
 *
 *  Created on: Nov 10, 2022
 *      Author: CBT
 */

#include "main.h"
#include "peripheral.h"
#include "sensor.h"

// ------------------- Variables -------------------
#define DoorHandle_Port	GPIO_IN5_GPIO_Port
#define DoorHandle_Pin	GPIO_IN5_Pin

extern unsigned char Running_Flag;


int DoorCheckcnt=0;
int DoorOpenFlag;
int DoorOpenVentFlag;
int DoorOpenVentCnt;

// ------------------- Functions -------------------

/*
int DoorHandleCheck(){
	if(HAL_GPIO_ReadPin(DoorHandle_Port, DoorHandle_Pin)==1){
		return 1;
	}
	else{
		return 0;
	}
}
*/

int DoorHandleCheck(){
	if(HAL_GPIO_ReadPin(DoorHandle_Port, DoorHandle_Pin)==1){
	//정상

	//if(HAL_GPIO_ReadPin(DoorHandle_Port, DoorHandle_Pin)==0){
		//기구물 거리 확인 필요 일단 반대로 인식되게 설정
		return 0;
	}
	else{
		return 1;
	}
}



int DoorLatchCheck(){
	return Limit1();
	//return ValveCheck();	//테스트
}

int BottleDoorCheck(){
	return Limit2();
}

int BottleCheck(){
	return Limit3();
}


void DoorSensorOpenProcess(){
	if(Running_Flag==0){
		if(DoorHandleCheck()){//핸드센서 체크 1초
			if(DoorLatchCheck()){//래치가 잠겨있다면,
				DoorLatch(1);
			}
			else{				//래치가 열려있다면, 동작하지 않음.
				DoorLatch(0);
			}
		}
	}
}

void ButtonSensorOpenProcess(){
	if(Running_Flag==0){
		if(DoorLatchCheck()){//래치가 잠겨있다면,
			DoorLatch(1);
		}
	}
}

int DoorOpenProcess(){
	if(DoorHandleCheck()){
		DoorCheckcnt++;
	}
	else{
		DoorCheckcnt=0;
	}
	if(DoorCheckcnt==1){
	//if(DoorCheckcnt==2){
		//기존 체크 방식
		if(DoorLatchCheck()){
    		if(Pressure>DoorOpenPressure){
    			return 1;
    		}
    		else{
    			beforepage=currentpage;
    			DisplayPage(LCD_DOOROPENMESSAGE_PAGE);
    			return 0;
    		}
			DoorCheckcnt=0;
		}
	}
	else{
		return 0;
	}
}
