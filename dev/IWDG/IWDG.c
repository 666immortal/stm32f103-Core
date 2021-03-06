﻿/*********************************************************************************************************
* 模块名称: IWDG.c
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
#include "IWDG.h"
#include <stm32f10x_conf.h>
#include "UART.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void ConifigIWDG(u8 prer, u16 rlr);       //配置独立看门狗

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: ConifigIWDG
* 函数功能: 配置独立看门狗 
* 输入参数: prer：分频数，最大值是256，rlr：重装载寄存器值，低11位有效
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
static  void ConifigIWDG(u8 prer, u16 rlr) 
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);   //使能对寄存器IWDG_PR和IWDG_RLR的写操作

  IWDG_SetPrescaler(prer);                        //设置IWDG预分频值:
  
  IWDG_SetReload(rlr);                            //设置IWDG重装载值
  
  IWDG_ReloadCounter();                           //按照IWDG重装载寄存器的值重装载IWDG计数器
  
  IWDG_Enable();                                  //使能IWDG
}

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitIWDG
* 函数功能: 初始化独立看门狗 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 如果独立看门狗已经由硬件选项或软件启动，LSI振荡器将被强制在打开状态，并且不能被关闭
*           LSI的时钟频率为40KHz，在30-60KHz之间
*           时间计算（大约）：
*           ((4*2^prer)*(rlr+1))/40 = 4*(2^4)*625/40=1000(ms) 666-1333ms
*           ((4*2^prer)*(rlr+1))/40 = 4*(2^4)*1250/40=2000(ms) 1333-2666ms
*********************************************************************************************************/
void InitIWDG(void)
{   
  ConifigIWDG(USER_DEFINE_IWDG_PRER, USER_DEFINE_IWDG_RLR);    //配置独立看门狗,溢出时间为1s
}

/*********************************************************************************************************
* 函数名称: InitIWDG
* 函数功能: 喂独立看门狗 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 
*********************************************************************************************************/
void FeedIWDG(void)
{
  IWDG_ReloadCounter();      //按照IWDG重装载寄存器的值重装载IWDG计数器
}
