#pragma once

#include<iomanip>

using namespace std;

void extract_head(string &line, string &delimiter, double& money, int& asset);

double value_calculator(double* ptr_w, double*ptr_v,int &counter,double &money);

void print(string &output_file_name,double &money,int &asset,double* ptr_w, double* iptr_r,double &value, double &rate);
