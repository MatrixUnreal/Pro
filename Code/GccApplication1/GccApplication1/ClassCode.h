/*
 * ClassCode.h
 *
 * Created: 08.06.2017 19:46:49
 *  Author: Rustam
 */ 
#include "Init.h"
#include "PortIO.h"

#ifndef CLASSCODE_H_
#define CLASSCODE_H_

class Properties
{	
	public:
	bool state, 	//0-free,1-busy
	     dirrect;	//0-clockwise,1-counter-clockwise
	char location;	//0-middle,1-bottom,2-top
	
	
	//int time_from_start;
};

class MotorDC : public Properties
{
	public:
	void Stop()
	{
		O_ROT1_OFF;
		O_ROT2_OFF;
		state=false;
	}
	void Run_Forward()//по часовой
	{
		state=true;
		dirrect=false;
		O_ROT2_OFF;
		O_ROT1_ON;
		location=0;
	}
	void Run_Backward()//против часовой
	{
		state=true;
		dirrect=true;
		O_ROT1_OFF;
		O_ROT2_ON;
		location=0;
	}
	
	void Run(bool dir)
	{
		if(dir)Run_Backward();
		else Run_Forward();
	}
	
} ;


class MotorStep : public Properties
{
	public:
	char position;
		
	protected:
	int current_angle;
	
	private:
	void Run_0()
	{
		state=true;
		current_angle=0;
		OPORTE_ON;
		OPORT1_ON;
		OPORT2_OFF;
		OPORT3_OFF;
		OPORT4_ON;
	}
	
	void Run_45()
	{
		state=true;
		current_angle=45;
		OPORTE_ON;
		OPORT1_OFF;
		OPORT2_OFF;
		OPORT3_OFF;
		OPORT4_ON;
	}
	void Run_90()
	{
		state=true;
		current_angle=90;
		OPORTE_ON;
		OPORT1_OFF;
		OPORT2_OFF;
		OPORT3_ON;
		OPORT4_ON;
	}
	void Run_135()
	{
		state=true;
		current_angle=135;
		OPORTE_ON;
		OPORT1_OFF;
		OPORT2_OFF;
		OPORT3_ON;
		OPORT4_OFF;
	}
	void Run_180()
	{
		state=true;
		current_angle=180;
		OPORTE_ON;
		OPORT1_OFF;
		OPORT2_ON;
		OPORT3_ON;
		OPORT4_OFF;
	}
	void Run_225()
	{
		state=true;
		current_angle=225;
		OPORTE_ON;
		OPORT1_OFF;
		OPORT2_ON;
		OPORT3_OFF;
		OPORT4_OFF;
	}	
	void Run_270()
	{
		state=true;
		current_angle=270;
		OPORTE_ON;
		OPORT1_ON;
		OPORT2_ON;
		OPORT3_OFF;
		OPORT4_OFF;
	}
	void Run_315()
	{
		state=true;
		current_angle=315;
		OPORTE_ON;
		OPORT1_ON;
		OPORT2_OFF;
		OPORT3_OFF;
		OPORT4_OFF;
	}
		public:		
		void Stop()
		{
			state=false;
			OPORTE_OFF;
			OPORT1_OFF;
			OPORT2_OFF;
			OPORT3_OFF;
			OPORT4_OFF;
		}
		void operator + () //текущая позиция
		{
			if (position<3)
			position++;			
		}
		void operator - () //текущая позиция
		{	
			if (position>0)
			position--;	
		}
		void operator ++ ()//прокрутить двигатель дальше на 45
		{
			if (position<3)
			{
			
			switch (current_angle)
			{
				case 0:
				Run_45();
				break;
				case 45:
				Run_90();
				break;
				case 90:
				Run_135();
				break;
				case 135:
				Run_180();
				break;
				case 180:
				Run_225();
				break;
				case 225:
				Run_270();
				break;
				case 270:
				Run_315();
				break;
				case 315:
				Run_0();
				break;				
			}
			}			
			
		}
		void operator --() //прокрутить двигатель дальше на 45
		{
			if(position>0)
			{
			switch (current_angle)
			{
				case 0:
				Run_315();
				break;
				case 45:
				Run_0();
				break;
				case 90:
				Run_45();
				break;
				case 135:
				Run_90();
				break;
				case 180:
				Run_135();
				break;
				case 225:
				Run_180();
				break;
				case 270:
				Run_225();
				break;
				case 315:
				Run_270();
				break;
			}
			}			
		}

	
};




#endif /* CLASSCODE_H_ */