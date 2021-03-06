#include "PL3/shellcode_egghunt.h"

#define MAGIC_NUMBER		0x50, 0x53, 0x47, 0x72, 0x6f, 0x6f, 0x76, 0x65

#if defined (FIRMWARE_3_41)
	#define FIRMWARE		3_41
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xe7, 0x20
#elif defined (FIRMWARE_3_41_KIOSK)
	#define FIRMWARE		3_41_kiosk
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xe7, 0x20
#elif defined (FIRMWARE_3_40)
	#define FIRMWARE		3_40
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xe7, 0x20
#elif defined (FIRMWARE_3_30)
	#define FIRMWARE		3_30
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xdb, 0xc0
#elif defined (FIRMWARE_3_21)
	#define FIRMWARE		3_21
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xda, 0x90
#elif defined (FIRMWARE_3_15)
	#define FIRMWARE		3_15
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xda, 0x10
#elif defined (FIRMWARE_3_10)
	#define FIRMWARE		3_10
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x33, 0xda, 0x10
#elif defined (FIRMWARE_3_01)
	#define FIRMWARE		3_01
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x32, 0x06, 0x40
#elif defined (FIRMWARE_2_76)
	#define FIRMWARE		2_76
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x31, 0x3E, 0x70
#elif defined (FIRMWARE_2_70)
	#define FIRMWARE		2_70
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x31, 0x3E, 0x70
#elif defined (FIRMWARE_2_60)
	#define FIRMWARE		2_60
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x30, 0x4f, 0x60
#elif defined (FIRMWARE_2_53)
	#define FIRMWARE		2_53
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x30, 0x42, 0xa0
#elif defined (FIRMWARE_2_43)
	#define FIRMWARE		2_43
	#define RTOC_TABLE		0x80, 0x00, 0x00, 0x00, 0x00, 0x31, 0xff, 0x40
#else
	#error You must specify the target firmware. Define a supported FIRMWARE_X_YZ in Makefile
#endif /* FIRMWARE_X_YZ */

#define default_shellcode shellcode_egghunt
#define default_shellcode_macro shellcode_egghunt_macro

#ifdef USE_JIG

	#define PAYLOAD_FW_DEPENDENT

	#if defined (FIRMWARE_3_41)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x70
	#elif defined (FIRMWARE_3_41_KIOSK)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x70
	#elif defined (FIRMWARE_3_40)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xee, 0x70
	#elif defined (FIRMWARE_3_30)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xde, 0x70
	#elif defined (FIRMWARE_3_21)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xde, 0x30
	#elif defined (FIRMWARE_3_15)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xde, 0x30
	#elif defined (FIRMWARE_3_10)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3d, 0xde, 0x30
	#elif defined (FIRMWARE_3_01)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3B, 0xFB, 0xC8
	#elif defined (FIRMWARE_2_76)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x1B, 0xC8
	#elif defined (FIRMWARE_2_70)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x1b, 0xc8
	#elif defined (FIRMWARE_2_60)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x2b, 0xa8
	#elif defined (FIRMWARE_2_53)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x2b, 0xa8
	#elif defined (FIRMWARE_2_43)
		#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x3b, 0xeb, 0xa8
	#endif /* FIRMWARE_X_YZ */

	#define SHELLCODE_PAGE			0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00
	#define SHELLCODE_DESTINATION	SHELLCODE_ADDR_BASE
	#define SHELLCODE_PTR			SHELLCODE_ADDR_BASE + 0x08
	#define SHELLCODE_ADDRESS		SHELLCODE_ADDR_BASE + 0x18

	#define PORT1_NUM_CONFIGS		4

#else /* USE_JIG */

	#define SHELLCODE_ADDR_BASE		0x80, 0x00, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x00

	#define SHELLCODE_PAGE			SHELLCODE_ADDR_BASE
	#define SHELLCODE_DESTINATION	SHELLCODE_ADDR_BASE + 0x20
	#define SHELLCODE_PTR			SHELLCODE_ADDR_BASE + 0x28
	#define SHELLCODE_ADDRESS		SHELLCODE_ADDR_BASE + 0x38

	#define PORT1_NUM_CONFIGS		100

#endif /* USE_JIG */

#ifdef PAYLOAD_FW_DEPENDENT

	#define PAYLOAD_INCLUDE_(payload_dir, payload, firmware) <payload_dir##/payload##_pic_##firmware.h>
	#define PAYLOAD_INCLUDE(payload_dir, payload, firmware) PAYLOAD_INCLUDE_(payload_dir, payload, firmware)
	#include PAYLOAD_INCLUDE(PAYLOAD_DIR, PAYLOAD, FIRMWARE)

	#define payload_macro_pic_pad_inc_(payload, firmware) payload##_##firmware##_macro_pic_pad
	#define payload_macro_pic_pad_inc(payload, firmware) \
		payload_macro_pic_pad_inc_(payload, firmware)


	#define payload_macro_(payload, firmware, num) payload##_##firmware##_macro_pic_##num
	#define payload_macro(payload, firmware, num) \
		payload_macro_(payload, firmware, num)
		

	#define payload_macro_1 payload_macro(PAYLOAD, FIRMWARE, 1)
	#define payload_macro_2 payload_macro(PAYLOAD, FIRMWARE, 2)
	#define payload_macro_3 payload_macro(PAYLOAD, FIRMWARE, 3)
	#define payload_macro_4 payload_macro(PAYLOAD, FIRMWARE, 4)

	#define payload_macro_pic_pad payload_macro_pic_pad_inc(PAYLOAD, FIRMWARE)

