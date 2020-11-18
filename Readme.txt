

g++ -c src/*.cpp -I./SFML/ -I./src
g++ *.o -o sfml-app -L./SFML -lsfml-graphics -lsfml-window -lsfml-system