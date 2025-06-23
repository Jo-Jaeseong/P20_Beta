/*
 * heater.c
 *
 *  Created on: Nov 10, 2022
 *      Author: CBT
 */
#include "main.h"
#include "sensor.h"
#include "hardware.h"
#include "peripheral.h"

int TestTempErrorValue;


/*
 * 히터 5가지
 *
 * 도어   - DoorHeater
 * 챔버1 - ChamberHeater
 * 챔버2 - ChamberHeater2
 * 기화기 - VaporizerHeater
 * 순환   - CirculationHeater
 *
 */
// ------------------- Variables -------------------


#define DoorHeater_Port GPIO_OUT11_GPIO_Port
#define DoorHeater_Pin GPIO_OUT11_Pin

#define ChamberHeater_Port GPIO_OUT6_GPIO_Port
#define ChamberHeater_Pin GPIO_OUT6_Pin

#define ChamberHeater2_Port GPIO_OUT12_GPIO_Port
#define ChamberHeater2_Pin GPIO_OUT12_Pin

#define VaporizerHeater_Port GPIO_OUT13_GPIO_Port
#define VaporizerHeater_Pin GPIO_OUT13_Pin


// ------------------- Functions -------------------

void DoorHeater(int onoff){
	AC1(onoff);
}

void ChamberHeater(int onoff){
	DC6(onoff);
}

void ChamberBackHeater(int onoff){
	AC2(onoff);
}

void VaporizerHeater(int onoff){
	AC3(onoff);
}


void DoorHeaterControl(int Temp){
	//컨트롤 하는 방식 고민
	//얼마에 한번씩 체크 할지 생각
	if(Temperature[0]>=Temp){
		DoorHeater(0);
	}
	else{
		DoorHeater(1);
	}
}

void ChamberHeaterControl(int Temp){
	//컨트롤 하는 방식 고민
	//얼마에 한번씩 체크 할지 생각
	if(Temperature[1]>=Temp){
		ChamberHeater(0);
	}
	else{
		ChamberHeater(1);
	}
}

void ChamberBackHeaterControl(int Temp){
	//컨트롤 하는 방식 고민
	//얼마에 한번씩 체크 할지 생각
	if(Temperature[2]>=Temp){
		ChamberBackHeater(0);
	}
	else{
		ChamberBackHeater(1);
	}
}


void VaporizerHeaterControl(int Temp){
	//컨트롤 하는 방식 고민
	//얼마에 한번씩 체크 할지 생각
	if(Temperature[3]>=Temp){
		VaporizerHeater(0);
	}
	else{
		VaporizerHeater(1);
	}
}

void HeaterControl(){
	switch (HeaterControlMode) {
		case 0:	//컨트롤 안함
			break;
		case 1:	//대기
			DoorHeaterControl(DoorSettingTemp[0]);
			ChamberHeaterControl(ChamberSettingTemp[0]);
			ChamberBackHeaterControl(ChamberBackSettingTemp[0]);
			VaporizerHeaterControl(VaporizerSettingTemp[0]);
			break;

		case 2:	//공정
			DoorHeaterControl(DoorSettingTemp[1]);
			ChamberHeaterControl(ChamberSettingTemp[1]);
			ChamberBackHeaterControl(ChamberBackSettingTemp[1]);
			VaporizerHeaterControl(VaporizerSettingTemp[1]);
			break;

		case 3:	//슬립
			DoorHeaterControl(DoorSettingTemp[2]);
			ChamberHeaterControl(ChamberSettingTemp[2]);
			ChamberBackHeaterControl(ChamberBackSettingTemp[2]);
			VaporizerHeaterControl(VaporizerSettingTemp[2]);
			break;
		default:
			break;
	}
}

int DoorHeaterCheck(){
	if((DoorSettingTemp[1]-TestTempErrorValue)>Temperature[0]){
		return 1;
	}
	else{
		return 0;
	}
}
int ChamberHeaterCheck(){
	if((ChamberSettingTemp[1]-TestTempErrorValue)>Temperature[1]){
		return 1;
	}
	else{
		return 0;
	}
}
int ChamberBackHeaterCheck(){
	if((ChamberBackSettingTemp[1]-TestTempErrorValue)>Temperature[2]){
		return 1;
	}
	else{
		return 0;
	}
}
int VaporizerHeaterCheck(){
	if((VaporizerSettingTemp[1]-TestTempErrorValue)>Temperature[3]){
		return 1;
	}
	else{
		return 0;
	}
}
