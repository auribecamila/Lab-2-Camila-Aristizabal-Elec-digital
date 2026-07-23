#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>

/* Lab 2 Camila Aristizabal */

// *******************************************************************************************
// LEDs contador manual
// *******************************************************************************************
// 250 ms = 250000 microsegundos
// *******************************************************************************************

#define alarma 250000

// *******************************************************************************************
// LEDs contador manual
// *******************************************************************************************

#define LED_M0 32
#define LED_M1 33
#define LED_M2 25
#define LED_M3 26

// *******************************************************************************************
// LEDs contador automático
// *******************************************************************************************

#define LED_A0 27
#define LED_A1 14
#define LED_A2 12
#define LED_A3 13

// *******************************************************************************************
// Botones
// *******************************************************************************************

#define B1 34
#define B2 35

// *******************************************************************************************
// PROTOTIPOS DE FUNCIONES
// *******************************************************************************************

void configInterrupts(void);
void configTimer(void);

void mostrarContadorManual(void);
void mostrarContadorAutomatico(void);

void IRAM_ATTR B1_ISR();
void IRAM_ATTR B2_ISR();
void IRAM_ATTR Timer0_ISR();

// *******************************************************************************************
// VARIABLES GLOBALES
// *******************************************************************************************

// Configuración del timer
hw_timer_t *Timer0_cfg = NULL;

// Contador manual
volatile int contadorManual = 0;

// Contador automático
volatile int contadorAutomatico = 0;

// Variables para anti-rebote
volatile unsigned long ultimoTiempoB1 = 0;
volatile unsigned long ultimoTiempoB2 = 0;

const int antiRebote = 200;

// *******************************************************************************************
// CONFIGURACIÓN
// *******************************************************************************************

void setup()
{
  // ******************************
  // LEDs contador manual
  // ******************************

  pinMode(LED_M0, OUTPUT);
  pinMode(LED_M1, OUTPUT);
  pinMode(LED_M2, OUTPUT);
  pinMode(LED_M3, OUTPUT);

  digitalWrite(LED_M0, LOW);
  digitalWrite(LED_M1, LOW);
  digitalWrite(LED_M2, LOW);
  digitalWrite(LED_M3, LOW);

  // ******************************
  // LEDs contador automático
  // ******************************

  pinMode(LED_A0, OUTPUT);
  pinMode(LED_A1, OUTPUT);
  pinMode(LED_A2, OUTPUT);
  pinMode(LED_A3, OUTPUT);

  digitalWrite(LED_A0, LOW);
  digitalWrite(LED_A1, LOW);
  digitalWrite(LED_A2, LOW);
  digitalWrite(LED_A3, LOW);

  // ******************************
  // Botones
  // ******************************

  pinMode(B1, INPUT_PULLDOWN);
  pinMode(B2, INPUT_PULLDOWN);

  // Configurar interrupciones
  configInterrupts();

  // Configurar temporizador
  configTimer();
}

// *******************************************************************************************
// LOOP
// *******************************************************************************************

void loop()
{
  mostrarContadorManual();

  mostrarContadorAutomatico();
}

// *******************************************************************************************
// CONFIGURACIÓN DE INTERRUPCIONES
// *******************************************************************************************

void configInterrupts(void)
{
  attachInterrupt(B1, B1_ISR, RISING);

  attachInterrupt(B2, B2_ISR, RISING);
}

// *******************************************************************************************
// ISR BOTÓN B1
// *******************************************************************************************

void IRAM_ATTR B1_ISR()
{
  if (millis() - ultimoTiempoB1 > antiRebote)
  {
    contadorManual++;

    // Contador circular
    if (contadorManual > 15)
    {
      contadorManual = 0;
    }

    ultimoTiempoB1 = millis();
  }
}

// *******************************************************************************************
// ISR BOTÓN B2
// *******************************************************************************************

void IRAM_ATTR B2_ISR()
{
  if (millis() - ultimoTiempoB2 > antiRebote)
  {
    contadorManual--;

    // Contador circular
    if (contadorManual < 0)
    {
      contadorManual = 15;
    }

    ultimoTiempoB2 = millis();
  }
}

// *******************************************************************************************
// ISR DEL TEMPORIZADOR
// *******************************************************************************************

void IRAM_ATTR Timer0_ISR()
{
  contadorAutomatico++;

  // Contador circular
  if (contadorAutomatico > 15)
  {
    contadorAutomatico = 0;
  }
}

// *******************************************************************************************
// CONFIGURACIÓN DEL TEMPORIZADOR
// *******************************************************************************************

void configTimer(void)
{
  // Timer 0, prescaler 80, conteo ascendente
  Timer0_cfg = timerBegin(0, 80, true);

  // Asociar la interrupción del timer
  timerAttachInterrupt(Timer0_cfg, &Timer0_ISR, true);

  // Activar alarma cada 250 ms
  timerAlarmWrite(Timer0_cfg, alarma, true);

  // Iniciar el timer
  timerAlarmEnable(Timer0_cfg);
}
// *******************************************************************************************
// FUNCIÓN PARA MOSTRAR EL CONTADOR MANUAL
// *******************************************************************************************

void mostrarContadorManual()
{
  if (contadorManual == 0)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 1)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 2)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 3)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 4)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 5)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 6)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 7)
  {
    digitalWrite(LED_M3, LOW);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 8)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 9)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 10)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 11)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, LOW);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 12)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 13)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, LOW);
    digitalWrite(LED_M0, HIGH);
  }

  else if (contadorManual == 14)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, LOW);
  }

  else if (contadorManual == 15)
  {
    digitalWrite(LED_M3, HIGH);
    digitalWrite(LED_M2, HIGH);
    digitalWrite(LED_M1, HIGH);
    digitalWrite(LED_M0, HIGH);
  }
}

// *******************************************************************************************
// FUNCIÓN PARA MOSTRAR EL CONTADOR AUTOMÁTICO
// *******************************************************************************************

void mostrarContadorAutomatico()
{
  if (contadorAutomatico == 0)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 1)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 2)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 3)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 4)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 5)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 6)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 7)
  {
    digitalWrite(LED_A3, LOW);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 8)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 9)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 10)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 11)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, LOW);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 12)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 13)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, LOW);
    digitalWrite(LED_A0, HIGH);
  }

  else if (contadorAutomatico == 14)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, LOW);
  }

  else if (contadorAutomatico == 15)
  {
    digitalWrite(LED_A3, HIGH);
    digitalWrite(LED_A2, HIGH);
    digitalWrite(LED_A1, HIGH);
    digitalWrite(LED_A0, HIGH);
  }
}