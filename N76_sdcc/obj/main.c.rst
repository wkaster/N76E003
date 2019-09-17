                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.9.0 #11195 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _Timer0_Delay1ms
                                     13 	.globl _InitialUART0_Timer3
                                     14 	.globl _printf_small
                                     15 	.globl _MOSI
                                     16 	.globl _P00
                                     17 	.globl _MISO
                                     18 	.globl _P01
                                     19 	.globl _RXD_1
                                     20 	.globl _P02
                                     21 	.globl _P03
                                     22 	.globl _STADC
                                     23 	.globl _P04
                                     24 	.globl _P05
                                     25 	.globl _TXD
                                     26 	.globl _P06
                                     27 	.globl _RXD
                                     28 	.globl _P07
                                     29 	.globl _IT0
                                     30 	.globl _IE0
                                     31 	.globl _IT1
                                     32 	.globl _IE1
                                     33 	.globl _TR0
                                     34 	.globl _TF0
                                     35 	.globl _TR1
                                     36 	.globl _TF1
                                     37 	.globl _P10
                                     38 	.globl _P11
                                     39 	.globl _P12
                                     40 	.globl _SCL
                                     41 	.globl _P13
                                     42 	.globl _SDA
                                     43 	.globl _P14
                                     44 	.globl _P15
                                     45 	.globl _TXD_1
                                     46 	.globl _P16
                                     47 	.globl _P17
                                     48 	.globl _RI
                                     49 	.globl _TI
                                     50 	.globl _RB8
                                     51 	.globl _TB8
                                     52 	.globl _REN
                                     53 	.globl _SM2
                                     54 	.globl _SM1
                                     55 	.globl _FE
                                     56 	.globl _SM0
                                     57 	.globl _P20
                                     58 	.globl _EX0
                                     59 	.globl _ET0
                                     60 	.globl _EX1
                                     61 	.globl _ET1
                                     62 	.globl _ES
                                     63 	.globl _EBOD
                                     64 	.globl _EADC
                                     65 	.globl _EA
                                     66 	.globl _P30
                                     67 	.globl _PX0
                                     68 	.globl _PT0
                                     69 	.globl _PX1
                                     70 	.globl _PT1
                                     71 	.globl _PS
                                     72 	.globl _PBOD
                                     73 	.globl _PADC
                                     74 	.globl _I2CPX
                                     75 	.globl _AA
                                     76 	.globl _SI
                                     77 	.globl _STO
                                     78 	.globl _STA
                                     79 	.globl _I2CEN
                                     80 	.globl _CM_RL2
                                     81 	.globl _TR2
                                     82 	.globl _TF2
                                     83 	.globl _P
                                     84 	.globl _OV
                                     85 	.globl _RS0
                                     86 	.globl _RS1
                                     87 	.globl _F0
                                     88 	.globl _AC
                                     89 	.globl _CY
                                     90 	.globl _CLRPWM
                                     91 	.globl _PWMF
                                     92 	.globl _LOAD
                                     93 	.globl _PWMRUN
                                     94 	.globl _ADCHS0
                                     95 	.globl _ADCHS1
                                     96 	.globl _ADCHS2
                                     97 	.globl _ADCHS3
                                     98 	.globl _ETGSEL0
                                     99 	.globl _ETGSEL1
                                    100 	.globl _ADCS
                                    101 	.globl _ADCF
                                    102 	.globl _RI_1
                                    103 	.globl _TI_1
                                    104 	.globl _RB8_1
                                    105 	.globl _TB8_1
                                    106 	.globl _REN_1
                                    107 	.globl _SM2_1
                                    108 	.globl _SM1_1
                                    109 	.globl _FE_1
                                    110 	.globl _SM0_1
                                    111 	.globl _EIPH1
                                    112 	.globl _EIP1
                                    113 	.globl _PMD
                                    114 	.globl _PMEN
                                    115 	.globl _PDTCNT
                                    116 	.globl _PDTEN
                                    117 	.globl _SCON_1
                                    118 	.globl _EIPH
                                    119 	.globl _AINDIDS
                                    120 	.globl _SPDR
                                    121 	.globl _SPSR
                                    122 	.globl _SPCR2
                                    123 	.globl _SPCR
                                    124 	.globl _CAPCON4
                                    125 	.globl _CAPCON3
                                    126 	.globl _B
                                    127 	.globl _EIP
                                    128 	.globl _C2H
                                    129 	.globl _C2L
                                    130 	.globl _PIF
                                    131 	.globl _PIPEN
                                    132 	.globl _PINEN
                                    133 	.globl _PICON
                                    134 	.globl _ADCCON0
                                    135 	.globl _C1H
                                    136 	.globl _C1L
                                    137 	.globl _C0H
                                    138 	.globl _C0L
                                    139 	.globl _ADCDLY
                                    140 	.globl _ADCCON2
                                    141 	.globl _ADCCON1
                                    142 	.globl _ACC
                                    143 	.globl _PWMCON1
                                    144 	.globl _PIOCON0
                                    145 	.globl _PWM3L
                                    146 	.globl _PWM2L
                                    147 	.globl _PWM1L
                                    148 	.globl _PWM0L
                                    149 	.globl _PWMPL
                                    150 	.globl _PWMCON0
                                    151 	.globl _FBD
                                    152 	.globl _PNP
                                    153 	.globl _PWM3H
                                    154 	.globl _PWM2H
                                    155 	.globl _PWM1H
                                    156 	.globl _PWM0H
                                    157 	.globl _PWMPH
                                    158 	.globl _PSW
                                    159 	.globl _ADCMPH
                                    160 	.globl _ADCMPL
                                    161 	.globl _PWM5L
                                    162 	.globl _TH2
                                    163 	.globl _PWM4L
                                    164 	.globl _TL2
                                    165 	.globl _RCMP2H
                                    166 	.globl _RCMP2L
                                    167 	.globl _T2MOD
                                    168 	.globl _T2CON
                                    169 	.globl _TA
                                    170 	.globl _PIOCON1
                                    171 	.globl _RH3
                                    172 	.globl _PWM5H
                                    173 	.globl _RL3
                                    174 	.globl _PWM4H
                                    175 	.globl _T3CON
                                    176 	.globl _ADCRH
                                    177 	.globl _ADCRL
                                    178 	.globl _I2ADDR
                                    179 	.globl _I2CON
                                    180 	.globl _I2TOC
                                    181 	.globl _I2CLK
                                    182 	.globl _I2STAT
                                    183 	.globl _I2DAT
                                    184 	.globl _SADDR_1
                                    185 	.globl _SADEN_1
                                    186 	.globl _SADEN
                                    187 	.globl _IP
                                    188 	.globl _PWMINTC
                                    189 	.globl _IPH
                                    190 	.globl _P2S
                                    191 	.globl _P1SR
                                    192 	.globl _P1M2
                                    193 	.globl _P1S
                                    194 	.globl _P1M1
                                    195 	.globl _P0SR
                                    196 	.globl _P0M2
                                    197 	.globl _P0S
                                    198 	.globl _P0M1
                                    199 	.globl _P3
                                    200 	.globl _IAPCN
                                    201 	.globl _IAPFD
                                    202 	.globl _P3SR
                                    203 	.globl _P3M2
                                    204 	.globl _P3S
                                    205 	.globl _P3M1
                                    206 	.globl _BODCON1
                                    207 	.globl _WDCON
                                    208 	.globl _SADDR
                                    209 	.globl _IE
                                    210 	.globl _IAPAH
                                    211 	.globl _IAPAL
                                    212 	.globl _IAPUEN
                                    213 	.globl _IAPTRG
                                    214 	.globl _BODCON0
                                    215 	.globl _AUXR1
                                    216 	.globl _P2
                                    217 	.globl _CHPCON
                                    218 	.globl _EIE1
                                    219 	.globl _EIE
                                    220 	.globl _SBUF_1
                                    221 	.globl _SBUF
                                    222 	.globl _SCON
                                    223 	.globl _CKEN
                                    224 	.globl _CKSWT
                                    225 	.globl _CKDIV
                                    226 	.globl _CAPCON2
                                    227 	.globl _CAPCON1
                                    228 	.globl _CAPCON0
                                    229 	.globl _SFRS
                                    230 	.globl _P1
                                    231 	.globl _WKCON
                                    232 	.globl _CKCON
                                    233 	.globl _TH1
                                    234 	.globl _TH0
                                    235 	.globl _TL1
                                    236 	.globl _TL0
                                    237 	.globl _TMOD
                                    238 	.globl _TCON
                                    239 	.globl _PCON
                                    240 	.globl _RWK
                                    241 	.globl _RCTRIM1
                                    242 	.globl _RCTRIM0
                                    243 	.globl _DPH
                                    244 	.globl _DPL
                                    245 	.globl _SP
                                    246 	.globl _P0
                                    247 	.globl _putchar
                                    248 ;--------------------------------------------------------
                                    249 ; special function registers
                                    250 ;--------------------------------------------------------
                                    251 	.area RSEG    (ABS,DATA)
      000000                        252 	.org 0x0000
                           000080   253 _P0	=	0x0080
                           000081   254 _SP	=	0x0081
                           000082   255 _DPL	=	0x0082
                           000083   256 _DPH	=	0x0083
                           000084   257 _RCTRIM0	=	0x0084
                           000085   258 _RCTRIM1	=	0x0085
                           000086   259 _RWK	=	0x0086
                           000087   260 _PCON	=	0x0087
                           000088   261 _TCON	=	0x0088
                           000089   262 _TMOD	=	0x0089
                           00008A   263 _TL0	=	0x008a
                           00008B   264 _TL1	=	0x008b
                           00008C   265 _TH0	=	0x008c
                           00008D   266 _TH1	=	0x008d
                           00008E   267 _CKCON	=	0x008e
                           00008F   268 _WKCON	=	0x008f
                           000090   269 _P1	=	0x0090
                           000091   270 _SFRS	=	0x0091
                           000092   271 _CAPCON0	=	0x0092
                           000093   272 _CAPCON1	=	0x0093
                           000094   273 _CAPCON2	=	0x0094
                           000095   274 _CKDIV	=	0x0095
                           000096   275 _CKSWT	=	0x0096
                           000097   276 _CKEN	=	0x0097
                           000098   277 _SCON	=	0x0098
                           000099   278 _SBUF	=	0x0099
                           00009A   279 _SBUF_1	=	0x009a
                           00009B   280 _EIE	=	0x009b
                           00009C   281 _EIE1	=	0x009c
                           00009F   282 _CHPCON	=	0x009f
                           0000A0   283 _P2	=	0x00a0
                           0000A2   284 _AUXR1	=	0x00a2
                           0000A3   285 _BODCON0	=	0x00a3
                           0000A4   286 _IAPTRG	=	0x00a4
                           0000A5   287 _IAPUEN	=	0x00a5
                           0000A6   288 _IAPAL	=	0x00a6
                           0000A7   289 _IAPAH	=	0x00a7
                           0000A8   290 _IE	=	0x00a8
                           0000A9   291 _SADDR	=	0x00a9
                           0000AA   292 _WDCON	=	0x00aa
                           0000AB   293 _BODCON1	=	0x00ab
                           0000AC   294 _P3M1	=	0x00ac
                           0000AC   295 _P3S	=	0x00ac
                           0000AD   296 _P3M2	=	0x00ad
                           0000AD   297 _P3SR	=	0x00ad
                           0000AE   298 _IAPFD	=	0x00ae
                           0000AF   299 _IAPCN	=	0x00af
                           0000B0   300 _P3	=	0x00b0
                           0000B1   301 _P0M1	=	0x00b1
                           0000B1   302 _P0S	=	0x00b1
                           0000B2   303 _P0M2	=	0x00b2
                           0000B2   304 _P0SR	=	0x00b2
                           0000B3   305 _P1M1	=	0x00b3
                           0000B3   306 _P1S	=	0x00b3
                           0000B4   307 _P1M2	=	0x00b4
                           0000B4   308 _P1SR	=	0x00b4
                           0000B5   309 _P2S	=	0x00b5
                           0000B7   310 _IPH	=	0x00b7
                           0000B7   311 _PWMINTC	=	0x00b7
                           0000B8   312 _IP	=	0x00b8
                           0000B9   313 _SADEN	=	0x00b9
                           0000BA   314 _SADEN_1	=	0x00ba
                           0000BB   315 _SADDR_1	=	0x00bb
                           0000BC   316 _I2DAT	=	0x00bc
                           0000BD   317 _I2STAT	=	0x00bd
                           0000BE   318 _I2CLK	=	0x00be
                           0000BF   319 _I2TOC	=	0x00bf
                           0000C0   320 _I2CON	=	0x00c0
                           0000C1   321 _I2ADDR	=	0x00c1
                           0000C2   322 _ADCRL	=	0x00c2
                           0000C3   323 _ADCRH	=	0x00c3
                           0000C4   324 _T3CON	=	0x00c4
                           0000C4   325 _PWM4H	=	0x00c4
                           0000C5   326 _RL3	=	0x00c5
                           0000C5   327 _PWM5H	=	0x00c5
                           0000C6   328 _RH3	=	0x00c6
                           0000C6   329 _PIOCON1	=	0x00c6
                           0000C7   330 _TA	=	0x00c7
                           0000C8   331 _T2CON	=	0x00c8
                           0000C9   332 _T2MOD	=	0x00c9
                           0000CA   333 _RCMP2L	=	0x00ca
                           0000CB   334 _RCMP2H	=	0x00cb
                           0000CC   335 _TL2	=	0x00cc
                           0000CC   336 _PWM4L	=	0x00cc
                           0000CD   337 _TH2	=	0x00cd
                           0000CD   338 _PWM5L	=	0x00cd
                           0000CE   339 _ADCMPL	=	0x00ce
                           0000CF   340 _ADCMPH	=	0x00cf
                           0000D0   341 _PSW	=	0x00d0
                           0000D1   342 _PWMPH	=	0x00d1
                           0000D2   343 _PWM0H	=	0x00d2
                           0000D3   344 _PWM1H	=	0x00d3
                           0000D4   345 _PWM2H	=	0x00d4
                           0000D5   346 _PWM3H	=	0x00d5
                           0000D6   347 _PNP	=	0x00d6
                           0000D7   348 _FBD	=	0x00d7
                           0000D8   349 _PWMCON0	=	0x00d8
                           0000D9   350 _PWMPL	=	0x00d9
                           0000DA   351 _PWM0L	=	0x00da
                           0000DB   352 _PWM1L	=	0x00db
                           0000DC   353 _PWM2L	=	0x00dc
                           0000DD   354 _PWM3L	=	0x00dd
                           0000DE   355 _PIOCON0	=	0x00de
                           0000DF   356 _PWMCON1	=	0x00df
                           0000E0   357 _ACC	=	0x00e0
                           0000E1   358 _ADCCON1	=	0x00e1
                           0000E2   359 _ADCCON2	=	0x00e2
                           0000E3   360 _ADCDLY	=	0x00e3
                           0000E4   361 _C0L	=	0x00e4
                           0000E5   362 _C0H	=	0x00e5
                           0000E6   363 _C1L	=	0x00e6
                           0000E7   364 _C1H	=	0x00e7
                           0000E8   365 _ADCCON0	=	0x00e8
                           0000E9   366 _PICON	=	0x00e9
                           0000EA   367 _PINEN	=	0x00ea
                           0000EB   368 _PIPEN	=	0x00eb
                           0000EC   369 _PIF	=	0x00ec
                           0000ED   370 _C2L	=	0x00ed
                           0000EE   371 _C2H	=	0x00ee
                           0000EF   372 _EIP	=	0x00ef
                           0000F0   373 _B	=	0x00f0
                           0000F1   374 _CAPCON3	=	0x00f1
                           0000F2   375 _CAPCON4	=	0x00f2
                           0000F3   376 _SPCR	=	0x00f3
                           0000F3   377 _SPCR2	=	0x00f3
                           0000F4   378 _SPSR	=	0x00f4
                           0000F5   379 _SPDR	=	0x00f5
                           0000F6   380 _AINDIDS	=	0x00f6
                           0000F7   381 _EIPH	=	0x00f7
                           0000F8   382 _SCON_1	=	0x00f8
                           0000F9   383 _PDTEN	=	0x00f9
                           0000FA   384 _PDTCNT	=	0x00fa
                           0000FB   385 _PMEN	=	0x00fb
                           0000FC   386 _PMD	=	0x00fc
                           0000FE   387 _EIP1	=	0x00fe
                           0000FF   388 _EIPH1	=	0x00ff
                                    389 ;--------------------------------------------------------
                                    390 ; special function bits
                                    391 ;--------------------------------------------------------
                                    392 	.area RSEG    (ABS,DATA)
      000000                        393 	.org 0x0000
                           0000FF   394 _SM0_1	=	0x00ff
                           0000FF   395 _FE_1	=	0x00ff
                           0000FE   396 _SM1_1	=	0x00fe
                           0000FD   397 _SM2_1	=	0x00fd
                           0000FC   398 _REN_1	=	0x00fc
                           0000FB   399 _TB8_1	=	0x00fb
                           0000FA   400 _RB8_1	=	0x00fa
                           0000F9   401 _TI_1	=	0x00f9
                           0000F8   402 _RI_1	=	0x00f8
                           0000EF   403 _ADCF	=	0x00ef
                           0000EE   404 _ADCS	=	0x00ee
                           0000ED   405 _ETGSEL1	=	0x00ed
                           0000EC   406 _ETGSEL0	=	0x00ec
                           0000EB   407 _ADCHS3	=	0x00eb
                           0000EA   408 _ADCHS2	=	0x00ea
                           0000E9   409 _ADCHS1	=	0x00e9
                           0000E8   410 _ADCHS0	=	0x00e8
                           0000DF   411 _PWMRUN	=	0x00df
                           0000DE   412 _LOAD	=	0x00de
                           0000DD   413 _PWMF	=	0x00dd
                           0000DC   414 _CLRPWM	=	0x00dc
                           0000D7   415 _CY	=	0x00d7
                           0000D6   416 _AC	=	0x00d6
                           0000D5   417 _F0	=	0x00d5
                           0000D4   418 _RS1	=	0x00d4
                           0000D3   419 _RS0	=	0x00d3
                           0000D2   420 _OV	=	0x00d2
                           0000D0   421 _P	=	0x00d0
                           0000CF   422 _TF2	=	0x00cf
                           0000CA   423 _TR2	=	0x00ca
                           0000C8   424 _CM_RL2	=	0x00c8
                           0000C6   425 _I2CEN	=	0x00c6
                           0000C5   426 _STA	=	0x00c5
                           0000C4   427 _STO	=	0x00c4
                           0000C3   428 _SI	=	0x00c3
                           0000C2   429 _AA	=	0x00c2
                           0000C0   430 _I2CPX	=	0x00c0
                           0000BE   431 _PADC	=	0x00be
                           0000BD   432 _PBOD	=	0x00bd
                           0000BC   433 _PS	=	0x00bc
                           0000BB   434 _PT1	=	0x00bb
                           0000BA   435 _PX1	=	0x00ba
                           0000B9   436 _PT0	=	0x00b9
                           0000B8   437 _PX0	=	0x00b8
                           0000B0   438 _P30	=	0x00b0
                           0000AF   439 _EA	=	0x00af
                           0000AE   440 _EADC	=	0x00ae
                           0000AD   441 _EBOD	=	0x00ad
                           0000AC   442 _ES	=	0x00ac
                           0000AB   443 _ET1	=	0x00ab
                           0000AA   444 _EX1	=	0x00aa
                           0000A9   445 _ET0	=	0x00a9
                           0000A8   446 _EX0	=	0x00a8
                           0000A0   447 _P20	=	0x00a0
                           00009F   448 _SM0	=	0x009f
                           00009F   449 _FE	=	0x009f
                           00009E   450 _SM1	=	0x009e
                           00009D   451 _SM2	=	0x009d
                           00009C   452 _REN	=	0x009c
                           00009B   453 _TB8	=	0x009b
                           00009A   454 _RB8	=	0x009a
                           000099   455 _TI	=	0x0099
                           000098   456 _RI	=	0x0098
                           000097   457 _P17	=	0x0097
                           000096   458 _P16	=	0x0096
                           000096   459 _TXD_1	=	0x0096
                           000095   460 _P15	=	0x0095
                           000094   461 _P14	=	0x0094
                           000094   462 _SDA	=	0x0094
                           000093   463 _P13	=	0x0093
                           000093   464 _SCL	=	0x0093
                           000092   465 _P12	=	0x0092
                           000091   466 _P11	=	0x0091
                           000090   467 _P10	=	0x0090
                           00008F   468 _TF1	=	0x008f
                           00008E   469 _TR1	=	0x008e
                           00008D   470 _TF0	=	0x008d
                           00008C   471 _TR0	=	0x008c
                           00008B   472 _IE1	=	0x008b
                           00008A   473 _IT1	=	0x008a
                           000089   474 _IE0	=	0x0089
                           000088   475 _IT0	=	0x0088
                           000087   476 _P07	=	0x0087
                           000087   477 _RXD	=	0x0087
                           000086   478 _P06	=	0x0086
                           000086   479 _TXD	=	0x0086
                           000085   480 _P05	=	0x0085
                           000084   481 _P04	=	0x0084
                           000084   482 _STADC	=	0x0084
                           000083   483 _P03	=	0x0083
                           000082   484 _P02	=	0x0082
                           000082   485 _RXD_1	=	0x0082
                           000081   486 _P01	=	0x0081
                           000081   487 _MISO	=	0x0081
                           000080   488 _P00	=	0x0080
                           000080   489 _MOSI	=	0x0080
                                    490 ;--------------------------------------------------------
                                    491 ; overlayable register banks
                                    492 ;--------------------------------------------------------
                                    493 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        494 	.ds 8
                                    495 ;--------------------------------------------------------
                                    496 ; internal ram data
                                    497 ;--------------------------------------------------------
                                    498 	.area DSEG    (DATA)
                                    499 ;--------------------------------------------------------
                                    500 ; overlayable items in internal ram 
                                    501 ;--------------------------------------------------------
                                    502 	.area	OSEG    (OVR,DATA)
                                    503 ;--------------------------------------------------------
                                    504 ; Stack segment in internal ram 
                                    505 ;--------------------------------------------------------
                                    506 	.area	SSEG
      000051                        507 __start__stack:
      000051                        508 	.ds	1
                                    509 
                                    510 ;--------------------------------------------------------
                                    511 ; indirectly addressable internal ram data
                                    512 ;--------------------------------------------------------
                                    513 	.area ISEG    (DATA)
                                    514 ;--------------------------------------------------------
                                    515 ; absolute internal ram data
                                    516 ;--------------------------------------------------------
                                    517 	.area IABS    (ABS,DATA)
                                    518 	.area IABS    (ABS,DATA)
                                    519 ;--------------------------------------------------------
                                    520 ; bit data
                                    521 ;--------------------------------------------------------
                                    522 	.area BSEG    (BIT)
                                    523 ;--------------------------------------------------------
                                    524 ; paged external ram data
                                    525 ;--------------------------------------------------------
                                    526 	.area PSEG    (PAG,XDATA)
                                    527 ;--------------------------------------------------------
                                    528 ; external ram data
                                    529 ;--------------------------------------------------------
                                    530 	.area XSEG    (XDATA)
                                    531 ;--------------------------------------------------------
                                    532 ; absolute external ram data
                                    533 ;--------------------------------------------------------
                                    534 	.area XABS    (ABS,XDATA)
                                    535 ;--------------------------------------------------------
                                    536 ; external initialized ram data
                                    537 ;--------------------------------------------------------
                                    538 	.area HOME    (CODE)
                                    539 	.area GSINIT0 (CODE)
                                    540 	.area GSINIT1 (CODE)
                                    541 	.area GSINIT2 (CODE)
                                    542 	.area GSINIT3 (CODE)
                                    543 	.area GSINIT4 (CODE)
                                    544 	.area GSINIT5 (CODE)
                                    545 	.area GSINIT  (CODE)
                                    546 	.area GSFINAL (CODE)
                                    547 	.area CSEG    (CODE)
                                    548 ;--------------------------------------------------------
                                    549 ; interrupt vector 
                                    550 ;--------------------------------------------------------
                                    551 	.area HOME    (CODE)
      000000                        552 __interrupt_vect:
      000000 02 00 06         [24]  553 	ljmp	__sdcc_gsinit_startup
                                    554 ;--------------------------------------------------------
                                    555 ; global & static initialisations
                                    556 ;--------------------------------------------------------
                                    557 	.area HOME    (CODE)
                                    558 	.area GSINIT  (CODE)
                                    559 	.area GSFINAL (CODE)
                                    560 	.area GSINIT  (CODE)
                                    561 	.globl __sdcc_gsinit_startup
                                    562 	.globl __sdcc_program_startup
                                    563 	.globl __start__stack
                                    564 	.globl __mcs51_genRAMCLEAR
                                    565 	.area GSFINAL (CODE)
      00001F 02 00 03         [24]  566 	ljmp	__sdcc_program_startup
                                    567 ;--------------------------------------------------------
                                    568 ; Home
                                    569 ;--------------------------------------------------------
                                    570 	.area HOME    (CODE)
                                    571 	.area HOME    (CODE)
      000003                        572 __sdcc_program_startup:
      000003 02 00 32         [24]  573 	ljmp	_main
                                    574 ;	return from main will return to caller
                                    575 ;--------------------------------------------------------
                                    576 ; code
                                    577 ;--------------------------------------------------------
                                    578 	.area CSEG    (CODE)
                                    579 ;------------------------------------------------------------
                                    580 ;Allocation info for local variables in function 'putchar'
                                    581 ;------------------------------------------------------------
                                    582 ;c                         Allocated to registers r6 r7 
                                    583 ;------------------------------------------------------------
                                    584 ;	src/main.c:16: int putchar (int c) {
                                    585 ;	-----------------------------------------
                                    586 ;	 function putchar
                                    587 ;	-----------------------------------------
      000022                        588 _putchar:
                           000007   589 	ar7 = 0x07
                           000006   590 	ar6 = 0x06
                           000005   591 	ar5 = 0x05
                           000004   592 	ar4 = 0x04
                           000003   593 	ar3 = 0x03
                           000002   594 	ar2 = 0x02
                           000001   595 	ar1 = 0x01
                           000000   596 	ar0 = 0x00
      000022 AE 82            [24]  597 	mov	r6,dpl
      000024 AF 83            [24]  598 	mov	r7,dph
                                    599 ;	src/main.c:17: while (!TI);
      000026                        600 00101$:
                                    601 ;	src/main.c:18: TI = 0;
                                    602 ;	assignBit
      000026 10 99 02         [24]  603 	jbc	_TI,00114$
      000029 80 FB            [24]  604 	sjmp	00101$
      00002B                        605 00114$:
                                    606 ;	src/main.c:19: SBUF = c;
      00002B 8E 99            [24]  607 	mov	_SBUF,r6
                                    608 ;	src/main.c:20: return c;
      00002D 8E 82            [24]  609 	mov	dpl,r6
      00002F 8F 83            [24]  610 	mov	dph,r7
                                    611 ;	src/main.c:21: }
      000031 22               [24]  612 	ret
                                    613 ;------------------------------------------------------------
                                    614 ;Allocation info for local variables in function 'main'
                                    615 ;------------------------------------------------------------
                                    616 ;	src/main.c:25: void main (void) 
                                    617 ;	-----------------------------------------
                                    618 ;	 function main
                                    619 ;	-----------------------------------------
      000032                        620 _main:
                                    621 ;	src/main.c:27: InitialUART0_Timer3(115200);
      000032 90 C2 00         [24]  622 	mov	dptr,#0xc200
      000035 75 F0 01         [24]  623 	mov	b,#0x01
      000038 E4               [12]  624 	clr	a
      000039 12 00 9F         [24]  625 	lcall	_InitialUART0_Timer3
                                    626 ;	src/main.c:28: TI = 1;															// Important, use prinft function must set TI=1;
                                    627 ;	assignBit
      00003C D2 99            [12]  628 	setb	_TI
                                    629 ;	src/main.c:30: while(1)
      00003E                        630 00102$:
                                    631 ;	src/main.c:32: printf_small("\n Hello world");
      00003E 74 AA            [12]  632 	mov	a,#___str_0
      000040 C0 E0            [24]  633 	push	acc
      000042 74 06            [12]  634 	mov	a,#(___str_0 >> 8)
      000044 C0 E0            [24]  635 	push	acc
      000046 74 80            [12]  636 	mov	a,#0x80
      000048 C0 E0            [24]  637 	push	acc
      00004A 12 03 24         [24]  638 	lcall	_printf_small
      00004D 15 81            [12]  639 	dec	sp
      00004F 15 81            [12]  640 	dec	sp
      000051 15 81            [12]  641 	dec	sp
                                    642 ;	src/main.c:33: Timer0_Delay1ms(300);
      000053 90 01 2C         [24]  643 	mov	dptr,#0x012c
      000056 E4               [12]  644 	clr	a
      000057 F5 F0            [12]  645 	mov	b,a
      000059 12 01 AE         [24]  646 	lcall	_Timer0_Delay1ms
                                    647 ;	src/main.c:35: }
      00005C 80 E0            [24]  648 	sjmp	00102$
                                    649 	.area CSEG    (CODE)
                                    650 	.area CONST   (CODE)
                                    651 	.area CONST   (CODE)
      0006AA                        652 ___str_0:
      0006AA 0A                     653 	.db 0x0a
      0006AB 20 48 65 6C 6C 6F 20   654 	.ascii " Hello world"
             77 6F 72 6C 64
      0006B7 00                     655 	.db 0x00
                                    656 	.area CSEG    (CODE)
                                    657 	.area CABS    (ABS,CODE)
