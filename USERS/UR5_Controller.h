/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UR5_CONTROLLER_H__
#define __UR5_CONTROLLER_H__
/* =================================================================================
File name:       __UR5_CONTROLLER_H__

===================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Robotics.h"

#define L_1 0.425
#define L_2 0.3922
#define W_1 0.1333
#define W_2 0.0996
#define H_1 0.1625
#define H_2 0.0997

extern Robotics* UR5_Robot;

void UR5_Robot_init(void);

#endif