#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>

/* Lab 2 Camila Aristizabal */
// *******************************************************************************************
// LEDs contador manual
// *******************************************************************************************

#define LED_M0 32
#define LED_M1 33
#define LED_M2 25
#define LED_M3 26

// *******************************************************************************************
// Botones
// *******************************************************************************************

#define B1 34
#define B2 35

// *******************************************************************************************
// PROTOTIPOS DE FUNCIONES
// *******************************************************************************************

void configInterrupts(void);
void mostrarContadorManual(void);
void IRAM_ATTR B1_ISR();
void IRAM_ATTR B2_ISR();

// *******************************************************************************************
// VARIABLES GLOBALES
// *******************************************************************************************

// Contador manual de 0 a 15
volatile int contadorManual = 0;

// Variables para anti-rebote
volatile unsigned long ultimoTiempoB1 = 0;
volatile unsigned long ultimoTiempoB2 = 0;

const int antiRebote = 200;

// *******************************************************************************************
// CONFIGURACIÓN
// *******************************************************************************************

void setup()
{
  // Configurar los LEDs como salidas
  pinMode(LED_M0, OUTPUT);
  pinMode(LED_M1, OUTPUT);
  pinMode(LED_M2, OUTPUT);
  pinMode(LED_M3, OUTPUT);

  // Apagar todos los LEDs al inicio
  digitalWrite(LED_M0, LOW);
  digitalWrite(LED_M1, LOW);
  digitalWrite(LED_M2, LOW);
  digitalWrite(LED_M3, LOW);

  // Configurar botones
  pinMode(B1, INPUT_PULLDOWN);
  pinMode(B2, INPUT_PULLDOWN);

  // Configurar interrupciones
  configInterrupts();
}

// *******************************************************************************************
// LOOP
// *******************************************************************************************

void loop()
{
  mostrarContadorManual();
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
// ISR BOTÓN B1 (INCREMENTAR)
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
// ISR BOTÓN B2 (DECREMENTAR)
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
// FUNCIÓN PARA MOSTRAR EL CONTADOR EN LOS LEDs
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