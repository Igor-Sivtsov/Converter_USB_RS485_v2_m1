#include "uart.h"
#include <string.h>

exchange rx = {}, tx = {};
uint8_t clean;

static void reset_uart_error_flags();

void start_uart_resive()
{
  TX_EN_GPIO_Port->BSRR = TX_EN_Pin << 16;
  clean = USART3->RDR;
  USART3->CR1 |= USART_CR1_RE;
}

void start_uart_transmit()
{
  USART3->CR1 &= ~USART_CR1_RE;
  TX_EN_GPIO_Port->BSRR = TX_EN_Pin;
  USART3->CR1 |= USART_CR1_TE;
  USART3->TDR = tx.buf[tx.cnt++];
}

void clean_obj(exchange* obj)
{
  memset(&obj->buf, 0, obj->buf_len);
  obj->buf_len    = 0;
  obj->cnt        = 0;
  obj->state      = waiting;
}

void reset_state()
{
  reset_uart_error_flags();

  clean_obj(&tx);
  clean_obj(&rx);

  start_uart_resive();
}

static void reset_uart_error_flags()
{
  if(USART3->ISR & USART_ISR_PE)	USART3->ICR |= USART_ICR_PECF;
  if(USART3->ISR & USART_ISR_FE)	USART3->ICR |= USART_ICR_FECF;
  if(USART3->ISR & USART_ISR_NE)	USART3->ICR |= USART_ICR_NCF;
  if(USART3->ISR & USART_ISR_ORE)	USART3->ICR |= USART_ICR_ORECF;
}
