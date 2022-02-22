//Source code: http://waitingkuo.blogspot.co.uk/2012/06/conversion-between-ntp-time-and-unix.html

#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

struct ntp_time_t {
    uint32_t   second;
    uint32_t    fraction;
};

void convert_ntp_time_into_unix_time(struct ntp_time_t *ntp, struct timeval *nunix)
{
    nunix->tv_sec = ntp->second - 0x83AA7E80; // the seconds from Jan 1, 1900 to Jan 1, 1970
    nunix->tv_usec = (uint32_t)( (double)ntp->fraction * 1.0e6 / (double)(1LL<<32) );
}

void convert_unix_time_into_ntp_time(struct timeval *nunix, struct ntp_time_t *ntp)
{
    ntp->second = nunix->tv_sec + 0x83AA7E80;
    ntp->fraction = (uint32_t)( (double)(nunix->tv_usec+1) * (double)(1LL<<32) * 1.0e-6 );
}
