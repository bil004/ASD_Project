# Relazione relativa all'Esercizio 2

## Descrizione Generale

L'esercizio implementa un programma per esaminare un file di testo (`correctme`) utilizzando un dizionario di riferimento (`dictionary`). La correzione avviene calcolando la **edit distance** tra le parole del file da esaminare e quelle del dizionario, scegliendo la prima parola più simile.

Il programma principale (`main_ex2.c`) legge i file di input, utilizza le funzioni definite nei moduli per elaborare i dati e stampa i risultati, inclusi i tempi di esecuzione.

## File Principali

### 1. `main_ex2.c`
- **Funzione principale**: Gestisce l'input da riga di comando, apre i file, chiama la funzione `correctFile` e misura i tempi di esecuzione.
- **Input**:
  - Percorso del file dizionario.
  - Percorso del file da correggere.
- **Output**: Correzione delle parole stampata su console, con la prima parola trovata, la parola corretta e la distanza di edit.

### 2. `correctFile.c`
- **Funzione principale**: `correctFile`.
  - Legge le parole dal dizionario e le memorizza in una struttura `Dictionary`.
  - Legge le parole dal file da correggere, rimuove la punteggiatura e le converte in minuscolo.
  - Per ogni parola, calcola la **edit distance** con tutte le parole del dizionario e seleziona la parola con la distanza minima.
  - Stampa i risultati su console.
- **Funzioni ausiliarie**:
  - `findSize`: Calcola il numero di righe in un file.
  - `deletePunct`: Rimuove la punteggiatura da una stringa.
  - `toLowerCase`: Converte una stringa in minuscolo.

### 3. `editDistance.c`
- Contiene le implementazioni delle funzioni per calcolare la **edit distance**:
  - `edit_distance`: Calcolo ricorsivo della distanza di edit.
  - `edit_distance_dyn`: Calcolo della distanza di edit utilizzando la programmazione dinamica.
  - `edit_distance_dynA`: Variante che utilizza una matrice per ottimizzare il calcolo.

### 4. `edit.h`
- Contiene le dichiarazioni delle funzioni e la definizione della struttura `Dictionary`.

## Test

Per verificare la correttezza delle funzioni implementate, sono stati sviluppati test unitari utilizzando la libreria **Unity**. I test coprono diversi scenari, inclusi casi limite, per garantire che le funzioni producano risultati corretti in tutte le situazioni.

### File Principale dei Test

#### `test_ex2.c`
- **Funzioni di Test**:
  - `test_edit_distance`: Verifica che la funzione `edit_distance` calcoli correttamente la distanza di edit tra due stringhe.
  - `test_edit_distance_dyn`: Controlla che la funzione `edit_distance_dyn` produca risultati corretti utilizzando la programmazione dinamica.
  - `test_edit_distance_dynA`: Verifica che la variante `edit_distance_dynA` ottimizzi il calcolo della distanza di edit.

### Risultati dei Test

Tutti i test sono stati eseguiti con successo, confermando la correttezza delle implementazioni. I test sono stati eseguiti su diverse piattaforme per garantire la portabilità del codice.

### Conclusioni sui Test

- I test hanno dimostrato che le funzioni per il calcolo della **edit distance** producono risultati corretti sia con l'approccio ricorsivo che con la programmazione dinamica.
- La funzione `correctFile` è stata verificata per garantire che le parole vengano corrette correttamente, con la rimozione della punteggiatura e la conversione in minuscolo.
- L'uso della libreria **Unity** ha facilitato lo sviluppo e l'esecuzione dei test, migliorando la qualità complessiva del codice.



## Tempi di Esecuzione

I tempi di esecuzione sono stati misurati utilizzando la funzione `clock()` della libreria `<time.h>`, eseguito per 10 volte per poi calcolare una media(manuale).  le dimensioni dei datatest sono: dizionario(elenco di parole corrette) = 661562 parole, file da correggere = 49 parole:

| Tipo di CPU                               | Tempo di ricerca media di 10 esecuzioni (secondi)     | Miglior Tempo (secondi) | Peggior Tempo (secondi) |
|-------------------------------------------|-------------------------------------------------------|-------------------------|-------------------------|
| 11th Gen intel(R) Core(TM) i7-11800H      | 32.16                                                 | 29.79                   | 44.67                   |
| AMD Ryzen 7 7730U                         | 32.71                                                 | 32.21                   | 33.51                   |

## Conclusioni

- L'uso della programmazione dinamica per il calcolo della **edit distance** migliora significativamente le prestazioni rispetto all'approccio ricorsivo puro.
- Il tempo di esecuzione cresce linearmente con il numero di parole nel file da correggere e nel dizionario.
- La funzione edit_distance (anche la versione dyn), quando deve "correggere" il file, prende la prima parola con la minima distanza. Per questo alcune parole non sono quelle che ci si aspetta, purché si implementi un filtro che permetta di riconoscere il contesto.

### Possibili Ottimizzazioni

1. **Parallelizzazione**: Suddividere il calcolo della **edit distance** tra più thread per migliorare le prestazioni su sistemi multi-core.
2. **Strutture Dati Ottimizzate**: Utilizzare strutture dati come alberi di ricerca o tabelle hash per ridurre il numero di confronti necessari.
3. **Filtraggio Preliminare**: Applicare un filtro preliminare per ridurre il numero di parole del dizionario da confrontare con ogni parola del file da correggere.
4. **output multipli**: Creare una lista di parole con la stessa **edit distance** che potrebbero essere usate per correggere il file