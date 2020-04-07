#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "math.h"
#include "ds18b20.h"
#include "spi.h"
#include "24l01.h"  
#include <stdlib.h>
//ALIENTEK Mini STM32�����巶������9
//���벶��ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
void get_position(double t1,double t2);
void TIM4_Cap_Init(u16 arr,u16 psc);
extern u8 res;
double Sound_velo;

u16 TIM4CH_CAPTURE_VAL[3];
u8 count;
double position_x_f = 0,position_y_f = 0;



void delay_xms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //�Լ�����
      while(i--) ;    
   }
}



 int main(void)
 {	
	 double position_target_x = 0.5;
	 double position_target_y;
	 double position_start_x = 1;
	 double position_start_y = 1;
	 	 
	 double position_second_x,position_second_y,position_last_x ,position_last_y,position_location_x,position_location_y;
	 double final_direction;
	 int final_direction_int;
	 double  start_direction,go_double;
	 int start_direction_int,go_int,angle_int;
	 char angle_string[16],go_string[16];
	
	 
	int A = 0 , B = 0,C = 0 ,AC = 0,AB = 0;
	double t = 20, ab = 0,ac = 0,t1 = 0;
	int i = 0;
	int position_x_int = 0, position_y_int = 0,position_x_dec = 0,position_y_dec = 0;
    u8 tmp_buf[33];
	char abc;
	 abc = 'a';
	 
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	 
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(115200);	 			//���ڳ�ʼ��Ϊ9600	 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	DS18B20_Init();
	 USART3_Configuration(115200);
 	//TIM1_PWM_Init(719,999); 			//1000��Ƶ��PWMƵ��=72000/720=100hz
	//TIM_SetCompare1(TIM1,360);//ռ�ձ�50%
	 /*
	NRF24L01_Init();    	//��ʼ��NRF24L01  
	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		;
	}	  						
    NRF24L01_TX_Mode();
	
	*/
 	TIM4_Cap_Init(0XFFFF,71);		//��1Mhz��Ƶ�ʼ��� 



while(1)
	{
		
		
		
		
		
		
		
		
		
//------------------------------------------------------��һ�ο�ʼ-------------------------------------------------------------		
		
	position_target_x = 1.0;
	position_target_y = 0.5;
		
		
	while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				res = NULL;
			}
			}
	
			printf("a\r");
		
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2)
	{break;}
	
	
	}

	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;


	USART3_Send_String("G10");
		
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
//------------------------------------------------------��һ�ο�ʼ-------------------------------------------------------------		
			
			
			
			
			
			
			
			
			
			
			
			
//--------------------------------------------------------��һ��ѭ����λ-------------------------------------------------------			
			
while(1)
{

		
	
while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
		
					res = NULL;
			}
			}
			
			
			
				
			printf("a\r");
			
				
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2 && fabs(position_second_x- position_last_x)<0.3 && fabs(position_second_y- position_last_y)<0.3)
	{break;}
	
	
	
	}
	
	position_location_x = 	position_second_x;
	position_location_y =   position_second_y;
	

	
	
	if((position_location_x<(position_target_x+0.05)) &&(position_location_x>(position_target_x-0.05)))
	{
		break;		
	}
	
	
	
	start_direction =atan(fabs( position_location_y - position_last_y)/fabs(position_location_x - position_last_x));
	start_direction = 180*start_direction/3.1415926;
	start_direction_int = start_direction;
	
if((position_location_y - position_last_y)>=0 && (position_location_x - position_last_x) >0)
	{
		start_direction_int = start_direction_int;
	}
	if((position_location_y - position_last_y)>0 && (position_location_x - position_last_x) <=0)
	{
		start_direction_int = 180- start_direction_int;
	}
	if((position_location_y - position_last_y)<=0 && (position_location_x - position_last_x) <0)
	{
		start_direction_int = 180 + start_direction_int;
	}
	if((position_location_y - position_last_y)<0 && (position_location_x - position_last_x) >=0)
	{
		start_direction_int = 360 - start_direction_int;
	}
	
	final_direction =atan(fabs( position_target_y - position_location_y)/fabs(position_target_x - position_location_x));
	final_direction = 180*final_direction/3.1415926;
	final_direction_int = final_direction;
	
