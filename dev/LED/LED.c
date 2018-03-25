/*********************************************************************************************************
* 模块名称: LED.c
* 摘    要: 
* 当前版本: 1.0.0
* 作    者: 666immortal
* 完成日期: 2018年03月01日
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "LED.h"
#include <stm32f10x_conf.h>

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void  ConfigLEDGPIO(void);         //配置LED的GPIO

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: ConfigLEDGPIO
* 函数功能: 配置LED的GPIO，作为系统运行指示灯 
* 输入参数: void 
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
static  void  ConfigLEDGPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;           //定义结构体GPIO_InitStructure,用来配置LED的GPIO
                                                                     
  RCC_APB2PeriphClockCmd(USER_DEFINE_LED0_GPIO_CLK, ENABLE);         //使能LED0的时钟
  RCC_APB2PeriphClockCmd(USER_DEFINE_LED1_GPIO_CLK, ENABLE);         //使能LED1的时钟
                                                                                                                  
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_LED0_GPIO_PIN;         //设置LED0的引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //设置I/O速率为50MHz
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;                  //推挽输出模式
  GPIO_Init(USER_DEFINE_LED0_GPIO_PORT, &GPIO_InitStructure);        //根据参数初始化LED0的GPIO端口

  GPIO_WriteBit(USER_DEFINE_LED0_GPIO_PORT, USER_DEFINE_LED0_GPIO_PIN, Bit_RESET); //LED0默认值为点亮

  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_LED1_GPIO_PIN;         //设置LED1的引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //设置I/O口速率为50MHz
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;                  //推挽输出模式
  GPIO_Init(USER_DEFINE_LED1_GPIO_PORT, &GPIO_InitStructure);        //根据参数初始化LED1的GPIO端口

  GPIO_WriteBit(USER_DEFINE_LED1_GPIO_PORT, USER_DEFINE_LED1_GPIO_PIN, Bit_SET);   //LED1默认值为熄灭
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitLED
* 函数功能: 初始化LED函数
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void InitLED(void)
{
  ConfigLEDGPIO();      //配置LED的GPIO
}

/*********************************************************************************************************
* 函数名称: LEDFlicker
* 函数功能: LED闪烁函数，主要是为了测试方便
* 输入参数: cnt
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: cnt = 500表示每2s闪烁一次（亮灭各1s）
*********************************************************************************************************/
void LEDFlicker(u16 cnt)
{
  static u16 s_iCnt;     //定义静态变量s_iCnt作为循环计数器
  
  s_iCnt++;              //计数器数值加1
  
  if(s_iCnt >= cnt)      //计数器数值大于LED闪烁定时参数cnt
  { 
    s_iCnt = 0;          //计数器数值重置为0

    //LED0状态取反，实现LED0闪烁
    GPIO_WriteBit(USER_DEFINE_LED0_GPIO_PORT, USER_DEFINE_LED0_GPIO_PIN, 
    (BitAction)(1 - GPIO_ReadOutputDataBit(USER_DEFINE_LED0_GPIO_PORT, USER_DEFINE_LED0_GPIO_PIN)));
    
    //LED1状态取反，实现LED1闪烁
    GPIO_WriteBit(USER_DEFINE_LED1_GPIO_PORT, USER_DEFINE_LED1_GPIO_PIN,
    (BitAction)(1 - GPIO_ReadOutputDataBit(USER_DEFINE_LED1_GPIO_PORT, USER_DEFINE_LED1_GPIO_PIN)));
  }
}
