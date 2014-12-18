/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);

void gpio_init();

void led_on();

void led_off();

void led_switch();

void Initialize_UART();

void Initialize_ADC();

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : main
 * Description    : Main program.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int main(void)
{
#ifdef DEBUG
debug();
#endif

InitializeUSART();

//RCC_Configuration();
SystemInit();
    
// NVIC Configuration 
NVIC_Configuration();
  
// Configure PC.8 as Output push-pull 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);

while (1)
  {
/* Turn on led connected to PC.8 pin */
GPIO_SetBits(GPIOA, GPIO_Pin_5);
/* Insert delay */
Delay(100000);

/* Turn off led connected to PC.8 pin */
GPIO_ResetBits(GPIOA, GPIO_Pin_5);
/* Insert delay */
Delay(300000);
}

}

/*******************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Configures the different system clocks.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/

/* * Initialize GPIOA, Pin PA5 * Enable system clock * Configure PA_5 Output push-pull * PA_5 = LED2 */ 
void gpio_init(){ uint32_t tmpreg;

//Enable system clock for GPIOA 
RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN); RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN);

//Configure PA5 output push-pull 
tmpreg = GPIOA->CRL; tmpreg &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5); tmpreg |= GPIO_CRL_MODE5; GPIOA->CRL = tmpreg; }

void led_on(){ GPIOA->BSRR |= (1<<5); }

void led_off(){ GPIOA->BRR |= (1<<5); }

void led_switch(){ if(GPIOA->ODR & (1 << 5)) led_off(); else led_on(); }


void RCC_Configuration(void)
{
/* RCC system reset(for debug purpose) */
RCC_DeInit();

/* Enable HSE */
RCC_HSEConfig(RCC_HSE_ON);

/* Wait till HSE is ready */
HSEStartUpStatus = RCC_WaitForHSEStartUp();

if(HSEStartUpStatus == SUCCESS)
  {
/* Enable Prefetch Buffer */
FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

/* Flash 2 wait state */
FLASH_SetLatency(FLASH_Latency_2);
 	
/* HCLK = SYSCLK */
RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
/* PCLK2 = HCLK */
RCC_PCLK2Config(RCC_HCLK_Div1); 

/* PCLK1 = HCLK/2 */
RCC_PCLK1Config(RCC_HCLK_Div2);

/* PLLCLK = 8MHz * 9 = 72 MHz */
RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

/* Enable PLL */ 
RCC_PLLCmd(ENABLE);

/* Wait till PLL is ready */
while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
}

/* Select PLL as system clock source */
RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

/* Wait till PLL is used as system clock source */
while(RCC_GetSYSCLKSource() != 0x08)
  {
}
}
}

/*******************************************************************************
 * Function Name  : NVIC_Configuration
 * Description    : Configures Vector Table base location.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
/* Set the Vector Table base location at 0x20000000 */ 
NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
/* Set the Vector Table base location at 0x08000000 */ 
NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
 * Function Name  : Delay
 * Description    : Inserts a delay time.
 * Input          : nCount: specifies the delay time length.
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Delay(vu32 nCount)
{
for(; nCount != 0; nCount--);
}


/*******************************************************************************
 * Function Name  : InitializeUSART
 * Description    : Initialize USART
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void Initialize_USART()
{

USART_InitTypeDef usartConfig;                     

RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |

RCC_APB2Periph_GPIOA |

RCC_APB2Periph_AFIO, ENABLE);

USART_Cmd(USART1, ENABLE);

                       
usartConfig.USART_BaudRate = 9600;

usartConfig.USART_WordLength = USART_WordLength_8b;                        

 usartConfig.USART_StopBits = USART_StopBits_1;

 usartConfig.USART_Parity = USART_Parity_No;

 usartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

 usartConfig.USART_HardwareFlowControl =

   USART_HardwareFlowControl_None;

 USART_Init(USART1, &usartConfig);
                       
 GPIO_InitTypeDef gpioConfig;                   

 //PA9 = USART1.TX => Alternative Function Output

 gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;

 gpioConfig.GPIO_Pin = GPIO_Pin_9;

 gpioConfig.GPIO_Speed = GPIO_Speed_2MHz;

 GPIO_Init(GPIOA, &gpioConfig);

                       
 //PA10 = USART1.RX => Input

 gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;

 gpioConfig.GPIO_Pin = GPIO_Pin_10;

 GPIO_Init(GPIOA, &gpioConfig);
}


/*******************************************************************************
 * Function Name  : Initialize_ADC
 * Description    : Initialize ADC
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
/*
void InitializeADC()
{
  // Pas bon car pas la meme lib .. bon ba aparament si ..
  //PLL Config : PLLCLK = HSI/2 *14 = 56MHz
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLMULL));
  RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2|RCC_CFGR_PLLMULL14);

  
}
*/

#ifdef  DEBUG
/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
    {
    }
}
#endif

