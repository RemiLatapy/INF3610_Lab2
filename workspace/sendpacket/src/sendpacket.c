/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <byteswap.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <sys/mman.h>
#include <time.h>

#define PAGE_SIZE ((size_t)getpagesize())
#define PAGE_MASK ((uint64_t)(long)~(PAGE_SIZE - 1))

#define COMM_BASE        0xFFFF9000
#define COMM_TX_FLAG_OFFSET    0x00
#define COMM_TX_DATA_OFFSET    0x04
#define COMM_RX_FLAG_OFFSET    0x08
#define COMM_RX_DATA_OFFSET    0x0C

#define INTERRUPT_BASE   0x78600000


typedef struct {
    unsigned int src;
    unsigned int dst;
    unsigned int type;
    unsigned int crc;
    unsigned int data[12];
} Packet;

unsigned int computeCRC(unsigned short* w, int nleft) {
    unsigned int sum = 0;
    unsigned short answer = 0;

    // Adding words of 16 bits
    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    // Handling the last byte
    if (nleft == 1) {
        *(unsigned char *) (&answer) = *(const unsigned char *) w;
        sum += answer;
    }

    // Handling overflow
    sum = (sum & 0xffff) + (sum >> 16);
    sum += (sum >> 16);

    answer = ~sum;
    return (unsigned int) answer;
}
int main()
{
	//Creation d'un paquet
	srand(4600);

	int i,j,k;
	int fd;
	Packet packet;
    volatile uint8_t *mm1, *mm2;

    fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd < 0) {
		fprintf(stderr, "open(/dev/mem) failed (%d)\n", errno);
		return 1;
	}

    mm1 = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, COMM_BASE);
    if (mm1 == MAP_FAILED) {
    	fprintf(stderr, "mmap64(0x%x@0x%x) failed (%d)\n",
    	        PAGE_SIZE, (uint32_t)(COMM_BASE), errno);
    	return 1;
    }

    mm2 = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, INTERRUPT_BASE);
	if (mm2 == MAP_FAILED) {
		fprintf(stderr, "mmap64(0x%x@0x%x) failed (%d)\n",
				PAGE_SIZE, (uint32_t)(INTERRUPT_BASE), errno);
		return 1;
	}


	for(i = 0; i < 1000; i++) {
		packet.src = rand();
		packet.dst = 2 * (unsigned int) rand();
		packet.type = rand() % 3; // Three types of packet (High = 0, Medium = 1, Low = 2);
		for (j = 0; j < 12; j++) {
			packet.data[j] = rand();
		}
		packet.crc = 0;
		if (rand() % 10 == 9) // 10% of Packets with bad CRC
			packet.crc = 1234;
		else
			packet.crc = computeCRC((unsigned short*) (&packet), 64);

		printf("\n ***** LINUX : Generation du Paquet # %d ***** \n", i);
		printf("    -src : %#8X \n", packet.src);
		printf("    -dst : %#8X \n", packet.dst);
		printf("    -type: %d \n", packet.type);
		printf("    -crc : %#8X \n", packet.crc);

	   //G�n�ration d'une interruption
	   *(volatile uint32_t *)(mm2 + 0) = (uint32_t) 1;

		//Envoi du paquet sur la m�moire partag�e
		uint32_t *ll;
		ll = (uint32_t *) (&packet);
		for(k = 0; k < 16; k++)
		{
			while(*(mm1 + COMM_RX_FLAG_OFFSET)); //wait for uC to consume the value
			*(volatile uint32_t *)( mm1 + COMM_RX_DATA_OFFSET ) = *ll++; // next part of the packet
			*(volatile uint32_t *)( mm1 + COMM_RX_FLAG_OFFSET ) = 1;
		}

		sleep(1);
	}
	munmap((void *)mm1, PAGE_SIZE);
	munmap((void *)mm2, PAGE_SIZE);
	close(fd);
    return 0;
}
