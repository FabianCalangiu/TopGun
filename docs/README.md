**TOP GUN**

CONTRIBUTORI:
 - Manuel Menghetti | manuel.menghetti@studio.unibo.it
 - Fabian Costinel Calangiu | fabian.calangiu@studio.unibo.it

SVILUPPO:
Abbiamo deciso di suddividere il progetto in 3 stati finiti, poichè a seguito della traccia data, siamo riusciti a mappare coerentemente quanto richiesto. C'è stata anche una grossa suddivisione della logica, funzioni di utilità e dei vari componenenti in diversi file, per poter allegerire il codice nel file .ino principale.

Gli stati sono:

- STANDBY: qui il programma viene eseguito, e qual'ora il sensore di PIR non dovesse rilevare movimento sotto i 350 cm, viene messi in sleep mode. Solamente quando la distanza dell'oggetto simulato sarà inferiore ai 350 cm e il PIR rileverà movimento, avremo il cambio di stato al successivo.

- TRACKING: in questo stato, il sonar esegue le misure sulle distanze dell'oggetto entrato nella nostra area protetta e, tramite vari calcoli, viene calcolata e stampata la velocità dell'oggetto ogni 100ms. Il servo(torretta) non viene ancora allarmato, poichè l'oggetto si trova ancora troppo lontano dalla distanza di sicurezza minima, ovvero 100cm. Si da il caso che, il passaggio di stato lo avremo quando la distanza rilevata dal sonar sarà inferiore ai 100cm. Mentre se esce dalla zona specificata(350cm), tornerà nel primo stato e si rimetterà a dormire, in attesa di movimento.

- LOCKIN: in questo stato, viene allarmato il servo(torretta), che inizia a muoversi casualmente, simulando come se stesse effettivamente seguendo l'oggetto. La simulazione dello sparo avviene tramite la pressione del tasto verde. Qui abbiamo voluto renderlo un po più interattivo, inserendo anche la possibilità del 50% di poter mancare o colpire il bersaglio. Qual'ora si mancasse il bersaglio, si può ritentare, affinchè non si avrà successo o il bersaglio non uscirà dalla zona in cui è entrato (100cm di distanza), ritornando allo stato precedente. Mentre se il bersaglio viene colpito, il programma viene rimesso nel primo stato in sleep, fino a quando non verrà rilevato di nuovo un movimento.