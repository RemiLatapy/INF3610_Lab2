#include "cpu1_uc.h"

///////////////////////////////////////////////////////////////////////////////////////
//								Routines d'interruptions
///////////////////////////////////////////////////////////////////////////////////////

void irq_gen_0_isr(void* data) {
	/* � compl�ter */
	xil_printf("+++ irq_gen_0_isr\n");
	err_msg ("", OSSemPost( semReceptionTask ) );
	XIntc_Acknowledge(&m_axi_intc, RECEIVE_PACKET_IRQ_ID);

	//a notice for linux
	Xil_Out32(m_irq_gen_0.Config.BaseAddress, 0x0);//Xil_In32(m_irq_gen_0.Config.BaseAddress) & 0x0FFFFFFF);//****verifier
	xil_printf("--- irq_gen_0_isr\n");
}

void irq_gen_1_isr(void* data) {
	/* � compl�ter */
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
	/* � compl�ter */
	//xil_printf("+++ fit_timer_1s_isr\n");
	err_msg ("", OSSemPost( semStopServiceTask ) );
	XIntc_Acknowledge(&m_axi_intc, FIT_1S_IRQ_ID);
	//xil_printf("--- fit_timer_1s_isr\n");
}
void fit_timer_5s_isr(void *not_valid) {
	/* � compl�ter */
	//xil_printf("+++ fit_timer_5s_isr\n");
	err_msg ("", OSSemPost( semVerificationTask ) );
	XIntc_Acknowledge(&m_axi_intc, FIT_5S_IRQ_ID);
	//xil_printf("--- fit_timer_5s_isr\n");
}

///////////////////////////////////////////////////////////////////////////////////////
//								uC/OS-II part
///////////////////////////////////////////////////////////////////////////////////////
int main() {
	initialize_bsp();

	// Initialize uC/OS-II
	OSInit();

	create_application();

	prepare_and_enable_irq();

	xil_printf("*** Starting uC/OS-II scheduler ***\n");

	OSStart();

	cleanup();
	
    return 0;
}

void create_application() {
	int error;

	error = create_tasks();
	if (error != 0)
		xil_printf("Error %d while creating tasks\n", error);

	error = create_events();
	if (error != 0)
		xil_printf("Error %d while creating events\n", error);
}

int create_tasks() {
	/* � compl�ter */
	if(OSTaskCreate(TaskReceivePacket, NULL, &TaskReceiveStk[TASK_STK_SIZE - 1], TASK_RECEIVE_PRIO))	return -1;
    return 0;
}

int create_events() {
	/*CREATION DES FILES*/
	inputQ = OSQCreate(inputMsg, 16);
	if(!inputQ)	return -1;

	verifQ = OSQCreate(verifMsg, 10);
	if(!verifQ)	return -1;

	lowQ = OSQCreate(lowMsg, 4);
	if(!lowQ)	return -1;

	mediumQ = OSQCreate(mediumMsg, 4);
	if(!mediumQ)	return -1;

	highQ = OSQCreate(highMsg, 4);
	if(!highQ)	return -1;

	/*CREATION DES MAILBOXES*/


	/*ALLOCATION ET DEFINITIONS DES STRUCTURES PRINT_PARAM*/

	/*CREATION DES SEMAPHORES*/
	semReceptionTask = OSSemCreate(0);
	semVerificationTask = OSSemCreate(0);
	semStopServiceTask = OSSemCreate(0);
	semStatisticTask = OSSemCreate(0);

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

    	/* � compl�ter : R�ception des paquets de Linux */
    	xil_printf("+++ ReceiveTask\n");
    	OSSemPend(semReceptionTask, 0, &err);
    	err_msg("", err);

    	packet = malloc(sizeof(Packet));///a verifierrrrrrrrrr
    	packet->src = Xil_In32(COMM_RX_DATA);
    	Xil_Out32( COMM_RX_FLAG, 0x0 );

    	while( Xil_In32(COMM_RX_FLAG) != 0x1 );
    	packet->dst = Xil_In32(COMM_RX_DATA);
    	Xil_Out32( COMM_RX_FLAG, 0x0 );

    	while( Xil_In32(COMM_RX_FLAG) != 0x1 );
		packet->type = Xil_In32(COMM_RX_DATA);
		Xil_Out32( COMM_RX_FLAG, 0x0 );

		while( Xil_In32(COMM_RX_FLAG) != 0x1 );
		packet->crc = Xil_In32(COMM_RX_DATA);
		Xil_Out32( COMM_RX_FLAG, 0x0 );

		//reading the payload of the packet
		int i = 0;
		for(i = 0; i < 12; i++)
		{
			while( Xil_In32(COMM_RX_FLAG) != 0x1 );
			packet->data[i] = Xil_In32(COMM_RX_DATA);
			Xil_Out32( COMM_RX_FLAG, 0x0 );
		}

		xil_printf("RECEIVE : ********Reception du Paquet # %d ******** \n", nbPacketSent++);
		xil_printf("ADD %x \n", packet);
		xil_printf("    ** src : %x \n", packet->src);
		xil_printf("    ** dst : %x \n", packet->dst);
		xil_printf("    ** type : %d \n", packet->type);
		xil_printf("    ** crc : %x \n", packet->crc);

		/* � compl�ter: Transmission des paquets dans l'inputQueue */
		OSQPost(inputQ, (void *)packet);

		xil_printf("+++ ReceiveTask");

    }
}


