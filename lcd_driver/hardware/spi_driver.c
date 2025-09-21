#include "spi_driver.h"


void LCD_Write_Data(uint8_t data){
	CLR_LCD_CSX;
	SET_LCD_DC;
	for(int i=0;i<8;i++){
		if(data&0x80){
			SET_LCD_SDA;
		}
		else{
			CLR_LCD_SDA;
		}
		CLR_LCD_SCK;
		SET_LCD_SCK;
		data=data <<1;
	}
	SET_LCD_CSX;
}

void LCD_Write_Command(uint8_t cmd){
	CLR_LCD_CSX;
	CLR_LCD_DC;
	for(int i=0;i<8;i++){
		if(cmd&0x80){
			SET_LCD_SDA;
		}
		else{
			CLR_LCD_SDA;
		}
		CLR_LCD_SCK;
		SET_LCD_SCK;
		cmd=cmd <<1;
	}
	SET_LCD_CSX;
}


void LCD_Parameter(void){
		LCD_Write_Command(0x11); //Sleep out 
    HAL_Delay(120);   
		LCD_Write_Command(0xB1); 
    LCD_Write_Data(0x05); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Command(0xB2); 
    LCD_Write_Data(0x05); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Command(0xB3); 
    LCD_Write_Data(0x05); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Data(0x05); 
    LCD_Write_Data(0x3C); 
    LCD_Write_Data(0x3C); 
    //------------------------------------End ST7735S Frame Rate---------------------------------// 
    LCD_Write_Command(0xB4); //Dot inversion 
    LCD_Write_Data(0x03); 
    //------------------------------------ST7735S Power Sequence---------------------------------// 
    LCD_Write_Command(0xC0); 
    LCD_Write_Data(0x28); 
    LCD_Write_Data(0x08); 
    LCD_Write_Data(0x04); 
    LCD_Write_Command(0xC1); 
    LCD_Write_Data(0XC0); 
    LCD_Write_Command(0xC2); 
    LCD_Write_Data(0x0D); 
    LCD_Write_Data(0x00); 
    LCD_Write_Command(0xC3); 
    LCD_Write_Data(0x8D); 
    LCD_Write_Data(0x2A); 
    LCD_Write_Command(0xC4); 
    LCD_Write_Data(0x8D); 
    LCD_Write_Data(0xEE); 
    //---------------------------------End ST7735S Power Sequence-------------------------------------// 
    LCD_Write_Command(0xC5); //VCOM 
    LCD_Write_Data(0x1A); 
    LCD_Write_Command(0x36); //MX, MY, RGB mode 
    LCD_Write_Data(0xC0); 
    //------------------------------------ST7735S Gamma Sequence---------------------------------// 
    LCD_Write_Command(0xE0); 
    LCD_Write_Data(0x04); 
    LCD_Write_Data(0x22); 
    LCD_Write_Data(0x07); 
    LCD_Write_Data(0x0A); 
    LCD_Write_Data(0x2E); 
    LCD_Write_Data(0x30); 
    LCD_Write_Data(0x25); 
    LCD_Write_Data(0x2A); 
    LCD_Write_Data(0x28); 
    LCD_Write_Data(0x26); 
    LCD_Write_Data(0x2E); 
    LCD_Write_Data(0x3A); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x03); 
    LCD_Write_Data(0x13); 
    LCD_Write_Command(0xE1); 
    LCD_Write_Data(0x04); 
    LCD_Write_Data(0x16); 
    LCD_Write_Data(0x06); 
    LCD_Write_Data(0x0D); 
    LCD_Write_Data(0x2D); 
    LCD_Write_Data(0x26); 
    LCD_Write_Data(0x23); 
    LCD_Write_Data(0x27); 
    LCD_Write_Data(0x27); 
    LCD_Write_Data(0x25); 
    LCD_Write_Data(0x2D); 
    LCD_Write_Data(0x3B); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x04); 
    LCD_Write_Data(0x13); 
    //------------------------------------End ST7735S Gamma Sequence-----------------------------// 
    LCD_Write_Command(0x3A); //65k mode 
    LCD_Write_Data(0x05); 
    LCD_Write_Command(0x29); //Display on 
}

void LCD_Init(void){
	CLR_LCD_RST;
	HAL_Delay(1);
	SET_LCD_RST;
	HAL_Delay(120);
	LCD_Parameter();
}


void LCD_Write_16bitRGB(uint16_t rgb){
	LCD_Write_Data(rgb>>8);
	LCD_Write_Data(rgb&0xFF);
}



//设置接下来要写入的屏幕坐标范围
void LCD_SET_Address(uint8_t x_start,uint8_t x_end,uint8_t y_start,uint8_t y_end){
	LCD_Write_Command(0x2A);
	LCD_Write_Data(0x00);
	LCD_Write_Data(x_start&0xFF);
	LCD_Write_Data(0x00);
	LCD_Write_Data(x_end&0xFF);

	LCD_Write_Command(0x2B);
	LCD_Write_Data(0x00);
	LCD_Write_Data(y_start&0xFF);
	LCD_Write_Data(0x00);
	LCD_Write_Data(y_end&0xFF);

	LCD_Write_Command(0x2C);		//启动下面的内存写入，对lcd写入rgb参数
}

//设置屏幕背景颜色（全屏写入颜色,因为屏幕使用的是128*160的，根据具体需求进行更改）   
void LCD_clear(uint16_t color)
{
	
	LCD_SET_Address(0,128,0,160);
	for(int i=0;i<128;i++){
		for(int j=0;j<160;j++){
			LCD_Write_16bitRGB(color);	
		}
	}
}

void LCD_Fill(uint8_t x_start,uint8_t x_end,uint8_t y_start,uint8_t y_end,uint16_t color)
{
	LCD_SET_Address(x_start,x_end,y_start,y_end);
	for(int i=x_start;i<x_end+1;i++){
		for(int j=y_start;j<y_end+1;j++){
			LCD_Write_16bitRGB(color);	
		}
	}
}
void LCD_DrawPoint(uint8_t x,uint8_t y,uint16_t color)
{
	LCD_SET_Address(x,x,y,y);
	LCD_Write_16bitRGB(color);
}

void saber(void){
	LCD_SET_Address(10,109,10,109);
	for(uint32_t i=0;i<20000;i++)
	{
		LCD_Write_Data(gImage_saber[i]);
	
	}
}

