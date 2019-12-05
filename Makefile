DAY=1
UTILS_DIR=./util/inc

ifeq ($(OS), Windows_NT)
OUT=out.exe
else
OUT=out
endif

all: 
	@echo Building Day $(DAY)!
	@$(MAKE) -s -C ./day$(DAY) UTILS=../$(UTILS_DIR)
	@./day$(DAY)/build/$(OUT) ./day$(DAY)/input/input.txt

clean:
	@$(MAKE) -s -C ./day$(DAY) clean