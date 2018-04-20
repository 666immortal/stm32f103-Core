/*********************************************************************************************************
* 模块名称: IWDG.h
* 摘    要: IWDG驱动
* 当前版本: 1.0.0
* 作    者: 
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
#ifndef _IWDG_H_
#define _IWDG_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define USER_DEFINE_IWDG_PRER    IWDG_Prescaler_64    //用户定义IWDG预分频值
#define USER_DEFINE_IWDG_RLR     624                  //用户定义IWDG自动重装载寄存器值

void InitIWDG(void);
void FeedIWDG(void);

#endif
