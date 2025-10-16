# Relazione relativa all'Esercizio 3-4

## Descrizione Generale

L'esercizio 3-4 si concentra sull'implementazione e il testing di una struttura dati **grafo** generico in C, con supporto per nodi e archi etichettati, sia orientati che non orientati. Il progetto include anche l'integrazione con la libreria di testing **Unity** per la verifica automatica delle funzionalità implementate.

Il programma principale (`main_ex3-4.c`) permette di leggere un file CSV contenente la descrizione di un grafo, costruirlo in memoria, ed eseguire una visita in ampiezza (BFS) a partire da un nodo specificato, salvando l'ordine di visita su file.

## File Principali

### 1. `main_ex3-4.c`
- **Funzione principale**: Gestisce l'input da riga di comando, apre i file, invoca la funzione `bsf` per la visita in ampiezza e gestisce la chiusura dei file.
- **Input**:
  - Percorso del file CSV di input.
  - Nome del nodo di partenza per la BFS.
  - Percorso del file di output.
- **Output**: File contenente l'ordine di visita dei nodi.

### 2. `graph.c` e `graph.h`
- **Funzionalità principali**:
  - Creazione e distruzione di grafi generici.
  - Aggiunta/rimozione di nodi e archi (con o senza etichette).
  - Recupero di nodi, archi, vicini, etichette.
  - Supporto per grafi orientati e non orientati.
  - Implementazione della visita in ampiezza (BFS) tramite la funzione `breadth_first_visit`.

### 3. `hashTable.c` e `hash.h`
- **Funzionalità principali**:
  - Implementazione di una tabella hash generica per la gestione efficiente dei nodi e delle liste di adiacenza.
  - Funzioni di hash e confronto personalizzabili.
  - Supporto per keyset, inserimento, rimozione e ricerca.

### 4. `bfs.c`
- **Funzione principale**: `bsf`
  - Costruisce il grafo a partire dal file CSV.
  - Esegue la visita in ampiezza dal nodo specificato.
  - Scrive l'ordine di visita su file.

### 5. `test_ex3-4.c`
- **Funzioni di test**:
  - Verifica delle operazioni di base su grafi (aggiunta/rimozione nodi e archi, presenza, etichette, vicini, ecc.).
  - Test di casi limite (archi tra nodi non esistenti, rimozione di elementi non presenti).
  - Utilizzo della libreria **Unity** per l'automazione e la validazione dei test.

## Scelte Progettuali

- **Generalità**: Tutte le strutture sono progettate per essere generiche, accettando funzioni di confronto e hash come parametri.
- **Gestione della memoria**: La responsabilità della gestione della memoria per i dati dei nodi e delle etichette è lasciata al chiamante, mentre la struttura del grafo si occupa di liberare le proprie risorse interne.
- **Testing**: L'integrazione con Unity permette di garantire la correttezza delle operazioni fondamentali tramite test automatici ripetibili.

## Tempi di Esecuzione

I tempi di esecuzione sono stati misurati per le principali operazioni (costruzione del grafo, visita BFS) utilizzando la funzione `clock()` della libreria `<time.h>`. Esempio di output:


| Tipo di CPU                               | Lettura file e Creazione del Grafo        | BFS            |
|-------------------------------------------|-------------------------------------------|----------------|
| 11th Gen Intel(R) Core(TM) i7-11800H      | 0.07                                      | 0.03           |
| AMD Ryzen 7 7730U                         | 0.07                                      | 0.05           |



## Test

Sono stati sviluppati test unitari con Unity per coprire i seguenti scenari:

- Aggiunta e verifica di nodi e archi.
- Rimozione di nodi e archi.
- Recupero di vicini e etichette.
- Gestione di casi limite (nodi o archi non esistenti).
- Verifica della correttezza della visita in ampiezza.

Tutti i test sono stati eseguiti con successo, confermando la correttezza delle implementazioni.

## Conclusioni

- La struttura dati grafo è stata implementata in modo generico, efficiente e facilmente estendibile.
- L'integrazione con la tabella hash garantisce buone prestazioni anche su grafi di grandi dimensioni.
- I test automatici con Unity hanno permesso di validare tutte le funzionalità richieste.
- La soluzione soddisfa pienamente i requisiti dell'esercizio, fornendo una base solida per eventuali estensioni future (es. algoritmi di cammino minimo, DFS, ecc.).
