#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>

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
// LED de alarma
// *******************************************************************************************

#define LED_ALARMA 23

// *******************************************************************************************
// Botones
// *******************************************************************************************

#define B1 18
#define B2 19

// *******************************************************************************************
// PROTOTIPOS DE FUNCIONES
// *******************************************************************************************

void configInterrupts(void);
void configTimer(void);

void mostrarContadorManual(void);
void mostrarContadorAutomatico(void);
void compararContadores(void);

void IRAM_ATTR B1_ISR();
void IRAM_ATTR B2_ISR();
void IRAM_ATTR Timer0_ISR();

// *******************************************************************************************
// VARIABLES GLOBALES
// *******************************************************************************************

hw_timer_t *Timer0_cfg = NULL;

// Contador manual
volatile int contadorManual = 0;

// Contador automático
volatile int contadorAutomatico = 0;

// Variables para detectar pulsaciones
volatile bool B1_presionado = false;
volatile bool B2_presionado = false;

// Variables para anti-rebote
unsigned long tiempoB1 = 0;
unsigned long tiempoB2 = 0;

const int antiRebote = 200;

// Variable de comparación
bool alarmaActivada = false;

// *******************************************************************************************
// CONFIGURACIÓN
// *******************************************************************************************

void setup()
{
  // LEDs contador manual

  pinMode(LED_M0, OUTPUT);
  pinMode(LED_M1, OUTPUT);
  pinMode(LED_M2, OUTPUT);
  pinMode(LED_M3, OUTPUT);

  digitalWrite(LED_M0, LOW);
  digitalWrite(LED_M1, LOW);
  digitalWrite(LED_M2, LOW);
  digitalWrite(LED_M3, LOW);

  // LEDs contador automático

  pinMode(LED_A0, OUTPUT);
  pinMode(LED_A1, OUTPUT);
  pinMode(LED_A2, OUTPUT);
  pinMode(LED_A3, OUTPUT);

  digitalWrite(LED_A0, LOW);
  digitalWrite(LED_A1, LOW);
  digitalWrite(LED_A2, LOW);
  digitalWrite(LED_A3, LOW);

  // LED alarma

  pinMode(LED_ALARMA, OUTPUT);
  digitalWrite(LED_ALARMA, LOW);

  // Botones

  pinMode(B1, INPUT_PULLDOWN);
  pinMode(B2, INPUT_PULLDOWN);

  configInterrupts();

  configTimer();
}

// *******************************************************************************************
// LOOP
// *******************************************************************************************

void loop()
{
  // ******************************
  // Incrementar contador manual
  // ******************************

  if (B1_presionado)
  {
    if (millis() - tiempoB1 > antiRebote)
    {
      contadorManual++;

      if (contadorManual > 15)
      {
        contadorManual = 0;
      }

      tiempoB1 = millis();
    }

    B1_presionado = false;
  }

  // ******************************
  // Decrementar contador manual
  // ******************************

  if (B2_presionado)
  {
    if (millis() - tiempoB2 > antiRebote)
    {
      contadorManual--;

      if (contadorManual < 0)
      {
        contadorManual = 15;
      }

      tiempoB2 = millis();
    }

    B2_presionado = false;
  }

  mostrarContadorManual();

  mostrarContadorAutomatico();

  compararContadores();
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
  B1_presionado = true;
}

// *******************************************************************************************
// ISR BOTÓN B2
// *******************************************************************************************

void IRAM_ATTR B2_ISR()
{
  B2_presionado = true;
}

// *******************************************************************************************
// ISR DEL TIMER
// *******************************************************************************************

void IRAM_ATTR Timer0_ISR()
{
  contadorAutomatico++;

  if (contadorAutomatico > 15)
  {
    contadorAutomatico = 0;
  }
}

// *******************************************************************************************
// COMPARADOR Y ALARMA
// *******************************************************************************************

void compararContadores()
{
  if (contadorManual == contadorAutomatico)
  {
    if (alarmaActivada == false)
    {
      digitalWrite(LED_ALARMA, !digitalRead(LED_ALARMA));

      contadorAutomatico = 0;

      alarmaActivada = true;
    }
  }
  else
  {
    alarmaActivada = false;
  }
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

// *******************************************************************************************
// CONFIGURACIÓN DEL TEMPORIZADOR
// *******************************************************************************************

void configTimer(void)
{
  // Timer 0, prescaler 80, conteo ascendente
  Timer0_cfg = timerBegin(0, 80, true);

  // Asociar la interrupción del timer
  timerAttachInterrupt(Timer0_cfg, &Timer0_ISR, true);

  // Activar alarma cada 250000 microsegundos
  timerAlarmWrite(Timer0_cfg, alarma, true);

  // Iniciar la alarma
  timerAlarmEnable(Timer0_cfg);
}