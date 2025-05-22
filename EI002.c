/********************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 2
Descrizione: Dato in input il livello massimo richiesto, restituire il rispettivo
			 triangolo di Tartaglia memorizzando consecutivamente i vari livelli
			 all'interno di un array monodimensionale.

********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	unsigned int livello = 8;		// livello massimo del triangolo di tartaglia da generare

	// Output
	unsigned int triangolo[1024];	// risultato: il vettore contiene i numeri del 
	// triangolo dal livello 0 al più alto richiesto

	unsigned int i;
	unsigned int k = 0;

	__asm{
		MOV EAX, 0; contatore dei livelli
		XOR EDX, EDX
		MOV triangolo[EDX], 1; livello 0 impostato di forza

		CMP EAX, livello
		JE fine

		ADD EDX, 4; livello 1
		MOV triangolo[EDX], 1
		ADD EDX, 4
		MOV triangolo[EDX], 1

		ciclo_esterno: CMP EAX, livello
		JE fine
		INC EAX; cambio di livello
		ADD EDX, 4
		MOV triangolo[EDX], 1; salvo 1 nella prima pozione
		MOV ECX, EAX
		DEC ECX; numero di volte da aggiungere un numero nel mezzo del vettore di quel livello

		ciclo_interno :
		ADD EDX, 4
		MOV EBX, EDX
		PUSH EAX
		IMUL AX, 4
		SUB EBX, EAX; indice del primo elemento per ottenere il nuovo numero 
		XOR EAX, EAX
		MOV EAX, triangolo[EBX]
		ADD EAX, triangolo[EBX - 4]; somma dei numeri in posizione indice - livello e indice - livello - 1
		MOV triangolo[EDX], EAX
		POP EAX
		LOOP ciclo_interno
		ADD EDX, 4; posizone ultimo 1 del livello corrente
		MOV triangolo[EDX], 1
		JMP ciclo_esterno; salto al nuovo livello

		fine :

	}

	// Stampa su video
	printf("Triangolo di Tartaglia fino al livello %d\n", livello);
	for (i = 0; i <= livello; i++)
	{
		unsigned int j;
		for (j = 0; j <= i; j++)
			printf("%d ", triangolo[k++]);
		printf("\n");
	}
}
