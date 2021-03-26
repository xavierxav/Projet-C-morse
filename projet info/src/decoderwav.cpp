#include <fstream>
#include <iostream>
using namespace std;
#include "coder.h"


string read(){
    ifstream f("message_code.wav",ifstream::binary);
    if(f.is_open()){
    }

    f.seekg(0, ios::end);
    long int taille_fichier = f.tellg();
    f.seekg(0, ios::beg);
    char c[44];
    f.read((char*) c,44);//passer les 44 premières infos, liées au paramètres du wav
    int t1;
    int t2;
    int hz        = 44100;    // fréquence des signaux
    double seconds   = 0.4;      // temps d'un ti
    const int n=(taille_fichier-44)/(4*hz*seconds); //nombres de temps

/*pour décoder, on se place au milieu d'un "temps": si deux valeurs 
consécutives sont nulles, le temps est nul, sinon il est non nul*/

    for(int j=0;j<0.5*(hz*seconds)-1;j+=1){
        f.read((char*)&t1,2);
        f.read((char*)&t1,2);  
    }
    f.read((char*)&t1,2);
    f.read((char*)&t1,2);
    f.read((char*)&t2,2);
    f.read((char*)&t2,2);
    int l[n];

    l[0]=1;
    if(t1==0 && t2==0){
        l[0]=0;
    }
    int m=1;
    while(m<n){
        for(int j=0;j<(hz*seconds-2);j+=1){
            f.read((char*)&t1,2);
            f.read((char*)&t1,2);
        }
        f.read((char*)&t1,2);
        f.read((char*)&t1,2);
        f.read((char*)&t2,2);
        f.read((char*)&t2,2);
        l[m]=1;
        if(t1==0 && t2==0){
            l[m]=0;
        }
        m++;
    }
//on a alors une liste l de tous les temps nuls(si l[i]=0) ou non (l[i]=1)
//on traduit alors cela en morse conventionnel avec des . et des -
//pour cela on sépare en mots (séparés par trois 0) puis en lettres, puis 
//on traduit les lettres avec la fonction coder
    
    int a =0;
    string solution="";
    while (a<n){
        int m=0;
        string s="";
        while(l[a+m]!=0 || l [a+m+1]!=0){
            int j =0;
            while(l[a+m+j]!=0){
                j++;
            }
            if (j==1){
                s.append(".");
            }
            if (j==3){
                s.append("-");
            }
            m+=j+1;
        }
        solution.append(coder(s));
        a+=m+2;
    }
    
    return solution;
}
