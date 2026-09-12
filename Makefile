# Course-wide OpenGL/GLUT build entry point.
#
# Examples:
#   make MODULE=1 MODE=examples
#   make MODULE=1 MODE=exercise
#   make MODULE=1 MODE=mini-exercises
#   make MODULE=1 MODE=all
#   make MODULE=1 MODE=examples RUN=1

CXX       ?= g++
CPPFLAGS  +=
CXXFLAGS  ?= -std=c++17 -Wall -Wextra -Wpedantic
LDLIBS    ?= -lglut -lGL -lGLU

MODULE    ?= 1
MODE      ?= all
RUN       ?=
BUILD_DIR ?= build

MODULE_DIR := Module$(MODULE)
EXAMPLE_DIR := $(MODULE_DIR)/example
MINI_EXERCISE_DIR := $(MODULE_DIR)/mini-exercises
MODULE_NUMBERS := $(patsubst Module%,%,$(notdir $(wildcard Module*)))

# Exercise sources live directly in a module directory.  Example sources may
# be organised in subdirectories beneath example/ as the course grows.
EXERCISE_SOURCES := $(sort $(wildcard $(MODULE_DIR)/*.cpp $(MODULE_DIR)/*.cc $(MODULE_DIR)/*.cxx))
EXAMPLE_SOURCES  := $(sort $(shell find "$(EXAMPLE_DIR)" -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) 2>/dev/null))
MINI_EXERCISE_SOURCES := $(sort $(shell find "$(MINI_EXERCISE_DIR)" -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) 2>/dev/null))

EXERCISE_BINS := $(patsubst $(MODULE_DIR)/%, $(BUILD_DIR)/$(MODULE_DIR)/exercise/%, $(basename $(EXERCISE_SOURCES)))
EXAMPLE_BINS  := $(patsubst $(EXAMPLE_DIR)/%, $(BUILD_DIR)/$(MODULE_DIR)/examples/%, $(basename $(EXAMPLE_SOURCES)))
MINI_EXERCISE_BINS := $(patsubst $(MINI_EXERCISE_DIR)/%, $(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/%, $(basename $(MINI_EXERCISE_SOURCES)))

.DEFAULT_GOAL := build
.PHONY: build help list modules examples exercise mini-exercises all run clean check-module

# Shortcuts are generated for every ModuleN directory found at Makefile load.
# m1  = everything in Module1; m1e = examples; m1x = exercises.
define MODULE_SHORTCUTS
.PHONY: m$(1) m$(1)e m$(1)x
m$(1): MODULE := $(1)
m$(1): MODE := all
m$(1): build
m$(1)e: MODULE := $(1)
m$(1)e: MODE := examples
m$(1)e: build
m$(1)x: MODULE := $(1)
m$(1)x: MODE := exercise
m$(1)x: build
endef
$(foreach number,$(MODULE_NUMBERS),$(eval $(call MODULE_SHORTCUTS,$(number))))

build: check-module
	@if test -n "$(RUN)"; then \
		case "$(MODE)" in \
			examples) program='$(BUILD_DIR)/$(MODULE_DIR)/examples/$(RUN)' ;; \
			exercise) program='$(BUILD_DIR)/$(MODULE_DIR)/exercise/$(RUN)' ;; \
			mini-exercises) program='$(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/$(RUN)' ;; \
			*) echo 'RUN needs MODE=examples, MODE=exercise, or MODE=mini-exercises.'; exit 2 ;; \
		esac; \
		$(MAKE) --no-print-directory MODULE=$(MODULE) MODE=$(MODE) RUN=$(RUN) "$$program"; \
		$(MAKE) --no-print-directory MODULE=$(MODULE) MODE=$(MODE) RUN=$(RUN) run; \
	else \
		case "$(MODE)" in \
			examples|exercise|mini-exercises|all) $(MAKE) --no-print-directory MODULE=$(MODULE) MODE=$(MODE) RUN= $(MODE) ;; \
			*) echo "Unknown MODE: $(MODE). Use MODE=examples, MODE=exercise, MODE=mini-exercises, or MODE=all."; exit 2 ;; \
		esac; \
	fi

help:
	@printf '%s\n' 'Computer Graphics course builder'
	@printf '%s\n' ''
	@printf '%s\n' 'Usage:'
	@printf '%s\n' '  make m1                         Build all of Module1'
	@printf '%s\n' '  make m1e                        Build Module1 examples only'
	@printf '%s\n' '  make m1x                        Build Module1 exercises only'
	@printf '%s\n' '  make MODULE=1 MODE=examples     Build all examples in Module1'
	@printf '%s\n' '  make MODULE=1 MODE=exercise     Build module exercise source files'
	@printf '%s\n' '  make MODULE=1 MODE=mini-exercises Build mini-exercises in Module1'
	@printf '%s\n' '  make MODULE=1 MODE=all          Build all task types (the default MODE)'
	@printf '%s\n' '  make m1e RUN=1                  Build and run example 1'
	@printf '%s\n' '  make m1e RUN=2                  Build and run example 2'
	@printf '%s\n' '  make list                       Show discoverable modules and outputs'
	@printf '%s\n' '  make clean                      Remove generated build files'
	@printf '%s\n' ''
	@printf '%s\n' 'Executables are written under $(BUILD_DIR)/ModuleN/.'

check-module:
	@test -d "$(MODULE_DIR)" || { echo "Unknown module: $(MODULE). Available modules:"; find . -maxdepth 1 -type d -name 'Module*' -printf '  %f\n' | sort; exit 2; }

modules:
	@find . -maxdepth 1 -type d -name 'Module*' -printf '%f\n' | sort

list:
	@printf '%s\n' 'Modules:'
	@$(MAKE) --no-print-directory modules | sed 's/^/  /'
	@printf '%s\n' 'Module $(MODULE) sources:'
	@for source in $(EXERCISE_SOURCES); do printf '  exercise: %s\n' "$$source"; done
	@for source in $(EXAMPLE_SOURCES); do printf '  example:  %s\n' "$$source"; done
	@for source in $(MINI_EXERCISE_SOURCES); do printf '  mini-exercise: %s\n' "$$source"; done

examples: check-module $(EXAMPLE_BINS)
	@test -n "$(EXAMPLE_SOURCES)" || { echo "No example source files found in $(EXAMPLE_DIR)."; exit 2; }

exercise: check-module $(EXERCISE_BINS)
	@test -n "$(EXERCISE_SOURCES)" || { echo "No exercise source files found directly in $(MODULE_DIR)."; exit 2; }

mini-exercises: check-module $(MINI_EXERCISE_BINS)
	@test -n "$(MINI_EXERCISE_SOURCES)" || { echo "No mini-exercise source files found in $(MINI_EXERCISE_DIR)."; exit 2; }

all: examples exercise mini-exercises

# A source file is compiled into an executable at the corresponding build path.
$(BUILD_DIR)/$(MODULE_DIR)/exercise/%: $(MODULE_DIR)/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/exercise/%: $(MODULE_DIR)/%.cc
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/exercise/%: $(MODULE_DIR)/%.cxx
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/examples/%: $(EXAMPLE_DIR)/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/examples/%: $(EXAMPLE_DIR)/%.cc
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/examples/%: $(EXAMPLE_DIR)/%.cxx
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/%: $(MINI_EXERCISE_DIR)/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/%: $(MINI_EXERCISE_DIR)/%.cc
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

$(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/%: $(MINI_EXERCISE_DIR)/%.cxx
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "$<" -o "$@" $(LDLIBS)

run: check-module
	@case "$(MODE)" in \
		examples) bins='$(EXAMPLE_BINS)'; program='$(BUILD_DIR)/$(MODULE_DIR)/examples/$(RUN)' ;; \
		exercise) bins='$(EXERCISE_BINS)'; program='$(BUILD_DIR)/$(MODULE_DIR)/exercise/$(RUN)' ;; \
		mini-exercises) bins='$(MINI_EXERCISE_BINS)'; program='$(BUILD_DIR)/$(MODULE_DIR)/mini-exercises/$(RUN)' ;; \
		*) echo 'For run, use MODE=examples, MODE=exercise, or MODE=mini-exercises.'; exit 2 ;; \
	esac; \
	test -n "$(RUN)" || { echo 'Set RUN to a program name or number, e.g. RUN=1.'; exit 2; }; \
	test -n "$$bins" || { echo "No $$MODE program found for $(MODULE_DIR)."; exit 2; }; \
	test -x "$$program" || { echo "No $$MODE executable named $(RUN). Run 'make list MODULE=$(MODULE)' to see available programs."; exit 2; }; \
	"$$program"

clean:
	@rm -rf "$(BUILD_DIR)"
