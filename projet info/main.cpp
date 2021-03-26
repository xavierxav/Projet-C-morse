#include <iostream>
#include "creerwav.h"
#include "decoderwav.h"



/*Par manque de temps, ce programme ne lit pas les fichiers textes et n'est
capable de décoder que des fichiers wav ayant le même temps pour un ti (0.4 s). 
Ne maitrisant pas bien l'interface avec les fichiers wav, j'ai codé tout en 
stéréo donc beaucoup d'instructions sont en double.
De plus, ayant commencé à coder avec des strings, je me suis ensuite rendu
compte de l'impossibilité de mettre des espaces. Les minuscules sont aussi à 
proscrire. En bref ce code est bien loin de mes espérances de départ, mais
il a le mérite de fonctionner et m'a pris beaucoup de temps. Bonne lecture!*/


int main(){
  int r;
  std::cout << "pour coder un message, tapez 1, pour décoder un message, tapez 2";
  std::cin >> r;
  if(r==1){
    std::string l;
    std::cout << "tapez votre message";
    std::cin >> l;
    creerwav(l);
  }
  if(r==2){

    std::string s=read();
    std::cout << s<<std::endl;
  }
  return 0;
}