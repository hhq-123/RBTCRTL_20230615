#include "MyMaths.h"

/* includes ------------------------------------------------------------------*/

/* typedef -------------------------------------------------------------------*/
/* define --------------------------------------------------------------------*/
/* variables -----------------------------------------------------------------*/

/* 取0~90度的结果，其他角度可以通过对称性和周期性推算出 */

arm_matrix_instance_q15* new_mat_q15(uint16_t nRows, uint16_t nColumns)
{
	arm_matrix_instance_q15* pObj = NULL;
	q15_t* pData = NULL;
	
	pObj = (arm_matrix_instance_q15*)malloc(sizeof(arm_matrix_instance_q15));
	pData = (q15_t*)malloc(sizeof(q15_t)* nRows * nColumns);
	memset(pData, 0, sizeof(q15_t)* nRows * nColumns);
	
	if (pObj == NULL)
	{
		printf("WARN: Matrix memory allocation failed.(pObj)\r\n");
		return NULL;
	}

	if (pData == NULL)
	{
		printf("WARN: Matrix memory allocation failed.(pData)\r\n");
		return NULL;
	}
	
	arm_mat_init_q15(pObj, nRows, nColumns, pData);
	printf("INFO: Matrix memory allocation succeeded.\r\n");
	return pObj;
}

void delete_mat_q15(arm_matrix_instance_q15* const pMatObj)
{

}

void mat_q15_set(arm_matrix_instance_q15* const pMatObj, uint16_t nRows, uint16_t nColumns, q15_t value)
{
	pMatObj->pData[nRows * pMatObj->numCols + nColumns] = value;
}

q15_t mat_q15_get(arm_matrix_instance_q15* const pMatObj, uint16_t nRows, uint16_t nColumns)
{
	return pMatObj->pData[nRows * pMatObj->numCols + nColumns];
}

void mat_q15_print(arm_matrix_instance_q15* const pMatObj)
{
	uint16_t i, j = 0;
	for(i = 0; i<pMatObj->numRows; i++)
	{
		for(j = 0; j<pMatObj->numRows; j++)
			printf("%+.4f ", my_q15_to_float(mat_q15_get(pMatObj, i, j)));
		printf("\r\n");
	}
}

q15_t my_float_to_q15(float Src)
{
	q15_t temp;
	arm_float_to_q15(&Src, &temp, 1);
	return temp;
}

float my_q15_to_float(q15_t Src)
{
	float temp;
	arm_q15_to_float(&Src, &temp, 1);
	return temp;
}
