

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

#define SYSTEM_STATUS_NORMAL 0
#define SYSTEM_STATUS_PWM_ERROR 1

const uint16_t SYSTICK_COUNTER_TO = 2000;

uint32_t systemClock;

uint8_t systemStatus;
uint32_t ledFreqDiv;

uint8_t ledCode[] = {0b11110000, 0b00101010};
uint8_t ledRotator;
uint32_t ui32Counter_0_125s;

void initVariables(uint32_t ui32SysClock){
    systemStatus = SYSTEM_STATUS_NORMAL;
    ledFreqDiv = 0;
    ledRotator = 0;
    ui32Counter_0_125s = ui32SysClock / (8 * SYSTICK_COUNTER_TO);
}

//função de atendimento à interrupção do SysTick
void intSysTick(void){
    ledFreqDiv++;
}

//configura o SysTick, para ter interrupção a cada clockNumber clocks
void configureSysTick(uint32_t clockNumber, void (*funPtr)(void)){
    SysTickPeriodSet(clockNumber);
    SysTickIntEnable();
    SysTickIntRegister(funPtr);
    SysTickEnable();
}

void configureGPIOs(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
}
/*
void flipGPIOBit(uint32_t port_base, uint8_t pins){
    uint8_t ui8Value = GPIOPinRead(port_base, pins);
    ui8Value = pins & (~ui8Value);
    GPIOPinWrite(port_base, pins, ui8Value);
}
*/
//void setupTimersPWM
//  Configura os timers para atuarem como PWM
//  TIMER0
//  A - PD0 - 2k
//  B - PD1 - 1,5K
//  TIMER1
//  A - PD2 - 1K
//  B - PD3 - 2,5K
void setupTimersPWM(uint32_t ui32SysClock){
    //pega clock do sistema
    //uint32_t ui32SysClock = SysCtlClockGet();
    uint32_t ui32FreqDiv2k = ui32SysClock / 2000;
    uint32_t ui32FreqDiv1_5k = ui32SysClock / 1500;
    uint32_t ui32FreqDiv1k = ui32SysClock / 1000;
    uint32_t ui32FreqDiv2_5k = ui32SysClock / 2500;

    if(ui32FreqDiv1k > 65535){
        systemStatus = SYSTEM_STATUS_PWM_ERROR;
    }

    //Iniciar periférico do TIMER0 e TIMER1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));

    //Iniciar a porta GPIO  associada ao Timer -> GPIO Port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

    //Associar o Pino da GPIO ao Timer e Configurar o Pino da GPIO como de timer
    //PD0 a PD3 como saídas
    GPIOPinConfigure(GPIO_PD0_T0CCP0);
    GPIOPinConfigure(GPIO_PD1_T0CCP1);
    GPIOPinConfigure(GPIO_PD2_T1CCP0);
    GPIOPinConfigure(GPIO_PD3_T1CCP1);
    GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);


    //Configurar TIMER0 e TIMER1 como PWM separado
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);

    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);

    //freq
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32FreqDiv2k);
    //duty_cycle
    TimerMatchSet(TIMER0_BASE, TIMER_A, ui32FreqDiv2k / 2);

    //freq
    TimerLoadSet(TIMER0_BASE, TIMER_B, ui32FreqDiv1_5k);
    //duty_cycle
    TimerMatchSet(TIMER0_BASE, TIMER_B, ui32FreqDiv1_5k / 2);

    //freq
    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32FreqDiv1k);
    //duty_cycle
    TimerMatchSet(TIMER1_BASE, TIMER_A, ui32FreqDiv1k / 2);

    //freq
    TimerLoadSet(TIMER1_BASE, TIMER_B, ui32FreqDiv2_5k);
    //duty_cycle
    TimerMatchSet(TIMER1_BASE, TIMER_B, ui32FreqDiv2_5k / 2);


    //Habilitar os TIMERS
    TimerEnable(TIMER0_BASE, TIMER_BOTH);
    TimerEnable(TIMER1_BASE, TIMER_BOTH);
}


void ledRoutine(){
    if(ledFreqDiv >= ui32Counter_0_125s){
        ledFreqDiv = 0;
        uint8_t ui8Value = (ledCode[systemStatus] >> ledRotator) & 0b1;
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, ui8Value);
        ledRotator++;
        if(ledRotator >= 8){
            ledRotator = 0;
        }
    }
}

int
main(void)
{
    //volatile uint32_t ui32Loop;

    //para tm4c129 SysCtlClockGet nao funciona direito
    uint32_t ui32SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT, 16000000);
    //SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //uint32_t ui32SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);

    initVariables(ui32SysClock);

    configureGPIOs();
    setupTimersPWM(ui32SysClock);

    configureSysTick(SYSTICK_COUNTER_TO, intSysTick);
    while(1){
        /*
        if(ledFreqDiv >= 30000){
            ledFreqDiv = 0;
            flipGPIOBit(GPIO_PORTN_BASE, GPIO_PIN_0);
        }
        */
        ledRoutine();
    }
}
