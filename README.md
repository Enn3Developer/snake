# Snake

## 🇮🇹 Italiano 🇮🇹

### Descrizione

Questo è un progetto universitario con lo scopo di ricreare snake su terminale usando C++ e ncurses.

Sviluppato e testato su Linux x86_64, dovrebbe funzionare anche su Linux aarch64 e Windows x86_64/aarch64.

### Compilazione

Per compilare, basta andare nella root del progetto e creare una nuova cartella per la build:

```shell
mkdir build
```

Dopodiché, si deve usare `cmake` per creare il `Makefile` per compilare il progetto:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -B build -S .
```

Infine, per compilare bisogna evocare il comando `make`:

```shell
make snake
```

L'eseguibile si chiamerà `snake`.

N.B.: È necessario aver installato la libreria `ncurses` per poter compilare il progetto.

## 🇬🇧 English 🇬🇧

### Description

This is a university project with the goal to recreate snake in the terminal using C++ and ncurses.

Developed and tested on Linux x86_64, it should work on Linux aarch64 and Windowx x86_64/aarch64, too.

### Build

To build it, you need to move to the project's root and create a new folder for the resulting build:

```shell
mkdir build
```

After that, you should use `cmake` to create the `Makefile` needed to compile the project:

```shell
cmake -DCMAKE_BUILD_TYPE=Release -B build -S .
```

At last, to build it you should invoke the `make` command:

```shell
make snake
```

The binary executable will be `snake`.

N.B.: It is necessary installing `ncurses` to compile the project.