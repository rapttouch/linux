/*
 * hid_device.h
 *
 *  Created on: Mar 31, 2015
 *      Author: odroid
 */

#ifndef HID_DEVICE_H_
#define HID_DEVICE_H_

#define MAX_TOUCHES_REPORTED	10
#define MAX_FINGER_TOUCHES_REPORTED	10
#define MAX_STYLUS_TOUCHES_REPORTED	10
#if ((MAX_FINGER_TOUCHES_REPORTED > MAX_TOUCHES_REPORTED) || (MAX_STYLUS_TOUCHES_REPORTED > MAX_TOUCHES_REPORTED))
#error "Max number of finger or stylus touches reported cannot be greater than max total number of touches reported."
#endif

#define REPORTID_MTOUCH_FINGER	0xF1
#define REPORTID_MAX_COUNT 		0xF2
#define REPORTID_FEATURE   		0xF3
#define REPORTID_MOUSE     		0xF4
#define REPORTID_MTOUCH_STYLUS  0xF5
#define REPORTID_FIRMWARE_KEY	0x44

#define REPORT_ID_SIZE			1
#define CONTACT_COUNT_MAX_SIZE    1
#define CONTACT_COUNT_SIZE        1
#define BOOLEAN_INFO_SIZE         1
#define CONTACT_ID_SIZE           1
#define TRANSDUCER_INDEX_SIZE     1
#define REPORT_X_SIZE             2
#define REPORT_Y_SIZE             2
#define REPORT_WIDTH_SIZE         2
#define REPORT_HEIGHT_SIZE        2
#define TIP_PRESSURE_SIZE         2
#define CONFIDENCE_SIZE           2
#define SCAN_TIME_SIZE            2

#define ONE_FINGER_DATA_SIZE    ( BOOLEAN_INFO_SIZE + CONTACT_ID_SIZE + REPORT_X_SIZE + REPORT_Y_SIZE + REPORT_WIDTH_SIZE + REPORT_HEIGHT_SIZE + TIP_PRESSURE_SIZE + CONFIDENCE_SIZE)
#define FINGERS_DATA_SIZE       ( MAX_FINGER_TOUCHES_REPORTED * ONE_FINGER_DATA_SIZE )

#define ONE_STYLUS_DATA_SIZE    ( BOOLEAN_INFO_SIZE + CONTACT_ID_SIZE + TRANSDUCER_INDEX_SIZE + REPORT_X_SIZE + REPORT_Y_SIZE + REPORT_WIDTH_SIZE + REPORT_HEIGHT_SIZE + TIP_PRESSURE_SIZE + CONFIDENCE_SIZE)
#define STYLII_DATA_SIZE       ( MAX_STYLUS_TOUCHES_REPORTED * ONE_STYLUS_DATA_SIZE )

#define DIGITIZER_REPORT_MAX_COUNT_SIZE ( REPORT_ID_SIZE + CONTACT_COUNT_MAX_SIZE )
#define FINGER_REPORT_LENGTH      ( REPORT_ID_SIZE + FINGERS_DATA_SIZE + CONTACT_COUNT_SIZE + SCAN_TIME_SIZE )
#define STYLUS_REPORT_LENGTH      ( REPORT_ID_SIZE + STYLII_DATA_SIZE + CONTACT_COUNT_SIZE + SCAN_TIME_SIZE )
#if (FINGER_REPORT_LENGTH > STYLUS_REPORT_LENGTH)
#define MAX_REPORT_LENGTH FINGER_REPORT_LENGTH
#else
#define MAX_REPORT_LENGTH STYLUS_REPORT_LENGTH
#endif

/*
 * Definitions of the report indices, offsets and masks for F1 report type.
 */
#define FINGER_REPORT_ID_INDEX       0
#define FINGERS_BASE_INDEX           ( FINGER_REPORT_ID_INDEX + REPORT_ID_SIZE )
#define FINGER_CONTACT_COUNT_INDEX   ( FINGERS_BASE_INDEX + ( ONE_FINGER_DATA_SIZE * MAX_FINGER_TOUCHES_REPORTED ) )
#define FINGER_SCAN_TIME_LSB_INDEX   ( FINGER_CONTACT_COUNT_INDEX + CONTACT_COUNT_SIZE )
#define FINGER_SCAN_TIME_MSB_INDEX   ( FINGER_SCAN_TIME_LSB_INDEX + 1 )

