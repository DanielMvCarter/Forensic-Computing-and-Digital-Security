/* ntpclient.c - A client for the ntp protocol which sends and recieves a packet from an ntp server to set the clients system clock
 * Authors: Daniel Carter 15019617
 * Last updated: 07/12/2016 09:30pm
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include "timeconverter.h"
#include "packetstructure.h"

/* for gethostbyname() */
#define PORT 123
/* server port the client connects to */
int main( int argc, char * argv[]) {
int sockfd, numbytes, addr_len;
struct hostent *he;
struct sockaddr_in their_addr;

struct ntp_time_t ntp;
struct timeval nunix;
struct ntppacket packet;
struct ntppacket packet1;

packet.flags = 0x23;
packet.stratum = 0x03;
packet.poll = 0x00;
packet.precision = 0x00;

packet.rootDelay = 0x0000;
packet.rootDispersion = 0x0000;
packet.referenceIdentifier = 0x0000;

packet.referenceTimestampSec = 0x0000;
packet.referenceTimestampFrac = 0x0000;

packet.originateTimestampSec = 0x0000;
packet.originateTimestampFrac = 0x0000;

packet.recieveTimestampSec = 0x0000;
packet.recieveTimestampFrac = 0x0000;

gettimeofday(&nunix, NULL);

convert_unix_time_into_ntp_time(&nunix, &ntp);

packet.transmitTimestampSec = ntp.second;
packet.transmitTimestampFrac = ntp.fraction;

packet.transmitTimestampSec = htonl(packet.transmitTimestampSec);
packet.transmitTimestampFrac = htonl(packet.transmitTimestampFrac);


/* resolve server host name or IP address */
if( (he = gethostbyname( argv[ 1])) == NULL) {
perror( "Talker gethostbyname");
exit( 1);
}
if( (sockfd = socket( AF_INET, SOCK_DGRAM, 0)) == -1) {
perror( "Talker socket");
exit( 1);
}
memset( &their_addr,0, sizeof(their_addr));
/* zero struct */
their_addr.sin_family = AF_INET;
/* host byte order .. */
their_addr.sin_port = htons( PORT);
/* .. short, netwk byte order */
their_addr.sin_addr = *((struct in_addr *)he -> h_addr);
if( (numbytes = sendto( sockfd, &packet, sizeof(packet), 0,
(struct sockaddr *)&their_addr, sizeof( struct sockaddr))) == -1) {
perror( "Talker sendto");
exit( 1);
}
printf( "Sent %d bytes to %s\n", numbytes,
 inet_ntoa( their_addr.sin_addr));

addr_len = sizeof(their_addr);
numbytes = recvfrom(sockfd, (char*)&packet1, sizeof(packet1), 0,(struct sockaddr *)&their_addr, addr_len);

printf("time: %ld", packet1.transmitTimestampSec);


packet1.originateTimestampSec = ntohl(packet1.originateTimestampSec);
packet1.originateTimestampFrac = ntohl(packet1.originateTimestampFrac);

convert_ntp_time_into_unix_time(&ntp, &nunix);

time_t timesec = packet1.transmitTimestampSec;

printf("time: %s", ctime(&timesec));
printf("unix Time: %ld %ld\n", packet1.originateTimestampSec, packet1.originateTimestampFrac);

close( sockfd);
return 0;
}
