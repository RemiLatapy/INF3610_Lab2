#include "cpu1_uc.h"

///////////////////////////////////////////////////////////////////////////////////////
//								Routines d'interruptions
///////////////////////////////////////////////////////////////////////////////////////

void irq_gen_0_isr(void* data) {
	/* À compléter */
	xil_printf("+++ irq_gen_0_isr\n");
	err_msg ("", OSSemPost( semReceptionTask ) );
	XIntc_Acknowledge(&m_axi_intc, RECEIVE_PACKET_IRQ_ID);
	//a notice for linux
	Xil_Out32(m_irq_gen_0.Config.BaseAddress, 0x0);//Xil_In32(m_irq_gen_0.Config.BaseAddress) & 0x0FFFFFFF);//****verifier
	xil_printf("--- irq_gen_0_isr\n");
}

void irq_gen_1_isr(void* data) {
	/* À compléter */
	xil_printf("+++ irq_gen_1_isr\n");
	err_msg ("", OSSemPost( semStatisticTask ) );
	XIntc_Acknowledge(&m_axi_intc, PRINT_STATS_IRQ_ID);

	//a notice for linux
	Xil_Out32(m_irq_gen_1.Config.BaseAddress, 0);//Xil_In32(m_irq_gen_1.Config.BaseAddress) & 0x0FFFFFFF);//******verifier
	xil_printf("+++ irq_gen_1_isr\n");
}
void timer_isr(void* not_valid) {
	if (private_timer_irq_triggered()) {
		private_timer_clear_irq();
		OSTimeTick();
	}                           
}

void fit_timer_1s_isr(void *not_valid) {
	/* À compléter */
	//xil_printf("+++ fit_timer_1s_isr\n");
	err_msg ("", OSSemPost( semStopServiceTask ) );
	XIntc_Acknowledge(&m_axi_intc, FIT_1S_IRQ_ID);
	//xil_printf("--- fit_timer_1s_isr\n");
}
void fit_timer_5s_isr(void *not_valid) {
	/* À compléter */
	//xil_printf("+++ fit_timer_5s_isr\n");
	err_msg ("", OSSemPost( semVerificationTask ) );
	XIntc_Acknowledge(&m_axi_intc, FIT_5S_IRQ_ID);
	//xil_printf("--- fit_timer_5s_isr\n");
}

///////////////////////////////////////////////////////////////////////////////////////
//								uC/OS-II part
///////////////////////////////////////////////////////////////////////////////////////
int main() {
	int error;
	initialize_bsp();

	// Initialize uC/OS-II
	OSInit();

	error = create_application();
	if(error != 0) return error;

	xil_printf("*** Application created ***\n");

	prepare_and_enable_irq();
	xil_printf("*** IRQ enable ***\n");

	xil_printf("*** Starting uC/OS-II scheduler ***\n");

	OSStart();

	cleanup();

	return 0;
}

int create_application() {
	int error = 0;

	error = create_tasks();
	if (error != 0)
		xil_printf("Error %d while creating tasks\n", error);

	error = create_events();
	if (error != 0)
		xil_printf("Error %d while creating events\n", error);

	return error;
}

int create_tasks() {
	/* À compléter */
	if(OSTaskCreate(TaskReceivePacket, NULL, &TaskReceiveStk[TASK_STK_SIZE - 1], TASK_RECEIVE_PRIO))	return -101;
	if(OSTaskCreate(TaskComputing, NULL, &TaskComputeStk[TASK_STK_SIZE - 1], TASK_COMPUTING_PRIO))	return -102;
	if(OSTaskCreate(TaskVerification, NULL, &TaskVerificationStk[TASK_STK_SIZE - 1], TASK_VERIFICATION_PRIO))	return -103;
	if(OSTaskCreate(TaskPrint, &print_param1, &TaskPrint1Stk[TASK_STK_SIZE - 1], TASK_PRINT1_PRIO))	return -104;
	if(OSTaskCreate(TaskPrint, &print_param2, &TaskPrint2Stk[TASK_STK_SIZE - 1], TASK_PRINT2_PRIO))	return -105;
	if(OSTaskCreate(TaskPrint, &print_param3, &TaskPrint3Stk[TASK_STK_SIZE - 1], TASK_PRINT3_PRIO))	return -106;
	if(OSTaskCreate(TaskStats, NULL, &TaskStatsStk[TASK_STK_SIZE - 1], TASK_STATS_PRIO))	return -107;
	if(OSTaskCreate(TaskStop, NULL, &TaskStopStk[TASK_STK_SIZE - 1], TASK_STOP_PRIO))	return -108;
	return 0;
}

