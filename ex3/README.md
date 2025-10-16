# Relazione ex3

## Descrizione Generale

L'esercizio implementa un programma per analizzare un file di testo e determinare la parola più frequente con una lunghezza minima specificata. Il programma utilizza una tabella hash per memorizzare e contare le occorrenze delle parole, ottimizzando così le operazioni di ricerca e aggiornamento.

Il programma principale (`main_ex3.c`) legge i file di input, utilizza le funzioni definite nei moduli per elaborare i dati e stampa i risultati.

## File Principali

### 1. `main_ex3.c`
- **Funzione principale**: Gestisce l'input da riga di comando, apre i file, chiama la funzione `processFile` e stampa i risultati.
- **Input**:
  - Percorso del file sorgente.
  - Lunghezza minima delle parole da considerare.
- **Output**: La parola più frequente con la lunghezza minima specificata e il numero di occorrenze.

### 2. `processFile.c`
- **Funzione principale**: `processFile`.
  - Legge le parole dal file sorgente.
  - Rimuove la punteggiatura e converte le parole in minuscolo.
  - Utilizza una tabella hash per contare le occorrenze delle parole.
  - Determina la parola più frequente con una lunghezza minima specificata.
  - Stampa i risultati su console.

### 3. `hashTable.c`
- Contiene l'implementazione delle funzioni per la gestione della tabella hash:
  - Creazione, inserimento, ricerca, rimozione e liberazione della memoria.
  - Funzioni ausiliarie per ottenere il numero di elementi e l'insieme delle chiavi.

## Test

Per verificare la correttezza delle funzioni implementate, sono stati sviluppati test unitari utilizzando la libreria **Unity**. I test coprono diversi scenari, inclusi casi limite, per garantire che le funzioni producano risultati corretti in tutte le situazioni.

### File Principale dei Test

#### `test_ex3.c`
- **Funzioni di Test**:
  - `test_hash_table_put_and_get`: Verifica l'inserimento e il recupero di elementi nella tabella hash.
  - `test_hash_table_contains_key`: Controlla la presenza di una chiave nella tabella hash.
  - `test_hash_table_remove`: Verifica la rimozione di una chiave dalla tabella hash.
  - `test_hash_table_size`: Controlla il numero di elementi nella tabella hash.
  - `test_hash_table_keyset`: Verifica il recupero dell'insieme delle chiavi.

### Risultati dei Test

Tutti i test sono stati eseguiti con successo, confermando la correttezza delle implementazioni. I test sono stati eseguiti su diverse piattaforme per garantire la portabilità del codice.

### Conclusioni sui Test

- I test hanno dimostrato che le funzioni della tabella hash funzionano correttamente in tutti gli scenari testati.
- La funzione `processFile` è stata verificata per garantire che le parole vengano elaborate correttamente, con la rimozione della punteggiatura e la conversione in minuscolo.

## Tempi di Esecuzione

I tempi di esecuzione sono stati misurati utilizzando la funzione `clock()` della libreria `<time.h>`. I risultati mostrano che l'uso della tabella hash rende il programma efficiente anche con file di grandi dimensioni.

| Tipo di CPU                               | Tempo di esecuzione lenght = 1 (secondi) | Tempo di esecuzione lenght = 6 (secondi) |
|-------------------------------------------|------------------------------------------|------------------------------------------|
| 11th Gen Intel(R) Core(TM) i7-11800H      | 0.17                                     | 0.11                                     |
| AMD Ryzen 7 7730U                         | 0.15                                     | 0.09                                     |

## Conclusioni

- L'uso della tabella hash ha migliorato significativamente le prestazioni rispetto a un approccio basato su strutture dati meno efficienti.
- Il programma è in grado di gestire file di grandi dimensioni in tempi ragionevoli.
- La modularità del codice facilita l'estensione e la manutenzione.
- Abbiamo riscontrato un errore riguardante la parola 'the', presente all'interno di `iliade.txt`. Alcune occorrenze (3 su 9958) non vengono considerate dal programma.

### Possibili Ottimizzazioni

1. **Espansione Dinamica della Tabella Hash**: Implementare una strategia per ridimensionare dinamicamente la tabella hash in base al numero di elementi.
2. **Filtraggio Preliminare**: Applicare un filtro preliminare per ignorare parole non rilevanti prima di inserirle nella tabella hash.

## Prompt utilizzati
L'esercizio è stato svolto tramite l'utilizzo di Copilot/Copilot github secondo i seguenti prompt:

1. **Testo dell'esercizio**: Abbiamo incollato nella chat dell'IA il testo chiedendo:
- il concetto alla base
- suggerimenti riguardo alla struttura (Nodi e la struct relativa alla tabella Hash)

2. **Implementazione delle funzioni**: impostando i vari file, abbiamo chiesto come devono essere implementate le funzioni. 

- In `processFile.c`, abbiamo aperto il file 'iliade.txt' e organizzato le parole all'interno della Hash table, eliminando i vari caratteri speciali. Dopodiché identifica le parole più utilizzate e calcola il tempo impiegato

- In `hashTable.c`, abbiamo implementato le funzioni secondo le specifiche dell'esercizio

- In `main_ex3.c`, avviamo l'intero programma passandogli come parametro il documento di riferimento e la lunghezza minima da considerare

3. **Inserimento di alcune funzioni ausiliarie**: Abbiamo utilizzato alcune funzioni ausiliarie (`compare_strings`, `hash_string`) utili per lo svolgimento corretto della consegna e per la pulizia generale del codice.

4. **Creazione dei test**: L'IA ha individuato e creato alcuni test per le funzioni utilizzate. La creazione dei test è stata realizzata utilizzando la libreria Unity.