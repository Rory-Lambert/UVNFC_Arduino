/********************************************
 *           NDEF MESSAGE HEADER            *
 *              Rory Lambert                *
 *        last edited: 3 March 2014         *
 *               V1.0                       *
 ********************************************/

/*This Header Contains all the necessary byte
 *arrays for preparing our NDEF message	    */

#ifndef RLMSG2_H
#define RLMSG2_H


/****************************************
 *Array defining the message setup bytes*
 ***************************************/

#define MSG_SETUP { 						\
/*NDEF Tag Application*/					\
0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01,	\
											\
/*Capability Container ID*/					\
0xE1, 0x03,									\
											\
/*Capability Container File Start*/			\
											\
0x00, 0x0F, /*CC File Length - 15Bytes*/	\
0x20, 		/*Mapping Version 2.0*/			\
0x00, 0x3B, /*MLe*/							\
0x00, 0x34,	/*MLc*/							\
0x04,		/*TLV*/							\
0x06, 		/*Length*/						\
0xE1, 0x04, /*Type 4 Tag File Identifier*/	\
0x0B, 0xDF,	/*Max NDEF File Size 3037*/ 	\
0x00, 0x00,	/*Read/Write Conditions*/		\
											\
/**********NDEF File Start **************/	\
											\
/*NDEF File ID*/ 							\
0xE1, 0x04, 								\
											\
/*****NDEF FILE LENGTH********/				\
/*2 Bytes reserved for varying file length*/\
0x00, 0x40,	/*[0x1A, 0x1B]*/				\
											\
/*Ndef message start*/						\	
0x92, 0x1B, 0x01, /*last bit payload length!!!*/\
}


/****************************************
 *Array defining message MIME TYPE      *
 ***************************************/

/*"application/uk.ac.gla.uvnfc"*/ 
#define MIME_TYPE {							\
0x61,\
0x70,\
0x70,\
0x6C,\
0x69,\
0x63,\
0x61,\
0x74,\
0x69,\
0x6F,\
0x6E,\
0x2F,\
0x75,\
0x6B,\
0x2E,\
0x61,\
0x63,\
0x2E,\
0x67,\
0x6C,\
0x61,\
0x2E,\
0x75,\
0x76,\
0x6E,\
0x66,\
0x63,\
}
 

/****************************************
 * Payload Data-------------------------*
 ***************************************/
#define PAYLOAD{\
0x49,\
0x52,\
0x4E,\
0x42,\
0x52,\
0x55,\
0x20,\
0x40,\
}

#define PAYLOAD2{\
0x52, 0x52, 0x52\
}

/****************************************
 *------ANDROID APPLICATION RECORD------*
 ***************************************/

#define AAR{								\
0x54,\  
0x0F,\  
0x0F,\  
0x61,\  
0x6E,\  
0x64,\  
0x72,\  
0x6F,\  
0x69,\  
0x64,\  
0x2E,\
0x63,\
0x6F,\
0x6D,\
0x3A,\
0x70,\
0x6B,\
0x67,\
0x75,\
0x6B,\
0x2E,\
0x61,\
0x63,\
0x2E,\
0x67,\
0x6C,\
0x61,\
0x2E,\
0x75,\
0x76,\
0x6E,\
0x66,\
0x63,\
}

//define the lengths of the arrays - const, wont change!
const static int SETUP_LEN=  31;
const static int MIME_LEN =  27; 
const static int AAR_LEN =   33;
const static int PRE_PAY_LEN = 91;
const static int PACK_LEN = 63;

//define the locations of the two bytes dictating message length
const static int LEN_BYTE_PACK = 0x1B;   //full NDEF (after setup)
const static int LEN_BYTE_PAY = 0x1E;    //payload length

/***************************************************************/
#define EEPROM_address_W1 0xA0      //changed from 0x50 //write to block 1
#define EEPROM_address_R1 0xA1      //read from bloack 1 
byte Device_ID_MSB = 0;     //Allows for 65536 devices… 
byte Device_ID_LSB = 1;     //… as a gallery may have over 128
byte Year = 14;             //1 byte allows for 128 years. 0 = year 2000
byte Day_MSB = 1;           //xxxxxxBB  10 bits allow for 512 days > 365
byte Day_LSB = 83;          //Day 183 is July 3
byte Time_Hr = 23;          //Hour of Day (24hr clock)     
byte Time_Min =59;          //Time in minutes 
byte Interval = 5;          //Measurement Interval (1 to 128 mins)
byte Total_1  = 0;          //(Memory pointer) (byte 1)
byte Total_2  = 0;
byte Total_3  = 1;

//made a change for github

#endif /* RLMSG2_H */

