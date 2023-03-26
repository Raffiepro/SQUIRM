<br />
 <p align="center">
  <img src="logo.png" alt="Logo" width="80" height="80">

  <h1 align="center">Wyrm</h1>
    <p align="center">
    The most powerful programming language
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

## Raons per las quals Wyrm hauria d'existir

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

El llenguatge de programació Wyrm per defecte genera una "representació intermitja" (feta per mi, similar a la de LLVM).

- **Wyrm**: Llenguatge de programació. Passa un projecte de Wyrm a la representació intermitja
- **Phi**: Interprete de Wyrm
- **Drac**: Compilador de Wyrm
- **Zmey**: Gestor de paquets i llibreries de Wyrm

## Dependències

Les marcades amb un (*) necessiten ser instalades manualment per l'usuari final. (Podria fer un instalador potser).

- [CMake](https://cmake.org/)* (En cas que es vulgui compilar)
- [SWIG](https://www.swig.org/)
- [GMP - The GNU Multiple Precision Arithmetic Library](https://gmplib.org/)
- [MPFR](https://www.mpfr.org/)