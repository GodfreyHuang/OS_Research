include toolchain.mk

CFLAGS = -march=rv32i -mabi=ilp32 -fasm
ASFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = --oformat=elf32-littleriscv

%.S: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ -S $<

%.o: %.S
	$(CROSS_COMPILE)as $(ASFLAGS) -o $@ $<

all: CLZ_FindMSB.elf

CLZ_FindMSB.S: CLZ_FindMSB.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ -S $<

CLZ_FindMSB.elf: CLZ_FindMSB.o
	 $(CROSS_COMPILE)gcc -o $@ $<

.PHONY: clean
clean:
	$(RM) CLZ_FindMSB.elf CLZ_FindMSB.o CLZ_FindMSB.S