if((position_target_y - position_location_y)>=0 && (position_target_x - position_location_x) >0)
	{
		final_direction_int = final_direction_int;
		printf("a");
	}
	if((position_target_y - position_location_y)>0 && (position_target_x - position_location_x) <=0)
	{
		final_direction_int = 180- final_direction_int;
		printf("b");
	}
	
	if((position_target_y - position_location_y)<=0 && (position_target_x - position_location_x) <0)
	{
		final_direction_int = 180 + final_direction_int;
		printf("c");
	}
	if((position_target_y - position_location_y)<0 && (position_target_x - position_location_x) >=0)
	{
		final_direction_int = 360 - final_direction_int;
		printf("d");
	}
	
	angle_int =( final_direction_int - start_direction_int);
	
	printf("%d r\n",angle_int);
	
	if(angle_int > 0)
	{
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("L");
		USART3_Send_String(angle_string);
	}
	
	if(angle_int <= 0)
	{
		sprintf(angle_string, "%d", -angle_int); 
	    USART3_Send_String("R");
		USART3_Send_String(angle_string);
	}
	
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
	printf("%s r\n","go");
	
	go_double = sqrt(     (position_target_x-   position_location_x)*100 *(position_target_x-  position_location_x)*100  + (position_target_y- position_location_y) *100  *(position_target_y- position_location_y) *100         ) ;
	go_int = go_double/2;
	if (go_int>=18)		
	{
	USART3_Send_String("G20");
					
	}
		
	else
	{		
	sprintf(go_string, "%d", go_int); 
	USART3_Send_String("G");		
	USART3_Send_String(go_string);
	}						
	

			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
			

			
	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;	
			
		}
//--------------------------------------------------------ѭ����λ-------------------------------------------------------		
		
		
		
		
		
		
		
		




//--------------------------------------------------------��һ�����-------------------------------------------------------		
   	
		printf("finish");
		
		
	USART3_Send_String("N");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
			
			USART3_Send_String("N");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
		
		
//--------------------------------------------------------��һ�����-------------------------------------------------------				




			
			
			
			
			
			
			

//--------------------------------------------------------�ڶ��ο�ʼ--------------------------------------------------------

		
		
	position_target_x = 0.5;
	position_target_y = 1.0;
		
		
	
		
while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
		
					res = NULL;
			}
			}
				
			printf("a\r");
			
			//delay_ms(1000);		
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2)
	{break;}
	
	}

	

	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;


	USART3_Send_String("G10");
		
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
//------------------------------------------------------�ڶ��ο�ʼ-------------------------------------------------------------		
			
		









			
			
			
//--------------------------------------------------------�ڶ���ѭ����λ-------------------------------------------------------			
			
			



while(1)
{

			
	
		
	
while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
		
					res = NULL;
			}
			}
			
			
			
				
			printf("a\r");
			
				
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2 && fabs(position_second_x- position_last_x)<0.3 && fabs(position_second_y- position_last_y)<0.3)
	{break;}
	
	
	/*
	
	else
	{
	
			
	USART3_Send_String("G10");
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
	
	}
	*/
	 
	
	}
	
	position_location_x = 	position_second_x;
	position_location_y =   position_second_y;
	

	
	
	if((position_location_x<(position_target_x+0.05)) &&(position_location_x>(position_target_x-0.05)))
	{
		break;		
	}
	
	
	
	start_direction =atan(fabs( position_location_y - position_last_y)/fabs(position_location_x - position_last_x));
	start_direction = 180*start_direction/3.1415926;
	start_direction_int = start_direction;
	
if((position_location_y - position_last_y)>=0 && (position_location_x - position_last_x) >0)
	{
		start_direction_int = start_direction_int;
	}
	if((position_location_y - position_last_y)>0 && (position_location_x - position_last_x) <=0)
	{
		start_direction_int = 180- start_direction_int;
	}
	if((position_location_y - position_last_y)<=0 && (position_location_x - position_last_x) <0)
	{
		start_direction_int = 180 + start_direction_int;
	}
	if((position_location_y - position_last_y)<0 && (position_location_x - position_last_x) >=0)
	{
		start_direction_int = 360 - start_direction_int;
	}
	
	final_direction =atan(fabs( position_target_y - position_location_y)/fabs(position_target_x - position_location_x));
	final_direction = 180*final_direction/3.1415926;
	final_direction_int = final_direction;
	
