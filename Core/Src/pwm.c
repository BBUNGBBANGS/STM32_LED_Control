#include "main.h"

uint32_t total_counter;
uint32_t pwm_output_counter;
uint32_t Low_Counter_1,High_Counter_1;
uint32_t Low_Counter_2,High_Counter_2;
float High_Time_1,High_Time_2;
float Low_Time_1,Low_Time_2;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    uint32_t value = 0;
    if (htim->Instance == TIM1)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
        {
            value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            Low_Counter_1 = value - High_Counter_1;
            High_Time_1 = High_Counter_1 * 13.88888888f;
            Low_Time_1 = Low_Counter_1 * 13.88888888f;
            htim->Instance->CNT = 0;
        }
        else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  
            High_Counter_1 = value;
        }
    }
    else if (htim->Instance == TIM2)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // If the interrupt is triggered by channel 1
        {
            value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            Low_Counter_2 = value - High_Counter_2;
            High_Time_2 = High_Counter_2 * 13.88888888f;
            Low_Time_2 = Low_Counter_2 * 13.88888888f;
            htim->Instance->CNT = 0;
        }
        else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);     
            High_Counter_2 = value;  
        }
    }
    total_counter++;
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    pwm_output_counter++;
    if (pwm_output_counter > 71)
    {
    	pwm_output_counter = 0;
    }
    TIM3->CCR1 = pwm_output_counter;
    TIM3->CCR2 = pwm_output_counter;
}

void Pwm_Write(void)
{

}
