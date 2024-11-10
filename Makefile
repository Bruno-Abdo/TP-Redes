# Definir o compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Nome do arquivo executável
TARGET = Labirinto

# Arquivos objeto
OBJ = TP1V0.o rules.o

# Regra para compilar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Regras para compilar arquivos .c em .o
TP1V0.o: TP1V0.c rules.h
	$(CC) $(CFLAGS) -c TP1V0.c

rules.o: rules.c rules.h
	$(CC) $(CFLAGS) -c rules.c

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Regra padrão para compilar e limpar ao mesmo tempo
all: clean $(TARGET)
