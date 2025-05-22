MOV EAX, 0; contatore dei livelli
XOR EDX, EDX; indice del vettore
MOV triangolo[EDX], 1; livello 0 impostato di forza

CMP EAX, livello; esco se ho raggiunto il livello chiesto
JE fine

INC EAX; procedura per il livello 1
ADD EDX, 4; livello 1
MOV triangolo[EDX], 1
ADD EDX, 4
MOV triangolo[EDX], 1

ciclo_esterno: CMP EAX, livello
JE fine
INC EAX; cambio di livello
ADD EDX, 4
MOV triangolo[EDX], 1; imposto 1 nella prima pozione
MOV ECX, EAX
DEC ECX; numeri da aggiungere nel mezzo del vettore di quel livello

ciclo_interno : ADD EDX, 4
MOV EBX, EDX
PUSH EAX; mi tengo salvato il valore del livello
IMUL AX, 4
SUB EBX, EAX; indice del primo elemento per ottenere il nuovo numero
XOR EAX, EAX
MOV EAX, triangolo[EBX]
ADD EAX, triangolo[EBX - 4]; somma dei numeri in posizione indice - livello e indice - livello - 1
MOV triangolo[EDX], EAX
POP EAX
LOOP ciclo_interno; quando devo completare il livello interno
ADD EDX, 4; posizone ultimo 1 del livello corrente
MOV triangolo[EDX], 1
JMP ciclo_esterno; salto al nuovo livello

fine :
