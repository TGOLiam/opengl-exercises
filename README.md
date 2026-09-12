# Computer Graphics course exercises

Each course module lives in a `ModuleN/` directory. Put exercise source files
directly in that module and put instructor/demo programs beneath
`ModuleN/example/`. The root Makefile discovers the source files automatically,
so adding another module does not require copying build rules.

## Build a module

```sh
./run 1 e 2       # compile and run example 2 from Module1
./run 1 x 1       # compile and run exercise 1 from Module1
./run 1 m 3       # compile and run mini-exercise 3 from Module1
./run 1 m 10      # compile and run mini-exercise 10 from Module1

# Direct Makefile commands are also available:
make m1          # everything in Module1
make m1e         # Module1 examples only
make m1x         # Module1 exercises only
make m1e RUN=1   # compile and run example 1
make m1e RUN=2   # compile and run example 2

# Long form, useful for scripts or unusual module numbers
make MODULE=1 MODE=examples
make MODULE=1 MODE=exercise
make MODULE=1 MODE=all
```

Built programs are placed under `build/ModuleN/`, separated into `examples/`
and `exercise/`. To see the modules and files the Makefile currently finds,
run `make list`. Use `make help` for the complete command summary and
`make clean` to remove generated outputs.

The Makefile uses `g++` and links GLUT/OpenGL through `-lglut -lGL -lGLU`.
Override standard Make variables if your platform needs different toolchain or
library flags, for example `make CXX=clang++ MODULE=1 MODE=examples`.
