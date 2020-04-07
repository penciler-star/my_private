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
//ALIENTEK Mini STM32开发板范例代码9
//输入捕获实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
void get_position(double t1,double t2);
void TIM4_Cap_Init(u16 arr,u16 psc);

double Sound_velo;

u16 TIM4CH_CAPTURE_VAL[3];
u8 count;
double position_x_f = 0,position_y_f = 0;



 int main(void)
 {	
	 double position_target_x;
	 double position_target_y;
	 double position_last_x,position_last_y;
	 double position_second_x,position_second_y;
	 double position_location_x,position_location_y;
	 double final_direction;
	 int final_direction_int;
	 double  start_direction,go_double;
	 int start_direction_int,go_int,angle_int;
	 int times;
	 char angle_string[30],go_string[30];

	u8 len;
	 char send_string[100];

	 
	char target_x_string_middle[100]; 
	char target_y_string_middle[100];
	 
	 char target_x_string[30];
	 char target_y_string[30];
	 
	 int target_x_int,target_y_int;
	 int send_int_x,send_int_y,send_int;
	int flag;
	 
	int A = 0 , B = 0,C = 0 ,AC = 0,AB = 0;
	double t = 20, ab = 0,ac = 0;
	int i,j;
	char instruction;

    //u8 tmp_buf[33];

	 
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	 
	delay_init();	    	 //延时函数初始化	
	uart_init(115200);	 			//串口初始化为9600	 
	LED_Init();		  	//初始化与LED连接的硬件接口
	DS18B20_Init();
	 USART3_Configuration(115200);
 	//TIM1_PWM_Init(719,999); 			//1000分频。PWM频率=72000/720=100hz
	//TIM_SetCompare1(TIM1,360);//占空比50%
	 /*
	NRF24L01_Init();    	//初始化NRF24L01  
	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		;
	}	  						
    NRF24L01_TX_Mode();
	
	*/
 	TIM4_Cap_Init(0XFFFF,71);		//以1Mhz的频率计数 


		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
		
//------------------------------------------------------开始-------------------------------------------------------------	
		
	
	while(1){
	
	USART3_Send_String("N");
	
	while(1)
	 {
		if(count == 3)
		{
			
			t = DS18B20_Get_Temp();
			t = t/10;
			//printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 348;
			
			//printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//得到总的高电平时间
			//printf("A:%d us\r\n",A);	//打印总的高点平时间
			B = TIM4CH_CAPTURE_VAL[1];		//得到总的高电平时间
			//printf("B:%d us\r\n",B);	//打印总的高点平时间
			C = TIM4CH_CAPTURE_VAL[2];		//得到总的高电平时间
			//printf("C:%d us\r\n",C);	//打印总的高点平时间	
			
			AC = C-A;//AC之间的时间差，单位u秒
			AB = B-A;//AB之间的时间差，单位u秒
			
			//printf("AB:%d us\r\n",AB);
			//printf("AC:%d us\r\n",AC);
			
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			//printf("ab:%f s\r\n",ab);
			//printf("ac:%f s\r\n",ac);
			
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			//printf("start_x:%f r\n",position_second_x);
			//printf("start_y:%f r\n",position_second_y);
			
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
			
			delay_ms(500);		
			
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断
			count = 0;
			
			break;
		}
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.05&&position_second_y>0.05)
	{
		break;
	}
	
	}
	
	if(position_second_x>=0.1 &&position_second_x<1 &&position_second_y<1  &&position_second_y>=0.1) 
	{
	send_int_x = position_second_x*100;
	send_int_x = send_int_x*100;
	send_int_y = position_second_y*100;
	send_int = send_int_x + send_int_y;
	sprintf(send_string, "%d", send_int); 
	printf("%s\r\n",send_string);}
	

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
//------------------------------------------------------开始-------------------------------------------------------------		

			

while(1)
	{



	
//-------------------------------------------------------------接收下一目标点--------------------------------------------		
	
			while(1)
		{
	if(USART_RX_STA&0x8000)
		{	
		
		
			
		len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			
		if(len>3)
		{
		flag = 1;
		times = len/4;

		
		for ( i =0;i<times;i++)
			{
			   target_x_string_middle[2*i+0] = USART_RX_BUF[4*i+0];
               target_x_string_middle[2*i+1] = USART_RX_BUF[4*i+1];
			   target_y_string_middle[2*i+0] = USART_RX_BUF[4*i+2];
               target_y_string_middle[2*i+1] = USART_RX_BUF[4*i+3];
							
			}
		}
		
		else
		{
			flag = 0;
			instruction = USART_RX_BUF[0];
		}
			
		USART_RX_STA=0;
					
		break;
		
		}
	}
		

	if(flag == 1)
	{		
	for(j = 0;j<times;j++)
	{	

	
	target_x_string[0] = target_x_string_middle[2*j+0];
	target_x_string[1] = target_x_string_middle[2*j+1];
	target_y_string[0] = target_y_string_middle[2*j+0];
	target_y_string[1] = target_y_string_middle[2*j+1];

	
	

	target_x_int = atoi(target_x_string);
	target_y_int = atoi(target_y_string);	
	position_target_x = target_x_int;
	position_target_x = position_target_x/100;
	position_target_y = target_y_int;
	position_target_y = position_target_y/100;
	
	
	
	
//------------------------------------------------------------接收下一目标点--------------------------------------------		
		


			
	
			
			
//--------------------------------------------------------循环定位-------------------------------------------------------			
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
			//printf("temp:%f \n",t);
			//Sound_velo = 331.45*sqrt(1+t/273.15);
			Sound_velo = 347;
			
			//printf("v:%f m/s\r\n",Sound_velo);
			
			A = TIM4CH_CAPTURE_VAL[0];		//得到总的高电平时间
			//printf("A:%d us\r\n",A);	//打印总的高点平时间
			B = TIM4CH_CAPTURE_VAL[1];		//得到总的高电平时间
			//printf("B:%d us\r\n",B);	//打印总的高点平时间
			C = TIM4CH_CAPTURE_VAL[2];		//得到总的高电平时间
			//printf("C:%d us\r\n",C);	//打印总的高点平时间	
			
			AC = C-A;//AC之间的时间差，单位u秒
			AB = B-A;//AB之间的时间差，单位u秒
			
			//printf("AB:%d us\r\n",AB);
			//printf("AC:%d us\r\n",AC);
			
			ab = 0.000001*AB;
			ac = 0.000001*AC;
			
			//printf("ab:%f s\r\n",ab);
			//printf("ac:%f s\r\n",ac);
			
			get_position(ab,ac);
			position_second_x = position_x_f;
			position_second_y = position_y_f;
			
			//printf("second_x:%f r\n",position_second_x);
			//printf("second_y:%f r\n",position_second_y);
			
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
						
			delay_ms(500);					
			TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断
			count = 0;
			break;
		}
	}
	 
	if(position_second_x<1.2 && position_second_y<1.2  &&position_second_x>0.01&&position_second_y>0.01 && fabs(position_second_x- position_last_x)<0.3 && fabs(position_second_y- position_last_y)<0.3 )
		{
			break;
		}
	
	}

	if(position_second_x>=0.1 &&position_second_x<1 &&position_second_y<1  &&position_second_y>=0.1) 
	{

	send_int_x = position_second_x*100;
	send_int_x = send_int_x*100;
	send_int_y = position_second_y*100;
	send_int = send_int_x + send_int_y;
	sprintf(send_string, "%d", send_int); 
	printf("%s\r\n",send_string);
	}
	
	
	position_location_x = 	position_second_x;
	position_location_y =   position_second_y;
	
	if((position_location_x<(position_target_x+0.07)) &&(position_location_x>(position_target_x-0.07))&&(position_location_y<(position_target_y+0.07)) &&(position_location_y>(position_target_y-0.07)))
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
		//printf("a");
	}
	if((position_target_y - position_location_y)>0 && (position_target_x - position_location_x) <=0)
	{
		final_direction_int = 180- final_direction_int;
		//printf("b");
	}
	
	if((position_target_y - position_location_y)<=0 && (position_target_x - position_location_x) <0)
	{
		final_direction_int = 180 + final_direction_int;
		//printf("c");
	}
	if((position_target_y - position_location_y)<0 && (position_target_x - position_location_x) >=0)
	{
		final_direction_int = 360 - final_direction_int;
		//printf("d");
	}
	
	
	
	angle_int =( final_direction_int - start_direction_int);
	
	
	if(fabs(angle_int)<50)
	{angle_int = angle_int/3;}
	
	else
	{
		angle_int = angle_int;
	}
		
	//printf("%d r\n",angle_int);
	
	if(angle_int > 180)
	{
		angle_int = 360-angle_int;
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("R");
		USART3_Send_String(angle_string);
	}
	
	 
	
	else if(angle_int > 0)
	{
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("L");
		USART3_Send_String(angle_string);
	}
	
	else if(angle_int >= -180)
	{
		sprintf(angle_string, "%d", -angle_int); 
	    USART3_Send_String("R");
		USART3_Send_String(angle_string);
	}
	
	else 
	{
		angle_int = 360+angle_int;
		sprintf(angle_string, "%d", angle_int); 
	    USART3_Send_String("L");
		USART3_Send_String(angle_string);
	
	}
	
	
	while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	
	//printf("%s r\n","go");
	go_double = sqrt(     (position_target_x-   position_location_x)*100 *(position_target_x-  position_location_x)*100  + (position_target_y- position_location_y) *100  *(position_target_y- position_location_y) *100         ) ;
	go_int = go_double/2;
	if (go_int>=14)		
	{
		
		USART3_Send_String("G13");
					
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
//--------------------------------------------------------循环定位-------------------------------------------------------		














//--------------------------------------------------------完成-------------------------------------------------------		
		//printf("finish");
		
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
			
			USART3_Send_String("N");		
	
			while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
//--------------------------------------------------------完成-------------------------------------------------------				

		}
			
	}
	
	
	
	else{
	if(instruction=='g')
	{ 
		USART3_Send_String("G5"); 
		while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	}
	if(instruction=='b')
	{
		USART3_Send_String("B5");
		while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	}
	if(instruction=='l')
	{
		USART3_Send_String("L5");
		while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}	
	}
	if(instruction=='r')
	{
		USART3_Send_String("R5");
		while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	}
    if(instruction=='n')
	{
		USART3_Send_String("N");
		while(1)
			{if (res!=NULL)
			{ if(res == 'F')
					{res = NULL;
					   break;
		     }res = NULL;	
			}}
	}

	
	
	
	}
			
	}
}
 
