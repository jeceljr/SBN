.nolist

/* conjunto de instruções básicas do SBN
*/

.macro	sbn a, b, dest
	.word \b, \a, \dest
.endm

.macro sub a,b
    sbn \a,\b, .+2   /* pula para proxima instrução de qualquer jeito */
.endm

.macro add a, b
    sub temp,temp   /*  temp = 0 */
    sub temp, \b    /*  temp = -b */
    sub \a, temp    /*  a = a + b */
.endm

.macro move a,b
     sub \a,\a      /*  a = 0 */
     add \a, \b    /*  a = b */
.endm

.macro jmp dest
    sub temp, temp     /* temp = 0 */
    sbn temp, one, dest
.endm

.altmacro
.macro jmpz a, dest
LOCAL notzero
    sub temp, temp         /* temp = 0 */
    sbn temp, \a, notzero  /* temp = -a */
    sbn temp, one, \dest       /* temp = -a - 1  e -a >= 0 */
notzero:    /*   a > 0 ou a < 0   */
.endm

.macro out a, port=0x8000
    move iotmp, \port    /*  iotemp = current value of switches */
    sub iotmp, \a      /*  iotemp = switches-a */
    sub \port, iotmp  /*  switches - (switches - a) = a */
.endm

.macro in a, port=0x8000
    move \a, \port
.endm

.list

