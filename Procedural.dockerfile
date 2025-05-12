# Imagem base com sistema Debian
FROM debian:bookworm

# Instala dependências do sistema e SDL
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    cmake \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev \
    libx11-6 \
    libxext6 \
    libxrandr2 \
    libxi6 \
    libgl1-mesa-dev \
    libasound2 \
    libpulse-dev \
    libudev-dev \
    x11-xserver-utils \
    && apt-get clean

# Cria diretório da aplicação
WORKDIR /app

# Copia todos os arquivos do projeto
COPY . /app

# Compila o programa
RUN g++ -std=c++17 -o procedural-map Procedural.cpp `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Comando padrão ao iniciar o container
CMD ["./procedural-map"]