if((position_target_y - position_location_y)>=0 && (position_target_x - position_location_x) >0)
	{
		final_direction_int = final_direction_int;
		printf("a");
	}
	if((position_target_y - position_location_y)>0 && (position_target_x - position_location_x) <=0)
	{
		final_direction_int = 180- final_direction_int;
		printf("b");
	}
	
	if((position_target_y - position_location_y)<=0 && (position_target_x - position_location_x) <0)
	{
		final_direction_int = 180 + final_direction_int;
		printf("c");
	}
	if((position_target_y - position_location_y)<0 && (position_target_x - position_location_x) >=0)
	{
		final_direction_int = 360 - final_direction_int;
		printf("d");
	}
	
	angle_int =( final_direction_int - start_direction_int);
	
	printf("%d r\n",angle_int);
	
	if(angle_int > 0)
	{
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("L");
		USART3_Send_String(angle_string);
	}
	
	if(angle_int <= 0)
	{
		sprintf(angle_string, "%d", -angle_int); 
	    USART3_Send_String("R");
		USART3_Send_String(angle_string);
	}
	
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
	printf("%s r\n","go");
	
	go_double = sqrt(     (position_target_x-   position_location_x)*100 *(position_target_x-  position_location_x)*100  + (position_target_y- position_location_y) *100  *(position_target_y- position_location_y) *100         ) ;
	go_int = go_double/2;
	if (go_int>=18)		
	{
	USART3_Send_String("G20");
					
	}
		
	else
	{		
	sprintf(go_string, "%d", go_int); 
	USART3_Send_String("G");		
	USART3_Send_String(go_string);
	}						
	

			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
			
	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;	
			
		}
		
//--------------------------------------------------------�ڶ���ѭ����λ-------------------------------------------------------		
		
		
		
		
		


		
		
		
		
		
		


//--------------------------------------------------------�ڶ������-------------------------------------------------------		
   	
		printf("finish");
		
		
	USART3_Send_String("N");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
			
			USART3_Send_String("N");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
		
		
//--------------------------------------------------------�ڶ������-------------------------------------------------------				


			
			
			
			
			
			



//--------------------------------------------------------�����ο�ʼ--------------------------------------------------------
	position_target_x = 0.5;
	position_target_y = 0.5;
			
			
		
	USART3_Send_String("N");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}	

			
			
if(position_location_y> position_start_y +0.15)
{
			
	USART3_Send_String("L150");
}			
			
			

else if(position_location_y> position_start_y +0.08)
{
			
	USART3_Send_String("L120");
}

else if (position_location_y< position_start_y -0.08)
{
			
	USART3_Send_String("L60");
}

else
{
	USART3_Send_String("L90");
}


					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
		

	printf("L90\r");	
		
		
			
	while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
		
					res = NULL;
			}
			}
			
			printf("a\r");
			
			//delay_ms(1000);		
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2)
	{break;}
	
	 
	
	}
		
	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;	
	
	
		USART3_Send_String("G10");
					
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}	

		
//--------------------------------------------------------�����ο�ʼ--------------------------------------------------------
			
			
			
			
			
			
			
			
			
			
			
//--------------------------------------------------------������ѭ����λ--------------------------------------------------------			
			
			
			
while(1)
{

			
	
	
while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//�õ��ܵĸߵ�ƽʱ��
			printf("A:%d us\r\n",A);	//��ӡ�ܵĸߵ�ƽʱ��
			B = TIM4CH_CAPTURE_VAL[1];		//�õ��ܵĸߵ�ƽʱ��
			printf("B:%d us\r\n",B);	//��ӡ�ܵĸߵ�ƽʱ��
			C = TIM4CH_CAPTURE_VAL[2];		//�õ��ܵĸߵ�ƽʱ��
			printf("C:%d us\r\n",C);	//��ӡ�ܵĸߵ�ƽʱ��	
			
			AC = C-A;//AC֮���ʱ����λu��
			AB = B-A;//AB֮���ʱ����λu��
			
			printf("AB:%d us\r\n",AB);
			printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			printf("ab:%f s\r\n",ab);
			printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			
			printf("second_x:%f r\n",position_second_x);
			printf("second_y:%f r\n",position_second_y);
			
			
			while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
		
					res = NULL;
			}
			}
			
			
			
				
			printf("a\r");
			
			//delay_ms(1000);		
			delay_ms(500);		
			
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж�
			count = 0;
			
			break;
			
		}
		
		
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.2&&position_second_y>0.2&& fabs(position_second_x- position_last_x)<0.3 && fabs(position_second_y- position_last_y)<0.3)
	{break;}
	
	 
	}
	
	position_location_x = 	position_second_x;
	position_location_y =   position_second_y;
	

	
	
	if((position_location_x<(position_target_x+0.03)) &&(position_location_x>(position_target_x-0.03))&&(position_location_y>(position_target_y-0.03))&&(position_location_y<(position_target_y+0.03)))
	{
		break;		
	}
	
	start_direction =atan(fabs( position_location_y - position_last_y)/fabs(position_location_x - position_last_x));
	start_direction = 180*start_direction/3.1415926;
	start_direction_int = start_direction;
	