#define FINGER_REPORT_BOOLEAN_INFO_OFFSET     0
#define FINGER_REPORT_CONTACT_ID_OFFSET       1
#define FINGER_REPORT_X_LSB_OFFSET            2
#define FINGER_REPORT_X_MSB_OFFSET            3
#define FINGER_REPORT_Y_LSB_OFFSET            4
#define FINGER_REPORT_Y_MSB_OFFSET            5
#define FINGER_REPORT_WIDTH_LSB_OFFSET        6
#define FINGER_REPORT_WIDTH_MSB_OFFSET        7
#define FINGER_REPORT_HEIGHT_LSB_OFFSET       8
#define FINGER_REPORT_HEIGHT_MSB_OFFSET       9
#define FINGER_REPORT_TIP_PRESSURE_LSB_OFFSET 10
#define FINGER_REPORT_TIP_PRESSURE_MSB_OFFSET 11
#define FINGER_REPORT_CONFIDENCE_LSB_OFFSET   12
#define FINGER_REPORT_CONFIDENCE_MSB_OFFSET   13

#define STYLUS_REPORT_BOOLEAN_INFO_OFFSET     0
#define STYLUS_REPORT_CONTACT_ID_OFFSET       1
#define STYLUS_REPORT_TRANSDUCER_INDEX_OFFSET 2
#define STYLUS_REPORT_X_LSB_OFFSET            3
#define STYLUS_REPORT_X_MSB_OFFSET            4
#define STYLUS_REPORT_Y_LSB_OFFSET            5
#define STYLUS_REPORT_Y_MSB_OFFSET            6
#define STYLUS_REPORT_WIDTH_LSB_OFFSET        7
#define STYLUS_REPORT_WIDTH_MSB_OFFSET        8
#define STYLUS_REPORT_HEIGHT_LSB_OFFSET       9
#define STYLUS_REPORT_HEIGHT_MSB_OFFSET       10
#define STYLUS_REPORT_TIP_PRESSURE_LSB_OFFSET 11
#define STYLUS_REPORT_TIP_PRESSURE_MSB_OFFSET 12
#define STYLUS_REPORT_CONFIDENCE_LSB_OFFSET   13
#define STYLUS_REPORT_CONFIDENCE_MSB_OFFSET   14

#define MASK_TIP_SWITCH       ( 1 << 0 )
#define MASK_INVERT           ( 1 << 1 )
#define MASK_ERASER           ( 1 << 2 )

#define PEN_TYPE_UNKNOWN 0x00
#define PEN_TYPE_STYLUS1 0x01
#define PEN_TYPE_STYLUS2 0x02
#define PEN_TYPE_ERASER  0xee


#define STYLUS_REPORT_ID_INDEX	     0
#define STYLII_BASE_INDEX            ( STYLUS_REPORT_ID_INDEX + REPORT_ID_SIZE )
#define STYLUS_CONTACT_COUNT_INDEX   ( STYLII_BASE_INDEX + ( ONE_STYLUS_DATA_SIZE * MAX_STYLUS_TOUCHES_REPORTED ) )
#define STYLUS_SCAN_TIME_LSB_INDEX   ( STYLUS_CONTACT_COUNT_INDEX + CONTACT_COUNT_SIZE )
#define STYLUS_SCAN_TIME_MSB_INDEX   ( STYLUS_SCAN_TIME_LSB_INDEX + 1 )

#define PHYSICAL_SCREEN_SIZE_X		18600
#define PHYSICAL_SCREEN_SIZE_Y		10460
#define LOGICAL_SCREEN_SIZE_X		5097
#define LOGICAL_SCREEN_SIZE_Y		2867

/*
 * HID IDs
 */
#define USB_VID_RAPT_TOUCH		0x2986
#undef HIDG_VENDOR_NUM
#define HIDG_VENDOR_NUM			USB_VID_RAPT_TOUCH
#undef HIDG_PRODUCT_NUM
#define HIDG_PRODUCT_NUM		0x0045

#define int16_to_le_bytes(i16)	((i16)&0xff), ((i16)>>8)

