#include "Utils.hpp"

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    //caratteristiche del file
    string file_name = "data.csv";
    string delimiter = ";";

    //controllo che file si apra correttamente
    ifstream myFile(file_name);
    if(myFile.fail()){
        cerr << "Errore apertura file \n";
        return 1;
    }

    //inizializzazione variabili
    string line = "";
    string head = "";
    double money = 0.0; //S
    int asset = 1; //n = 1 affinche non dia warning new [0]
    bool first = true;
    int counter = 0;
    double* ptr_w = NULL; //inizializzo puntatori che puntano a nulla;
    double* ptr_r = NULL;

    //leggo file uan riga alla volta
    while (getline (myFile,line)) {
        bool data = isdigit(line[0]); //variabile booleana per capire se sto leggendo inzio file
        if(!data){
            extract_head(line,delimiter,money,asset); //funzione che legge parte inziale file e estrapola valore di S e di n
        }
        else{
            //la prima volta alloco spazio in memoria dalla seconda in poi assegno solo valori
            if(first){
                ptr_w = new double[asset]; //puntatore assegnato a nuova memoria che punta primp elemento di array di dimensione size(double)*asset
                ptr_r = new double[asset];
                first = false;
            }
            ptr_w[counter] = stod(line.substr(0,line.find(delimiter))); //prendo sottostringa e poi trasfromo in double
            ptr_r[counter] = stod(line.substr(line.find(delimiter)+1));
            counter++;
        }
        }

    //Chiusura file
    myFile.close();

    //calcolo il valore del portafoglio
    double value = value_calculator(ptr_w,ptr_r,asset,money);
    double rate = (value/money) -1;

    //print
    string output_file_name = "result.txt";
    print(output_file_name,money,asset,ptr_w,ptr_r,value,rate);

    //cancello array
    delete [] ptr_w;
    delete [] ptr_r;

  return 0;
}

