
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "tpad.h"
#include "stdlib.h"

#define a 7    //小鸟的长和宽
#define b 15   
#define birdv 10  //下落速度
#define birdfly 28  //小鸟飞速度

#define width 60   //柱子宽度
#define high 100    //柱子缺口高度

void DrawDird(u16 x,u16 y,int fly)      //画小鸟
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	
	if(fly==0)   //下落
	{
	x1=x-a;y1=y-b;
	x2=x+a;y2=y+b;
	x3=x-b;y3=y-a;
	x4=x+b;y4=y+a;
		
	
		
	}
	else if(fly==1)   //飞翔
	{
	x1=x+a;y1=y-b;
	x2=x-a;y2=y+b;
	x3=x-b;y3=y+a;
	x4=x+b;y4=y-a;
		
	
		
	}
	
	LCD_Draw_Circle(x,y,5);     //小鸟的身体
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x1,y1,x4,y4);
	LCD_DrawLine(x2,y2,x3,y3);
	LCD_DrawLine(x2,y2,x4,y4);

}
  
void DrawBar(u16 x,u16 y)    //画柱子
{
	int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8;  
	//POINT_COLOR=color;
	
	x1=x,y1=0;
	x2=x+60,y2=0;
	x3=x,y3=y;
	x4=x+60,y4=y;
	x5=x,y5=y+high;
	x6=x+60,y6=y+high;
	x7=x,y7=320;
	x8=x+60,y8=320;
	
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x4,y4);
	LCD_DrawLine(x3,y3,x4,y4);
	
	LCD_DrawLine(x5,y5,x6,y6);
	LCD_DrawLine(x5,y5,x7,y7);
	LCD_DrawLine(x6,y6,x8,y8);
	LCD_DrawLine(x7,y7,x8,y8);
	
	
	
}



 int main(void)
 {	 int i = 0;     //游戏进程
	 u8 score=0;     //分数
	u8 num[12];      //存放分数字符串
	 
	 
	 u16 barx=240;   //柱子x
	 u16 bary=100;   //柱子y
	u16 birdx=120;   //小鸟x
	u16 birdy=160;   //小鸟y
	 
	 
	 //以下是背景
	u16 firex=300;       //火焰x
	u16 firey=200;       //火焰y
	u16 waterx=300;       //水x
	u16 watery=150;       //水y 
	u16 gx=300;       //gx
	u16 gy=150;       //gy 
	u16 hx=300;       //hx
	u16 hy=150;       //hy 
	


	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();
	
  TPAD_Init(6);			//初始化触摸按键	 
  
while(1)
{	
	
	  POINT_COLOR=BLACK;    
	
	
	DrawDird(birdx,birdy,TPAD_Scan(1));  //画鸟*********************************
	

	birdy = birdy + birdv;    //下落
	
	if(barx==64) {score++;}   //得分
	
	sprintf((char*)num,"SCORE:%d",score);   //将分数存储在字符串里
	
	LCD_ShowString(10,10,200,16,16,num);    //打印分数
	
	if(i>20)                            //游戏开始后稍等一段时间
	{
	DrawBar(barx,bary);                  //画柱子*********************************
	barx = barx-8;   //柱子移动
	if(barx<10)    //柱子刷新
		{barx = 240;
		bary = rand()%150;}
	}
	
	/****************************背景的移动与渐变************************************************/
	POINT_COLOR=0x0000+i;
	LCD_Draw_Circle(firex,firey,2*i);
	POINT_COLOR=0x0000+2*i;
	LCD_Draw_Circle(waterx,watery,3*i);
	POINT_COLOR=0x0000+3*i;
	LCD_Draw_Circle(gx,gy,i);
	POINT_COLOR=0x0000+3*i;
	LCD_Draw_Circle(hx,hy,6*i);
	POINT_COLOR=BLACK;
	/**********************************************************************************************/

	
	/*******************************背景的刷新***********************************/	
	firex = firex-30;
  if(firex==0)    
		{firex = 300;
		firey = rand()%350;}	
		
	waterx = waterx-50;
  if(waterx==0)    
		{waterx = 300;
		watery = rand()%350;}
		
	gx = gx-15;
  if(gx==0)    
		{gx = 300;
		gy = rand()%350;}	
		
	hx = hx-5;
  if(hx==0)    
		{hx = 300;
		hy = rand()%350;}	
	/*******************************************************************************/	
	
		
	if(birdy>=300) break;  //摔死
	if(birdy<=50) birdy =60;//不能飞太高
	if(TPAD_Scan(1))	//成功捕获到了一次上升沿(此函数执行时间至少15ms)
		{
			birdy = birdy - birdfly;		//跳
		}
		
	if(barx<120&&barx>60)      //撞死在柱子上
		if(bary>birdy||bary<birdy-100) break;
	

		
	
  if(i%2==0) LCD_Clear(WHITE-1*i);  //渐变色清屏
	

	i++;   //游戏进程
}

while(1)  //game over
{



LCD_ShowString(70,130,210,24,24,"GAME OVER"); 
	LCD_ShowString(95,160,200,16,16,num);
	
}
}
 