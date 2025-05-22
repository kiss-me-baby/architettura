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
		;lunghezza massima
		XOR EAX, EAX; indice che scorre il vettore
		XOR ECX, ECX
		XOR EDX, EDX
		XOR EBX, EBX
		MOV CX, len

		MOV BL, vet[EAX]

		ciclo1: INC BH
		CMP BH, 8
		JE nuovo_byte1
		TEST BL, 1
		JNZ passo_oltre1
		INC DL
		SHR BL, 1
		LOOP ciclo1
		JMP fine1

		passo_oltre1 : SHR BL, 1
		CMP DH, DL
		JB da_cambiare1
		JMP intatto1

		da_cambiare1 : MOV DH, DL
		intatto1 : XOR DL, DL
		LOOP ciclo1
		JMP fine1

		nuovo_byte1 : XOR BH, BH
		INC EAX
		MOV BL, vet[EAX]
		JMP ciclo1

		fine1 : CMP DH, DL
		JB basso1
		JMP alto1

		basso1: XOR DH, DH
		MOV maxLung, DX
		JMP esci1

		alto1: XCHG DL, DH
		XOR DH, DH
		MOV maxLung, DX

		esci1:

		;lunghezza minima
		XOR EAX, EAX; indice che scorre il vettore
		XOR ECX, ECX
		XOR EDX, EDX
		XOR EBX, EBX
		MOV CX, len

		MOV BL, vet[EAX]

		ciclo2: INC BH
		CMP BH, 8
		JE nuovo_byte2
		TEST BL, 1
		JNZ passo_oltre2
		INC DL
		SHR BL, 1
		LOOP ciclo2
		JMP fine2

		passo_oltre2 : SHR BL, 1

		CMP DL, 0
		JZ intatto2
		CMP DH, 0
		JZ da_cambiare2
		CMP DH, DL
		JA da_cambiare2
		JMP intatto2

		da_cambiare2 : MOV DH, DL
		intatto2 : XOR DL, DL
		LOOP ciclo2
		JMP fine2

		nuovo_byte2 : XOR BH, BH
		INC EAX
		MOV BL, vet[EAX]
		JMP ciclo2

		fine2 : CMP DH, 0
		JZ esci2
		
		XCHG DL, DH
		XOR DH, DH
		
		esci2: CMP DL, 0
		JE nulla
		MOV minLung, DX
		JMP basta

		nulla: MOV minLung, -1

		basta:
		

	}

	// Stampa su video
	printf("Lunghezza minima delle sotto-sequenze di 0: %d\n", minLung);
	printf("Lunghezza massima delle sotto-sequenze di 0: %d\n", maxLung);
}
