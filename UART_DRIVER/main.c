#include <stm32f10x.h>
#define GPIO_EN  (1 <<  2)
#define UART1_EN (1 << 14)
#define UART1_TX_EN (1 << 3)
#define UART1_EN_FUN (1 << 13)

#define UART2_EN (1 << 17)
#define UART2_TX_EN (1 << 3)
#define UART2_EN_FUN (1 << 13)

void Uart_int(void);
void UART_TX(char  ch);
void UART_SEND(char str[]);
char UART_RX(void);
int main(){
  char myName[] = "AT";
	Uart_int();
	while(1){
	UART_SEND(myName);
  }
}

  void Uart_int(void){
	RCC->APB2ENR |=  GPIO_EN;
	RCC->APB2ENR |= UART1_EN;
		
	RCC->APB1ENR |= UART2_EN ;

  GPIOA->CRH &= 0xFFFFF00F;
	GPIOA->CRH |= 0x000008B0;
		
	GPIOA->CRL &= 0xFFFF00FF;
	GPIOA->CRL |= 0x00008B00;
		
	USART2->BRR = 0xEA6;
	USART2->CR1  = UART1_TX_EN;
	USART2->CR1 |= UART1_EN_FUN;
}
void UART_TX(char  ch){
while((USART2->SR & (1<<6)) == 0x00){}
USART2->DR = ch;
}

char UART_RX(){
char c;
while((USART1->SR & 0x20) == 0x00){}
c = USART1->DR;
	return c;
}
	
void UART_SEND(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		UART_TX(str[i]);
		i++;
	}
}
