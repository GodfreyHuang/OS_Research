include toolchain.mk

CFLAGS = -march=rv32i -mabi=ilp32 -fasm
ASFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = --oformat=elf32-littleriscv

%.S: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ -S $<

%.o: %.S
	$(CROSS_COMPILE)as $(ASFLAGS) -o $@ $<

all: clz_FLM.elf

clz_FLM.S: clz_FLM.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ -S $<

clz_FLM.elf: clz_FLM.o
	 $(CROSS_COMPILE)gcc -o $@ $<

.PHONY: clean
clean:
	$(RM) clz_FLM.elf clz_FLM.o clz_FLM.S