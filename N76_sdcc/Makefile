#
# SDCC Makefile for mcs51
# Modified for N76E003
# ------------------------------------------------------
# PATH

INCDIR  = ./inc
SRCDIR  = ./src
OBJDIR  = ./obj
OUTDIR  = ./out
LIBDIR  = ./lib

# ------------------------------------------------------
# Target and Source
TARGET = $(OUTDIR)/main

C_SRC := $(wildcard $(SRCDIR)/*.c $(LIBDIR)/*.c)
ASM_SRC = $(wildcard $(SRCDIR)/*.asm)

C_SRC_FILE = $(notdir $(C_SRC))
C_OBJ_FILE = $(C_SRC_FILE:%.c=%.c.rel)
C_TO_ASM_FILE = $(C_SRC_FILE:%.c=%.asm)

ASM_SRC_FILE = $(notdir $(ASM_SRC))
ASM_OBJ_FILE = $(ASM_SRC_FILE:%.asm=%.asm.rel)

OBJ = $(addprefix $(OBJDIR)/, $(C_OBJ_FILE)) $(addprefix $(OBJDIR)/, $(ASM_OBJ_FILE)) 
CTOASM = $(addprefix $(OUTDIR)/, $(C_TO_ASM_FILE))

#$(info $(CTOASM))

# ------------------------------------------------------
# Usually SDCC's small memory model is the best choice.  If
# you run out of internal RAM, you will need to declare
# variables as "xdata", or switch to larger model

# Memory Model (small, medium, large, huge)
MODEL  = small

# ------------------------------------------------------
# Memory Layout
# PRG Size = 4K Bytes
#CODE_SIZE = --code-loc 0x0000 --code-size 18432
CODE_SIZE = --code-size 18432
# INT-MEM Size = 256 Bytes
#IRAM_SIZE = --idata-loc 0x0000  --iram-size 256
IRAM_SIZE = --iram-size 256
# EXT-MEM Size = 4K Bytes
#XRAM_SIZE = --xram-loc 0x0000 --xram-size 768
XRAM_SIZE = --xram-size 768

# See Datasheet section 13.5 for 16.6MHz HIRC mode
# N76 Clock Frequency (-DFOSC_160000, -DFOSC_166000)
# USE_FLOATS (this should be combined with model large if set 1)
# -DUSE_FLOATS=1
DEFS = -DFOSC_160000

# ------------------------------------------------------
# SDCC

CC = sdcc
AS = sdas8051

MCU_MODEL = mcs51

#LIBS    = 
#LIBPATH = -L $(LIBDIR)

#DEBUG = --debug
AFLAGS =  -l -s 
CFLAGS = -I$(INCDIR) -m$(MCU_MODEL) --model-$(MODEL) --out-fmt-ihx --no-xinit-opt $(DEBUG) $(DEFS) --peep-file tools/peep.def
LFLAGS = $(LIBPATH) $(LIBS) -m$(MCU_MODEL) --model-$(MODEL) $(CODE_SIZE) $(IRAM_SIZE) $(XRAM_SIZE) --out-fmt-ihx $(DEBUG) $(DEFS)

# ------------------------------------------------------
# Recepies, see GNU MAKE manual

.PHONY: all

all: $(TARGET).bin $(TARGET).hex

$(OUTDIR)/%.hex: $(OBJDIR)/%.ihx
	packihx $^ > $@

$(OUTDIR)/%.bin: $(OBJDIR)/%.ihx
	makebin -p $^ $@

$(OBJDIR)/%.ihx: $(OBJ)
	$(CC) -o $@ $(LFLAGS) $^

$(OBJDIR)/%.c.rel: $(LIBDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $^

$(OBJDIR)/%.c.rel: $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $^

$(OBJDIR)/%.asm.rel: $(SRCDIR)/%.asm
	$(AS) $(AFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(TARGET).hex
	rm -rf $(TARGET).bin
	rm -rf $(TARGET).asm


asm: $(CTOASM)

$(OUTDIR)/%.asm: $(LIBDIR)/%.c
	$(CC) -o $@ -S $(CFLAGS) -c $^

$(OUTDIR)/%.asm: $(SRCDIR)/%.c
	$(CC) -o $@ -S $(CFLAGS) -c $^

