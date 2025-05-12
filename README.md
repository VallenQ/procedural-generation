🐳 Executando com Docker 🐳 

1 - Clone este repositório:
  "git clone https://github.com/VallenQ/procedural-generation.git"
   "cd procedural-generation"
   
2 - Construa a imagem Docker:
  "docker build -t procedural-map ."

3 - Execute o contêiner:
  xhost +local:docker  # (apenas uma vez, para liberar acesso ao X11)
  docker run --rm -it \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    procedural-map
  
❗ Se estiver usando Linux, talvez você precise rodar xhost +local:root antes para permitir o acesso à sua interface gráfica. ❗
❗ Se estiver no Windows ou macOS, será necessário usar soluções como XQuartz (macOS) ou VcXsrv/Xming (Windows) para redirecionar a interface gráfica do contêiner.❗ 

O dockerfile Atualiza pacotes e instala dependências para executar o programa sem problemas.
  🚧 Requisitos 🚧
    Docker instalado
    Ambiente gráfico X11 habilitado (Linux)