void get_position(double t1,double t2){
  double x1,x2,x3,x4;               //中间参数
  double a,b,c;                     //二元一次方程系数
  double t1_2,t2_2;
   double Sound_velo_2;   //声速，声速平方
   double l1,l2,l3;                  //发声点到三个传感器距离
  double p1,p2;                     //海伦公式
  double pos_x,pos_y;               //位置坐标

	
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
  
  p1 = 0.5*(1+l1+l2);            //海伦公式
  pos_x = 2*sqrt(p1*(p1-l1)*(p1-l2)*(p1-1));  //三角形面积求高
  p2 = 0.5*(1+l2+l3);            //海伦公式
  pos_y = 2*sqrt(p2*(p2-1)*(p2-l2)*(p2-l3));  //三角形面积求高
  
 
  position_x_f = pos_x;
  position_y_f = pos_y;

}



TIM_ICInitTypeDef  TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 //PA0 下拉
	

	//初始化定时器2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	//初始化TIM2输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	//初始化TIM2输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
    TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
	TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4,ENABLE ); 	//使能定时器2
  

}



//[7]:0,没有成功捕获；1,成功捕获到一次
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出第次数



//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{
	
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			
			
			if( count == 0 )						//还未开始,第一次捕获上升沿
			{
				TIM4CH_CAPTURE_VAL[0] = 0;
	 			TIM_SetCounter(TIM4,0);		
				TIM_ITConfig(TIM4, TIM_IT_CC2, DISABLE);
				
				count = count + 1;
				
			}
		    else if( (count	== 1 || count ==2))						//二次捕获上升沿
			{
				TIM4CH_CAPTURE_VAL[0] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC2, DISABLE);
				count = count + 1;
			}
		}			     	    					   
 	
	
 
		  
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获2发生捕获事件
		{	
			
			if( count == 0  )						//还未开始,第一次捕获上升沿
			{
				TIM4CH_CAPTURE_VAL[1] = 0;
	 			TIM_SetCounter(TIM4,0);		
				TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
				
				count = count + 1;
			}
		    else if((count	== 1 || count ==2) )							//二次捕获上升沿
			{
				TIM4CH_CAPTURE_VAL[1] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
				count = count + 1;
				
			}	    
		}			     	    					   
 	
	
	
		  
		
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)//捕获3发生捕获事件
		{	
			
			if( count == 0  )						//还未开始,第一次捕获上升沿
			{
				
	 			TIM_SetCounter(TIM4,0);
				TIM_ITConfig(TIM4, TIM_IT_CC4, DISABLE);
				TIM4CH_CAPTURE_VAL[2] = 0;
				count = count + 1;
			}
		    else if( (count	== 1 || count ==2)  )							//二次捕获上升沿
			{
				TIM4CH_CAPTURE_VAL[2] = TIM_GetCounter(TIM4);
				TIM_ITConfig(TIM4, TIM_IT_CC4, DISABLE);
				count = count + 1;
				
			}	    
		}
		
	
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4); //清除中断标志位
	
}
