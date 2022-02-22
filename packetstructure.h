#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

struct ntppacket {
	unsigned char flags; //Holds the flags, the 1st 2 bits are LI, next 3 are VN and the last 3 are Mode.
	unsigned char stratum;
	unsigned char poll;
	unsigned char precision;

	int rootDelay;
	int rootDispersion;
	int referenceIdentifier;

	uint32_t referenceTimestampSec;
	uint32_t referenceTimestampFrac;

	uint32_t originateTimestampSec;
	uint32_t originateTimestampFrac;

	uint32_t recieveTimestampSec;
	uint32_t recieveTimestampFrac;

	uint32_t transmitTimestampSec;
	uint32_t transmitTimestampFrac;
};
