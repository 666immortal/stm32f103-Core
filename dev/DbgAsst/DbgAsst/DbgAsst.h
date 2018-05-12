﻿/*********************************************************************************************************
* 模块名称: DbgAsst.h
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
#ifndef _DBG_ASST_
#define _DBG_ASST_
  
/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "ProcString.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define MAX_FUNC_NAME_LEN   30    //函数名最大长度，应该设置函数名不大于最长长度
#define MAX_PARA_NUM        10    //最大为10个参数 ,修改此参数,必须修改ExeFunc与之对应
//所有参数之和的长度不超过PARM_LEN个字节,注意串口接收部分要与之对应(不小于PARM_LEN)
#define PARM_LEN            200
    
#define DBG_ASST_OK             0 //无错误
#define DBG_ASST_FUNC_ERR       1 //函数错误
#define DBG_ASST_PARA_ERR       2 //参数错误
#define DBG_ASST_PARA_OVER      3 //参数溢出
#define DBG_ASST_FUNC_MISMATCH  4 //未找到匹配函数

#define SP_TYPE_DEC       0       //10进制参数显示
#define SP_TYPE_HEX       1       //16进制参数显示

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/
extern u8  g_arrPara[PARM_LEN];     //函数的参数

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void InitDbgAsst(void);            //初始化DbgAsst

u32  ReadAddr(u32 addr);           //读取指定地址的值
void WriteAddr(u32 addr, u32 val); //在指定地址写入指定的值

void DbgAsstScan(void);            //扫描函数,该函数需要每隔一定时间被调用一次,用于处理从串口接收来的数据

void SetParaType(u16 paraType);    //设置参数的类型
u16  GetParaType(void);            //得到参数的类型

#endif
