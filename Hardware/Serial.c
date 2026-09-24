#include"stm32f10x.h"
#include"Serial.h"
#include"Car.h"
#include"Servo.h"
/*对USART1进行初始化
TX-PA9 RX -PA10
9600bits 数据位8，停止位1，无校验位
*/
void Serial_Init(void)
{
    //初始化串口USART1
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//使能USART1时钟
    USART_InitStructure.USART_BaudRate = 9600;//设置波特率为9600
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置硬件流控制为无
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位为8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位为1位
    USART_InitStructure.USART_Parity = USART_Parity_No;//设置奇偶校验为无
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//设置模式为发送和接收
    USART_Init(USART1, &USART_InitStructure);//初始化USART1
    USART_Cmd(USART1, ENABLE);//使能USART1
    //初始化GPIOA的9号引脚为USART1的TX引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//设置GPIOA的9号引脚为USART1的TX引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//设置引脚模式为复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA的9号引脚
    //初始化GPIOA的10号引脚为USART1的RX引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//设置GPIOA的10号引脚为USART1的RX引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置引脚模式为上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA的10号引脚
    /*
    //练习重映射，将USART1两个引脚重映射到PB6和7
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO的时钟
    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//USART_REMAP = 1,即为告诉USART1要重映射

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure2;
    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure2);

    GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_InitStructure2);
    */
    //打开串口中断
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    //初始化USARTNVIC 
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;//打开USART1的优先级通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//设置抢占优先级为0
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//设置子优先级为0
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能
    
    NVIC_Init(&NVIC_InitStruct);//初始化
}
//发送数组函数，三个参数分别为要用的串口，要传的数组首地址，数组长度
void Serial_SendBytes(USART_TypeDef * A, int16_t* Data1,int16_t length)
{
    for(int i = 0;i < length;i ++)//循环发送数组中每个数据
    {
        while(USART_GetFlagStatus(A,USART_FLAG_TXE) == RESET);//检测输出寄存器是否为RESET，为RESET意味着不为空，上一个数据还没发完，故一直循环
        USART_SendData(A,Data1[i]);//将当前要发送的数据放入输出寄存器
    }
    
    while(USART_GetFlagStatus(A,USART_FLAG_TC) == RESET);//检测整个数组是否全部发完，为RESET意味着没有发完，故一直循环
}

void Serial_ReceiveByte(USART_TypeDef *A,int16_t *Data1)
{
    while(USART_GetFlagStatus(A,USART_FLAG_RXNE) == RESET);

    *Data1 = USART_ReceiveData(A);

}
//蓝牙串口的中断函数，用来操控小车
void USART1_IRQHandler(void)
{
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
    {
        uint16_t cmd = USART_ReceiveData(USART1);
        if (cmd >= 'a' && cmd <= 'z')//小写字母自动当大写处理
        {
            cmd = cmd - 'a' + 'A';
        }
        switch (cmd)
        {
            case 'F': case '1': Car_Go_Forward();  break;
            case 'B': case '2': Car_Go_Backward(); break;
            case 'L': case '3': Car_Turn_Left();   break;
            case 'R': case '4': Car_Turn_Right();  break;
            case'5': SetServoAngle(0);             break;
            case'6': SetServoAngle(90);            break;
            case'7': SetServoAngle(180);           break;
            default:            Car_Stop();        break;//S和不认识的字符都停车
        }
        
    }
}