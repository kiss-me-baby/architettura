/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 1
 Descrizione:	Cifrare/decifrare il testo data la parola chiave. Nel testo cifrato
				il codice ASCII di ogni carattere � aumentato del codice ASCII del
				corrispondente carattere nella parola chiave sovrapposta (e ripetuta
				se necessario) al testo.

 ********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	char testo[] = "Chi non e' savio, paziente e forte, si lamenti di se', non della sorte";
	//char testo[] = "\x12\x67\x48\x5B\x5D\x63\x05\x59\x1B\x15\x67\x53\x61\x57\x4F\x49\x4B\x63\x57\x55\x68\x64\x12\x49\x2A\x12\x24\x3A\x2C";
	char chiave[] = "Password";
	char decifra = 0; // 0 = cifra; 1 = decifra

	// Output
	char risultato[1024];

	__asm
	{
		MOV CL, 0; indici del vettore
		MOV DL, 0


		ciclo: MOV AL, testo[ECX]; ciclo di copia e somma dei valori nel vettore
			MOV BL, chiave[EDX]
			ADD AL, BL
			MOV risultato[ECX], AL
			INC CL; incremento gli indici
			INC DL

			CMP testo[ECX], 0; controllo che non sia a fine testo o chiave
			JZ fine
			CMP chiave[EDX], 0
			JZ nuovo_inizio
			JMP ciclo

		nuovo_inizio : MOV DL, 0; azzera indice della chiave
			JMP ciclo

		fine :

	}

	// Stampa su video
	printf("Risultato: |%s|\n", risultato);
	{ // N.B. Nella stringa precedente alcuni caratteri possono non essere stampabili: 
	  //    crea anche una stringa con tutti i caratteri come codici ascii esadecimali
		char* t = risultato;
		while (*t)
		{
			printf("\\x%02X", (unsigned char)(*t++));
		}
	}
}


