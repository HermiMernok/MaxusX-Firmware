/*
 * TCP.c
 *
 *  Created on: 03 Oct 2018
 *      Author: H du Plessis
 */
#include "lwip.h"

struct netif gnetif;


void Ethernet_Handler()
{
	/* Read a received packet from the Ethernet buffers and send it   to the lwIP for handling */
	ethernetif_input(&gnetif);
	/* Handle timeouts */
	sys_check_timeouts();
}

void Init_Ethernet()
{
	ethernetif_set_link(&gnetif);
}
