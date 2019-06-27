    section  CSTACK:DATA:NOROOT(3)
    section .intvec:CONST(2)
__isr_vector:
    dc32   sfe(CSTACK)
    dc32   Reset_Handler

    section MYCODE:CODE(2)
    thumb
Reset_Handler:
    bl      start
start:
    nop
    b       start

    end
