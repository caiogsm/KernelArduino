/*
 * @kernel.h
 * 
 * Header file: contem todas as macros, variáveis globais e protótipos de funções
 *              utilizados pelo kernel
 * 
 * Autor: Caio Moraes
 * Data: março/2017
 * Versão: V01
 */
 
#ifndef KERNEL_H
#define KERNEL_H

#include <TimerOne.h>   // Inclui a biblioteca do timer 1

// Definições para as tarefas
#define NUMBER_OF_TASKS  3
#define TEMPO_MAXIMO_EXECUCAO 100   // 100ms

// Definições gerais
#define SUCCESS 1
#define FAIL    0

//---------------------------------------------------------------------------------------------------------------
// Variáveis do Kernel
//---------------------------------------------------------------------------------------------------------------
typedef void(*ptrFunc)();  // Definição ponteiro de função

// Definição da estrutura que contem as informações das tarefas
typedef struct{
  ptrFunc Function;
  unsigned char *taskName;
  uint32_t period;
  bool enableTask; 
}TaskHandle;

// Definição do buffer para armazenar as tarefas
TaskHandle* buffer[NUMBER_OF_TASKS]; 

// Variáveis globais do kernel
volatile uint32_t taskCounter[NUMBER_OF_TASKS];
volatile int16_t TempoEmExecucao;
volatile uint32_t sysTickCounter = 0;
volatile bool TemporizadorEstourou;
volatile bool TarefaSendoExecutada;

//---------------------------------------------------------------------------------------------------------------
// Protótipos de funções do Kernel
//---------------------------------------------------------------------------------------------------------------
char KernelInit(void);
char KernelAddTask(ptrFunc _function, unsigned char _nameFunction, uint16_t _period, char _enableTask, TaskHandle* task); 
char KernelRemoveTask(TaskHandle* task);
void KernelStart(void);

#endif
