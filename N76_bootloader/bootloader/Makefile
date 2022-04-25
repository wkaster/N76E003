#
# SDCC Makefile for mcs51
# Modified for N76E003 bootloader
# ------------------------------------------------------

INCDIR  = ../../N76_sdcc/inc
MODEL  = small
DEFS = -DFOSC_160000 -DFOSC=16000000

# ------------------------------------------------------
# SDCC

CC = sdcc
MCU_MODEL = mcs51

CFLAGS = -I$(INCDIR) -m$(MCU_MODEL) --model-$(MODEL) --out-fmt-ihx --no-xinit-opt $(DEFS) --peep-file peep.def
CFLAGS+= --opt-code-size --fomit-frame-pointer --peep-asm --peep-return --std-c11 --acall-ajmp
LFLAGS = -m$(MCU_MODEL) --model-$(MODEL) --out-fmt-ihx $(DEFS)

# ------------------------------------------------------
# Recepies, see GNU MAKE manual

.PHONY: all

all: bootloader.hex

bootloader.hex: bootloader.ihx
	packihx $^ > $@

bootloader.ihx: bootloader.c.rel
	$(CC) -o $@ $(LFLAGS) $^

bootloader.c.rel: main.c
	$(CC) -o $@ $(CFLAGS) -c $^

