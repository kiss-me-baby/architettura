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
		LEA ESI, testo; puntatore del vettore testo
LEA EDI, risultato; puntatore del vettore risultato
XOR EBX, EBX; indice vettore chiave
XOR EAX, EAX; registri per la somma o sottrazione
XOR EDX, EDX
MOV CL, decifra

ciclo : MOV DL, [ESI]; salvo nei registri i valori dei vettori
CMP DL, 0
JZ fine; salto alla fine se ho torvato il carattere 0 nel testo

MOV AL, chiave[EBX]

CMP CL, 0; in base a byte decifra sommo o sottraggo
JZ aggiungi
JNZ togli

aggiungi : ADD DL, AL
JMP ris

togli : SUB DL, AL
ris : MOV[EDI], DL; salvo il valore ottenuto nel vettore risultato e incremento gli indici
INC EDI
INC EBX
INC ESI
CMP chiave[EBX], 0
JNZ continua
XOR EBX, EBX; azzero la chiave se sono arrivato in fondo
continua : JMP ciclo

fine : MOV[EDI], 0; aggiungo lo zero alla fine del risultato
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


