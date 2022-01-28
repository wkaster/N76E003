#
# SDCC Makefile for mcs51
# Modified for N76E003
# ------------------------------------------------------
# PATH

INCDIR  = ./inc
SRCDIR  = ./src
OBJDIR  = ./obj
OUTDIR  = ./hex
LIBDIR  = ./lib

# ------------------------------------------------------
# Target and Source
TARGET = $(OUTDIR)/main

#C_SRC = $(SRCDIR)/helloworld.c
C_SRC := $(wildcard $(SRCDIR)/*.c $(LIBDIR)/*.c)
ASM_SRC = $(wildcard $(SRCDIR)/*.asm)

C_SRC_FILE = $(notdir $(C_SRC))
C_OBJ_FILE = $(C_SRC_FILE:%.c=%.c.rel)

ASM_SRC_FILE = $(notdir $(ASM_SRC))
ASM_OBJ_FILE = $(ASM_SRC_FILE:%.asm=%.asm.rel)

OBJ = $(addprefix $(OBJDIR)/, $(C_OBJ_FILE)) $(addprefix $(OBJDIR)/, $(ASM_OBJ_FILE)) 

#$(info $(OBJ))

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
# S = @

.PHONY: all

all: $(TARGET).bin $(TARGET).hex

$(OUTDIR)/%.hex: $(OBJDIR)/%.ihx
	$(S) packihx $^ > $@

$(OUTDIR)/%.bin: $(OBJDIR)/%.ihx
	$(S) makebin -p $^ $@

$(OBJDIR)/%.ihx: $(OBJ)
	$(S) $(CC) -o $@ $(LFLAGS) $^

$(OBJDIR)/%.c.rel: $(LIBDIR)/%.c
	$(S) $(CC) -o $@ $(CFLAGS) -c $^

$(OBJDIR)/%.c.rel: $(SRCDIR)/%.c
	$(S) $(CC) -o $@ $(CFLAGS) -c $^

$(OBJDIR)/%.asm.rel: $(SRCDIR)/%.asm
	$(S) $(AS) $(AFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	$(S) rm -rf $(OBJDIR)/*
	$(S) rm -rf $(TARGET).hex
	$(S) rm -rf $(TARGET).bin
	$(S) rm -rf $(TARGET).a51

disasm: $(TARGET).hex
	./tools/mcs51-disasm.pl -M N76E003.h -I ./inc -fl -rj -as $(TARGET).hex > $(TARGET).a51
