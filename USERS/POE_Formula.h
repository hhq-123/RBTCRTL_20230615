/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POE_FORMULA_H__
#define __POE_FORMULA_H__
/* =================================================================================
File name:       __POE_Formula_H__

===================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MyMaths.h"

typedef struct POE_Formula_ POE_Formula;

typedef void (*POEFfptrInit)(POE_Formula*, q15_t, q15_t*);
typedef void (*POEFfptrCalc)(POE_Formula*, q15_t);
typedef void (*POEFfptrSet)(POE_Formula*, q15_t);

struct POE_Formula_
{
	q15_t theta;
	
	uint8_t axis;//0:x, 1:y, 2:z, 
	
	q15_t pos[3];
	
	arm_matrix_instance_q15* POE_Mat;
	
	//interface for function
	POEFfptrInit init;
	POEFfptrCalc calc;
};
 
POE_Formula* new_POE_Formula(void);
void delete_POE_Formula(POE_Formula* const pPOEFObj);


void POE_Formula_init(POE_Formula* const pPOEFObj, q15_t axis, q15_t* pos);
void POE_Formula_calc(POE_Formula* const pPOEFObj, q15_t theta);
void mat_q15_print(arm_matrix_instance_q15* const pMatObj);

#endif