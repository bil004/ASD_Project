# Algorithms and Data Structures

# Informazioni preliminari

Repository contenente il progetto di Algoritmi e Strutture Dati dell'anno accademico 2024/25.



## Esercizio 1 - Merge Sort e Quick Sort

### Testo

Implementare una libreria che offre gli algoritmi di ordinamento  *Merge Sort* e *Quick Sort* su dati generici, implementando i seguenti prototipi di funzione:

```
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array da ordinare;
- `nitems` è il numero di elementi nell'array da ordinare;
- `size` è la dimensione in bytes di ogni elemento dell'array;
- `compar` è il criterio secondo cui ordinare i dati (dati due **puntatori a elementi** dell'array, restituisce un numero maggiore, uguale o minore di zero se il primo argomento è rispettivamente maggiore, uguale o minore del secondo).

È anche possibile implementare in alternativa i seguenti prototipi, che ordinano dati a patto che siano organizzati in un array di puntatori:

```
void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));
```

- `base` è un puntatore al primo elemento dell'array di puntatori da ordinare sulla base dei valori riferiti;
- `nitems` è il numero di elementi nell'array di puntatori da ordinare;
- `compar` è il criterio secondo cui ordinare i dati (dati due **elementi** dell'array di puntatori).

Dato che la prima versione è anche in grado di ordinare array di puntatori (passando un comparatore opportuno, i cui argomenti saranno puntatori a puntatori ai dati), non serve implementare questa seconda versione se avete già implementato la prima. In ogni caso non serve neanche implementare la prima se avete già implementato la seconda.

### Unit Testing

Implementare gli unit-test per la libreria secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Uso della libreria di ordinamento implementata

Il file `records.csv` che potete trovare (compresso) all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7](https://datacloud.di.unito.it/index.php/s/9sQmzB9TdDHezX7)

contiene 20 milioni di record da ordinare.
Ogni record è descritto su una riga e contiene i seguenti campi:

- `id`: (tipo intero) identificatore univoco del record;
- `field1`: (tipo stringa) contiene parole estratte dalla divina commedia,
  potete assumere che i valori non contengano spazi o virgole;
- `field2`: (tipo intero);
- `field3`: (tipo floating point).

Il formato è un CSV standard: i campi sono separati da virgole; i record sono
separati da `\n`.

Usando l'algoritmo implementato precedentemente, si realizzi la seguente funzione per ordinare *record* contenuti nel file `records.csv` in ordine non decrescente secondo i valori contenuti nei tre campi "field".

```
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);
```

- `infile` è il file contenente i record da ordinare;
- `outfile` è il file nel quale salvare i record ordinati (che deve essere diverso da `infile`);
- `field` può valere 1, 2 o 3 e indica quale dei tre campi deve essere usato per ordinare i record.
- `algo` può valere 1 o 2 e indica quale algoritmo di ordinamento deve essere usato (MergeSort o QuickSort) per ordinare i record.

Si misurino i tempi di risposta per i due algoritmi, per ciascuno dei tre field che si possono usare come chiave di ordinamento, e si produca una breve relazione in cui si riportano i risultati ottenuti insieme a un loro commento. Il commento deve essere basato su statistiche numeriche sui tempi di esecuzione misurati. Nel caso l'ordinamento si protragga per più di 10 minuti potete interrompere l'esecuzione e riportare un fallimento dell'operazione. I risultati sono quelli che vi sareste aspettati? Se sì, perché? Se no, fate delle ipotesi circa il motivo per cui gli algoritmi non funzionano come vi aspettate, verificatele e riportate quanto scoperto nella relazione. I risultati dipendono dal campo usato come chiave di ordinamento?

**Si ricorda che il file `records.csv` (e i file compilati) NON DEVONO ESSERE OGGETTO DI COMMIT SU GIT!**


## Esercizio 2 - Edit distance

### Testo

Si consideri il problema di determinare la minima distanza di edit tra due stringhe (_edit distance_): date due stringhe $s_1$ e $s_2$, non necessariamente della stessa lunghezza, determinare il minimo numero di operazioni necessarie per trasformare la stringa $s_2$ in $s_1$. Si assuma che le operazioni disponibili siano solo due: **cancellazione** e **inserimento**. Per esempio:

- "casa" e "cassa" hanno edit distance pari a 1 (1 cancellazione);
- "casa" e "cara" hanno edit distance pari a 2 (1 cancellazione + 1 inserimento);
- “vinaio” e “vino” hanno edit distance=2 (2 inserimenti);
- "tassa" e "passato" hanno edit distance pari a 4 (3 cancellazioni + 1 inserimento);
- "pioppo" e "pioppo" hanno edit distance pari a 0.

Si implementi innanzitutto una funzione ricorsiva di calcolo della edit distance, implementando il seguente prototipo di funzione:

```
int edit_distance(const char *s1, const char* s2);
```

- `s1` è la stringa che si vuole ottenere $s_1$;
- `s2` è la stringa di partenza $s_2$.

La struttura della funzione deve rispecchiare la seguente definizione (indichiamo con $|s|$ la lunghezza di $s$ e con $\mathrm{rest}(s)$ la sottostringa di $s$ ottenuta ignorando il primo carattere di $s$):

- se $|s_1|$ = 0, allora $\mathrm{edit\_distance}(s_1,s_2) = |s_2|$;
- se $|s_2|$ = 0, allora $\mathrm{edit\_distance}(s_1,s_2) = |s_1|$;
- altrimenti, siano:
  - $d_{\mathrm{no-op}} = \mathrm{edit\_distance}(\mathrm{rest}(s1),\mathrm{rest}(s2))$   se $s1[0]=s2[0]$, $\infty$ altrimenti
  - $d_{\mathrm{canc}} = 1 + \mathrm{edit\_distance}(s1,\mathrm{rest}(s2))$
  - $d_{\mathrm{ins}} = 1 + \mathrm{edit\_distance}(\mathrm{rest}(s1),s2)$

Si ha quindi che: $\mathrm{edit\_distance}(s_1,s_2) = \min\{d_{\mathrm{no-op}}, d_{\mathrm{canc}}, d_{\mathrm{ins}}\}$.

In seguito, si implementi anche una versione della funzione di calcolo della edit distance che adotta una strategia di programmazione dinamica. Tale versione deve essere anch'essa ricorsiva (in particolare, essa deve essere ottenuta attraverso un insieme minimale di modifiche apportate all'implementazione richiesta al punto precedente). La funzione deve implementare il seguente prototipo:

```
int edit_distance_dyn(const char *s1, const char* s2);
```

*Nota*: Le definizioni sopra riportate non corrispondono al modo usuale di definire la distanza di edit. Sono comunque quelle necessarie a risolvere l'esercizio e su cui dovrà essere basato il codice prodotto.

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Uso delle funzioni implementate

All'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB](https://datacloud.di.unito.it/index.php/s/9BKY7BXFCY4bMcB)

potete trovare un dizionario (`dictionary.txt`) e un file da correggere (`correctme.txt`).

Il dizionario contiene un elenco di parole. Le parole sono scritte di seguito, ciascuna su una riga.

Il file `correctme.txt` contiene un testo da correggere. Alcune parole in questo testo non ci sono nel dizionario.

Si implementi un'applicazione che usa la funzione `edit_distance_dyn` per determinare, per ogni parola `w` in `correctme.txt`, una breve lista di parole in `dictionary.txt` con edit distance minima da `w`. Si sperimenti il funzionamento dell'applicazione e si riporti in una breve relazione i risultati degli esperimenti.

**Si ricorda** che i file `dictionary.txt` e `correctme.txt` non devono essere oggetto di commit su git!


## Esercizio 3 - Tavole hash (con concatenamento)


### Testo

Si implementi, avvalendosi del supporto di un sistema basato su un Large Language Model, quale, ad esempio, ChatGPT (si veda sotto), una libreria generica che realizza la struttura dati *tavola hash (con concatenamento)* in grado di ospitare un insieme di coppie {<chiave_1,valore_1>,...,<chiave_n,valore_n>}.

La tavola hash deve accettare chiavi e valori di tipi generici (tutte le chiavi hanno uno stesso tipo, tutti i valori hanno uno stesso tipo, ma chiavi e valori possono avere tipi fra loro differenti).

La struttura dati deve offrire almeno le seguenti funzionalità (ricavare il significato delle varie funzioni e procedure e dei loro parametri a partire dai loro prototipi e da quanto studiato nella parte di teoria del corso):

```
HashTable* hash_table_create(int (*f1)(const void*,const void*), unsigned long (*f2)(const void*));
void hash_table_put(HashTable*, const void*, const void*);
void* hash_table_get(const HashTable*, const void*);
int hash_table_contains_key(const HashTable*, const void*);
void hash_table_remove(HashTable*, const void*);
int hash_table_size(const HashTable*);
void** hash_table_keyset(const HashTable*);
void hash_table_free(HashTable*);
```

### Unit Testing

Implementare avvalendosi del supporto di un sistema basato su un Large Language Model (LLM), quale, ad esempio, ChatGPT (si veda sotto), gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Uso delle funzioni implementate

All'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/Ti4Mz7j4Xtjn3Db](https://datacloud.di.unito.it/index.php/s/Ti4Mz7j4Xtjn3Db)

potete trovare un file (`iliade.txt`) contenente l'Iliade di Omero in inglese.

Avvalendosi di un sistema basato su LLM, scrivere un programma che utilizza l'hash table implementata per calcolare la parola di lunghezza almeno pari ad un valore minimo dato che sia più frequente nel file di testo dato.

### Uso di sistema basato su un Large Language Model

Si richiede che per implementare quanto richiesto dal presente esercizio ci si avvalga del supporto di un sistema basato su un Large Language Model, quale, ad esempio, ChatGPT.

E' possibile che il processo di sviluppo risulti iterativo, comportando varie interazioni con il sistema LLM.

Si documenti, in una relazione (README.md su git), il suddetto processo di sviluppo nei suoi aspetti principali (prompt iniziale, output prodotto dal sistema, analisi critica dell'output, raffinamento del prompt, ecc.) e si riportino alcune considerazioni generali sull'intero processo.

## Esercizio 4 - Grafi sparsi e Visita in Ampiezza

### Linguaggio richiesto: C

### Testo

Si implementi una libreria che realizza la struttura dati *Grafo* in modo che sia ottimale per dati sparsi
(**attenzione**: le scelte implementative che farete dovranno essere giustificate in relazione alle nozioni presentate
durante le lezioni in aula).

È richiesto che l'implementazione sfrutti la Tavola Hash implementata nell'esercizio 3.

L'implementazione deve essere generica sia per quanto riguarda il tipo dei nodi, sia per quanto riguarda le etichette
degli archi, implementando le funzioni riportate nel seguente header file (con requisiti minimi di complessità; dove _N_ può indicare il numero di nodi o il numero di archi, a seconda del contesto):

```
graph.h

