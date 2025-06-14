#include "oled_drv.h"
#include "codetab.h"  
 #include "tim.h" 
 // oled_drv.c
uint8_t OLED_GRAM[OLED_WIDTH][OLED_PAGES] = {0}; // 实际定义显存
#define GPIO_PIN_SET(port, pin, d)    P##port##_##pin## = d
//*功  能：OLED初始化
//*参  数: 无
//*返回值: 无 
//**************************************************************/
void OLED_Hinit(void) 
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
		 __HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();
		  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_1, GPIO_PIN_RESET);
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);
		  /*Configure GPIO pins : PE2 PE3 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	//使能PB,PE端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	 		 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;							//推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							//IO口速度为50MHz
//	GPIO_Init(GPIOE, &GPIO_InitStructure);					     

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;						// 端口配置, 推挽输出
//	GPIO_Init(GPIOB, &GPIO_InitStructure);										//推挽输出 ，IO口速度为50MHz
	
}



#define LCD_LED(d)		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PD8
#define LCD_D1(d)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PB8
#define LCD_D0(d)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PB9 
#define LCD_DC(d)		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PE1 
#define LCD_RES(d)		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PE2
#define LCD_CS(d)		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, (d) ? GPIO_PIN_SET : GPIO_PIN_RESET)		//PE3

#define LCD_CLK(d)		LCD_D0(d)
#define LCD_MOSI(d)		LCD_D1(d)

#define LCD_IODELAY	

#define OLED_CS_Clr()  LCD_CS(0)
#define OLED_CS_Set()  LCD_CS(1)

#define OLED_RST_Clr() LCD_RES(0)
#define OLED_RST_Set() LCD_RES(1)

#define OLED_DC_Clr() LCD_DC(0)
#define OLED_DC_Set() LCD_DC(1)

#define OLED_WR_Clr() 
#define OLED_WR_Set() 

#define OLED_RD_Clr() 
#define OLED_RD_Set() 

#define OLED_SCLK_Clr() LCD_CLK(0)
#define OLED_SCLK_Set() LCD_CLK(1)

#define OLED_SDIN_Clr() LCD_MOSI(0)
#define OLED_SDIN_Set() LCD_MOSI(1)

void OLED_ledTest(uint8_t d)
{
	LCD_LED(d);
}
/**
  * @brief  全屏刷新（将显存内容写入OLED）
  * @param  None
  * @retval None
  */
void OLED_Refresh_Full(void) {
    for (uint8_t page = 0; page < OLED_PAGES; page++) {
        OLED_Set_Pos(0, page); // 设置起始位置（列0，页page）
        
        // 发送当前页的128列数据
        for (uint8_t col = 0; col < OLED_WIDTH; col++) {
            OLED_WR_Byte(OLED_GRAM[col][page], OLED_DATA);
        }
    }
}
/**************************************************************
*功  能：OLED输入数据
*参  数: dat 数据 cmd 命令
*返回值: 无 
**************************************************************/
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
#if 1					//我们选择的是第一种方法模拟SPI 
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();  //DC高电位传输数据
	else 
	  OLED_DC_Clr();		  //DC低电位传输命令
	OLED_CS_Clr();		//CS低电位
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();//D0 低电位 时钟线（CLK）
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();	//D0 高电位 时钟线（CLK）跳变时传输数据
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();  //CS高电平 DC翻转电平表示通信结束
#else
	if(cmd)
		LCD_DO_WRITE();
	else
		LCD_DO_CONTROL();	
		LCD_SPI_BEGIN();
		//LCD_DO_WRITE();
		LCD_SPI_TX(dat);//ch);
		LCD_SPI_WAIT_RXRDY();
		LCD_SPI_END();
#endif
} 

/**************************************************************
*功  能：OLED设置光标
*参  数: x 第几列   y 第几行
*返回值: 无 
**************************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);//高位地址
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 		//低位地址
}   	  

/**************************************************************
*功  能：开启OLED显示
*参  数: 无
*返回值: 无 
**************************************************************/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/**************************************************************
*功  能：关闭OLED显示
*参  数: 无
*返回值: 无 
**************************************************************/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 	
/**************************************************************
*功  能：清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
*参  数: 无
*返回值: 无 
**************************************************************/
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x02,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	}//更新显示
}
			 
/**************************************************************
*功  能：在指定位置显示一个字符,包括部分字符
*参  数: x:0~127  y:0~63  
*返回值: 无 
**************************************************************/
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';				//得到偏移后的值  codetab.h和ASCII码顺序一样，所以相对位移是一致的
	
	if(x>Max_Column-1){x=0;y=y+2;}
	if(SIZE ==16)  	//有8*6 和8*16的显示模式，这里选择8*16的
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); //传输单个字符
		
		
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y+1);
		for(i=0;i<6;i++)
		OLED_WR_Byte(F6x8[c][i],OLED_DATA);				
	}
}

/**************************************************************
*功  能：m^n函数
*参  数: m n
*返回值: M^N 
**************************************************************/
 uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  

/**************************************************************
*功  能：显示2个数字
*参  数: x,y :起点坐标	len :数字的位数 size:字体大小
*返回值: 无 
**************************************************************/
void OLED_ShowNum(uint8_t x,uint8_t y,uint16_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
}

