#include <driverlib.h>

void LED_init() {
    // LED1 <---> P4.6
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
    // 默认熄灭
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
    // LED2 <---> P1.0
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    // 默认熄灭
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_toggleLED1() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void LED_toggleLED2() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_turnOnLED1() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void LED_turnOnLED2() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void LED_turnOffLED1() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
}

void LED_turnOffLED2() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
