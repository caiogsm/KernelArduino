#ifndef DISP7SEG_H
#define DISP7SEG_H

//#define CATODO_COMUM 1
#define ANODO_COMUM 

// Mapeamento de hardware
#define DISPLAY_1  8
#define DISPLAY_2  9
#define DISPLAY_3  10
#define DISPLAY_4  11

// Definições gerais
#if defined(CATODO_COMUM)
   #define LIGA 1
   #define DESLIGA 0
#else defined(ANODO_COMUM)
   #define LIGA 0
   #define DESLIGA 1
#endif

// Valores para a multriplexação do display
#define ESCREVE_DISPLAY_1  1
#define ESCREVE_DISPLAY_2  2
#define ESCREVE_DISPLAY_3  3
#define ESCREVE_DISPLAY_4  4

// Protótipos de funções
void vDisp7SegInit(void);
unsigned char ucObtemValorDisplay(int16_t valor, char disp);
void vEscreveNoDisplay(unsigned char valor, char disp);

#endif