// Size 63 bytes
#define FINGER_DESCRIPTOR \
		0x05, 0x0d, /* USAGE_PAGE (Digitizers) */ \
		0x09, 0x22, /* USAGE (Finger)          */ \
		0xa1, 0x02, /* COLLECTION (Logical)    */ \
			\
			 /* 1 bit: TIP */ \
			0x09, 0x42, /* USAGE (Tip Switch)   */ \
			0x15, 0x00, /* LOGICAL_MINIMUM (0)  */ \
			0x25, 0x01, /* LOGICAL_MAXIMUM (1)  */ \
			0x75, 0x01, /* REPORT_SIZE (1)      */ \
			0x95, 0x01, /* REPORT_COUNT (1)     */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			0x95, 0x07, /* REPORT_COUNT (7)     */ \
			0x81, 0x03, /* INPUT (Cnst,Ary,Abs) */ \
			\
		 	/* 8 bits: Contact ID */ \
			0x75, 0x08, /* REPORT_SIZE (8)             */ \
			0x09, 0x51, /* USAGE ( Contact Identifier) */ \
			0x95, 0x01, /* REPORT_COUNT (1)            */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
			\
			/* X and Y, width and height */ \
			0x05, 0x01, /* USAGE_PAGE (Generic Desktop) */ \
			0x75, 0x10, /* REPORT_SIZE (16)             */ \
			0x55, 0x0e, /* UNIT_EXPONENT (-2)  */ \
		    0x65, 0x11, /* UNIT(cm,SILinear)   */ \
		    \
		    /* X */ \
			0x09, 0x30, /* USAGE (X)                    */ \
			0x15, 0x00, /* LOGICAL_MINIMUM (0)  */ \
			0x26, int16_to_le_bytes(LOGICAL_SCREEN_SIZE_X), \
			0x35, 0x00, /* PHYSICAL_MINIMUM (0) */			\
			0x46, int16_to_le_bytes(PHYSICAL_SCREEN_SIZE_X), /* PHYSICAL_MAXIMUM (1205) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			\
			/* Y */ \
			0x09, 0x31, /* USAGE (Y) */ \
			0x26, int16_to_le_bytes(LOGICAL_SCREEN_SIZE_Y), \
			0x46, int16_to_le_bytes(PHYSICAL_SCREEN_SIZE_Y), /* PHYSICAL_MAXIMUM (906)	*/ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			/*0x45, 0x00, *//* PHYSICAL_MAXIMUM (0)reset */ \
			\
			/* Width and Height */ \
			0x05, 0x0d, /* USAGE_PAGE (Digitizers) */ \
			0x09, 0x48, /* USAGE (Width) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			0x09, 0x49, /* USAGE (Height) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			\
		 	/* 16 bits: Tip pressure */ \
			0x09, 0x30, /* USAGE (Tip Pressure)        */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
			\
		 	/* 16 bits: Confidence */ \
			0x06, 0x00,0xff, /* USAGE_PAGE (Vendor-Defined 1) */      \
			0x09, 0x01, /* USAGE (Vendor-Defined 1)    */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
		0xc0, // END_COLLECTION


