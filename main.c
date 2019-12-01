
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "tpad.h"
#include "stdlib.h"

#define a 7    //С��ĳ��Ϳ�
#define b 15   
#define birdv 10  //�����ٶ�
#define birdfly 28  //С����ٶ�

#define width 60   //���ӿ��
#define high 100    //����ȱ�ڸ߶�

void DrawDird(u16 x,u16 y,int fly)      //��С��
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	
	if(fly==0)   //����
	{
	x1=x-a;y1=y-b;
	x2=x+a;y2=y+b;
	x3=x-b;y3=y-a;
	x4=x+b;y4=y+a;
		
	
		
	}
	else if(fly==1)   //����
	{
	x1=x+a;y1=y-b;
	x2=x-a;y2=y+b;
	x3=x-b;y3=y+a;
	x4=x+b;y4=y-a;
		
	
		
	}
	
	LCD_Draw_Circle(x,y,5);     //С�������
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x1,y1,x4,y4);
	LCD_DrawLine(x2,y2,x3,y3);
	LCD_DrawLine(x2,y2,x4,y4);

}
  
void DrawBar(u16 x,u16 y)    //������
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
 {	 int i = 0;     //��Ϸ����
	 u8 score=0;     //����
	u8 num[12];      //��ŷ����ַ���
	 
	 
	 u16 barx=240;   //����x
	 u16 bary=100;   //����y
	u16 birdx=120;   //С��x
	u16 birdy=160;   //С��y
	 
	 
	 //�����Ǳ���
	u16 firex=300;       //����x
	u16 firey=200;       //����y
	u16 waterx=300;       //ˮx
	u16 watery=150;       //ˮy 
	u16 gx=300;       //gx
	u16 gy=150;       //gy 
	u16 hx=300;       //hx
	u16 hy=150;       //hy 
	


	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	
  TPAD_Init(6);			//��ʼ����������	 
  
while(1)
{	
	
	  POINT_COLOR=BLACK;    
	
	
	DrawDird(birdx,birdy,TPAD_Scan(1));  //����*********************************
	

	birdy = birdy + birdv;    //����
	
	if(barx==64) {score++;}   //�÷�
	
	sprintf((char*)num,"SCORE:%d",score);   //�������洢���ַ�����
	
	LCD_ShowString(10,10,200,16,16,num);    //��ӡ����
	
	if(i>20)                            //��Ϸ��ʼ���Ե�һ��ʱ��
	{
	DrawBar(barx,bary);                  //������*********************************
	barx = barx-8;   //�����ƶ�
	if(barx<10)    //����ˢ��
		{barx = 240;
		bary = rand()%150;}
	}
	
	/****************************�������ƶ��뽥��************************************************/
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

	
	/*******************************������ˢ��***********************************/	
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
	
		
	if(birdy>=300) break;  //ˤ��
	if(birdy<=50) birdy =60;//���ܷ�̫��
	if(TPAD_Scan(1))	//�ɹ�������һ��������(�˺���ִ��ʱ������15ms)
		{
			birdy = birdy - birdfly;		//��
		}
		
	if(barx<120&&barx>60)      //ײ����������
		if(bary>birdy||bary<birdy-100) break;
	

		
	
  if(i%2==0) LCD_Clear(WHITE-1*i);  //����ɫ����
	

	i++;   //��Ϸ����
}

while(1)  //game over
{



LCD_ShowString(70,130,210,24,24,"GAME OVER"); 
	LCD_ShowString(95,160,200,16,16,num);
	
}
}
 