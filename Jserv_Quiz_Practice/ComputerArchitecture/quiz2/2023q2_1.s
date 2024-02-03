# Part 1
calc_parity:
    li t1, 0         # t1 holds current parity value in LSB
loop:
    xor t1, t1, a0   # adds the current least significant bit
                     # in a0 to the parity value in t1
    srli a0, a0, 1   # shift to the next bit in a0,  __A01__ = srli t1, t1, 1 (X)
    bne a0, x0, loop # loop if there are more than 1 bit left in a0
                     # 0 bits will never affect parity
    andi a0, t1, 1   # we only want the one parity bit, __A02__ = lw t1, a0(X)
                     # in bit 0 of t1
    jr ra

# Part 2
store_nibble:
    # prologue omitted
    mv s0, a0
    mv s1, a1
    srli s7, s0, 1      # set d3 through d1
    slli s7, s7, 1      # make space for next bit
    andi a0, s0, 0b1110 # parity of d1, d2, and d3
    jal ra, calc_parity # compute p2
    add s7, s7, a0
    slli s7, s7, 1      # make space for next bit
    andi t0, s0, 1      # extract d0
    add s7, s7, t0
    slli s7, s7, 1      # make space for next bit
    andi a0, s0, 0b1101 # parity of d0, d2, and d3
    jal ra, calc_parity # compute p1
    add s7, s7, a0
    slli s7, s7, 1      # make space for next bit
    andi a0, s0, 0b1011 # parity of d0, d1, and d3
    jal ra, calc_parity # compute p0
    add s7, s7, a0      # __A03__ = a0(X)
    sb  s7, 0(s1)       # s1 contains the memory address passed in as a1 ,
                        #  __A04__ = a1(X), __A05__ = s7(X)
    # epilogue omitted
    jr ra

# Part 3
    __A06__ = s0, s1, s7, (miss ra)