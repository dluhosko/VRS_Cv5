/*
 * VRS_Cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Viktor
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_


void adc_init(void);
void NVIC_init(void);
void USART_init(void);
void sendDATA (char *text);
void dajDokopy(int val);
#endif /* VRS_CV5_H_ */
