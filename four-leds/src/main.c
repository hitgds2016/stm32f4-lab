#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

void INTTIM_Config()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // SystemCoreClock is 168M

    //    TIM_TimeBaseStructure.TIM_Prescaler = 84-1; // 24 MHz clock down to 1 MHz
    //    TIM_TimeBaseStructure.TIM_Period = 100 - 1; // 1 MHz down to 10 KHz (.1 ms)

//    TIM_TimeBaseStructure.TIM_Prescaler = 4200 -1;
//    TIM_TimeBaseStructure.TIM_Period = 10000 - 2;

    /*
     * We want 50 Hz
     */
    TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1; // down to 1 MHz
    TIM_TimeBaseStructure.TIM_Period = 100000; // down to 10 Hz

    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_Cmd (TIM2, ENABLE);
}

void LED_Config(void)
{
    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}






int main(void)
{
	SystemInit();

    INTTIM_Config();
    LED_Config();


    while (1)
    {
    	if (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) != RESET)
    	{
    		TIM_ClearFlag(TIM2, TIM_IT_Update);
    		GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    	}
    }

}
