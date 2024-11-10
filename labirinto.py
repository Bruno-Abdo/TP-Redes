import random

def gerar_matriz(m, n):
    # Inicializa a matriz com zeros
    matriz = [[0 for _ in range(n)] for _ in range(m)]

    # Posiciona o '2' em uma das bordas
    bordas = [(0, i) for i in range(n)] + [(m-1, i) for i in range(n)] + [(i, 0) for i in range(m)] + [(i, n-1) for i in range(m)]
    x2, y2 = random.choice(bordas)
    matriz[x2][y2] = 2

    # Posiciona o '3' em uma posição aleatória que não seja uma borda
    while True:
        x3, y3 = random.randint(1, m-2), random.randint(1, n-2)
        if (x3, y3) != (x2, y2):
            matriz[x3][y3] = 3
            break

    # Função para criar um caminho no labirinto usando DFS
    def criar_caminho(x, y):
        # Direções possíveis (Cima, Direita, Baixo, Esquerda)
        direcoes = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        random.shuffle(direcoes)
        
        for dx, dy in direcoes:
            nx, ny = x + dx, y + dy

            # Verifica se está dentro da matriz e se é um caminho válido (apenas '0' e '3')
            if 0 <= nx < m and 0 <= ny < n and (matriz[nx][ny] == 0 or matriz[nx][ny] == 3):
                if matriz[nx][ny] == 3:
                    return True  # Encontrou o destino
                matriz[nx][ny] = 1  # Marca como caminho
                if criar_caminho(nx, ny):
                    return True
                matriz[nx][ny] = 0  # Desfaz a marcação se não for um caminho válido
        return False

    # Cria o caminho a partir da posição do '2'
    criar_caminho(x2, y2)

    return matriz

# Gera dimensões aleatórias para a matriz
m, n = random.randint(5, 9), random.randint(5, 9)
matriz = gerar_matriz(m, n)

# Exibe a matriz no console
print("Matriz Gerada:")
for linha in matriz:
    print(' '.join(map(str, linha)))

# Salva a matriz no arquivo 'labirinto.txt'
with open("labirinto.txt", "w") as file:
    for linha in matriz:
        file.write(' '.join(map(str, linha)) + '\n')

print("\nMatriz salva no arquivo 'labirinto.txt'.")