/**************************************************************
*功  能：显示一个字符号串
*参  数: x,y :起点坐标	chr 字符串首地址，
y页地址在哪一行显示，x在哪一列显示
*返回值: 无 
**************************************************************/
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{
		OLED_ShowChar(x,y,chr[j]);
		x+=8;	//往右移8位显示下一个字符
		if(x>120){x=0;y+=2;}	//当前行到尾部时，换行显示
		j++;
	}
}

/**************************************************************
*功  能：显示汉字
*参  数: x,y :起点坐标	no 对应的字模
*返回值: 无 
**************************************************************/
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
	for(t=0;t<16;t++)
	{
		OLED_WR_Byte(String16_16[2*no][t],OLED_DATA);
		adder+=1;
	}	
	OLED_Set_Pos(x,y+1);	
	for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(String16_16[2*no+1][t],OLED_DATA);
		adder+=1;
	}					
} 


/********************************************
*功能描述：显示BMP图片128×64       
*参数：起始点坐标(x,y),x的范围0～127，y为页的范围0～7
*返回值：无          
*********************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
	unsigned int j=0;
	unsigned char x,y;
  
	if(y1%8==0) y=y1/8;      
	else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 

/**************************************************************
*功  能：初始化SSD1306	
*参  数: 无
*返回值: 无 
**************************************************************/
void OLED_SInit(void)
{ 	
  	OLED_RST_Set();
	
	HAL_Delay(100);

	OLED_RST_Clr();
	HAL_Delay(100);
	OLED_RST_Set(); 
					  	
	OLED_WR_Byte(0xAE,OLED_CMD);	//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);	//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);	//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);	//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);	//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);	// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);	//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);	//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);	//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);	//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);	//--1/64 duty
	OLED_WR_Byte(0x81,OLED_CMD);	//对比度设置
	OLED_WR_Byte(0xfF,OLED_CMD);	//1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WR_Byte(0xD3,OLED_CMD);	//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);	//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);	//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);	//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);	//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);	//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);	//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);	//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);	//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);	//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);	//
	OLED_WR_Byte(0x8D,OLED_CMD);	//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);	//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);	// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);	// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);	//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); 	/*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
	
}  

/**************************************************************
*功  能：OLED测试
*参  数: 无
*返回值: 无 
**************************************************************/	
void OLED_Test(void)
{
	static uint8_t c = 0;
	static uint8_t t = '1';
	if(c == 0)
	{
		OLED_Clear();
		OLED_ShowCHinese(0,0,0);	//中
		OLED_ShowCHinese(18,0,1);	//景
		OLED_ShowCHinese(36,0,2);	//园
		OLED_ShowCHinese(54,0,3);	//电
		OLED_ShowCHinese(72,0,4);	//子
		OLED_ShowCHinese(90,0,5);	//科
		OLED_ShowCHinese(108,0,6);	//技
		OLED_ShowString(0,3,"1.3' OLED TEST");
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	    //OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		OLED_ShowChar(48,6,t);		//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16); //显示ASCII字符的码值 				
	}
#if EN_BMP
	else if(c == 1)
	{
		OLED_Clear();
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
	}
	else 
	{
		OLED_Clear();
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP2);
	}
#endif
	if(++c > 2)
		c = 0;		
}

/**************************************************************
*功  能：OLED测试2
*参  数: 无
*返回值: 无 
**************************************************************/	
void OLED_Disp_Logo(void)
{
	OLED_ShowString(8,0,"<<R&C Zigbee>>\0");
}

/**************************************************************
*功  能：OLED显示 十六进制
*参  数: x,y 坐标  d 需要显示的数据
*返回值: 无 
**************************************************************/	
void OLED_Disp_hex16(uint8_t x,uint8_t y,uint32_t d)
{
	uint8_t tbuf[7];
	uint8_t i,t;
	
	tbuf[0] = '0';
	tbuf[1] = 'x';
	for(i = 0;i<4;i++)
	{
		t = (d>>12)&0x0f;
		tbuf[i+2] = (t < 10)? (t + '0'):(t + ('A'-10));
		d <<= 4;
	}
	tbuf[6] = 0;
	OLED_ShowString(x,y,tbuf);
}

/**************************************************************
*功  能：OLED显示指定的内容
*参  数: ch  id addr 需要显示的数据
*返回值: 无 
**************************************************************/	
void OLED_Disp_Info(uint16_t id,uint8_t ch,uint8_t addr)
{
	uint8_t t;
	OLED_ShowString(0,2,"CHANNEL:\0");
	if(ch >10)
		t = 2;
	else
		t = 1;
	OLED_ShowNum(8*9,2,ch,t,16);
	OLED_ShowString(0,4,"PAN_ID :\0");
	OLED_Disp_hex16(8*9,4,id);
	OLED_ShowString(0,6,"PAN_ADD:\0");
	OLED_ShowNum(8*9,6,addr,3,16);
}
/**************************************************************
*功  能：OLED显示测试3
*参  数: ch  id addr 需要显示的数据
*返回值: 无 
**************************************************************/	
void OLED_Disp_All(uint16_t id,uint8_t ch,uint8_t addr)
{ 
	OLED_Hinit();
	OLED_SInit();
	OLED_Clear();
	OLED_Disp_Logo();
	OLED_Disp_Info(id,ch,addr);
}



