#include "usb.h"

#include "emu_ft245_eeprom.h"

#define SD1P 20
#define SD2P (SD1P+USB_SD_Ptr[1][0])
#define SD3P (SD2P+USB_SD_Ptr[2][0])
#define SD4P (SD3P+USB_SD_Ptr[3][0])

extern const USB_DEVICE_DESCRIPTOR device_dsc;
extern const BYTE configDescriptor1[];
extern const BYTE *const USB_SD_Ptr[];

static WORD_VAL checksum;

BYTE eeprom_read(BYTE a) {

	switch(a) {
		case 2:
			return ((BYTE*)&device_dsc.idVendor)[0];	//vid,
			break;
		case 3:
			return ((BYTE*)&device_dsc.idVendor)[1];
			break;
		case 4:
			return ((BYTE*)&device_dsc.idProduct)[0];	//pid,
			break;
		case 5:
			return ((BYTE*)&device_dsc.idProduct)[1];
			break;
		case 6:
			return ((BYTE*)&device_dsc.bcdDevice)[0];	//ver
			break;
		case 7:
			return ((BYTE*)&device_dsc.bcdDevice)[1];
			break;
		case 8:
			return configDescriptor1[7];	//attr,
			break;
		case 9:
			return configDescriptor1[8];	//pow
			break;
		case 10:
			return 0x1C;
			break;
		case 12:
			return ((BYTE*)&device_dsc.bcdUSB)[0];
			break;
		case 13:
			return ((BYTE*)&device_dsc.bcdUSB)[1];
			break;
		case 14:
			return 0x80+SD1P;			//0x80+&sd001
			break;
		case 15:
			return USB_SD_Ptr[1][0];	//sizeof(sd001)
			break;
		case 16:
			return 0x80+SD2P;			//0x80+&sd002
			break;
		case 17:
			return USB_SD_Ptr[2][0];	//sizeof(sd002)
			break;
		case 18:
			return 0x80+SD3P;			//0x80+&sd003
			break;
		case 19:
			return USB_SD_Ptr[3][0];	//sizeof(sd003)
			break;
		case 126:
			return checksum.byte.LB;
			break;
		case 127:
			return checksum.byte.HB;
			break;
		default:
			if(SD1P<=a && a<SD2P) return USB_SD_Ptr[1][a-SD1P];
			if(SD2P<=a && a<SD3P) return USB_SD_Ptr[2][a-SD2P];
			if(SD3P<=a && a<SD4P) return USB_SD_Ptr[3][a-SD3P];
			if(SD4P<=a && a<SD4P+4) return ((BYTE*)&device_dsc.iManufacturer)[a-SD4P];
			return 0; 
			break;
		}
	return 0; 
	}

void eeprom_init(void){
	BYTE i;

	checksum.Val=0xAAAA;
	for(i=0; i<126; i+=2){
		checksum.byte.LB ^= eeprom_read(i);
		checksum.byte.HB ^= eeprom_read(i+1);
		if(checksum.Val&0x8000) 
			checksum.Val=(checksum.Val<<1) | 1;
		else 
			checksum.Val=(checksum.Val<<1);
		}
	}