#else

	#define PAYLOAD_INCLUDE_(payload_dir, payload) <payload_dir##/payload##_pic.h>
	#define PAYLOAD_INCLUDE(payload_dir, payload) PAYLOAD_INCLUDE_(payload_dir, payload)
	#include PAYLOAD_INCLUDE(PAYLOAD_DIR, PAYLOAD)

	#define payload_macro_pic_pad_inc_(payload) payload##_macro_pic_pad
	#define payload_macro_pic_pad_inc(payload) \
		payload_macro_pic_pad_inc_(payload)


	#define payload_macro_(payload, num) payload##_macro_pic_##num
	#define payload_macro(payload, num) \
		payload_macro_(payload, num)
		

	#define payload_macro_1 payload_macro(PAYLOAD, 1)
	#define payload_macro_2 payload_macro(PAYLOAD, 2)
	#define payload_macro_3 payload_macro(PAYLOAD, 3)
	#define payload_macro_4 payload_macro(PAYLOAD, 4)

	#define payload_macro_pic_pad payload_macro_pic_pad_inc(PAYLOAD)

#endif

#if defined (WBOOTLOADERHID)
	#define BOOTLOADER_EXPORT	wBTL_HID
#elif defined (WBOOTLOADERMCHP)
	#define BOOTLOADER_EXPORT	wBTL_MCHP
#else
	#define BOOTLOADER_EXPORT	nBTL
#endif

#define FILE_EXPORT(payload_dir_e, payload_e, firmware_e, btl_e) FILE=PSGrooPIC_##payload_dir_e##_##payload_e##_FW##firmware_e##_##btl_e##.hex
#export (HEX, FILE_EXPORT(PAYLOAD_DIR, PAYLOAD, FIRMWARE, BOOTLOADER_EXPORT))

#define PORT1_DESC_LEN		0x1000
#define PORT1_DESC_LEN_HI	((PORT1_DESC_LEN >> 8) & 0xFF)
#define PORT1_DESC_LEN_LO	(PORT1_DESC_LEN & 0xFF)

#define PORT3_DESC_LEN		0xa4d
#define PORT3_DESC_LEN_HI	((PORT3_DESC_LEN >> 8) & 0xFF)
#define PORT3_DESC_LEN_LO	(PORT3_DESC_LEN & 0xFF)

const unsigned int8 USB_DEVICE_DESC[] = {
	//HUB_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x09, 0x00, 0x01, 0x08,
		0xAA, 0xAA, 0xCC, 0xCC, 0x00, 0x01, 0x00, 0x00,
		0x00, 0x01,
	//HUB_HUB_DEVICE
		0x09, 0x29, 0x06, 0xa9, 0x00, 0x05, 0x64, 0x00,
		0xff,
	//PORT1_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
		0x00, PORT1_NUM_CONFIGS,
	//PORT2_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0xAA, 0xAA, 0xBB, 0xBB, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01,
	//PORT3_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x02,
	//PORT4_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0xAA, 0xAA, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x03,
	//PORT5_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0x4c, 0x05, 0xeb, 0x02, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01,
	//PORT6_DEVICE
		0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08,
		0xaa, 0xaa, 0xc0, 0xde, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01,
};