typedef struct graph *Graph;

typedef struct edge {
   void* source; //nodo d'origine
   void* dest; //nodo di destinazione
   void* label; //etichetta dell'arco
}Edge;

Graph graph_create(int labelled, int directed,
                     int (*compare)(const void*, const void*),
                     unsigned long (*hash)(const void*));

//crea un grafo vuoto, etichettato se labelled == 1 e diretto se directed == 1,
//le funzioni f1 e f2 sono necessarie per la costruzione della tavola hash che deve essere usata dalla libreria -- O(1)

int graph_is_directed(const Graph gr);                                                           // dice se il grafo è diretto o meno -- O(1)
int graph_is_labelled(const Graph gr);                                                           // dice se il grafo è etichettato o meno -- O(1)
int graph_add_node(Graph gr, const void* node);                                                  // aggiunge un nodo -- O(1)
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);           // aggiunge un arco dati estremi ed etichetta -- O(1) (*)
int graph_contains_node(const Graph gr, const void* node);                                       // controlla se un nodo è nel grafo -- O(1)
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);                   // controlla se un arco è nel grafo -- O(1) (*)
int graph_remove_node(Graph gr, const void* node);                                               // rimuove un nodo dal grafo -- O(N)
int graph_remove_edge(Graph gr, const void* node1, const void* node2);                           // rimuove un arco dal grafo -- O(1) (*)
int graph_num_nodes(const Graph gr);                                                             // numero di nodi -- O(1)
int graph_num_edges(const Graph gr);                                                             // numero di archi -- O(N)
void** graph_get_nodes(const Graph gr);                                                          // recupero dei nodi del grafo -- O(N)
Edge** graph_get_edges(const Graph gr);                                                          // recupero degli archi del grafo -- O(N)
void** graph_get_neighbours(const Graph gr, const void* node);                                   // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
int graph_num_neighbours(const Graph gr, const void* node);                                      // recupero del numero di nodi adiacenti ad un dato nodo -- O(1)
void* graph_get_label(const Graph gr, const void* node1, const void* node2);                     // recupero dell'etichetta di un arco -- O(1) (*)
void graph_free(Graph gr);

