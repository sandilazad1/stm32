#include <stm32f10x.h>
#define GPIO_EN  (1 <<  2)
#define UART1_EN (1 << 14)
#define UART1_TX_EN (1 << 3)
#define UART1_EN_FUN (1 << 13)

void Uart_int(void);
void Uart_write(int);

int main(){
	int ch = 1;
	Uart_int();
	Uart_write(ch);
  return 0;
}

  void Uart_int(void){
	RCC->APB2ENR |=  GPIO_EN;
	RCC->APB2ENR |= UART1_EN;
  GPIOA->CRH &= 0xFFFFF00F;
	GPIOA->CRH |= 0x000008B0;
	USART1->BRR = 0x2B8A;
	USART1->CR1  = UART1_TX_EN;
	USART1->CR1 |= UART1_EN_FUN;
}
void Uart_write(int ch){

	while(1){
		USART1->DR = (1 & 0xFF);

	}
}
