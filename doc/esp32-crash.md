
Guru Meditation Error: Core  1 panic'ed (Interrupt wdt timeout on CPU1)
Core 1 register dump:
PC      : 0x4008b95e  PS      : 0x00060334  A0      : 0x8008aaab  A1      : 0x3ffbe660  
A2      : 0x3ffb58bc  A3      : 0x3ffbc6c4  A4      : 0x00000001  A5      : 0x00000001  
A6      : 0x00060323  A7      : 0x00000000  A8      : 0x3ffbc6c4  A9      : 0x3ffbc6c4  
A10     : 0x00000019  A11     : 0x00000019  A12     : 0x00000001  A13     : 0x00000001  
A14     : 0x00060321  A15     : 0x00000000  SAR     : 0x00000018  EXCCAUSE: 0x00000006  
EXCVADDR: 0x00000000  LBEG    : 0x4000c2e0  LEND    : 0x4000c2f6  LCOUNT  : 0xffffffff  
Core 1 was running in ISR context:
EPC1    : 0x400865d4  EPC2    : 0x00000000  EPC3    : 0x00000000  EPC4    : 0x4008b95e

Backtrace: 0x4008b95e:0x3ffbe660 0x4008aaa8:0x3ffbe680 0x40089533:0x3ffbe6a0 0x40084421:0x3ffbe6e0 0x40113171:0x3ffbe700 0x40107b79:0x3ffbe720 0x400841bf:0x3ffbe760 0x40080f58:0x3ffbe780 0x400812fd:

