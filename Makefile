##  Makefile -- 
##  
##  Copyright (C) 2011 Enrico Costanza
##  Based on Copyright (C) 2001, 2003 Stephen Lacy (slacy@slacy.com)
##
##  This program is free software; you can redistribute it and/or
##  modify it under the terms of the GNU General Public License
##  as published by the Free Software Foundation; either version 2
##  of the License, or (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
##  or find it on the web at http:##www.gnu.org/copyleft/gpl.html

# TARGET is the name of the program we want to build
# this is the file where the main function is (without the .c extension)
TARGET=LEDMenu

# OBJECTS are any other c files that are part of the projects (if any)
# note that here the .c extensions are replaced by .o
#OBJECTS=
OBJECTS+=LEDlib.c input.c animation1.c animation2.c dodgegame.c snake.c charstack.c


# TDIR stands for tools dir root
# OS X 
TROOT=/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/
# iSolutions computer rooms
#TROOT=C:\PROGRA~2\arduino-0022\hardware\tools\avr\\
# for your own windows machine you may need to change to something like this:
#TROOT=C:\Program Files\arduino-0022\hardware\tools\avr\\

# TDIR stands for Tools Dir
#TDIR=
# OS X 
TDIR=$(TROOT)bin/

export PATH:=$(TDIR):$(PATH)

# Tools we need

# CC stands for C Compiler
CC=avr-gcc
OBJCOPY=avr-objcopy
PROGRAMMER=avrdude

# microcontroller model and frequency
MCU=atmega328p
CPU_FREQ=16000000UL

# C compiler flags and definitions
CCFLAGS= -Wall -Os
CCDEFS = -DF_CPU=$(CPU_FREQ)

# avrdude options
PROG_IC=ATMEGA328P
PROG_METHOD=arduino
# The port needs to be changed depending on the architecture!
# You should be able to take this from the tools->serial port setting in the Arduino IDE 
# (should be something like com6 on windows)
PROG_PORT=/dev/tty.usbmodem1421
PROG_RATE=115200
PROG_CONF=$(TROOT)etc/avrdude.conf

default: $(TARGET).hex

# this defines how .o files are made from .c files
%.o: %.c
	$(TDIR)$(CC) $(CCFLAGS) $(CCDEFS) -mmcu=$(MCU) -c $^ -o $@

# this defines how the target is built; it requires all the objects
$(TARGET): $(TARGET).o $(OBJECTS) 
	$(TDIR)$(CC) -g -mmcu=$(MCU) $(CCDEFS) $^ -o $@ 

# this defines how the .hex file is built
%.hex: $(TARGET)
	$(TDIR)$(OBJCOPY) -O ihex -R .eeprom $^ $@

# this is for uploading the code to the arduinon board
program: $(TARGET).hex
	$(TDIR)$(PROGRAMMER) -C $(PROG_CONF) -F -V -p $(PROG_IC) -c $(PROG_METHOD) -P $(PROG_PORT) -b $(PROG_RATE) -U flash:w:$^ 

# this removes all files that were created (if any)
clean:
	rm -f $(TARGET).hex $(TARGET) *.o 


