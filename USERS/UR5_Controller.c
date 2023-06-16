#include "UR5_Controller.h"

Robotics* UR5_Robot;


void UR5_Robot_init(void)
{
	uint8_t axes[6] = {2, 1, 1, 1, 2, 1};
	float positions_f32[6*3] = {
			0,						0,		H_1				,
			0,						0,		H_1				,
			L_1,					0,		H_1				,
			L_1 + L_2,		0,		H_1				,
			L_1 + L_2,		W_1,	H_1				,
			L_1 + L_2,		W_1,	H_1 - H_2	
		};
	float EPM_i_f32[16] = 
					{ -1, 0, 0, L_1 + L_2,
						 0, 0, 1, W_1 + W_2 ,
						 0, 1, 0, H_1 - H_2 ,
						 0, 0, 0, 1  };
	q15_t positions_q15[6*3] = {0};
	q15_t EPM_i_q15[16] = {0};
	
	arm_float_to_q15(positions_f32, positions_q15, 6*3);
	arm_float_to_q15(EPM_i_f32, EPM_i_q15, 16);
	
	UR5_Robot = new_Robotics();
	UR5_Robot->init(UR5_Robot, axes, positions_q15, EPM_i_q15);
}
