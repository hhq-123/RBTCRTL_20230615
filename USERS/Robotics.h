/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ROBOTICS_H__
#define __ROBOTICS_H__
/* =================================================================================
File name:       __ROBOTICS_H__

===================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "POE_Formula.h"

#define NoL 6

typedef struct Robotics_ Robotics;

typedef void (*RBTfptrInit)(Robotics*, uint8_t*, q15_t*, q15_t*);
typedef void (*RBTfptrCalc)(Robotics*, q15_t*);
typedef void (*RBTfptrPrint)(Robotics*);

struct Robotics_
{
	
	POE_Formula* UR5_POE[NoL];
	
	arm_matrix_instance_q15* EPM_i;
	arm_matrix_instance_q15* EPM_f;
	arm_matrix_instance_q15* Temp_Mat;

	//interface for function
	RBTfptrInit init;
	RBTfptrCalc calc;
	RBTfptrPrint print;
};
 
Robotics* new_Robotics(void);
void delete_Robotics(Robotics* const pRBTObj);

void Robotics_init(Robotics* const pRBTObj, uint8_t* axes, q15_t* positions, q15_t* EPM);
void Robotics_calc(Robotics* const pRBTObj, q15_t* theta);
void Robotics_print(Robotics* const pRBTObj);

#endif