#include "Robotics.h"

Robotics* new_Robotics(void)
{
	uint8_t i = 0;
	Robotics* pObj = NULL;
	pObj = (Robotics*)malloc(sizeof(Robotics));
	if (pObj == NULL)
	{
		printf("WARN: Robotics initialization failed.\r\n");
		return NULL;
	}
	
	pObj->init = Robotics_init;
	pObj->calc = Robotics_calc;
	pObj->print = Robotics_print;
	
	pObj->EPM_i = new_mat_q15(4, 4);
	pObj->EPM_f = new_mat_q15(4, 4);
	pObj->Temp_Mat = new_mat_q15(4, 4);
	
	for(i = 0; i<NoL; i++)
		pObj->UR5_POE[i] = new_POE_Formula();
	printf("INFO: Robotics initialization succeeded.\r\n");
	return pObj;
}

void Robotics_init(Robotics* const pRBTObj, uint8_t* axes, q15_t* positions, q15_t* EPM_i)
{
	uint8_t i = 0;
	for(i = 0; i<NoL; i++)
		pRBTObj->UR5_POE[i]->init(pRBTObj->UR5_POE[i], axes[i], positions + i*3);
	
	memcpy(pRBTObj->EPM_i->pData, EPM_i, 16*sizeof(q15_t));
	
}

void Robotics_calc(Robotics* const pRBTObj, q15_t* theta)
{
	uint8_t i = 0;
	q15_t pState[16] = {0};
	
	memcpy(pRBTObj->EPM_f->pData, pRBTObj->EPM_i->pData, 16 * sizeof(q15_t));
	for(i = 0; i<NoL; i++)
	{
		pRBTObj->UR5_POE[NoL-1-i]->calc(pRBTObj->UR5_POE[NoL-1-i], theta[NoL-1-i]);
		
		arm_mat_mult_q15(pRBTObj->UR5_POE[NoL-1-i]->POE_Mat, pRBTObj->EPM_f, pRBTObj->Temp_Mat, pState);
		memcpy(pRBTObj->EPM_f->pData, pRBTObj->Temp_Mat->pData, 16 * sizeof(q15_t));
	}
}

void Robotics_print(Robotics* const pRBTObj)
{
	uint16_t i, j = 0;
	printf("EPM_f:\r\n");
	for(i = 0; i<pRBTObj->EPM_f->numRows; i++)
	{
		for(j = 0; j<pRBTObj->EPM_f->numRows; j++)
			printf("%+.4f ", my_q15_to_float(mat_q15_get(pRBTObj->EPM_f, i, j)));
		printf("\r\n");
	}
}