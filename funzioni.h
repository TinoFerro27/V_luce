#include <fstream>
#include <iostream>
#include <string>
// argc si becca il numero di parametri passati dalla linea di comando
// argv si becca i parametri passati dalla linea di comando
// il primo parametro è sempre il nome dell'eseguibile
using namespace std;

double media(int ndata, double *data);
double mediana(int ndata, double *data);
double devstd(int ndata, vector<double> data, double media);
void ordina(int ndata, double *data, double *ordinato);
void Print(const double *  data, int ndata);//a video
void Print(const double *  data, int ndata, const char * filename); //su file