#define STYLUS_DESCRIPTOR \
		0x05, 0x0d, /* USAGE_PAGE (Digitizers) */ \
		0x09, 0x20, /* USAGE (Stylus)          */ \
		0xa1, 0x02, /* COLLECTION (Logical)    */ \
			\
			 /* 1 bit values: Tip, Invert, Eraser */ \
			0x15, 0x00, /* LOGICAL_MINIMUM (0)  */ \
			0x25, 0x01, /* LOGICAL_MAXIMUM (1)  */ \
			0x75, 0x01, /* REPORT_SIZE (1)      */ \
			0x95, 0x03, /* REPORT_COUNT (3)     */ \
			0x09, 0x42, /* USAGE (Tip Switch)   */ \
			0x09, 0x3c, /* USAGE (Invert)       */ \
			0x09, 0x45, /* USAGE (Eraser)       */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			0x95, 0x05, /* REPORT_COUNT (5)     */ \
			0x81, 0x03, /* INPUT (Cnst,Ary,Abs) */ \
			\
		 	/* 8 bits: Contact ID */ \
			0x26, 0xff, 0x00,/* LOGICAL_MAXIMUM (0xff) */ \
			0x75, 0x08, /* REPORT_SIZE (8)             */ \
			0x09, 0x51, /* USAGE (Contact Identifier)  */ \
			0x95, 0x01, /* REPORT_COUNT (1)            */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
			\
		 	/* 8 bits: Pen type/Transducer index       */ \
			0x09, 0x38, /* USAGE (Transducer Index)    */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
			\
			/* X and Y, width and height */ \
			0x05, 0x01, /* USAGE_PAGE (Generic Desktop) */ \
			0x75, 0x10, /* REPORT_SIZE (16)             */ \
			0x55, 0x0e, /* UNIT_EXPONENT (-2)  */ \
		    0x65, 0x11, /* UNIT(cm,SILinear)   */ \
		    \
		    /* X */ \
			0x09, 0x30, /* USAGE (X)                    */ \
			0x15, 0x00, /* LOGICAL_MINIMUM (0)  */ \
			0x26, int16_to_le_bytes(LOGICAL_SCREEN_SIZE_X), \
			0x35, 0x00, /* PHYSICAL_MINIMUM (0) */			\
			0x46, int16_to_le_bytes(PHYSICAL_SCREEN_SIZE_X), /* PHYSICAL_MAXIMUM (1205) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			\
			/* Y */ \
			0x09, 0x31, /* USAGE (Y) */ \
			0x26, int16_to_le_bytes(LOGICAL_SCREEN_SIZE_Y), \
			0x46, int16_to_le_bytes(PHYSICAL_SCREEN_SIZE_Y), /* PHYSICAL_MAXIMUM (906)	*/ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			/*0x45, 0x00, *//* PHYSICAL_MAXIMUM (0)reset */ \
			\
			/* Width and Height */ \
			0x05, 0x0d, /* USAGE_PAGE (Digitizers) */ \
			0x09, 0x48, /* USAGE (Width) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			0x09, 0x49, /* USAGE (Height) */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs) */ \
			\
		 	/* 16 bits: Tip pressure */ \
			0x09, 0x30, /* USAGE (Tip Pressure)        */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
			\
		 	/* 16 bits: Confidence */ \
			0x06, 0x00,0xff, /* USAGE_PAGE (Vendor-Defined 1) */      \
			0x09, 0x01, /* USAGE (Vendor-Defined 1)    */ \
			0x81, 0x02, /* INPUT (Data,Var,Abs)        */ \
		0xc0, // END_COLLECTION


