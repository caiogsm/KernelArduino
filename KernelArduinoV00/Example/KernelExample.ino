/* 1) Documentação
 *   
 *    @ESTUDO_RTOS_01.ino
 *    
 *    Este código utiliza o kernel desenvolvido para gerenciar três tarefas:
 *       vDisp7SegTask(): executa um contador de 500ms num display de 7 segmentos. Roda a cada 5ms para
 *                        multiplexar os quatro diplays
 *       vTecladoTask(): faz a leitura de dois pushbuttons. Cada um deles é responsável por
 *                       modificar o sentido da contagem dos contadores.
 *       vDispLcdTask(): roda um contador de 1s num display lcd 16x2
 *    
 *    Autor: Caio Moraes
 *    Data: março/2017
 */
//---------------------------------------------------------------------------------------------------------------------
// 2) Diretivas do Pre-processador

#include <LiquidCrystal.h>
#include "kernel.h"
#include "disp7seg.h"

#define LED1 13
#define BOTAO1 2
#define BOTAO2 3
#define TASK1_PERIOD 5       // 200ms
#define TASK2_PERIOD 25      // 500ms
#define TASK3_PERIOD 1000    // 1000ms

#define TIME_INTERVAL 500

#define SIM 1
#define NAO 0

//---------------------------------------------------------------------------------------------------------------------
// 3) Declarações Globais
boolean botao1FoiPressionado, botao2FoiPressionado;

// Objeto para a biblioteca do display lcd
LiquidCrystal lcd(52,53,51,49,47,45);  // Criando um LCD de 16x2 

//---------------------------------------------------------------------------------------------------------------------
// 4) Protótipos de funções
void vDisp7SegTask();
void vDispLcdTask();
void vTecladoTask();
//---------------------------------------------------------------------------------------------------------------------

// 5) Subrotinas
void setup() 
{
  // Inicializaçãos dos pinos IO
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  pinMode(BOTAO1, INPUT);
  pinMode(BOTAO2, INPUT);
  // Inicialização da Serial
  Serial.begin(9600);
  
  // Inicialização do módulo I2C para LCD
  lcd.begin(16,2); // Inicializando o LCD 16x2
  lcd.clear();     // Limpa o LCD
 
  vDisp7SegInit();

  botao1FoiPressionado = NAO;
  botao2FoiPressionado = NAO;

  TaskHandle task1; 
  TaskHandle task2;
  TaskHandle task3;
  
  KernelInit();                 // Inicializa o kernel
  // Adicionando as tarefas
  KernelAddTask(vDisp7SegTask,  // Função correspondente a tarefa 
                NULL,           // Nome da tarefa (opcional)
                TASK1_PERIOD,   // Periodo da tarefa
                SIM,            // Tarefa habilitada 
                &task1);        // Estrutura da tarefa
  KernelAddTask(vTecladoTask, NULL, TASK2_PERIOD, SIM, &task2);
  KernelAddTask(vDispLcdTask, NULL, TASK3_PERIOD, SIM, &task3);
  KernelStart();                // Executa o kernel
}

void loop() 
{}

//---------------------------------------------------------------------------------------------------------------------
// vDispLcdTask(): escreve no display LCD o valor de um contador sempre que é executada
//---------------------------------------------------------------------------------------------------------------------
void vDisp7SegTask()
{
  static char disp = 1;
  static uint32_t previousCounter = 0;
  static int16_t valor = 0;
  unsigned char digito;

  if((sysTickCounter - previousCounter) > TIME_INTERVAL)
  {
    previousCounter = sysTickCounter;  // Salva o tempo atual

    // Muda o sentido da contagem 
    if(botao2FoiPressionado == SIM) valor--;
    else valor++;
    // Saturação da contagem
    if(valor < 0) valor = 9999;
    if(valor > 9999) valor = 0;
    //Serial.println(valor);
  }
  if(disp > 4) disp = 1; 

  digito = ucObtemValorDisplay(valor, disp);
  vEscreveNoDisplay(digito, disp);
  
  disp++;
}

//---------------------------------------------------------------------------------------------------------------------
// vDispLcdTask(): escreve no display LCD o valor de um contador sempre que é executada
//---------------------------------------------------------------------------------------------------------------------
void vDispLcdTask(void)
{
  static int count = 0;

  if(botao1FoiPressionado == SIM) count--;
  else count++;

  if(count<0) count = 10000;
  if(count > 10000) count = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RTOS STUDY");
  lcd.setCursor(0,1);
  lcd.print(count);
  
}//end Task2

//---------------------------------------------------------------------------------------------------------------------
// vDispLcdTask(): escreve no display LCD o valor de um contador sempre que é executada
//---------------------------------------------------------------------------------------------------------------------
void vTecladoTask(void)
{
  static char flagBotao1 = 0, flagBotao2 = 0;
  
  if(digitalRead(BOTAO1)) flagBotao1 = 1;
  if(!digitalRead(BOTAO1) && flagBotao1){
    botao1FoiPressionado ^= SIM;
    flagBotao1 = 0;
  }

  if(digitalRead(BOTAO2)) flagBotao2 = 2;
  if(!digitalRead(BOTAO2) && flagBotao2){ 
    botao2FoiPressionado ^= SIM;
    flagBotao2 = 0;
  }

}

