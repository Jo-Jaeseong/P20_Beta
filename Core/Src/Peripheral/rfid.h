/*
 * rfid.h
 *
 *  Created on: May 31, 2019
 *      Author: monster
 */

#ifndef PERIPHERAL_RFID_H_
#define PERIPHERAL_RFID_H_

struct RFID_format {
	/*
	시리얼 넘버(생산일자+생산숫자)
	 - 생산 일자(production_date)
	 - 생산 숫자
	인식 날짜
	잔량
	*/
	unsigned int production_year, production_month, production_day;
	unsigned int production_number;
	unsigned int open_year, open_month, open_day;
	unsigned int expiry_year, expiry_month, expiry_day;
	unsigned int volume, volumemax;
};

extern struct RFID_format ReadRFIDData;//현재 RFID
extern struct RFID_format CurrentRFIDData;//현재 RFID
extern struct RFID_format FlashRFIDData[5];// FlashRFID
extern int RFIDflashIndex; // Flash 데이터 인덱스
extern int CurrentRFIDIndex;

extern int checkret;
extern int expiry_date1;
extern int expiry_date2;
extern int firstRFIDFlag, firstRFIDCount;

void RFIDCheck();
bool is_same(unsigned char a[], unsigned char b[], int length);
void InitRFID(void);
uint32_t ReadRFID(void);

#endif /* PERIPHERAL_RFID_H_ */
