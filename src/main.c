#include <driverlib.h>
#include <msp430.h>
#include <stdio.h>
#include <string.h>

#include "led.h"

static void __attribute__((naked, section(".crt_0042"), used)) disable_watchdog(void) {
    WDTCTL = WDTPW | WDTHOLD;
}

void UART_init() {
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 146;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    EUSCI_A_UART_init(EUSCI_A0_BASE, &param);
    EUSCI_A_UART_enable(EUSCI_A0_BASE);
}

int main(void) {
    LED_init();

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    // GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4, GPIO_PIN5);
    // GPIO_selectInterruptEdge(GPIO_PORT_P4, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN5);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_PJ, GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN1, GPIO_SECONDARY_MODULE_FUNCTION);

    PMM_unlockLPM5();

    CS_setExternalClockSource(32768, 0);
    CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_turnOnLFXT(CS_LFXT_DRIVE_0);

    UART_init();

    __bis_SR_register(GIE);

    LED_turnOnLED1();
    LED_turnOnLED2();

    char line[128];
    setbuf(stdout, NULL);
    while (true) {
        printf("$ ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;
        fflush(stdin);
        printf("you say: %s\n", line);
    }
    return 0;
}

void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void) {
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    LED_turnOffLED1();
    LED_turnOnLED2();
}

void __attribute__((interrupt(PORT4_VECTOR))) Port_4(void) {
    GPIO_clearInterrupt(GPIO_PORT_P4, GPIO_PIN5);
    LED_turnOffLED2();
    LED_turnOnLED1();
}
