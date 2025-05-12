🐳 Executando com Docker 🐳 

1 - Clone este repositório 
  "git clone https://github.com/VallenQ/procedural-generation.git"
   "cd procedural-generation"
   
2 - Construa a imagem Docker
  "docker build -t procedural-sdl ."

3 - Execute o contêiner
  "docker run --rm -it --env DISPLAY=$DISPLAY --volume /tmp/.X11-unix:/tmp/.X11-unix procedural-sdl"
❗ Se estiver usando Linux, talvez você precise rodar xhost +local:root antes para permitir o acesso à sua interface gráfica. ❗