```

_(*)_ quando il grafo è veramente sparso, assumendo che l'operazione venga effettuata su un nodo la cui lista di adiacenza ha una lunghezza in O(1).

La struttura ```struct graph``` deve essere decisa prendendo in considerazione la richiesta di usare la Tabella Hash dell'esercizio precedente.


*Suggerimento*:  un grafo non diretto può essere rappresentato usando un'implementazione per grafi diretti modificata
per garantire che, per ogni arco *(a,b)* etichettato *w*, presente nel grafo, sia presente nel grafo anche l'arco *(b,a)*
etichettato *w*. Ovviamente, il grafo dovrà mantenere l'informazione che specifica se esso è un grafo diretto o non diretto.
Similmente, un grafo non etichettato può essere rappresentato usando l'implementazione per grafi etichettati modificata per garantire
che le etichette siano sempre `null` (che invece non devono mai essere `null` per i grafi etichettati).

### Unit Testing

Implementare gli unit-test degli algoritmi secondo le indicazioni suggerite nel documento [Unit Testing](UnitTesting.md).

### Uso della libreria che implementa la struttura dati Grafo

Si implementi l'algoritmo di visita in ampiezza secondo il seguente prototipo di funzione

```
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
//start è il nodo di partenza da cui cominciare la visita, la funzione restituisce l'array dei nodi nell'ordine di visita.
//eventualmente, la funzione restituisce null se il nodo start non è presente nel grafo gr.