if((position_location_y - position_last_y)>=0 && (position_location_x - position_last_x) >0)
	{
		start_direction_int = start_direction_int;
	}
	if((position_location_y - position_last_y)>0 && (position_location_x - position_last_x) <=0)
	{
		start_direction_int = 180- start_direction_int;
	}
	if((position_location_y - position_last_y)<=0 && (position_location_x - position_last_x) <0)
	{
		start_direction_int = 180 + start_direction_int;
	}
	if((position_location_y - position_last_y)<0 && (position_location_x - position_last_x) >=0)
	{
		start_direction_int = 360 - start_direction_int;
	}
	
	final_direction =atan(fabs( position_target_y - position_location_y)/fabs(position_target_x - position_location_x));
	final_direction = 180*final_direction/3.1415926;
	final_direction_int = final_direction;
	
if((position_target_y - position_location_y)>=0 && (position_target_x - position_location_x) >0)
	{
		final_direction_int = final_direction_int;
		printf("a");
	}
	if((position_target_y - position_location_y)>0 && (position_target_x - position_location_x) <=0)
	{
		final_direction_int = 180- final_direction_int;
		printf("b");
	}
	
	if((position_target_y - position_location_y)<=0 && (position_target_x - position_location_x) <0)
	{
		final_direction_int = 180 + final_direction_int;
		printf("c");
	}
	if((position_target_y - position_location_y)<0 && (position_target_x - position_location_x) >=0)
	{
		final_direction_int = 360 - final_direction_int;
		printf("d");
	}
	
	angle_int =( final_direction_int - start_direction_int);
	
	printf("%d r\n",angle_int);
	
	if(angle_int > 0)
	{
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("L");
		USART3_Send_String(angle_string);
	}
	
	if(angle_int <= 0)
	{
		sprintf(angle_string, "%d", -angle_int); 
	    USART3_Send_String("R");
		USART3_Send_String(angle_string);
	}
	
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
	printf("%s r\n","go");
		
	go_double = sqrt(     (position_target_x-   position_location_x)*100 *(position_target_x-  position_location_x)*100  + (position_target_y- position_location_y) *100  *(position_target_y- position_location_y) *100         ) ;
	go_int = go_double/2;
	if (go_int>=18)		
	{
	USART3_Send_String("G15");
					
	}
		
	else
	{		
	sprintf(go_string, "%d", go_int); 
	USART3_Send_String("G");		
	USART3_Send_String(go_string);
	}	

			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
			

			
	position_last_x = 	position_second_x;
	position_last_y =   position_second_y;	
			
			
		}

		
		
		
//--------------------------------------------------------������ѭ����λ--------------------------------------------------------					


		
		
		
		
		


//-----------------------------------------------------------------����-----------------------------------------------------------
	

		while(1)
		{	
    printf("finish");
	delay_ms(1000);}
		
		
			
			
		/*	
	delay_ms(5000);
	
			
	USART3_Send_String("L90");
			
	while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
					res = NULL;
			}
			}
			
	go_double = position_second_y*100 - 0.5*100 ;
	go_int = go_double;
	
	printf("%s r\n","go");		
    printf("%d r\n",go_int);
			
	sprintf(go_string, "%d", go_int); 		
	USART3_Send_String("G");
	USART3_Send_String(go_string);	

		while(1)
			{
				if (res!=NULL)
			{ 
					if(res == 'F')
					{
					res = NULL;
					   break;
					}
				
					res = NULL;
			}
			}			
	
	
			*/
			
			
			
	}
	
	
	
}
 
