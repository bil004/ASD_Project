# Relazione relativa all'Esercizio 1

## Descrizione Generale

L'esercizio implementa due algoritmi di ordinamento generico: **Merge Sort** e **Quick Sort**. Entrambi gli algoritmi sono progettati per ordinare array di strutture `Records` in base a uno dei tre campi: `name`, `integerNum` o `floatNum`.

Il programma principale (`main.c`) permette di leggere un file CSV contenente i record, ordinarli utilizzando uno degli algoritmi selezionati e salvare i risultati in un file di output.

## File Principali

### 1. `main.c`
- **Funzione principale**: Gestisce l'input da riga di comando, apre i file, chiama la funzione `sort_records` e misura i tempi di esecuzione.
- **Input**: 
  - Percorso del file di input.
  - Percorso del file di output.
  - Campo su cui ordinare (1: `name`, 2: `integerNum`, 3: `floatNum`).
  - Algoritmo da utilizzare (1: Merge Sort, 2: Quick Sort).
- **Output**: File ordinato e tempo di esecuzione stampato su console.

### 2. `sortFiles.c`
- **Funzione principale**: `sort_records`.
  - Legge i record dal file di input.
  - Ordina i record utilizzando l'algoritmo e il campo specificati.
  - Scrive i record ordinati nel file di output.
- **Funzione ausiliaria**: `findSize` per calcolare il numero di righe nel file di input.

### 3. `order.c`
- Contiene le funzioni di confronto (`compar_name`, `compar_integerNum`, `compar_floatNum`) e le implementazioni di **Merge Sort** e **Quick Sort**.

## Scelta dell'Algoritmo di Partizionamento

Per l'implementazione di **Quick Sort**, abbiamo scelto di utilizzare lo schema di partizionamento di **Hoare**. Questa scelta è motivata dal fatto che il metodo di Hoare è generalmente più efficiente rispetto al partizionamento di Lomuto, in quanto riduce il numero di scambi necessari durante la partizione. Inoltre, lo schema di Hoare tende a funzionare meglio in termini di prestazioni su array di grandi dimensioni, poiché minimizza il costo complessivo delle operazioni di partizionamento.

## Tempi di Esecuzione

I tempi di esecuzione sono stati misurati utilizzando la funzione `clock()` della libreria `<time.h>`. I test sono stati eseguiti su un dataset di 20.000.000 record con i seguenti risultati:


### `i dati sono in media di 3 esecuzioni`

- Computer di Angela Luca (11th Gen intel(R) Core(TM) i7-11800H)


| Campo Ordinato | Algoritmo   | Tempo di sorting (secondi)    | tempo di scrittura (secondi)  | tempo totale (secondi) |
|----------------|-------------|-------------------------------|-------------------------------|------------------------|
| `name`         | Merge Sort  | 16.23                         | 22.45                         | 42.26                  |
| `name`         | Quick Sort  | 16.08                         | 27.57                         | 43.65                  |
| `integerNum`   | Merge Sort  | 17.50                         | 29.06                         | 46.57                  |
| `integerNum`   | Quick Sort  | 14.00                         | 31.70                         | 45.70                  |
| `floatNum`     | Merge Sort  | 19.11                         | 30.96                         | 50.07                  |
| `floatNum`     | Quick Sort  | 15.70                         | 31.77                         | 47.47                  |


- Computer di Benslimane Bilal (AMD Ryzen 7 7730U)

| Campo Ordinato | Algoritmo   | Tempo di sorting (secondi)    | tempo di scrittura (secondi)  | tempo totale (secondi) |
|----------------|-------------|-------------------------------|-------------------------------|------------------------|
| `name`         | Merge Sort  | 11.80                         | 15.68                         | 27.48                  |
| `name`         | Quick Sort  | 12.11                         | 15.96                         | 28.07                  |
| `integerNum`   | Merge Sort  | 10.81                         | 18.02                         | 28.83                  |
| `integerNum`   | Quick Sort  | 8.97                          | 16.04                         | 25.01                  |
| `floatNum`     | Merge Sort  | 11.08                         | 15.83                         | 26.91                  |
| `floatNum`     | Quick Sort  | 9.72                          | 15.83                         | 25.55                  |

## Test

Per verificare la correttezza degli algoritmi implementati, sono stati sviluppati test unitari utilizzando la libreria **Unity**. I test coprono diversi scenari, inclusi casi limite, per garantire che gli algoritmi funzionino correttamente in tutte le situazioni.

### File Principale dei Test

#### `test_ex1.c`
- **Funzioni di Test**:
  - `test_array_empty`: Verifica che gli algoritmi gestiscano correttamente array vuoti.
  - `test_array_equals`: Controlla che Merge Sort e Quick Sort producano lo stesso risultato su array ordinati.
  - `test_array_not_equals`: Verifica che array con tipi di dati diversi non siano uguali dopo l'ordinamento.
  - `test_swap_empty_elements`: Testa la funzione `swap` con elementi vuoti.
  - `test_swap`: Verifica che la funzione `swap` scambi correttamente due elementi.
  - `test_partition`: Controlla che la funzione `partition` divida correttamente l'array rispetto al pivot.
  - `test_quick_sort_order`: Verifica che Quick Sort ordini correttamente un array di interi.
  - `test_merge_sort_order`: Verifica che Merge Sort ordini correttamente un array di interi.
  - `test_sort_records`: Testa la funzione `sort_records` con un file di input e verifica che i record siano ordinati correttamente.
  - `test_merge_sort_function`: Verifica che Merge Sort ordini correttamente un array di strutture `Records` in base al campo `name`.
  - `test_quick_sort_function`: Verifica che Quick Sort ordini correttamente un array di strutture `Records` in base al campo `integerNum`.

### Risultati dei Test

Tutti i test sono stati eseguiti con successo, confermando la correttezza delle implementazioni. I test sono stati eseguiti su diverse piattaforme per garantire la portabilità del codice.

### Conclusioni sui Test

- I test hanno dimostrato che gli algoritmi di ordinamento funzionano correttamente per array di diverse dimensioni e tipi di dati.
- La funzione `sort_records` è stata verificata per garantire che i file di input vengano ordinati correttamente e salvati nel file di output.
- L'uso della libreria **Unity** ha facilitato lo sviluppo e l'esecuzione dei test, migliorando la qualità complessiva del codice.

## Conclusioni

- **Merge Sort** e **Quick Sort** hanno prestazioni simili per dataset di piccole dimensioni.
- **Quick Sort** tende a essere leggermente più veloce, ma la differenza è trascurabile.
- Entrambi gli algoritmi sono stati implementati in modo generico, rendendoli riutilizzabili per diversi tipi di dati.

La soluzione soddisfa i requisiti dell'esercizio e fornisce un'implementazione robusta e ben testata degli algoritmi di ordinamento.
