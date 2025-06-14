
#ifndef __OLED_DRV_H__
#define __OLED_DRV_H__

#include <stdint.h>



#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  
// oled_drv.h
#define OLED_WIDTH   128
#define OLED_HEIGHT  64
#define OLED_PAGES   (OLED_HEIGHT/8)

extern uint8_t OLED_GRAM[OLED_WIDTH][OLED_PAGES]; // 声明全局显存
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t); 
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr); 
void OLED_ShowNum(uint8_t x,uint8_t y,uint16_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_Refresh_Full(void);
void OLED_Hinit(void);
void OLED_SInit(void);
void OLED_Test(void);

void OLED_Disp_All(uint16_t id,uint8_t ch,uint8_t addr);

void Find_HZ(uint8_t x,uint8_t y,uint8_t *buf,uint8_t lenth);


#endif //__OLED_DRV_H__

