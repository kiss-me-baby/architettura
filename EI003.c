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
	unsigned char vet[] = {0xC6,0x1F,0x14,0x94,0x8A,0x95,0x93,0xAD,0xE5,0x69,0xAE,0xE4,0x2A,0xDC,0x54,0xC0,0xFB,0xA2,0xB8,0x2E,0x56,0xD8,0x1D,0x89,0x72,0x8A,0x16,0x54,0x3E,0x1A,0xC9,0x66,0x25,0xED,0x0B,0x69};	// Sequenza di bit
	unsigned short int len = 288;				// Lunghezza (in bit) della sequenza
    // Risultato corretto:
    //minLung = 1
    //maxLung = 7
	// Output
	short int minLung;		// Lunghezza minima sotto-sequenza di 0
	short int maxLung;		// Lunghezza massima sotto-sequenza di 0

	__asm
	{
		XOR EAX, EAX; indice sul vettore
XOR ECX, ECX; contatore bit
XOR EDX, EDX; maxLung(DL)
XOR EBX, EBX; BH = minLung, BL = byte corrente

MOV BL, vet[EAX]; carica il primo byte

inizio :
CMP CX, len; fine dei bit
	JE fine
	CMP CX, 0
	JZ salta
	TEST CX, 7; fine byte
	JZ nuovo_byte

	salta :
INC CX

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
CMP BH, 0
	JZ per_forza
	CMP DH, 0
	JZ continua
	CMP BH, DH; confronta con min
	JB continua

	per_forza :
MOV BH, DH; aggiorna min

	continua :
XOR DH, DH
	SHR BL, 1; scorro bit
	JMP inizio

	nuovo_byte : 
	MOV AX, CX
	SHR AX, 3; CX / 8
	MOV BL, vet[EAX]
	JMP salta

	fine :
CMP DL, DH; confronta con max
	JB cresce
	JMP L11

	cresce :
MOV DL, DH; aggiorna max

	L11 :
CMP BH, 0
	JZ per_forza1
	CMP DH, 0
	JZ continua1
	CMP BH, DH; confronta con min
	JB continua1

	per_forza1 :
MOV BH, DH; aggiorna min

	continua1 :
XOR DH, DH
	MOV CL, BH; muovo lunghezza minima in CL
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
