.PHONY: clean

include toolchain.mk

ASFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = --oformat=elf32-littleriscv

%.o: %.S
	$(CROSS_COMPILE)as -R $(ASFLAGS) -o $@ $<

all: clz.elf

clz.elf: clz.o
	 $(CROSS_COMPILE)ld -o $@ -T clz.ld $(LDFLAGS) $<

clean:
	$(RM) clz.elf clz.o
