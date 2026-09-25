#include"main_conf.h"

//超声波模块初始化
uint32_t Distance = 0;//超声波测得的距离
volatile uint32_t times = 0;//超声波发出和接受中间的时间
volatile uint32_t Flag = 0;//用来判断是高电位还是低电位
void Ultrasound_Init(void)
{
    //初始化PB5和6，一个作为超声波模块信号输出，一个作为超声波模块信号输入
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_Instruct;
    GPIO_Instruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Instruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_Instruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_Instruct);

    GPIO_Instruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Instruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Instruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_Instruct);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能AFIO,主要作用是分线器，比如之前的重映射，这里的分EXTI线
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);//把EXTI6分给PB6
    //初始化EXTI6这条线
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line6;//选择初始化EXTI6这条线
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断模式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//选择上升沿和下降沿都触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;//使能
    EXTI_Init(&EXTI_InitStruct);//初始化成功
    //初始化NVIC中断
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;//打开EXTI6所对应的中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级为0
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//子优先级为1
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能
    NVIC_Init(&NVIC_InitStruct);
    /*
    获取对应EXTI线标志位的值，结果为SET则代表对应线触发的中断
    EXTI_GetFlagStatus(EXTI_Line6);
    */
    MyDelay_Init();

}

uint32_t Ultrasound_GetDistance(void)
{
    Distance = 0;//单位为厘米
    for(int i = 0;i < 10;i ++)
    {
        Flag = 0;
        TIM_Cmd(TIM4,DISABLE);
        Currents = 0;
        times = 0;
        //按照超声波模块需求发送波形
        GPIO_SetBits(GPIOB,GPIO_Pin_5);
        Delay_us(15);
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
        Delay_ms(60);
        //得到一次的距离并累加
        Distance += times/58;
    }
    //求平均值
    Distance /= 10;
    return Distance;
}
//检测到PB6输入信号，通过信号测算距离
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetFlagStatus(EXTI_Line6) == SET)//判断是否是PB6引发的中断
    {
        EXTI_ClearFlag(EXTI_Line6);//清除标志位
        if(Flag == 0)//判断是不是高电位（0代表是高电位）
        {
            Flag = 1;
            TIM_SetCounter(TIM4,0);//清空定时器
            TIM_Cmd(TIM4,ENABLE);//开启定时器
        }
        else
        {
            Flag = 0;
            TIM_Cmd(TIM4,DISABLE);//关闭定时器
            times = Currents * 1000 + TIM_GetCounter(TIM4);//测得时间为计数器里的数（单位为微妙）加上目前测得的毫秒数（计数器触发中断次数）乘1000
            Currents = 0;//清零
        }
    }
}

