/*********************************************************************************************************
* 模块名称: DAC.h
* 摘    要: DAC驱动
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
#ifndef _DAC_H_
#define _DAC_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"
#include "stm32f10x_conf.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/              
#define USER_DEFINE_DAC_CHANNEL            DAC_Channel_1          //用户定义DAC通道
#define USER_DEFINE_DAC_GPIO               GPIOA                  //用户定义DAC通道的GPIO端口
#define USER_DEFINE_DAC_GPIO_CLK           RCC_APB2Periph_GPIOA   //用户定义DAC通道的GPIO端口的时钟
#define USER_DEFINE_DAC_GPIO_PIN           GPIO_Pin_4             //用户定义DAC通道的GPIO端口的引脚

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/    

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/								    
void InitDAC(void);             //初始化DAC通道输出	 	 
void SetDACVol(u16 volnum);     //设置DAC通道输出电压

#endif
