
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
	unsigned char vet[] = { 0xBC,0xFF,0x01 };	// Sequenza di bit
	unsigned short int len = 18;				// Lunghezza (in bit) della sequenza

	// Output
	short int minLung;		// Lunghezza minima sotto-sequenza di 0
	short int maxLung;		// Lunghezza massima sotto-sequenza di 0

	__asm
	{
		XOR EAX, EAX; indice sul vettore
XOR ECX, ECX; minLung(CL)
XOR EDX, EDX; maxLung(DL)
XOR EBX, EBX; BH = contatore bit, BL = byte corrente

MOV BL, vet[EAX]; carica il primo byte

ciclo :
MOV AL, BH
	CMP AX, len; fine dei bit ?
	JE L0
	CMP BH, 0
	JZ salta
	TEST BH, 7; fine byte ?
	JZ nuovo_byte

	salta :
INC BH

	prova :
	TEST BL, 1
	JNZ passo_oltre
	INC DH; incremento sequenza zeri
	SHR BL, 1
	JMP ciclo

	passo_oltre :
SHR BL, 1; scorro bit

	L0 :
CMP DL, DH; confronta con max
	JB L1
	JMP L2

	L1 :
MOV DL, DH; aggiorna max

	L2 :
CMP CL, 0
	JZ L3
	CMP DH, 0
	JZ continua
	CMP CL, DH; confronta con min
	JB continua

	L3 :
MOV CL, DH; aggiorna min

	continua :
XOR DH, DH
	MOV AL, BH
	CMP AX, len; fine dei bit ?
	JE fine
	JMP ciclo

	nuovo_byte :
INC CH; passo al byte
	MOV AL, CH
	MOV BL, vet[EAX]
    INC BH
	MOV AL, BH
	CMP AX, len; fine dei bit ?
	JE L0
	JMP prova

	fine :
CMP DL, 0
	JZ esci

	XOR CH, CH
	MOV maxLung, DX
	MOV minLung, CX
	JMP basta

	esci :
	MOV maxLung, -1; caso senza zeri
	MOV minLung, -1

	basta :
	}

	// Stampa su video
	printf("Lunghezza minima delle sotto-sequenze di 0: %d\n", minLung);
	printf("Lunghezza massima delle sotto-sequenze di 0: %d\n", maxLung);
}

/*XOR EAX, EAX              ; indice nel vettore
    XOR ECX, ECX              ; CL = minLung
    XOR EDX, EDX              ; DL = maxLung
    XOR EBX, EBX              ; BH = contatore bit, BL = byte corrente

    MOV BL, vet[EAX]          ; carica primo byte
    MOV CX, len               ; numero di bit da analizzare

ciclo:
    CMP BH, CX
    JE fine                   ; se letti tutti i bit, esci

    CMP BH, 0
    JZ salta
    TEST BH, 7
    JZ nuovo_byte             ; ogni 8 bit → nuovo byte

salta:
    INC BH                    ; incrementa contatore bit

prova:
    TEST BL, 1
    JNZ passo_oltre           ; bit = 1 → fine sequenza zeri

    INC DH                    ; conta zeri consecutivi
    SHR BL, 1                 ; prossimo bit
    JMP ciclo

passo_oltre:
    SHR BL, 1

    CMP DL, DH
    JB L1                     ; aggiorna max se DH > DL
    JMP L2

L1:
    MOV DL, DH

L2:
    CMP CL, 0
    JZ L3
    CMP DH, 0
    JZ continua
    CMP CL, DH
    JB continua

L3:
    MOV CL, DH                ; aggiorna min se serve

continua:
    XOR DH, DH                ; reset contatore zeri
    CMP BH, CX
    JE fine
    JMP ciclo

nuovo_byte:
    INC EAX                   ; byte successivo
    MOV BL, vet[EAX]
    INC BH
    JMP prova

fine:
    CMP DL, 0
    JZ esci                   ; se nessuno zero trovato

    XOR CH, CH
    MOV word ptr [maxLung], DX
    MOV word ptr [minLung], CX
    JMP basta

esci:
    MOV word ptr [maxLung], -1
    MOV word ptr [minLung], -1

basta:*/
