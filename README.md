# 🗝️ Mini Key-Value Store (Dynamic Library with `dlopen()`)

**Project Name:** `kvstore_project_M`

---

## 📘 Overview

This project modularizes a simple **Key-Value Store** system using **Dynamic Linking** in C.  
It demonstrates how to split a program into:
- A **shared library** (`libkvstore.so`) that implements the key-value store functions.
- A **main executable** (`dynamic_kvstore`) that dynamically loads the library at runtime using `dlopen()`, retrieves symbols with `dlsym()`, and releases it using `dlclose()`.

This structure provides **modularity**, **flexibility**, and **runtime extensibility**, allowing the application to load updated logic without recompiling the main executable.

---

## 🧩 Project Structure

kvstore_project_M/
│
├── kvstore.h           # Header file (function declarations)
├── kvstore.c           # Implements the key-value store (set/get)
├── main_dlopen.c       # Demonstrates dynamic loading using dlopen()
├── server.c            # Server side logic using Unix domain socket
├── client.c            # Client side logic using Unix domain socket
├── libkvstore.so       # Shared library generated after compilation
└── README.md           # Project documentation (this file)



---

## ⚙️ Objective

> **Task:**  
> Modularize your previous week’s key-value store by splitting it into a dynamic library and a separate executable using `dlopen()`.

---

## 🧠 Concept Recap

| Function | Description |
|-----------|--------------|
| **`dlopen()`** | Loads a shared library into memory at runtime. |
| **`dlsym()`** | Retrieves the address of a function or variable from the shared library. |
| **`dlclose()`** | Unloads the shared library from memory to free resources. |
| **`dlerror()`** | Returns a string describing the last error that occurred during dynamic linking. |

All these are declared in **`<dlfcn.h>`**.

---

## 🧱 Compilation and Execution Steps

Follow these commands **in order** to compile, create, and run your project.

---

## 🔹 Step 1: Compile the dynamic library (Position Independent Code)
gcc -fPIC -c kvstore.c -o kvstore.o
gcc -shared -o libkvstore.so kvstore.o
gcc main_dlopen.c -o dynamic_kvstore -ldl
export LD_LIBRARY_PATH=.
./dynamic_kvstore

### Expected Output:
name:Rojalin

### Compile key-value store to PIC
gcc -fPIC -c kvstore.c -o kvstore.o

### Create shared library
gcc -shared -o libkvstore.so kvstore.o

### Compile main using dynamic loading
gcc main_dlopen.c -o dynamic_kvstore -ldl

### Allow runtime linker to find shared library
export LD_LIBRARY_PATH=.

### Run dynamically loaded program
./dynamic_kvstore

### Compile and run server
gcc -o server server.c -ldl
./server

### Compile and run client
gcc -o client client.c
./client "SET name Rojalin"
./client "GET name"


