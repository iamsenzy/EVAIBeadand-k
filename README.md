# EVAIBeadandok
ELTE Eseményvezérelt Alkalmazások Fejlesztése I. Beadandóim

1. beadandóm feladata: Tili-toli

Készítsünk programot, amellyel a következő játékot lehet játszani.
Adott egy n×n mezőből tábla, amelyen véletlenszerűen elhelyezünk n^2 − 1 számozott bábut (1, 2, ..., n^2 − 1), 
egy mezőt pedig üresen hagyunk. A játékos feladata az, hogy a bábuk tologatásával kirakjuk a "sorfolytonos" sorrendet,
vagyis a számok sorban következzenek az első sorban balról jobbra, majd a második sorban ( n+ 1)-től indulva balról jobbra,
és így tovább. A tologatások során egy bábút áthelyezhetünk az egyetlen üres mezőre, ha azzal szomszédos mezőn áll
(csak vízszintesen és függőlegesen lehet mozogni, átlósan nem).A program biztosítson lehetőséget új játék kezdésére 
a táblaméret megadásával (3 × 3, 4 × 4, 6 × 6), és ismerje fel, ha vége a játéknak. 
Ekkor jelenítse meg, hány lépéssel győzött a játékos, majd kezdjen automatikusan új játékot.

2. beadandóm feladata: Labirintus

Készítsünk programot, amellyel a következő játékot játszhatjuk.
Adott egy n×n elemből álló játékpálya, amely labirintusként épül fel, azaz fal, illetve padló mezők találhatóak benne,
illetve egy kijárat a jobb felső sarokban. 
A játékos célja, hogy a bal alsó sarokból indulva minél előbb kijusson a labirintusból.
A labirintusban nincs világítás, csak egy fáklyát visz a játékos, amely a 2 szomszédos mezőt világítja meg 
(azaz egy 5 × 5-ös négyzetet), de a falakon nem tud átvilágítani.
A játékos figurája kezdetben a bal alsó sarokban helyezkedik el, és vízszintesen,
illetve függőlegesen mozoghat (egyesével) a pályán.
A pályák méretét, illetve felépítését (falak, padlók) tároljuk fájlban.
A program legalább 3 különböző méretű pályát tartalmazzon.
A program biztosítson lehetőséget új játék kezdésére a pálya kiválasztásával,
valamint játék szüneteltetésére (ekkor nem telik az idő, és nem léphet a játékos), továbbá ismerje fel, ha vége a játéknak. 
A program játék közben folyamatosan jelezze ki a játékidőt.


3. beadandóm feladata: Mozipénztár

Készítsünk programot, amely egy multiplex mozi jegyeladásait tudja kezelni, az
alábbi funkciókkal:
• A program listázza az előadásokat időpont szerint, és azt lehessen szűrni film, illetve terem alapján. 
  Minden előadásnál legyen látható, mennyi szabad hely van még rá.
• Lehet egy adott filmet, illetve termet kiválasztva új előadást hirdetni adott időpontra,
  valamint előadást lehet törölni, amennyiben senki sem foglalt rá helyet.
  A programnak figyelnie kell, hogy két előadás ne ütközzön az adott teremben
  (a film hossza után kell fél óra takarítási időt számolni).
• A meghirdetett előadásokra lehet helyet foglalni. A helyfoglalás adott székre
  (sor és oszlop megadásával) történik figyelembe véve, hogy az a szék még nincs lefoglalva. 
  A lefoglalt helyek ezek után bármikor kiadhatóak. Kiadott jegyet már nem lehet újra kiadni.
  
Az adatbázis az alábbi adatokat tárolja:
• filmek (cím, származás, szinkronizált-e, rendező, szinopszis, hossz);
• termek (név, sorok és oszlopok száma);
• előadások (film, kezdő időpont, terem);
• helyek (előadás, terem, sor, oszlop, státusz <foglalt, kiadott>).

