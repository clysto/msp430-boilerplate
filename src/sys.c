#include <driverlib.h>

int write(int fd, const char *buf, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, buf[i]);
    }
    return i;
}

int read(int fd, char *buf, int len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        buf[i] = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
        if (buf[i] == '\n') {
            i++;
            break;
        }
    }
    return i;
}