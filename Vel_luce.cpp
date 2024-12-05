#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "fmtlib.h"
#include "gplot++.h"
#include "funzioni.h"

using namespace std;
using namespace fmt;

double devstd(int ndata, vector<double> data, double media);

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fmt::println("Errore nell'esecuzione! Usa: <eseguibile> <grandezza passo>");
        return -1;
    }

    vector<double> serie, tutti, media(3), devst(3);
    double somma_media{};
    double data{};
    ofstream out("tuttidati.dat");

    Gnuplot histo{};

    for (int k = 1; k <= 3; k++)
    {
        string filename = fmt::format("dati{}.dat", k);
        ifstream in(filename);
        if (!in.is_open())
        {
            fmt::println("Errore nell'apertura del file: {}", filename);
            exit(1);
        }

        somma_media = 0;
        while (in >> data)
        {
            serie.push_back(data);
            tutti.push_back(data);
            somma_media += data;
            cout << data << endl;
            out << data << endl;
        }

        histo.set_yrange(0, NAN); // Replace NAN with a valid range.
        histo.histogram(serie, 20, fmt::format("Histo{}.png", k));
        histo.redirect_to_png(fmt::format("Immagini/Histo{}.png", k));
        histo.show();

        media[k - 1] = somma_media / serie.size();
        devst[k - 1] = devstd(20, serie, media[k - 1]); // Assumendo che devstd sia definita correttamente.
        serie.clear();
        in.close();
    }

    // media pesata
    double num{}, denom{};
    for (int i = 0; i < 3; i++)
    {
        num += double(media[i] / (devst[i] * devst[i]));
        denom += double(1.0 / (devst[i] * devst[i]));
    }

    double media_pesata = double(num / denom);
    out << "Media pesata = " << media_pesata << endl;
    out << "Errore media  = " << double(1.0 / sqrt(denom)) << endl;
    out << "T student  = " << fabs(299792458.0 - media_pesata)/double(1.0 / sqrt(denom)) << endl;
    out << "GDL = " << 58 << endl;
    out.close();

    histo.set_yrange(0, NAN); // Replace NAN with a valid range.
    histo.set_title("Distribuzione velocità rilevate per tutte le configurazioni");
    histo.set_xlabel("Velocità luce");
    histo.histogram(tutti, 20, fmt::format("Velocità luce"));
    histo.redirect_to_png(fmt::format("Immagini/Tuttidati.png"));
    histo.show();

    return 0;
}

double devstd(int ndata, vector<double> data, double media)
{
    double varianza = 0;
    for (int k = 0; k < ndata; k++)
    {
        varianza += (data[k] - media) * (data[k] - media);
    }

    varianza = sqrt(varianza) / double(ndata);
    return varianza;
}
