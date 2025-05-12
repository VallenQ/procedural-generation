
FROM debian:bookworm

# Atualiza pacotes e instala dependências
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev \
    && apt-get clean

# Cria diretório da aplicação
WORKDIR /app

# Copia os arquivos do projeto para o contêiner
COPY . /app

# Compila o código-fonte C++ 
RUN g++ -std=c++17 -o procedural.out Procedural.cpp `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Comando para executar a aplicação
CMD ["./procedural.out"]