static struct hidg_func_descriptor hid_data =
{
	.subclass		= 0, /* No subclass */
	.protocol		= 0,
	.report_length		= MAX_REPORT_LENGTH,
	.report_desc_length	= 84 * MAX_FINGER_TOUCHES_REPORTED + 81 + 95 * MAX_STYLUS_TOUCHES_REPORTED + 46,
	.report_desc		=
	{
		0x05, 0x0d, // USAGE_PAGE (Digitizers)
		0x09, 0x04, // USAGE (Touch Screen)

		0xa1, 0x01, // COLLECTION (Application)
		0x85, REPORTID_MTOUCH_FINGER, // REPORT_ID (Touch)

			FINGER_DESCRIPTOR //  1st FINGER
			FINGER_DESCRIPTOR //  2nd FINGER
			FINGER_DESCRIPTOR //  3rd FINGER
			FINGER_DESCRIPTOR //  4th FINGER
			FINGER_DESCRIPTOR //  5th FINGER
			FINGER_DESCRIPTOR //  6th FINGER
			FINGER_DESCRIPTOR //  7th FINGER
			FINGER_DESCRIPTOR //  8th FINGER
			FINGER_DESCRIPTOR //  9th FINGER
			FINGER_DESCRIPTOR // 10th FINGER

			// Number of finger contacts on the digitizer
			0x05, 0x0d, // USAGE_PAGE (Digitizers)				// 1 bytes report count
			0x09, 0x54, // USAGE (Contact Count)
			0x95, 0x01, // REPORT_COUNT (1)
			0x75, 0x08, // REPORT_SIZE (8)
			0x15, 0x00, // LOGICAL_MINIMUM (0)
			0x25, MAX_FINGER_TOUCHES_REPORTED, // LOGICAL_MAXIMUM (10)	// 1 byte report maximum count
			0x81, 0x02, // INPUT (Data,Var,Abs)

			// Scan Time
			0x55, 0x0C,                   // UNIT_EXPONENT (-4)
			0x66, 0x01, 0x10,             // UNIT (Seconds)
			0x47, 0xff, 0xff, 0x00, 0x00, // PHYSICAL_MAXIMUM (65535)
			0x27, 0xff, 0xff, 0x00, 0x00, // LOGICAL_MAXIMUM (65535)
			0x75, 0x10,                   // REPORT_SIZE (16)
			0x95, 0x01,                   // REPORT_COUNT (1)
			0x09, 0x56,                   // USAGE (Scan Time)
			0x81, 0x02,                   // INPUT (Data,Var,Abs)

		// Number of contacts on the digitizer
		0x85, REPORTID_MAX_COUNT, // REPORT_ID (Contact Count Max)
		0x05, 0x0d, // USAGE_PAGE (Digitizers)
		0x09, 0x55, // USAGE(Contact Count Maximum)
		0x95, 0x01, // REPORT_COUNT (1)
		0x75, 0x08, // REPORT_SIZE (8)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x25, MAX_TOUCHES_REPORTED, // LOGICAL_MAXIMUM (10) // 1 bytes report maximum count
		0xb1, 0x02, // FEATURE (Data,Var,Abs)

		// Definition of the binary blob report to support certification
		// Copied from "Windows Pointer Device Data Delivery Protocol", Oct 12, 2012,
		// section "Touch Hardware Quality Assurance" downloaded from
		// http://msdn.microsoft.com/library/windows/hardware/br259100
        //
        // Link now (09-Jun-2015) redirects to https://msdn.microsoft.com/en-us/library/windows/hardware/dn672287.aspx
        // which no longer has a link to the Word doc. Checking the original link on archive.org
        // gave a direct link to the Word doc:
        // http://download.microsoft.com/download/6/C/7/6C7720B0-0353-4D78-9D1E-12AC1D423C9B/windows-pointer-device-protocol.docx
        // "Touch Hardware Quality Assurance" section is also directly available at:
        // https://msdn.microsoft.com/en-us/library/windows/hardware/dn672284%28v=vs.85%29.aspx
		0x85, REPORTID_FIRMWARE_KEY,		// 	 REPORT_ID (Firmware key report)
		0x06, 0x00, 0xff,					//     USAGE_PAGE (Vendor Defined) 
		0x09, 0xC5,							//     USAGE (Vendor Usage 0xC5)   
		0x15, 0x00,							//     LOGICAL_MINIMUM (0)         
		0x26, 0xff, 0x00,					//     LOGICAL_MAXIMUM (0xff)
		0x75, 0x08,							//     REPORT_SIZE (8)            
		0x96, 0x00, 0x01,					//     REPORT_COUNT (0x100 (256))            
		0xb1, 0x02,							//     FEATURE (Data,Var,Abs)

		0xc0, // END_COLLECTION


		0x05, 0x0d, // USAGE_PAGE (Digitizers)
		0x09, 0x02, // USAGE (Pen)

		0xa1, 0x01, // COLLECTION (Application)
		0x85, REPORTID_MTOUCH_STYLUS, // REPORT_ID (Stylus)

			STYLUS_DESCRIPTOR //  1st STYLUS
			STYLUS_DESCRIPTOR //  2nd STYLUS
			STYLUS_DESCRIPTOR //  3rd STYLUS
			STYLUS_DESCRIPTOR //  4th STYLUS
			STYLUS_DESCRIPTOR //  5th STYLUS
			STYLUS_DESCRIPTOR //  6th STYLUS
			STYLUS_DESCRIPTOR //  7th STYLUS
			STYLUS_DESCRIPTOR //  8th STYLUS
			STYLUS_DESCRIPTOR //  9th STYLUS
			STYLUS_DESCRIPTOR //  10th STYLUS

			// Number of pen contacts
			0x05, 0x0d, // USAGE_PAGE (Digitizers)				// 1 bytes report count
			0x09, 0x54, // USAGE (Contact Count)
			0x95, 0x01, // REPORT_COUNT (1)
			0x75, 0x08, // REPORT_SIZE (8)
			0x15, 0x00, // LOGICAL_MINIMUM (0)
			0x25, MAX_STYLUS_TOUCHES_REPORTED, // LOGICAL_MAXIMUM (2)	// 1 byte report maximum count
			0x81, 0x02, // INPUT (Data,Var,Abs)

			// Scan Time
			0x55, 0x0C,                   // UNIT_EXPONENT (-4)
			0x66, 0x01, 0x10,             // UNIT (Seconds)
			0x47, 0xff, 0xff, 0x00, 0x00, // PHYSICAL_MAXIMUM (65535)
			0x27, 0xff, 0xff, 0x00, 0x00, // LOGICAL_MAXIMUM (65535)
			0x75, 0x10,                   // REPORT_SIZE (16)
			0x95, 0x01,                   // REPORT_COUNT (1)
			0x09, 0x56,                   // USAGE (Scan Time)
			0x81, 0x02,                   // INPUT (Data,Var,Abs)

		0xc0, // END_COLLECTION
	},
};


