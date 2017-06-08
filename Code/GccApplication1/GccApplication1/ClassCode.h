/*
 * ClassCode.h
 *
 * Created: 08.06.2017 19:46:49
 *  Author: Rustam
 */ 


#ifndef CLASSCODE_H_
#define CLASSCODE_H_

class Properties
{	
	public:
	char state,	//0-free,1-busy
	dirrect,	//0-clockwise,1-counter-clockwise
	location;	//0-middle,1-bottom,2-top
	//int time_from_start;
};

class MotorDC : public Properties
{
	public:
	void Stop()
	{
		O_ROT1_OFF;
		O_ROT2_OFF;
		state=0;
	}
	void Run_Forward()
	{
		state=1;
		dirrect=0;
		O_ROT2_OFF;
		O_ROT1_ON;
		location=0;
	}
	void Run_Backward()
	{
		state=1;
		dirrect=1;
		O_ROT1_OFF;
		O_ROT2_ON;
		location=0;
	}
	
} Motor;


class MotorStep : public Properties
{
	public:
	int current_angle;
		
	protected:
	int current_step,need_step,need_angle;
	
	public:
	void Stop()
	{
	}		
	
	
}MotorStep;




#endif /* CLASSCODE_H_ */