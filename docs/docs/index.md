# Welcome to Wyrm

This documentation will guide you through every aspect of the Wyrm programming language

Wyrm is an interpreted and compiled programming language. It is aimed to be very embeddable from both ends. You can create C/C++ libraries for a Wyrm project to extend its functionality, and the Wyrm interpreter can be embeddable everywhere from its source code.

- Wyrm: The name of the language. Translates Wyrm code to 
- Phi: An interpreter of Wyrm
- Drac: A transcompiler of Wyrm to C/C++
- Zmey: A package manager for Wyrm

Temporal:

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