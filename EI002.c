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

	__asm
	{
		LEA ESI, triangolo
		MOV EAX, 0 ;contatore dei livelli
		MOV [ESI], 1 ;livello 0 impostato di default

		CMP EAX, livello
		JE fine

		INC ESI ;livello 1 
		MOV [ESI], 1 
		INC [ESI], 1
		MOV [ESI], 1

		ciclo_esterno: CMP EAX, livello
		JE fine
		INC EAX ;cambio di livello
		INC ESI
		MOV [ESI], 1 ;salvo 1 nella prima pozione
		MOV ECX, EAX
		DEC ECX, 1 ;numero di volte da aggiungere un numero nel mezzo del vettore di quel livello
		
		ciclo_interno: INC ESI
		MOV EBX, ESI
		SUB EBX, EAX ;indice del primo elemento per ottenere il nuovo numero
		MOV EDX, triangolo[EBX]
		ADD EDX, triangolo[EBX-1] ;somma dei numeri in posizione indice-livello e indice-livello-1
		MOV ESI, EDX
		LOOP ciclo_interno
		INC ESI ;posizone ultimo 1 del livello corrente
		MOV [ESI], 1
		JMP ciclo_esterno ;salto al nuovo livello

		fine:


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


