/*
 * pm.c
 *
 *  Created on: 2023. 3. 17.
 *      Author: CBT
 */

#include "pm.h"
#include "main.h"

unsigned int CarbonFilterMax, HEPAFilterMax, PlasmaAssyMax;
unsigned int CarbonFilter, HEPAFilter, PlasmaAssy;

unsigned int totalCount, dailyCount;


void PMinit(){
	CarbonFilterMax=400;
	HEPAFilterMax=400;
	PlasmaAssyMax=800;

	CarbonFilter=400;
	HEPAFilter=400;
	PlasmaAssy=800;
}
void CarbonFilter_Count(){
	if(CarbonFilter==0){
		CarbonFilter=0;
	}
	else{
		CarbonFilter--;
	}
}
void CarbonFilter_Reset(){
	CarbonFilter=0;
}
void HEPAFilter_Count(){
	if(HEPAFilter==0){
		HEPAFilter=0;
	}
	else{
		HEPAFilter--;
	}
}
void HEPAFilter_Reset(){
	HEPAFilter=0;
}
void PlasmaAssy_Count(){
	if(PlasmaAssy==0){
		PlasmaAssy=0;
	}
	else{
		PlasmaAssy--;
	}
}
void PlasmaAssy_Reset(){
	PlasmaAssy=0;
}

void TotalCyle_Count(){
	totalCount++;
	if(totalCount>999){
		totalCount=1;
	}
}
void DailyCyle_Count(){
	dailyCount++;
}
void DailyCyle_Reset(){
	dailyCount=0;
}
