
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

inizio :
MOV AL, BH
	CMP AX, len; fine dei bit
	JE fine
	CMP BH, 0
	JZ salta
	TEST BH, 7; fine byte
	JZ nuovo_byte

	salta :
INC BH

	TEST BL, 1
	JNZ passo_oltre
	INC DH; incremento sequenza zeri
	SHR BL, 1
	JMP inizio

	passo_oltre :
	CMP DL, DH; confronta con max
	JB aumento
	JMP L1

	aumento :
MOV DL, DH; aggiorna max

	L1 :
CMP CL, 0
	JZ per_forza
	CMP DH, 0
	JZ continua
	CMP CL, DH; confronta con min
	JB continua

	per_forza :
MOV CL, DH; aggiorna min

	continua :
XOR DH, DH
	SHR BL, 1; scorro bit
	JMP inizio

	nuovo_byte :
MOV AL, BH; passo al byte successivo
	SHR AL, 3; AL = BH / 8
	MOVZX EAX, AL; estende AL a EAX
	MOV BL, vet[EAX]
	JMP salta

	fine :
CMP DL, DH; confronta con max
	JB cresce
	JMP L11

	cresce :
MOV DL, DH; aggiorna max

	L11 :
CMP CL, 0
	JZ per_forza1
	CMP DH, 0
	JZ continua1
	CMP CL, DH; confronta con min
	JB continua1

	per_forza1 :
MOV CL, DH; aggiorna min

	continua1 :
XOR DH, DH
	XOR CH, CH
	CMP DL, 0
	JNZ salvataggio_finale
	CMP CL, 0
	JNZ salvataggio_finale
	JMP esci

	salvataggio_finale :
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