const unsigned int8 USB_CONFIG_DESC[] = {
	//HUB_CONFIG
		// Config
			0x09, 0x02, 0x19, 0x00, 0x01, 0x01, 0x00, 0xe0,
			0x32,
		// Interface
			0x09, 0x04, 0x00, 0x00, 0x01, 0x09, 0x00, 0x00,
			0x00,
		// Endpoint (interrupt in)
			0x07, 0x05, 0x81, 0x03, 0x01, 0x00, 0x0c,
	//PORT1_SHORT_CONFIG
		0x09, 0x02, PORT1_DESC_LEN_LO, PORT1_DESC_LEN_HI, 0x01, 0x00, 0x00, 0x80,
		0xfa,
	//PORT1_CONFIG
		0x09, 0x02, 0x12, 0x00, 0x01, 0x00, 0x00, 0x80, 0xfa,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		MAGIC_NUMBER,
		#ifndef USE_JIG
			SHELLCODE_PTR,
			SHELLCODE_ADDRESS,
			RTOC_TABLE,
		#endif
		payload_macro_1, payload_macro_2, payload_macro_3, payload_macro_4,
	//PORT2_CONFIG
		// config
			0x09, 0x02, 0x16, 0x00, 0x01, 0x01, 0x00, 0x80,
			0x01,
		// interface
			0x09, 0x04, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x02,
			0x00,
		// extra
			0x04, 0x21, 0xb4, 0x2f,
	//PORT3_CONFIG
		0x09, 0x02, 0x4d, 0x0a, 0x01, 0x01, 0x00, 0x80, 0x01,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 0x09, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x02, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0x02, 0x00,
		0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
	//PORT4_CONFIG_1
		// config
			0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
			0x01,
		// interface
			0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
			0x00,
	//PORT4_SHORT_CONFIG_2
		// config
			0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
	//PORT4_CONFIG_2
		// config
			0x09, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x80,
			0x01,
		// interface
			0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
			0x00,
	//PORT4_CONFIG_3
		0x09, 0x02, 0x30, 0x00, 0x01, 0x01, 0x00, 0x80, 0x01, 0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01,
		0x02, 0x00, 0x3e, 0x21, 0x00, 0x00, 0x00, 0x00,
		MAGIC_NUMBER, /* magic number to look for in the start of the page */
		SHELLCODE_PAGE, /* Initial data search ptr */
		SHELLCODE_DESTINATION, /* destination ptr for heap structure (jig response) */
	//PORT5_CONFIG
		// config
			0x09, 0x02, 0x20, 0x00, 0x01, 0x00, 0x00, 0x80,
			0x01,
		// interface
			0x09, 0x04, 0x00, 0x00, 0x02, 0xff, 0x00, 0x00,
			0x00,
		// endpoint
			0x07, 0x05, 0x02, 0x02, 0x08, 0x00, 0x00,
		// endpoint
			0x07, 0x05, 0x81, 0x02, 0x08, 0x00, 0x00,
	//PORT6_CONFIG
		// config
			0x09, 0x02, 0x12, 0x00, 0x01, 0x01, 0x00, 0x80,
			0x01,
		// interface
			0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02,
			0x00,
};

const unsigned int8 jig_response[64] = {
	SHELLCODE_PTR,
	SHELLCODE_ADDRESS,
	RTOC_TABLE,
	default_shellcode_macro,
};

#define HUB_DEVICE_SIZE					0x0012
#define HUB_HUB_DEVICE_SIZE				0x0009
#define PORT1_DEVICE_SIZE				0x0012
#define PORT2_DEVICE_SIZE				0x0012
#define PORT3_DEVICE_SIZE				0x0012
#define PORT4_DEVICE_SIZE				0x0012
#define PORT5_DEVICE_SIZE				0x0012

#define HUB_DEVICE_OFFSET				0x0000
#define HUB_HUB_DEVICE_OFFSET			HUB_DEVICE_SIZE
#define PORT1_DEVICE_OFFSET				HUB_HUB_DEVICE_OFFSET + HUB_HUB_DEVICE_SIZE
#define PORT2_DEVICE_OFFSET				PORT1_DEVICE_OFFSET + PORT1_DEVICE_SIZE
#define PORT3_DEVICE_OFFSET				PORT2_DEVICE_OFFSET + PORT2_DEVICE_SIZE
#define PORT4_DEVICE_OFFSET				PORT3_DEVICE_OFFSET + PORT3_DEVICE_SIZE
#define PORT5_DEVICE_OFFSET				PORT4_DEVICE_OFFSET + PORT4_DEVICE_SIZE

#define HUB_CONFIG_SIZE					0x0019
#define PORT1_SHORT_CONFIG_SIZE			0x0009
#define PORT1_CONFIG_SIZE				0x1000
#define PORT2_CONFIG_SIZE				0x0016
#define PORT3_CONFIG_SIZE				0x0A4D
#define PORT4_CONFIG_1_SIZE				0x0012
#define PORT4_SHORT_CONFIG_2_SIZE		0x0008
#define PORT4_CONFIG_2_SIZE				0x0012
#define PORT4_CONFIG_3_SIZE				0x0030
#define PORT5_CONFIG_SIZE				0x0020

#define HUB_CONFIG_OFFSET				0x0000
#define PORT1_SHORT_CONFIG_OFFSET		HUB_CONFIG_SIZE
#define PORT1_CONFIG_OFFSET				PORT1_SHORT_CONFIG_OFFSET + PORT1_SHORT_CONFIG_SIZE
#define PORT2_CONFIG_OFFSET				PORT1_CONFIG_OFFSET + PORT1_CONFIG_SIZE - payload_macro_pic_pad
#define PORT3_CONFIG_OFFSET				PORT2_CONFIG_OFFSET + PORT2_CONFIG_SIZE
#define PORT4_CONFIG_1_OFFSET			PORT3_CONFIG_OFFSET + PORT3_CONFIG_SIZE
#define PORT4_SHORT_CONFIG_2_OFFSET		PORT4_CONFIG_1_OFFSET + PORT4_CONFIG_1_SIZE
#define PORT4_CONFIG_2_OFFSET			PORT4_SHORT_CONFIG_2_OFFSET + PORT4_SHORT_CONFIG_2_SIZE
#define PORT4_CONFIG_3_OFFSET			PORT4_CONFIG_2_OFFSET + PORT4_CONFIG_2_SIZE
#define PORT5_CONFIG_OFFSET				PORT4_CONFIG_3_OFFSET + PORT4_CONFIG_3_SIZE
