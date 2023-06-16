#include "POE_Formula.h"

POE_Formula* new_POE_Formula(void)
{
	POE_Formula* pObj = NULL;
	pObj = (POE_Formula*)malloc(sizeof(POE_Formula));
	if (pObj == NULL)
	{
		printf("WARN: POE_Formula initialization failed.\r\n");
		return NULL;
	}
	
	pObj->init = POE_Formula_init;
	pObj->calc = POE_Formula_calc;
	
	pObj->POE_Mat = new_mat_q15(4, 4);
	
	printf("INFO: POE_Formula initialization succeeded.\r\n");
	
	return pObj;
}

void delete_POE_Formula(POE_Formula* const pPOEFObj)
{
	
}

void POE_Formula_init(POE_Formula* const pPOEFObj, q15_t axis, q15_t* pos)
{
	q15_t pState[9];
	pPOEFObj->axis = axis;
	memcpy(pPOEFObj->pos, pos, 3*sizeof(q15_t));
	memset(pPOEFObj->POE_Mat->pData, 0, 16*sizeof(q15_t));
}

void POE_Formula_calc(POE_Formula* const pPOEFObj, q15_t theta)
{
	pPOEFObj->theta = theta;

	q15_t temp_sin, temp_cos = 0;
	temp_cos = arm_cos_q15(theta);
	temp_sin = arm_sin_q15(theta);
	
	mat_q15_set(pPOEFObj->POE_Mat, pPOEFObj->axis % 3, pPOEFObj->axis % 3, 0x7fff);
	mat_q15_set(pPOEFObj->POE_Mat, (pPOEFObj->axis + 1) % 3, (pPOEFObj->axis + 1) % 3, temp_cos);
	mat_q15_set(pPOEFObj->POE_Mat, (pPOEFObj->axis + 2) % 3, (pPOEFObj->axis + 2) % 3, temp_cos);
	mat_q15_set(pPOEFObj->POE_Mat, (pPOEFObj->axis + 1) % 3, (pPOEFObj->axis + 2) % 3, -temp_sin);
	mat_q15_set(pPOEFObj->POE_Mat, (pPOEFObj->axis + 2) % 3, (pPOEFObj->axis + 1) % 3, temp_sin);
	
	mat_q15_set(pPOEFObj->POE_Mat, 0, 3, 
		pPOEFObj->pos[0]
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 0, 0)) * pPOEFObj->pos[0])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 0, 1)) * pPOEFObj->pos[1])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 0, 2)) * pPOEFObj->pos[2])>>15)
		);
	mat_q15_set(pPOEFObj->POE_Mat, 1, 3, 
		pPOEFObj->pos[1]
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 1, 0)) * pPOEFObj->pos[0])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 1, 1)) * pPOEFObj->pos[1])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 1, 2)) * pPOEFObj->pos[2])>>15)
		);
	mat_q15_set(pPOEFObj->POE_Mat, 2, 3, 
		pPOEFObj->pos[2]
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 2, 0)) * pPOEFObj->pos[0])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 2, 1)) * pPOEFObj->pos[1])>>15)
		-(q15_t)((((q31_t)mat_q15_get(pPOEFObj->POE_Mat, 2, 2)) * pPOEFObj->pos[2])>>15)
		);

	mat_q15_set(pPOEFObj->POE_Mat, 3, 3, 0x7fff);

	return;
}
