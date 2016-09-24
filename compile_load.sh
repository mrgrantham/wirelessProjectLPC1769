#!/bin/bash

make clean
make

openocd -f embedded-artists-lpc1769.cfg -c "program main.elf verify reset exit"
