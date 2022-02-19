#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>

using namespace std;

class TezinskiGraf{
    vector<list<pair<int,double>>> lista_susjedstva;
    bool usmjeren;
public:
    TezinskiGraf(const int &brojVrhova, const bool &usmjeren = false);
    void dodajGranu(const int &i, const int &j, const double &tezina);

    /// rađeno na lv6
    bool BelmanFord(const int &pocetni, vector<double> &udaljenosti);

    /// PROJEKAT - AISA - Edin Smajić - TKN - 5810/M

    /// zad1 - 24.1-4
    vector<double> belmanFordModifikovan(const int &pocetni);
private:
    void DFS_oznaci(const int &vrh, vector<double> &udaljenosti);

public:
    /// zad2 - 24.1-5 *
    vector<double> najmanjiUlazeciPut(const int &pocetni);

    /// zad3 - 24.1-6 *
    vector<int> ciklusNegativneDuzine();

    /// linearno programiranje
    /// zad4/zad5/zad6 - 24.4-1/24.4-2/24.4-6
    vector<double> rijesiLinearniProgram();

    /// zad7 - 24.4-10
    vector<double> rijesiLinearniProgramSaSpecOgranicenjem();

    /// zad8/zad9 - 24.4-11 - modifikacija 24.4-1/24.4-2
    vector<double> rijesiLinearniProgram2();

    /// zad10 - 24.4-12 * - modifikacija 24.4-1
    vector<double> rijesiLinearniProgram3();
};

#endif // GRAF_H
