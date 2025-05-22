/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, restituire la lunghezza minima e
				massima	delle sotto-sequenze di bit a 0.

 ********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	unsigned char vet[] = { 0xF2 };	// Sequenza di bit
	unsigned short int len = 1;				// Lunghezza (in bit) della sequenza

	// Output
	short int minLung;		// Lunghezza minima sotto-sequenza di 0
	short int maxLung;		// Lunghezza massima sotto-sequenza di 0

	__asm
	{
		; lunghezza massima
XOR EAX, EAX; indice che scorre il vettore
XOR ECX, ECX; numeri di bit da considerare
XOR EDX, EDX; numero di bit a zero da confrontare
XOR EBX, EBX; contatore dei bit nei singoli byte del vettore
MOV CX, len

MOV BL, vet[EAX]

ciclo1: INC BH
CMP BH, 8; verifico la fine del primo byte
JE nuovo_byte1
TEST BL, 1
JNZ passo_oltre1
INC DL; contatore di zeri in fila
SHR BL, 1
LOOP ciclo1
JMP fine1

passo_oltre1 : SHR BL, 1; 1 come ultimo bit, e sposto i bit
CMP DH, DL
JB da_cambiare1
JMP intatto1

da_cambiare1 : MOV DH, DL; inverto i registri se ottengo seguenza maggiore
intatto1 : XOR DL, DL
LOOP ciclo1
JMP fine1

nuovo_byte1 : XOR BH, BH; passo al byte successivo
INC EAX
MOV BL, vet[EAX]
LOOP ciclo1

fine1 : CMP DH, 0
JZ esci1

XCHG DL, DH; scambio i registri per avere la sequenza in offset minore
XOR DH, DH

esci1 : CMP DL, 0
JE nulla1
MOV maxLung, DX
JMP basta1

nulla1 : MOV maxLung, -1; non ci sono zeri

basta1 :

; lunghezza minima
XOR EAX, EAX; indice che scorre il vettore
XOR ECX, ECX; numeri di bit da considerare
XOR EDX, EDX; numero di bit a zero da confrontare
XOR EBX, EBX; contatore dei bit nei singoli byte del vettore
MOV CX, len

MOV BL, vet[EAX]

ciclo2: INC BH
CMP BH, 8; verifico la fine del primo byte
JE nuovo_byte2
TEST BL, 1
JNZ passo_oltre2
INC DL; contatore di zeri in fila
SHR BL, 1
LOOP ciclo2
JMP fine2

passo_oltre2 : SHR BL, 1; 1 come ultimo bit, e sposto i bit
CMP DL, 0
JZ intatto2
CMP DH, 0
JZ da_cambiare2
CMP DH, DL
JA da_cambiare2
JMP intatto2

da_cambiare2 : MOV DH, DL; inverto i registri se ottengo seguenza maggiore
intatto2 : XOR DL, DL
LOOP ciclo2
JMP fine2

nuovo_byte2 : XOR BH, BH; passo al byte successivo
INC EAX
MOV BL, vet[EAX]
LOOP ciclo2

/*fine2 : CMP DH, 0
JZ esci2

CMP DL, DH
JB basso2
scambia2: XCHG DL, DH; scambio i registri per avere la sequenza in offset minore
JMP stampa

esci2: CMP DL, 0
JE nulla2
basso2: CMP DL, 0
JZ scambia2
stampa: XOR DH, DH
MOV minLung, DX
JMP basta2

nulla2: MOV minLung, -1; non ci sono zeri

basta2:*/

fine2:
CMP DH, 0
	JZ esci2; se nessuna sequenza salvata

	CMP DL, DH
	JB scambia2; se DL < DH → è la sequenza minima → scambia
	JMP stampa; altrimenti stampa DH come minimo

	esci2 :
CMP DL, 0
	JE nulla2; nessuna sequenza
	JMP stampa; altrimenti usa DL

	scambia2 :
XCHG DL, DH; scambia per avere DL come minimo

	stampa :
XOR DH, DH; azzera DH per sicurezza
	MOV minLung, DX; salva la lunghezza minima trovata
	JMP basta2

	nulla2 :
MOV minLung, -1; nessuna sequenza di 0 trovata

	basta2 :
		
	}

	// Stampa su video
	printf("Lunghezza minima delle sotto-sequenze di 0: %d\n", minLung);
	printf("Lunghezza massima delle sotto-sequenze di 0: %d\n", maxLung);
}