int create_events() {
	INT8U err;

	/*CREATION DES FILES*/
	// Some bugs here ******** maybe try &inputMsg[0] instead of inputMsg
	inputQ = OSQCreate(inputMsg, 16);
	if(!inputQ)	return -201;

	verifQ = OSQCreate(verifMsg, 10);
	if(!verifQ)	return -202;

	lowQ = OSQCreate(lowMsg, 4);
	if(!lowQ)	return -203;

	mediumQ = OSQCreate(mediumMsg, 4);
	if(!mediumQ)	return -204;

	highQ = OSQCreate(highMsg, 4);
	if(!highQ)	return -205;

	/*CREATION DES MAILBOXES*/

	Mbox1 = OSMboxCreate(NULL);
	if(!Mbox1)	return -206;

	Mbox2 = OSMboxCreate(NULL);
	if(!Mbox2)	return -207;

	Mbox3 = OSMboxCreate(NULL);
	if(!Mbox3)	return -208;

	/*CREATION DES MUTEX*/
	mutexPrint = OSMutexCreate(MTX_PRINT_PRIO, &err);
	err_msg("", err);
	if(!mutexPrint)	return -209;

	/*ALLOCATION ET DEFINITIONS DES STRUCTURES PRINT_PARAM*/
	print_param1.Mbox =  Mbox1;
	print_param1.interfaceID = 1;

	print_param2.Mbox =  Mbox2;
	print_param2.interfaceID = 2;

	print_param3.Mbox =  Mbox3;
	print_param3.interfaceID = 3;

	/*CREATION DES SEMAPHORES*/
	semReceptionTask = OSSemCreate(0);
	if(!mutexPrint)	return -210;

	semVerificationTask = OSSemCreate(0);
	if(!mutexPrint)	return -211;

	semStopServiceTask = OSSemCreate(0);
	if(!mutexPrint)	return -212;

	semStatisticTask = OSSemCreate(0);
	if(!mutexPrint)	return -213;

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////
//								uC/OS-II part
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//									TASKS
///////////////////////////////////////////////////////////////////////////////////////


/*
 *********************************************************************************************************
 *                                              computeCRC
   -Calcule la check value d'un paquet en utilisant un CRC (cyclic redudancy check)
 *********************************************************************************************************
 */
unsigned int computeCRC(INT16U* w, int nleft) {
	unsigned int sum = 0;
	INT16U answer = 0;

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

/*
 *********************************************************************************************************
 *                                              TaskreceivePacket
 *  -Injecte des paquets dans la InputQ lorsqu'il en recoit de linux
 *********************************************************************************************************
 */
void TaskReceivePacket(void *data) {
	int k;
	INT8U err;

	Packet *packet;

	for (;;) {

		/* À compléter : Réception des paquets de Linux */
		xil_printf("+++ ReceiveTask\n");
		OSSemPend(semReceptionTask, 0, &err);
		err_msg("", err);

		nbPacket++;

		packet = malloc(sizeof(Packet));

		while(COMM_RX_FLAG != 0x1);

		packet->src = COMM_RX_DATA;
		COMM_RX_FLAG = 0x0;
		while(COMM_RX_FLAG != 0x1);

		packet->dst = COMM_RX_DATA;
		COMM_RX_FLAG = 0x0;
		while(COMM_RX_FLAG != 0x1);

		packet->type = COMM_RX_DATA;
		COMM_RX_FLAG = 0x0;
		while(COMM_RX_FLAG != 0x1);

		packet->crc = COMM_RX_DATA;

		//reading the payload of the packet
		for(k = 0; k < 12; k++)
		{
			COMM_RX_FLAG = 0x0;
			while(COMM_RX_FLAG != 0x1);
			packet->data[k] = COMM_RX_DATA;
		}

		COMM_RX_FLAG = 0x0;

		OSMutexPend(mutexPrint, 0, &err);
		err_msg("", err);

		xil_printf("RECEIVE : ********Reception du Paquet # %d ******** \n", nbPacketSent++);
		xil_printf("ADD %x \n", packet);
		xil_printf("    ** src : %x \n", packet->src);
		xil_printf("    ** dst : %x \n", packet->dst);
		xil_printf("    ** type : %d \n", packet->type);
		xil_printf("    ** crc : %x \n", packet->crc);

		err_msg("", OSMutexPost(mutexPrint));

		/* À compléter: Transmission des paquets dans l'inputQueue */
		err_msg("", OSQPost(inputQ, (void *)packet));

		xil_printf("--- ReceiveTask\n");
	}
}


/*
 *********************************************************************************************************
 *                                              TaskVerification
 *  -Réinjecte les paquets rejetés des files haute, medium et basse dans la inputQ
 *********************************************************************************************************
 */
void TaskVerification(void *data) {
	INT8U err;
	Packet *packet = NULL;
	OS_Q_DATA pdata;
	INT16U nMsg;
	while (1)
	{
		/* À compléter */
		OSSemPend(semVerificationTask, 0, &err);
		err_msg("", err);
		xil_printf("+++ VerificationTask\n");

		err_msg("", OSQQuery(verifQ, &pdata));

		for(nMsg = pdata.OSNMsgs ; nMsg > 0 ; nMsg--)
		{
			packet = OSQPend(verifQ, 5, &err);
			err_msg("", err);
			if(err == OS_ERR_TIMEOUT)
			{
				xil_printf("VerificationTask: timeout err ***************************\n");
				break;
			}
			else if (err == OS_ERR_NONE)
			{
				err = OSQPost(inputQ, (void *)packet);
				err_msg("", err);

				if (err == OS_ERR_Q_FULL)
				{
					free(packet);
					nbPacketQFullRejete++;
					xil_printf("VerificationTask: packet rejected(InputQ FULL) ***************************\n");
				}

			}
		}

		xil_printf("--- VerificationTask\n");
	}
}
/*
 *********************************************************************************************************
 *                                              TaskStop
 *  -Stoppe le routeur une fois que 5 (15 ?)  paquets ont étés rejetés pour mauvais CRC
 *********************************************************************************************************
 */
void TaskStop(void *data) {
	INT8U err;
	while(1) {
		/* À compléter */
		OSSemPend(semStopServiceTask, 0, &err);
		err_msg("", err);
		if (nbPacketCRCRejete >= 15)
		{
			OSTaskDel(OS_PRIO_SELF);
		}
	}
}

/*
 *********************************************************************************************************
 *                                              TaskComputing
 *  -Vérifie si les paquets sont conformes (CRC,Adresse Source)
 *  -Dispatche les paquets dans des files (HIGH,MEDIUM,LOxmd
 *
 *********************************************************************************************************
 */
void TaskComputing(void *pdata) {
	INT8U err;
	Packet *packet = NULL;
	int rejected = 0;
	while(1){
		/* À compléter */
		packet = (Packet *) OSQPend(inputQ, 0, &err);
		xil_printf("+++ ComputingTask\n");
		rejected = 0;

		if(		(packet->src > REJECT_LOW1 && packet->src < REJECT_HIGH1)
				||
				(packet->src > REJECT_LOW2 && packet->src < REJECT_HIGH2)
				||
				(packet->src > REJECT_LOW3 && packet->src < REJECT_HIGH3)
				||
				(packet->src > REJECT_LOW4 && packet->src < REJECT_HIGH4)
		)
		{
			xil_printf("ComputingTask : packet destroy (bad src)\n"); //*********** A verifier la cond du if
			nbPacketSourceRejete++;
			rejected = 1;
		}
		else if (computeCRC((INT16U*) packet, 64) == 0)
		{
			switch (packet->type)
			{
			case 0: // video
				err = OSQPost(highQ, (void *)packet);
				break;
			case 1: // audio
				err = OSQPost(mediumQ, (void *)packet);
				break;
			case 2: // autres
				err = OSQPost(lowQ, (void *)packet);
				break;
			}
			err_msg("", err);
			if(err == OS_ERR_Q_FULL)
			{
				err =  OSQPost(verifQ, (void *)packet);
				err_msg("", err);
				if(err == OS_ERR_Q_FULL)
				{
					xil_printf("ComputingTask : packet destroy (verifQ is full)\n");
					nbPacketQFullRejete++;
					rejected = 1;
					free(packet);
				}
			}
		} else {
			xil_printf("ComputingTask : packet destroy (bad CRC)\n");
			nbPacketCRCRejete++;
			rejected = 1;
		}

		if(rejected == 1)
		{
			switch (packet->type)
			{
			case 0: // video
				nbPacketHighRejete++;
				break;
			case 1: // audio
				nbPacketMediumRejete++;
				break;
			case 2: // autres
				nbPacketLowRejete++;
				break;
			}
			free(packet);
		}

		xil_printf("--- ComputingTask\n");
	}
}

/*
 *********************************************************************************************************
 *                                              TaskForwarding1
 *  -traite la priorité des paquets : si un paquet de haute priorité est prêt,
 *   on l'envoie à l'aide de la fonction dispatch, sinon on regarde les paquets de moins haute priorité
 *********************************************************************************************************
 */
void TaskForwarding(void *pdata) {
	INT8U err;
	Packet *packet = NULL;

	while(1){
		/* À compléter */
		packet = OSQPend(highQ, 5, &err);
		if ( err == OS_ERR_TIMEOUT )
		{
			packet = OSQPend(mediumQ, 5, &err);
			if( err == OS_ERR_TIMEOUT )
			{
				packet = OSQPend(lowQ, 5, &err);
				if (err == OS_ERR_TIMEOUT)
				{
					continue;
				}
			}
		}
		OSTimeDly(2);

		if( packet->dst > INTBRDCST_LOW && packet->dst <= INTBRDCST_HIGH )
		{
			//BROADCASTING
			Packet *packet2 = malloc(sizeof(Packet));
			memcpy(packet2, packet, sizeof(Packet));

			Packet *packet3 = malloc( sizeof(Packet));
			memcpy(packet3, packet, sizeof(Packet));

			err_msg( "", OSMboxPost(Mbox1, packet));
			err_msg( "", OSMboxPost(Mbox2, packet2));
			err_msg( "", OSMboxPost(Mbox3, packet3));
		}
		else if( packet->dst > INT1_LOW && packet->dst < INT1_HIGH )
		{
			err_msg( "", OSMboxPost(Mbox1, packet));
		}
		else if( packet->dst > INT2_LOW && packet->dst < INT2_HIGH )
		{
			err_msg( "", OSMboxPost(Mbox2, packet));
		}
		else if ( packet->dst > INT3_LOW && packet->dst < INT3_HIGH )
		{
			err_msg( "", OSMboxPost(Mbox3, packet));
		}
	}
}

/*
 *********************************************************************************************************
 *                                              TaskStats
 *  -Est déclenchée lorsque le irq_gen_1_isr() libère le sémaphore
 *  -Lorsque déclenchée, Imprime les statistiques du routeur à cet instant
 *********************************************************************************************************
 */
void TaskStats(void *pdata) {
	INT8U err;

	while(1){
		/* À compléter */

		OSMutexPend(mutexPrint, 0, &err);
		err_msg("", err);

		xil_printf("STATS : ******** Statistiques du Routeur ******** \n");
		xil_printf("    ** nbPacketSent : %i \n", nbPacketSent);
		xil_printf("    ** nbPacketReceive : %i \n", nbPacket);
		xil_printf("    ** nbPacketLowRejete : %i \n", nbPacketLowRejete);
		xil_printf("    ** nbPacketMediumRejete : %i \n", nbPacketMediumRejete);
		xil_printf("    ** nbPacketHighRejete : %i \n", nbPacketHighRejete);
		xil_printf("    ** nbPacketCRCRejete : %i \n", nbPacketCRCRejete);
		xil_printf("    ** nbPacketSourceRejete : %i \n", nbPacketSourceRejete);
		xil_printf("    ** nbPacketQFullRejete : %i \n", nbPacketQFullRejete);

		err_msg("", OSMutexPost(mutexPrint));
	}

}


/*
 *********************************************************************************************************
 *                                              TaskPrint
 *  -Affiche les infos des paquets arrivés à destination et libere la mémoire allouée
 *********************************************************************************************************
 */
void TaskPrint(void *data) {
	INT8U err;
	Packet *packet = NULL;
	int intID = ((PRINT_PARAM*)data)->interfaceID;
	OS_EVENT* mb = ((PRINT_PARAM*)data)->Mbox;

	while(1)
	{
		/* À compléter */
		packet = OSMboxPend( mb, 0, &err);
		err_msg("", err);

		OSMutexPend(mutexPrint, 0, &err);
		err_msg("", err);

		xil_printf("interface %i\n", intID);
		xil_printf("    ** src : %x \n", packet->src);
		xil_printf("    ** dst : %x \n", packet->dst);
		xil_printf("    ** type : %d \n", packet->type);
		xil_printf("    ** crc : %x \n", packet->crc);

		err_msg("", OSMutexPost(mutexPrint));
	}

}
void err_msg(char* entete, INT8U err)
{
	if(err != 0)
	{
		xil_printf(entete);
		xil_printf(": Une erreur est retournée : code %d \n",err);
	}
}