static struct platform_device hid_device = {
	.name			= "hidg",
	.id			= 0,
	.num_resources		= 0,
	.resource		= 0,
	.dev.platform_data	= &hid_data,
};


/*
 * Constant reports
 */
static const unsigned char max_count_report[] = { REPORTID_MAX_COUNT, MAX_TOUCHES_REPORTED };
static const unsigned char sample_binary_blob_report[] =
{
	REPORTID_FIRMWARE_KEY,
	0xfc, 0x28, 0xfe, 0x84, 0x40, 0xcb, 0x9a, 0x87, 0x0d, 0xbe, 0x57, 0x3c, 0xb6, 0x70, 0x09, 0x88,
	0x07, 0x97, 0x2d, 0x2b, 0xe3, 0x38, 0x34, 0xb6, 0x6c, 0xed, 0xb0, 0xf7, 0xe5, 0x9c, 0xf6, 0xc2,
	0x2e, 0x84, 0x1b, 0xe8, 0xb4, 0x51, 0x78, 0x43, 0x1f, 0x28, 0x4b, 0x7c, 0x2d, 0x53, 0xaf, 0xfc,
	0x47, 0x70, 0x1b, 0x59, 0x6f, 0x74, 0x43, 0xc4, 0xf3, 0x47, 0x18, 0x53, 0x1a, 0xa2, 0xa1, 0x71,
	0xc7, 0x95, 0x0e, 0x31, 0x55, 0x21, 0xd3, 0xb5, 0x1e, 0xe9, 0x0c, 0xba, 0xec, 0xb8, 0x89, 0x19,
	0x3e, 0xb3, 0xaf, 0x75, 0x81, 0x9d, 0x53, 0xb9, 0x41, 0x57, 0xf4, 0x6d, 0x39, 0x25, 0x29, 0x7c,
	0x87, 0xd9, 0xb4, 0x98, 0x45, 0x7d, 0xa7, 0x26, 0x9c, 0x65, 0x3b, 0x85, 0x68, 0x89, 0xd7, 0x3b,
	0xbd, 0xff, 0x14, 0x67, 0xf2, 0x2b, 0xf0, 0x2a, 0x41, 0x54, 0xf0, 0xfd, 0x2c, 0x66, 0x7c, 0xf8,
	0xc0, 0x8f, 0x33, 0x13, 0x03, 0xf1, 0xd3, 0xc1, 0x0b, 0x89, 0xd9, 0x1b, 0x62, 0xcd, 0x51, 0xb7,
	0x80, 0xb8, 0xaf, 0x3a, 0x10, 0xc1, 0x8a, 0x5b, 0xe8, 0x8a, 0x56, 0xf0, 0x8c, 0xaa, 0xfa, 0x35,
	0xe9, 0x42, 0xc4, 0xd8, 0x55, 0xc3, 0x38, 0xcc, 0x2b, 0x53, 0x5c, 0x69, 0x52, 0xd5, 0xc8, 0x73,
	0x02, 0x38, 0x7c, 0x73, 0xb6, 0x41, 0xe7, 0xff, 0x05, 0xd8, 0x2b, 0x79, 0x9a, 0xe2, 0x34, 0x60,
	0x8f, 0xa3, 0x32, 0x1f, 0x09, 0x78, 0x62, 0xbc, 0x80, 0xe3, 0x0f, 0xbd, 0x65, 0x20, 0x08, 0x13,
	0xc1, 0xe2, 0xee, 0x53, 0x2d, 0x86, 0x7e, 0xa7, 0x5a, 0xc5, 0xd3, 0x7d, 0x98, 0xbe, 0x31, 0x48,
	0x1f, 0xfb, 0xda, 0xaf, 0xa2, 0xa8, 0x6a, 0x89, 0xd6, 0xbf, 0xf2, 0xd3, 0x32, 0x2a, 0x9a, 0xe4,
	0xcf, 0x17, 0xb7, 0xb8, 0xf4, 0xe1, 0x33, 0x08, 0x24, 0x8b, 0xc4, 0x43, 0xa5, 0xe5, 0x24, 0xc2
};
static const struct {
	uint16_t length;
	const unsigned char *report;
} constant_reports[] =
{
	{ sizeof(max_count_report), max_count_report },
	{ sizeof(sample_binary_blob_report), sample_binary_blob_report }
};


#endif /* HID_DEVICE_H_ */
