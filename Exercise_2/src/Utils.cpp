#include "Utils.hpp"

#include<iostream>
#include<fstream>

using namespace std;


void extract_head(string &line, string &delimiter, double& money, int& asset){
    if(line[0] == 'S'){
        money = stod(line.substr(line.find(delimiter)+1));
    }
    if(line[0] == 'n'){
        asset = stoi(line.substr(line.find(delimiter)+1));
    }
}

double value_calculator(double* ptr_w, double*ptr_v, int &asset, double &money){
    double value = 0;
    for(int counter = 0;counter < asset; counter++ ){
        value = value + (1+*(ptr_v+counter)) * ((*(ptr_w+counter)) * money);
    }
    return value;
}

void print(string &output_file_name, double &money,int &asset,double* ptr_w,double* ptr_r,double &value, double &rate){
    ofstream ofs(output_file_name);
    if ( ofs.is_open() ) { //controllo che il file si apra correttamente

        ofs <<setprecision(2)<< fixed;
        ofs << "S = " << money << ", n = " << asset << "\n";

        //print array
        ofs << defaultfloat;
        ofs << "w = [ ";
        for ( int i = 0; i < asset; i++){
            ofs << *(ptr_w + i) << " ";
        }
        ofs << "] " << "\n";
        ofs << "r = [ ";
        for ( int i = 0; i < asset; i++){
            ofs << *(ptr_r + i) << " ";
        }
        ofs << "]" << "\n";

        // print result
        ofs << setprecision(4) << fixed << "Rate of return of the portfolio: " << rate << "\n";
        ofs << setprecision(2) << "V: " << value << "\n";

        //chiusrua file (importnate specificare in questo caso perchè voglio riaprilo
        ofs.close();
    }
    else{
        cerr << "Errore apertura/creazione file: " << output_file_name << endl;
    }

    // per non ripetere stampa su terminale apro output file e "copio" su termnale
    ifstream f(output_file_name);
    if(f.is_open()){
        cout << f.rdbuf();
    }
}
