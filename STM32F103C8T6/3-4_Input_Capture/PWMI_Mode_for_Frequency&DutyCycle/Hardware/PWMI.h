#ifndef _PWMI_H
#define _PWMI_H

void PWMI_Init(void);
uint32_t PWMI_GetFreq(void);
uint32_t PWMI_GetDuty(void);

#endif