```

L'implementazione dell'algoritmo di visita in ampiezza dovrà utilizzare la libreria sui grafi appena implementata.
L'algoritmo dovrà poi essere usato con i dati contenuti nel file `italian_dist_graph.csv`, che potete recuperare all'indirizzo:

> [https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY](https://datacloud.di.unito.it/index.php/s/FqneW99EGWLSRpY)

Tale file contiene le distanze in metri tra varie località italiane e una frazione delle località a loro più vicine. Il formato è un CSV standard: i campi sono separati da virgole; i record sono separati dal carattere di fine riga (`\n`).

Ogni record contiene i seguenti dati:

- `place1`: (tipo stringa) nome della località "sorgente" (la stringa può contenere spazi ma non può contenere virgole);
- `place2`: (tipo stringa) nome della località "destinazione" (la stringa può contenere spazi ma non può contenere virgole);
- `distance`: (tipo float) distanza in metri tra le due località.

**Note:**

- Potete interpretare le informazioni presenti nelle righe del file come archi **non diretti** (per cui probabilmente vorrete inserire nel vostro grafo sia l'arco di andata che quello di ritorno a fronte di ogni riga letta).
- Il file è stato creato a partire da un dataset poco accurato. I dati riportati contengono inesattezze e imprecisioni.

**Si ricorda che il file `italian_dist_graph.csv` (e i file compilati) NON DEVONO ESSERE OGGETTO DI COMMIT SU GIT!**
