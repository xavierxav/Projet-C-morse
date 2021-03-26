
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#include "coder.h"

namespace little_endian_io
{
    template <typename Word>
    ostream& write_word( ostream& outs, Word value, unsigned size = sizeof( Word ) )
    {
        for (; size; --size, value >>= 8)
            outs.put( static_cast <char> (value & 0xFF) );
        return outs;
    }
}
using namespace little_endian_io;



void creerwav(string l)
{

// on commence par rentrer les données de base du fichier wav
    ofstream f( "message_code.wav", ios::binary );
    f << "RIFF----WAVEfmt ";     //taille du fichier
    write_word( f,     16, 4 );  
    write_word( f,      1, 2 );  
    write_word( f,      2, 2 );  
    write_word( f,  44100, 4 );  // fréquence des signaux
    write_word( f, 176400, 4 );  
    write_word( f,      4, 2 );  
    write_word( f,     16, 2 );  // nombre de bits par échantillons (ici 16)


    size_t data_chunk_pos = f.tellp();
    f << "data----";  


    double two_pi = 6.283185307179586476925286766559;
    double volume = 32760;  

    int hz        = 44100;    // fréquence des signaux
    double frequency = 440;  // fréquence sonore
    double seconds   = 0.4;      // temps d'un ti


//On traduit alors le message en morse avec la fonction coder, puis on code le wav
    for(int i=0;i<l.length();i++)
    {
        string s;
        s.append(1,l[i]);
        string h=coder(s);
        for(int j=0;j<h.length();j++){
            if (h[j]=='-'){
                int N = hz * seconds*3;
                for (int n = 0; n < N; n++)
                {
                    double value     = sin( (two_pi * n * frequency) / hz );
                    write_word( f, (int)((volume) * value), 2 );
                    write_word( f, (int)((volume) * value), 2 );
                }
            }
            if (h[j]=='.'){
                int N = hz * seconds;
                for (int n = 0; n < N; n++)
                {
                    double value     = sin( (two_pi * n * frequency) / hz );
                    write_word( f, (int)((volume) * value), 2 );
                    write_word( f, (int)((volume) * value), 2 );
                }
            }
            if (h[j]==' '){
                int N = hz * seconds*4;
                for (int n = 0; n < N; n++)
                {
                    double value     = 0;
                    write_word( f, (int)((volume) * value), 2 );
                    write_word( f, (int)((volume) * value), 2 );
                }
            }
            int N = hz * seconds;
            for (int n = 0; n < N; n++)
            {
                double value     = 0;
                write_word( f, (int)((volume) * value), 2 );
                write_word( f, (int)((volume) * value), 2 );
            }
        }
        int N = hz * seconds*2;
        for (int n = 0; n < N; n++)
        {
            double value     = 0;
            write_word( f, (int)((volume) * value), 2 );
            write_word( f, (int)((volume) * value), 2 );
        }
    }
    size_t file_length = f.tellp();//taille du fichier
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 ); 
}

