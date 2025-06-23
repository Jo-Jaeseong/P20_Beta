/*
 * pm.h
 *
 *  Created on: 2023. 3. 17.
 *      Author: CBT
 */

#ifndef SRC_PERIPHERAL_PM_H_
#define SRC_PERIPHERAL_PM_H_

extern unsigned int CarbonFilterMax, HEPAFilterMax, PlasmaAssyMax;
extern unsigned int CarbonFilter, HEPAFilter, PlasmaAssy;

extern unsigned int totalCount, dailyCount;

void PMinit();

void CarbonFilter_Count();
void CarbonFilter_Reset();
void HEPAFilter_Count();
void HEPAFilter_Reset();
void PlasmaAssy_Count();
void PlasmaAssy_Reset();

void TotalCyle_Count();
void DailyCyle_Count();
void DailyCyle_Reset();

#endif /* SRC_PERIPHERAL_PM_H_ */
