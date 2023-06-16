/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYMATHS_H
#define __MYMATHS_H

#ifdef __cplusplus
extern "C" {
#endif

#define M_2_PI 		6.28318530718
#define M_PI 		3.14159265359
#define M_PI_2 	1.57079632679
#define M_PI_4	0.785398163397

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "arm_math.h"

arm_matrix_instance_q15* new_mat_q15(uint16_t nRows, uint16_t nColumns);
void delete_mat_q15(arm_matrix_instance_q15* const pMatObj);


void mat_q15_set(arm_matrix_instance_q15* const pMatObj, uint16_t nRows, uint16_t nColumns, q15_t value);
q15_t mat_q15_get(arm_matrix_instance_q15* const pMatObj, uint16_t nRows, uint16_t nColumns);
void mat_q15_print(arm_matrix_instance_q15* const pMatObj);

q15_t my_float_to_q15(float Src);
float my_q15_to_float(q15_t Src);


#endif