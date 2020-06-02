#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
//#include "funciones.h"
//#include "ARP.h"

int main(int argc, char const *argv[])
{
	unsigned char checksum[2] = {0x4A,0xFD};
	unsigned char complemento[2] = {0xFF,0xFF};
	unsigned int aux = checksum[0],aux2 = complemento[0];
	aux2 = aux2 << 8;
	aux2 += complemento[1];

	aux = aux << 8;
	aux += checksum[1];
	aux += 2;
	aux = aux2 - aux;
	printf("%x\n",aux);


	return 0;
}