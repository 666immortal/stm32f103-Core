﻿/*********************************************************************************************************
* 模块名称: CPUID.c
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
#include "CPUID.h"
#include "UART.h"
#include <stm32f10x_conf.h>

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/



/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitCPUID
* 函数功能: 初始化CPUID 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void  InitCPUID(void)
{
  
}

/*********************************************************************************************************
* 函数名称: ReadCPUID
* 函数功能: 按照mcuisp的格式取出CPUID 
* 输入参数: void
* 输出参数: 按照mcuisp的格式存放，arrId[11]为最高位
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void  ReadCPUID(u8* pMCUISPID)
{
  u32 arrID[3];                                 //32位的CPUID
     
  //在固定地址获取STM32唯一的CPUID
  arrID[0] = *(vu32*)(0x1FFFF7E8);              //31-00
  arrID[1] = *(vu32*)(0x1FFFF7EC);              //63-32
  arrID[2] = *(vu32*)(0x1FFFF7F0);              //95-64
  
  //按照MCUISP的格式存放
  pMCUISPID[11] = (arrID[0] & 0x000000FF) >> 0; 
  pMCUISPID[10] = (arrID[0] & 0x0000FF00) >> 8;
  pMCUISPID[9]  = (arrID[0] & 0x00FF0000) >> 16;
  pMCUISPID[8]  = (arrID[0] & 0xFF000000) >> 24;

  pMCUISPID[7]  = (arrID[1] & 0x000000FF) >> 0;
  pMCUISPID[6]  = (arrID[1] & 0x0000FF00) >> 8;
  pMCUISPID[5]  = (arrID[1] & 0x00FF0000) >> 16;
  pMCUISPID[4]  = (arrID[1] & 0xFF000000) >> 24;

  pMCUISPID[3]  = (arrID[2] & 0x000000FF) >> 0;
  pMCUISPID[2]  = (arrID[2] & 0x0000FF00) >> 8;
  pMCUISPID[1]  = (arrID[2] & 0x00FF0000) >> 16;
  pMCUISPID[0]  = (arrID[2] & 0xFF000000) >> 24; 
}

/*********************************************************************************************************
* 函数名称: CheckCPUID
* 函数功能: 检测STM32的ID是否匹配，如果匹配继续向下执行，否则进入while死循环 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 
*********************************************************************************************************/
void  CheckCPUID(void)
{
  i8  i;                              //循环计数器
  u8  arrMCUISPID[12];                //用于存放STM32的CPUID
  u8  idOk = FALSE;                   //用作标志位，表示CPUID匹配是否成功，0-失败，1-成功

  u8  permitCPUID1[12];               //存储DL使用的系统板的CPUID
  u8  permitCPUID2[12];               //存储LYQ使用的系统板的CPUID
  u8  permitCPUID3[12];               //存储战舰板的CPUID

  //DL使用的系统板的CPUID
  permitCPUID1[11] = 0X30;            //96位的芯片唯一序列号的最左端一个字节
  permitCPUID1[10] = 0XFF;
  permitCPUID1[9]  = 0XD7;
  permitCPUID1[8]  = 0X05;
  permitCPUID1[7]  = 0X43;
  permitCPUID1[6]  = 0X4E;
  permitCPUID1[5]  = 0X35;
  permitCPUID1[4]  = 0X38;
  permitCPUID1[3]  = 0X41;
  permitCPUID1[2]  = 0X77;
  permitCPUID1[1]  = 0X25;
  permitCPUID1[0]  = 0X43;            //96位的芯片唯一序列号的最右端一个字节
    
  //LYQ使用的系统板的CPUID
  permitCPUID2[11] = 0X30;            //96位的芯片唯一序列号的最左端一个字节
  permitCPUID2[10] = 0XFF;
  permitCPUID2[9]  = 0XD6;
  permitCPUID2[8]  = 0X05;
  permitCPUID2[7]  = 0X43;
  permitCPUID2[6]  = 0X4E;
  permitCPUID2[5]  = 0X35;
  permitCPUID2[4]  = 0X38;
  permitCPUID2[3]  = 0X22;
  permitCPUID2[2]  = 0X75;
  permitCPUID2[1]  = 0X23; 
  permitCPUID2[0]  = 0X43;            //96位的芯片唯一序列号的最右端一个字节

  //战舰板的CPUID
  permitCPUID3[11] = 0X32;            //96位的芯片唯一序列号的最左端一个字节
  permitCPUID3[10] = 0XFF;
  permitCPUID3[9]  = 0XD7;
  permitCPUID3[8]  = 0X05;
  permitCPUID3[7]  = 0X4D;
  permitCPUID3[6]  = 0X59;
  permitCPUID3[5]  = 0X32;
  permitCPUID3[4]  = 0X32;
  permitCPUID3[3]  = 0X18;
  permitCPUID3[2]  = 0X71;
  permitCPUID3[1]  = 0X10;
  permitCPUID3[0]  = 0X51;            //96位的芯片唯一序列号的最右端一个字节

  ReadCPUID(arrMCUISPID);             //读取当前CPU的ID存放在arrMCUISPID数组中
  
  printf("The CPUID is:");            //打印提示信息“The CPUID is:”
  
  for(i = 11; i >= 0; i--)            //循环将CPUID打印输出
  {
    printf("%02x", arrMCUISPID[i]);   //将CPUID通过十六进制的格式打印输出
  }
  
  printf("\r\n");                     //输出换行
  
  //检查第1组允许运行的CPUID
  for(i = 0; i < 12; i++)
  {
    if (permitCPUID1[i] == arrMCUISPID[i])      //DL的系统板CPUID与读取到的CPUID比较
    {
      if(11 == i)                               
      {
        idOk = TRUE;                            //CPUID匹配成功
        printf("DL ID!\r\n");                   //输出“DL ID”
      }    
    }
    else
    {
      break;                                    //CPUID不匹配，跳出循环
    }
  }

  //检查第2组允许运行的CPUID
  for(i = 0; i < 12; i++)
  {
    if (permitCPUID2[i] == arrMCUISPID[i])      //LYQ的系统板CPUID与读取到的CPUID比较
    {
      if(11 == i)
      {
        idOk = TRUE;                            //CPUID匹配成功
        printf("LYQ ID!\r\n");                  //输出“LYQ ID”
      }    
    }
    else
    {
      break;                                    //CPUID不匹配，跳出循环
    }
  }

  //检查第3组允许运行的CPUID
  for(i = 0; i < 12; i++)
  {
    if (permitCPUID3[i] == arrMCUISPID[i])      //战舰板的CPUID与读取到的CPUID比较
    {
      if(11 == i)
      {
        idOk = TRUE;                            //CPUID匹配成功
        printf("This is STM32 ID!\r\n");        //输出“This is STM32 ID”
      }    
    }
    else
    {
      break;                                    //CPUID不匹配，跳出循环
    }
  }

  //CPUID不匹配，则进入死循环
  if(TRUE != idOk) 
  {
    printf("CheckCPUID failed!\r\n");           //输出“CheckCPUID failed!”
    while(1);                                   //进入死循环
  }
}
