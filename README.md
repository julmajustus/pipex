# pipex - Command Piping in C

pipex is a C project that replicates shell command piping. It demonstrates how to create child processes, manage file descriptors, and set up pipelines to emulate shell behavior.

---

### Install

Clone the repository and build the project using the provided Makefile:
```
git clone https://github.com/julmajustus/pipex.git
cd pipex
make
```
---

### Usage
Mandatory Example
```
./pipex infile "ls -l" "wc -l" outfile
```
Bonus Example (here_doc)
```
./pipex here_doc EOF "grep hello" "wc -l" outfile
```