/*
 *********************************************************************************************************
 *                                              TaskVerification
 *  -R�injecte les paquets rejet�s des files haute, medium et basse dans la inputQ
 *********************************************************************************************************
 */
void TaskVerification(void *data) {
	INT8U err;
	Packet *packet = NULL;
	while (1) {
		/* � compl�ter */
	}
}
/*
 *********************************************************************************************************
 *                                              TaskStop
 *  -Stoppe le routeur une fois que 5 paquets ont �t�s rejet�s pour mauvais CRC
 *********************************************************************************************************
 */
void TaskStop(void *data) {
	INT8U err;
	while(1) {
		/* � compl�ter */
	}
}

/*
 *********************************************************************************************************
 *                                              TaskComputing
 *  -V�rifie si les paquets sont conformes (CRC,Adresse Source)
 *  -Dispatche les paquets dans des files (HIGH,MEDIUM,LOxmd
 *
 *********************************************************************************************************
 */
void TaskComputing(void *pdata) {
    INT8U err;
    Packet *packet = NULL;
    while(1){
    	/* � compl�ter */
    }
}

/*
 *********************************************************************************************************
 *                                              TaskForwarding1
 *  -traite la priorit� des paquets : si un paquet de haute priorit� est pr�t,
 *   on l'envoie � l'aide de la fonction dispatch, sinon on regarde les paquets de moins haute priorit�
 *********************************************************************************************************
 */
void TaskForwarding(void *pdata) {
    INT8U err;
    Packet *packet = NULL;

    while(1){
        /* � compl�ter */
    }
}

/*
 *********************************************************************************************************
 *                                              TaskStats
 *  -Est d�clench�e lorsque le irq_gen_1_isr() lib�re le s�maphore
 *  -Lorsque d�clench�e, Imprime les statistiques du routeur � cet instant
 *********************************************************************************************************
 */
void TaskStats(void *pdata) {
    INT8U err;

    while(1){
    	/* � compl�ter */
    }

}


/*
 *********************************************************************************************************
 *                                              TaskPrint
 *  -Affiche les infos des paquets arriv�s � destination et libere la m�moire allou�e
 *********************************************************************************************************
 */
void TaskPrint(void *data) {
    INT8U err;
    Packet *packet = NULL;
    int intID = ((PRINT_PARAM*)data)->interfaceID;
    OS_EVENT* mb = ((PRINT_PARAM*)data)->Mbox;

    while(1){
        /* � compl�ter */
    }

}
void err_msg(char* entete, INT8U err)
{
	if(err != 0)
	{
		xil_printf(entete);
		xil_printf(": Une erreur est retourn�e : code %d \n",err);
	}
}

