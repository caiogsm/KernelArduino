
#include "disp7seg.h"

unsigned char ucDisplay(char num);

// Função vDisp7SegInit(): Inicializa os pinos utilizados para o controle do display
// Parâmetros: nenhum
// Saída: nenhuma
void vDisp7SegInit()
{
  // Configura os pinos de controle dos displays 7 segmentos com saída digital
  pinMode(DISPLAY_1, OUTPUT);
  pinMode(DISPLAY_2, OUTPUT);
  pinMode(DISPLAY_3, OUTPUT);
  pinMode(DISPLAY_4, OUTPUT);

  DDRA = 0xFF;    // Todos os pinos do PORTA como saída
  PORTA = 0xFF;   // Inicializa todos os pinos do PORTA em nível alto
}

// Função ucDisplay(): Encontra o códico correspondente ao digito a ser enviado para o Display
// Parâmetros: Digito a ser enviado para o Display
// Saída: Código correspondente ao digito desejado em hexadecimal
unsigned char ucDisplay(char num)
{
  // o vetor segmentos representa em hexadecimal os digitos de 0 a 9 correspondentes ao Display de 7 segmentos
  unsigned char segmentos[] = {0x3F,     // 0
                               0x06,     // 1
                               0x5B,     // 2
                               0x4F,     // 3
                               0x66,     // 4
                               0x6D,     // 5
                               0x7D,     // 6
                               0x07,     // 7
                               0x7F,     // 8
                               0x67      // 9
                              };

// No caso dos displays andodo comum, o valor é retornado com negação
#if defined(CATODO_COMUM) 
   return segmentos[num];
#elif defined(ANODO_COMUM)
   return ~segmentos[num];
#endif

}//end Display

// Função ucObtemValorDisplay(): Calcula o digito a ser mostrado em cada display
// Parâmetros: Valor inteiro a ser mostrado; qual dos 4 displays
// Saída: digito a ser enviado para o display
unsigned char ucObtemValorDisplay(int16_t valor, char disp)
{
  unsigned char digito;
  
  switch(disp)
  {
    case 1: digito = valor / 1000; break;
    case 2: digito = (valor % 1000) / 100; break;
    case 3: digito = (valor % 100) / 10; break;
    case 4: digito = valor % 10; break;
  }
  return digito;
}//end ucObtemValorDisplay

// Função vEscreveNoDisplay(): Faz a multiplexação dos displays
// Parâmetros: Valor a ser mostrado, e qual display
// Saída: Nenhuma
void vEscreveNoDisplay(unsigned char valor, char disp)
{
  // Maquina de Estados para a atualização do Display
  switch (disp)
  {
    case ESCREVE_DISPLAY_1:
      {
        digitalWrite(DISPLAY_1, LIGA);
        digitalWrite(DISPLAY_2, DESLIGA);
        digitalWrite(DISPLAY_3, DESLIGA);
        digitalWrite(DISPLAY_4, DESLIGA);
        PORTA = ucDisplay(valor);
        break;
      }
    case ESCREVE_DISPLAY_2:
      {
        digitalWrite(DISPLAY_1, DESLIGA);
        digitalWrite(DISPLAY_2, LIGA);
        digitalWrite(DISPLAY_3, DESLIGA);
        digitalWrite(DISPLAY_4, DESLIGA);
        PORTA = ucDisplay(valor);
        break;
      }
    case ESCREVE_DISPLAY_3:
      {
        digitalWrite(DISPLAY_1, DESLIGA);
        digitalWrite(DISPLAY_2, DESLIGA);
        digitalWrite(DISPLAY_3, LIGA);
        digitalWrite(DISPLAY_4, DESLIGA);
        PORTA = ucDisplay(valor);
        break;
      }
    case ESCREVE_DISPLAY_4:
      {
        digitalWrite(DISPLAY_1, DESLIGA);
        digitalWrite(DISPLAY_2, DESLIGA);
        digitalWrite(DISPLAY_3, DESLIGA);
        digitalWrite(DISPLAY_4, LIGA);
        PORTA = ucDisplay(valor);
        break;
      }
  }
}//end EscreveNoDisplay




