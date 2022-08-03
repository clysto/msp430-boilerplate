#!/bin/bash

nohup $MSP430GCC/bin/gdb_agent_console $MSP430GCC/msp430.dat > /dev/null &
pid=$!
echo gdb agent pid:$pid port:55000
$MSP430GCC/bin/msp430-elf-gdb build/MSP430FR5969.elf
kill $pid