void get_position(double t1,double t2){
  double x1,x2,x3,x4;               //�м����
  double a,b,c;                     //��Ԫһ�η���ϵ��
  double t1_2,t2_2;
   double Sound_velo_2;   //���٣�����ƽ��
   double l1,l2,l3;                  //�����㵽��������������
  double p1,p2;                     //���׹�ʽ
  double pos_x,pos_y;               //λ������

	
  t1_2 = pow(t1,2);
  t2_2 = pow(t2,2);

  Sound_velo_2 = pow(Sound_velo,2);
  
  x1 = 1 + Sound_velo_2 * (t1_2 - t2_2);
  x2 = 2 * Sound_velo * (t1-t2);
  x3 = 1 + Sound_velo_2 * t1_2;
  x4 = 2 * Sound_velo * t1;
  a = pow(x2,2) + pow(x4,2) - 4;
  b = 2*x1*x2 + 2*x3*x4 - 4*x4;
  c = pow(x1,2) + pow(x3,2) - pow(x4,2);
  
  l1 = (-1*b-sqrt(b*b-4*a*c))/(2*a);
  l2 = l1 + Sound_velo*t1;
  l3 = l1 + Sound_velo*t2;
  
  p1 = 0.5*(1+l1+l2);            //���׹�ʽ
  pos_x = 2*sqrt(p1*(p1-l1)*(p1-l2)*(p1-1));  //������������
  p2 = 0.5*(1+l2+l3);            //���׹�ʽ
  pos_y = 2*sqrt(p2*(p2-1)*(p2-l2)*(p2-l3));  //������������
  
 
  position_x_f = pos_x;
  position_y_f = pos_y;

}



TIM_ICInitTypeDef  TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 //PA0 ����
	

	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	//��ʼ��TIM2���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	//��ʼ��TIM2���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�
    TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
	TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��2
  

}



//[7]:0,û�гɹ�����1,�ɹ�����һ��
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������ڴ���



//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{
	
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			
			
			if( count == 0 )						//��δ��ʼ,��һ�β���������
			{
				TIM4CH_CAPTURE_VAL[0] = 0;
	 			TIM_SetCounter(TIM4,0);		
				TIM_ITConfig(TIM4, TIM_IT_CC2, DISABLE);
				
				count = count + 1;
				
			}
		    else if( (count	== 1 || count ==2))						//���β���������
			{
				TIM4CH_CAPTURE_VAL[0] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC2, DISABLE);
				count = count + 1;
			}
		}			     	    					   
 	
	
 
		  
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//����2���������¼�
		{	
			
			if( count == 0  )						//��δ��ʼ,��һ�β���������
			{
				TIM4CH_CAPTURE_VAL[1] = 0;
	 			TIM_SetCounter(TIM4,0);		
				TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
				
				count = count + 1;
			}
		    else if((count	== 1 || count ==2) )							//���β���������
			{
				TIM4CH_CAPTURE_VAL[1] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
				count = count + 1;
				
			}	    
		}			     	    					   
 	
	
	
		  
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)//����3���������¼�
		{	
			
			if( count == 0  )						//��δ��ʼ,��һ�β���������
			{
				
	 			TIM_SetCounter(TIM4,0);
				TIM_ITConfig(TIM4, TIM_IT_CC4, DISABLE);
				TIM4CH_CAPTURE_VAL[2] = 0;
				count = count + 1;
			}
		    else if( (count	== 1 || count ==2)  )							//���β���������
			{
				TIM4CH_CAPTURE_VAL[2] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC4, DISABLE);
				count = count + 1;
				
			}	    
		}
		
 	
	
	
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //����жϱ�־λ
	
	
 
 
}


/*
			while(NRF24L01_TxPacket(tmp_buf)!=TX_OK)
			{
				;
			}
			
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				
				for(i=0;t<32;t++)
				{
					if( i == 0 )
						tmp_buf[i] = position_x_int;
					if( i == 1 )
						tmp_buf[i] = position_x_dec;
					if( i == 2 )
						tmp_buf[i] = position_y_int;
					if( i == 3 )
						tmp_buf[i] = position_y_dec;
					if( i > 3 )
						tmp_buf[i] = 0;
					
				}
				tmp_buf[32]=0;//���������
				
				printf("Sended DATA:\r\n");
				for(i=0;i<32;i++)
				{
				printf("%d",tmp_buf[i]);
				}
				printf("\n");

						   
			}
			
			*/
			
			/*
			printf("x_f:%f m\r\n",position_x_f);
			printf("y_f:%f m\r\n",position_y_f);
			
			position_x_int = position_x_f;
			position_x_dec = position_x_f * 1000 - position_x_int * 1000;
			position_y_int = position_y_f;
			position_y_dec = position_y_f * 1000 - position_y_int * 1000;
			
			printf("x_int:%d ",position_x_int);
			printf(".%d m\r\n",position_x_dec);
			printf("y_int:%d ",position_y_int);
			printf(".:%d m\r\n",position_y_dec);
			
			*/
			