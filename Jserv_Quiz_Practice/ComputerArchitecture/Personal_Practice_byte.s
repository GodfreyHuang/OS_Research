.data
num: .word 0x180

.text
main:
    lw s0, num
    lb s1, 1(s0)
    lb s2, 0(s0)
    sb s2, 2(s0)