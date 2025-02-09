#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

#define BUF_SIZE 1000

typedef enum
{
  waiting,
  in_progress,
  completed
} state;

typedef struct
{
  uint8_t	buf[BUF_SIZE];
  size_t 	buf_len;
  uint16_t	cnt;
  state 	state;
} exchange;

void start_uart_resive();
void start_uart_transmit();
void clean_obj(exchange* obj);
void reset_state();

#endif /* INC_UART_H_ */
