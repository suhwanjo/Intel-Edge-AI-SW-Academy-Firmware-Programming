/*
 * type.h
 *
 *  Created on: Apr 16, 2024
 *      Author: IOT
 */

#ifndef INC_TYPE_H_
#define INC_TYPE_H_

#include "mem.h"
enum{
	E_MSG_CLI = 0x1000,
	E_MSG_CLI_INIT,
	E_MSG_CMD_RX = 0x2000,
	E_MSG_CMD_RX_0,
	E_MSG_CMD_TX,
	E_MSG_MAX
};

typedef struct __attribute__((packed)){ // gcc
	uint16_t id;
	union { // = type cast
		uint8_t 	b[4];
		uint16_t 	h[2];
		uint32_t 	w;
		void 		*vPtr;
		uint8_t 	*bPtr;
		uint16_t 	*hPtr;
		uint32_t 	*wPtr;
		MEM_T		*pMem;
	}body;
}MSG_T;

typedef struct __attribute__((packed)){
	uint16_t cmd;
	uint8_t len;
	uint8_t ctx[100];
}PKT_T;

#define Q_PUT(q_id, msg_id, pMem, wait) \
{ \
	MSG_T txMsg;  \
	txMsg.id = msg_id;  \
	txMsg.body.vPtr = (void *)pMem;  \
	if (osMessageQueuePut(q_id, &txMsg, 0, wait) != osOK) { \
		mem_free(pMem); \
	} \
}
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_TYPE_H_ */
