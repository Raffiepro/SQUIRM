<br />
 <p align="center">
  <img src="logo.png" alt="Logo" width="80" height="80">

  <h1 align="center">That</h1>
    <p align="center">
    Un llenguatge de programació programable que no et complica la vida
    <br />
    <a href="https://git.aranroig.com/BinarySandia04/that/issues">Informa d'un error</a>
</p>
<p align="center">
  <a href="https://git.aranroig.com/BinarySandia04/that">Pàgina web del repositori</a>
</p>
<p align="center">
<img src="https://img.shields.io/github/repo-size/BinarySandia04/That-mirror?color=%23fff&label=Repo%20size&style=for-the-badge">
<img src="https://img.shields.io/github/languages/code-size/BinarySandia04/That-mirror?color=%23ccc&style=for-the-badge">
<img src="https://img.shields.io/github/v/tag/BinarySandia04/That-mirror?color=%23a5dff2&label=Version&style=for-the-badge">
<img src="https://img.shields.io/github/downloads/BinarySandia04/That-mirror/total?style=for-the-badge">
</p>

## Coses
Això encara està en obres. Acabaré el README quan tingui temps. Com m'agrada fer amb tots els projectes que mai acabo, aqui poso una llista amb coses per fer:

## Roadmap

Aquesta llista pot canviar en un futur. La idea es com més o menys seràn les versions (m'estic flipant molt amb això)

### Fase de desenvolupament (pre v1.0)
- [X] Acabar de completar l'assamblador (v0.3)
- [X] Acabar de completar la màquina virtual (v0.4)
- [ ] Solucionar bugs i optimitzar (v0.5)
- [ ] Aconseguir un transcompilador a C++ (v0.6)
- [ ] Fer que sigui un llenguatge totalment estable i bàsic (v0.7)
- [ ] Poder importar llibreries (v0.8)
- [ ] Fer documentació (v0.9)

### Futur
- [ ] Fer una versió estable del llenguatge i una petita documentació (v1.0)
- [ ] Acabar la API per incorporar noves llibreries i gestor de paquets (v2.0)
- [ ] Completar les llibreries estandard per That (v3.0)
- [ ] Multithreading i altres coses molt a futur (v4.0)

## Possibles noms per That
No m'agrada el nom de That. Aquí apuntare noms guais que podrien molar
- Wyrm

## Raons per las quals That hauria d'existir

En un futur m'agradaria que That tingui les següents "features" (molt guais):

- That és un llenguatge interpretat que pot ser transcompilat a C/C++. La idea es que té per una banda una màquina virtual integrada que s'utilitza per defecte, i també en cas que es desitji, es pot transcompilar un codi escrit amb That a C/C++ com a un JIT, de manera que si es vol es pot obtenir el rendiment d'un llenguatge compilat mantenint simplicitat. Entre les funcionalitats de That hi ha:
- Suport per classes. En principi el mateix que a C++ pero ja veurem
- That serà un llenguatge amb precisió numèrica pràcticament infinita utilitzant GMP per defecte. El programador podrà inserir la precisió (en bytes) que necessita de coma flotant. Això és útil per a aplicacions matemàtiques i de no haver de fer estructures més complicades o l'ús de llibreries externes per tal de poder emmagatzemar nombres massa grans. Això pot ser útil per exemple, poder calcular el nombre pi amb una precisió de 300 xifres decimals, per exemple.
- That serà un llenguatge de programació que s'allunyi del paradigma de la programació orientada a objectes, pero sense allunyar-se massa per tal de que sigui cómode i funcional, pero alhora que sigui bastant optimitzat, (ja veurem com).
- That també tindrà un gestor de paquets invisible. La idea principal és que amb una línia (per exemple, `import "algo/algunacosa"`) el programa ja instal·li automàticament els paquets necessaris per funcionar en temps d'execució. A part també vindrà amb una utilitat de terminal per tal de poder gestionar de forma usual els paquets instal·lats. Com que també necessita dependre de CMake, es pot fer que aquests paquets es compilin en temps real o que ja vinguin compilats i l'interpret els pugui cridar. Ja veurem també, pero no ho veig gaire complicat.
- That disposarà d'una gran llibreria estàndard per tal de ser molt ràpid a l'hora de crear aplicacions multimèdia visuals lo més ràpid possible, similar a Processing. En principi vull implementar ImGui i Vulkan en un futur molt llunyà. També hauria de poder compilar in situ aquestes llibreries amb GCC/G++ i doncs que en pugui accedir i es pugui comunicar amb That. També estaria bastant bé fer que no només es limiti a C/C++, sino que també es pugui comunicar amb funcions base d'altres llenguatges de més baix nivell, com Rust per exemple.
- A la llibreria estàndard haurien d'haver-hi funcions modernes com poder fer peticions HTTP, escriure en fitxers, processament d'arxius JSON, manipulació d'imatges, vídeo, entre d'altres.
- That ha de ser un llenguatge bastant fàcil d'incorporar en altres entorns fora de l'execució autònoma.
- That també serà molt modificable i programable, de manera que es pugui modificar cada operació de forma senzilla (com C++) disposant del màxim nombre de símbols i personalització possible
- A part, també el compilador de That pot triar una opció Debug i una final, on el nom ja indica tot, la idea es que la final no tingui la informació per debugar i sigui molt més lleujera i fàcil d'executar
- També hauria de permetre implementar de la forma més senzilla possible (si existeix) la possibilitat de fer execucions paral·leles. (I si es pot amb la GPU també)

## Dependències

Les marcades amb un (*) necessiten ser instalades manualment per l'usuari final. (Podria fer un instalador potser).

- [CMake](https://cmake.org/)* (En cas que es vulgui compilar)
- [SWIG](https://www.swig.org/)
- [GMP - The GNU Multiple Precision Arithmetic Library](https://gmplib.org/)
- [MPFR](https://www.mpfr.org/)

## Sintaxis

```
### COMENTARIS ###
# That programming language test.

# Això és un comentari

##
Aquest comentari es llarg
Amb That l'execució d'un programa es realitza de la següent manera: primer
es fa una llegida sequencial i es declaren variables i funcions en ordre, i també
s'executen instruccions, i després (si existeix) es crida a una funció main. Es com
el punt d'entrada de Python, bastant similar. Aquesta linea per exemple mostra un 2
##

### HELLO WORLD ###
"Hello World!";

# Per a mostrar simplement un ';'. Això executa la "funció predeterminada" del tipus, que en
# tots els tipus predeterminats built-in, són fer un print per la sortida estàndard (excepte el buit). Per exemple,
# per mostrar 2+2, fariem
2+2;

# De fet, posar ';' és opcional. És a dir, un salt de linea s'interpreta com a un ';'. Jo el poso perque m'agrada

# Per declarar variables no cal indicar tipus
a = 0;
c = "Això és una C!!!";
q = True;

# En cas que declarem amb el tipus després no el podrem mutar. Es preferible per millor rendiment al compilar.
# Almenys en Wyrm, qualsevol cosa que puguis especificar més ràpida serà
int r = 3;
string s = "Això només és un string!";

# Per modificar el valor d'una variable és bastant senzill:
a = b + b * 50 - 3;

# Com que Wyrm es un llenguatge molt guai, tenim funcions! Per fer-ne una obrim {}
hola {
  "Hola!";
}
hola(); # Hola!

# Per declarar paràmetres s'ha d'escriure dos punts

ajunta: s, t {
  s + t;
}

ajunta("Hola", "que tal?"); # >> Hola que tal?
ajunta(2, 3); # 5

# Es possible fixar un tipus determinat a les funcions, simplement posant-ho. De fet,
# qualsevol moment que es posi un prefix de tipus, s'espera que la variable sigui d'aquest tipus,
# sino, doncs salta un error, exemple:

dividir: int a, int b {
  "La divisió dona: " + (a / b);
}
dividir(10, 2); # La divisió dona: 5

# Si una funció ha de retornar algo s'escriu "=>" després dels paràmetres '{' i després el tipus de retorn:

cub: int d => int {
  return d * d * d;
}

cub(3); # 27

tres => int {
  return 3;
}

cub(tres()); # 27

# També existeixen condicionals. Es poden compactificar
if q {
  "Q és True";
  if tres() == 3 {
    "tres és 3";
  } else if suma(2,2) == 4: "2+2 = 4";
    else {
    "Això no és possible!";
  }
} else: print("Q és False");

# Els bucles whiles també son com altres llenguatges
print("Comptem fins a 10!");
i = 1;
while i <= 10 {
  i;
  i += 1;
}

# També hi ha ordre de trencar while i seguir una altra volta. S'anomenen "break" i "skip" respectivament:
i = 2;
while i < 100 {
  if i % 2 == 0 {
    i += 3;
    skip;
  }
  if i % 3 == 0: i;
  if i % 23 == 0: break;
  i += 1;
}

# També existeix el bucle for, que és un while compacte, igual que els altres llenguatges:
for int j = 0; j < i; j += 1: print(j * i);

# També hi ha arrays! Hi ha de variables i de fixats.
j = []; # Variable. Podem posar coses de qualsevol tipus
r = int []; # Fixat. Només ints. És més ràpid!
int[] q = int []; # Arrays de ints a q que només guarda arrays de int

# Per posar coses als arrays podem fer servir el operador += !!!
q += 2;
q += 3;
q; # [2, 3];

# Per mostrar la mida podem fer servir el operador unari $:
$q; # 2

# Les funcions són de primer tipus. Podem fer coses rares com aquesta:
fact: int i => int {
  a = [];
  for int i = 1; i <= 10; i++ {
    f : int p => int {
      if p == 1: return 1;
      return a[i-1](p * i);
    }
    a += f;
  }

  return a[$a-1](i);
}
fact(10); # 3628800


# En cas que la volguem fer immutable afegim la keyword "fixed":
fixed suma: int a, int b => int {
  return a + b;
}

fixed mult: int a, int b => int; # Funció buida
mult: int a, int b => int {
  return a + b;
} # Ara mult és una funció que retorna a + b

# Hem de tenir en compte que els ':' s'utilitzen com a un igual en certa manera

### ESTRUCTURES ###
# Podem crear una estructura amb {}, encara que per assignar-la utilitzem '='. Recordem que si
# utilitzem ':' estariem definint una funció!
cotxe = {
  propietari;
  int rodes = 4;
  string nom = "Citroen";
};

# Ara cotxe és una variable amb tres coses dins. Té un propietari, un int rodes, i un nom:
cotxe.rodes; # 4
cotxe.nom; # Citroen
cotxe.propietari = "Josep";
cotxe.propietari; # Josep

# Per defecte, podem afegir propietats a les estructures que no existeixen, és a dir, per defecte les
# estructures són diccionaris
cotxe.color = "Vermell"; # Això és legal
cotxe.color; # Vermell

# Si volem una estructura fixa (i més ràpida) utilitzaem la paraula fixed, igual que abans
fixed moto = {
  int rodes = 2;
  int nom = "Yamaha";
};

moto.nom = "Honda";
moto.color = "Blau"; # Error

# Podem definir plantilles per estructures, és molt semblant a una classe o un struct de C++, pero en Wyrm
# s'anomenen models. Per fer-ne un, utilitzem la paraula model:

model complex = {
  real a, b;
};

complex a; # Una variable complexa
a.a = 3.24;
a.b = 1;

# Tots els models són immutables
complex r;
r.a = 5.3;
r.b = -3;
r.c = -800; # Error

# Igual que els llenguatges OOP, tenim constructors, destructors, coses privades i públiques
model complex = {
  @ real a, b; # Elements privats! Començen per @
  complex {
    a = 0;
    b = 0;
  }

  complex: real a, real b {
    .a = a; # Començar amb "." és igual a referir-se a la mateixa classe
    .b = b;
  }

  GetA => real {
    return a;
  }

  GetB => real {
    return b;
  }
};



```