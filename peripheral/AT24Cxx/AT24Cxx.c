/*********************************************************************************************************
* 模块名称: AT24Cxx.c
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
#include "AT24Cxx.h"
#include "I2C.h" 
#include "SysTick.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  u8    AT24CxxReadOneByte(u16 readAddr);                    //从指定地址读取一个字节
static  void  AT24CxxWriteOneByte(u16 writeAddr, u8 dataToWrite);  //从指定地址写入一个字节

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: AT24CxxReadOneByte
* 函数功能: 通过一个地址，读取一个字节 
* 输入参数: readAddr-开始读数的地址 
* 输出参数: void  
* 返 回 值: 读到的数据
* 创建日期: 2018年03月01日
* 注    意: 24WC01/02    1 0 1 0 A2  A1  A0  R/~W
*           24WC04       1 0 1 0 A2  A1  a8  R/~W
*           24WC08       1 0 1 0 A2  a9  a8  R/~W
*           24WC16       1 0 1 0 a10 a11 a12 R/~W
*           A0/A1/A2对应器件的管脚1/2/3，最多可以级联的器件数
*           a8/a9/a10对应存储阵列字地址
*           对应《AT24C01ASC/02SC/04SC/08SC/16SC数据手册》的Figure10. Random Read（Reference）  
*********************************************************************************************************/
static  u8 AT24CxxReadOneByte(u16 readAddr)
{          
  u8 temp = 0;       
  
  GenI2CStartSig();                       //发送起始信号  

  if(USER_DEFINE_EEPROM_TYPE > AT24C16)   //如果内存字节大于AT24C16  2047
	{
		I2CSendByte(0XA0);	                  //发送写命令
		I2CWaitAck();                         //等待应答
		I2CSendByte(readAddr >> 8);           //发送高地址
		I2CWaitAck();		                      //等待应答
	}
  else                                    //内存字节不大于2047
  {
    I2CSendByte(0XA0 + ((readAddr / 256) << 1));//发送器件地址0XA0，写数据  
  }
  
  I2CWaitAck();                           //等待应答
  I2CSendByte(readAddr % 256);            //发送BYTE ADDRESS（字节的地址）
  I2CWaitAck();                           //等待应答
                     
  GenI2CStartSig();                       //发送起始信号          
  I2CSendByte(0XA1);                      //发送SLAVE ADDRESS，为了进入接收模式，1 0 1 0 x  x  x  R/~W         
  I2CWaitAck();                           //等待应答
                 
  temp = I2CReadByte(0);                  //传入参数0表示发送无应答
                     
  GenI2CStopSig();                        //发送停止信号    
  
  return temp;                            //返回读取到的值
}

/*********************************************************************************************************
* 函数名称: AT24CxxWriteOneByte
* 函数功能: 在AT24Cxx指定地址写入一个字节数据 
* 输入参数: writeAddr-写入数据的目的地址，dataToWrite-待写入的字节数据 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 对应《AT24C01ASC/02SC/04SC/08SC/16SC数据手册》的Figure7. Byte Write（Reference）  
*********************************************************************************************************/
static  void AT24CxxWriteOneByte(u16 writeAddr, u8 dataToWrite)
{                                                      
  GenI2CStartSig();                             //发送起始信号

  I2CSendByte(0XA0 + ((writeAddr / 256) << 1)); //左移1位因为LSB是R/~W,发送SLAVE ADDRESS（字地址也包含其中）    
  I2CWaitAck();                                 //等待应答
              
  I2CSendByte(writeAddr % 256);                 //发送BYTE ADDRESS（字节的地址）
  I2CWaitAck();                                 //等待应答
                                              
  I2CSendByte(dataToWrite);                     //发送待写入的字节                 
  I2CWaitAck();                                 //等待应答
                            
  GenI2CStopSig();                              //发送停止信号      
  DelayNms(5);                                  //在主器件产生停止信号后SLAVE开始内部数据的擦写,
                                                //在擦写过程中不在应答主器件的任何请求,数据手册上的tWR是5ms   
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitAT24Cxx
* 函数功能: 初始化I2C接口 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:  
*********************************************************************************************************/
void InitAT24Cxx(void)
{
  InitI2C();              //主要是初始化GPIO
}

/*********************************************************************************************************
* 函数名称: CheckAT24Cxx
* 函数功能: 检查AT24Cxx是否正常，这里用了24XX的最后一个地址(255)来存储标志字，如用其他24C,这个地址要修改 
* 输入参数: void
* 输出参数: void  
* 返 回 值: 1:检测失败，0:检测成功
* 创建日期: 2018年03月01日
* 注    意: 这个检测方法不是很严谨，只能满足实验需求，后续如用于实际产品中，需要有个更加严谨的方案  
*********************************************************************************************************/
u8 CheckAT24Cxx(void)
{
  u8 temp;
  
  temp = AT24CxxReadOneByte(255);       //避免每次开机都写AT24Cxx        
  
  if(temp == 0X55)                      //检验是否AT24Cxx已写入
  {
    return 0;                           //检测成功
  }
  else                                  //排除第一次初始化的情况
  {
    AT24CxxWriteOneByte(255, 0X55);     //在地址255处写入字节0X55
    temp = AT24CxxReadOneByte(255);     //读取地址255的字节赋值给temp
    
    if(temp == 0X55)                    //检测是否已经更改完成
    {
      return 0;                         //检测成功
    }
  }
  return 1;                             //以上条件不符合，检测失败        
}
/*********************************************************************************************************
* 函数名称: AT24CxxRead
* 函数功能: 在AT24Cxx里面的指定地址开始读出指定个数的数据 
* 输入参数: readAddr-开始读出的地址，对24c02为0~255，pBuffer-数据数组首地址，numToRead-要读出的数据个数 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:  
*********************************************************************************************************/
void AT24CxxRead(u16 readAddr, u8* pBuffer, u16 numToRead)
{
  while(numToRead)                                //数据未读完
  {
    *pBuffer = AT24CxxReadOneByte(readAddr);      //逐个字节读出存放到数据数组
    
    readAddr++;                                   //读取字节地址加1
    pBuffer++;                                    //数据数组地址加1
    numToRead--;                                  //要读出的数据个数减1
  }
}  

/*********************************************************************************************************
* 函数名称: AT24CxxWrite
* 函数功能: 在AT24Cxx里面的指定地址开始写入指定个数的数据 
* 输入参数: writeAddr-开始写入的地址 对24c02为0~255，pBuffer-数据数组首地址，numToWrite-要写入的数据个数
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:  
*********************************************************************************************************/
void AT24CxxWrite(u16 writeAddr, u8* pBuffer, u16 numToWrite)
{
  while(numToWrite)                           //数据未写完
  {
    AT24CxxWriteOneByte(writeAddr,*pBuffer);  //逐个字节写入数据数组
    
    writeAddr++;                              //写入字节地址加1
    pBuffer++;                                //数据数组地址加1
    numToWrite--;                             //要写入的数据个数减1
  }
}
