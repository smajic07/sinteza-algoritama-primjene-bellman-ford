#include "graf.h"

TezinskiGraf::TezinskiGraf(const int &brojVrhova, const bool &usmjeren) : usmjeren(usmjeren) {
    lista_susjedstva.resize(brojVrhova);
}

void TezinskiGraf::dodajGranu(const int &i, const int &j, const double &tezina){
    lista_susjedstva[i].push_back({j, tezina});
    if(!usmjeren) lista_susjedstva[j].push_back({i, tezina});
}

/// v - broj vrhova, e - broj grana
/// dužina najkraćeg puta od čvora pocetni do svih ostalih čvorova u grafu, pri čemu
/// grane mogu biti negativne težine
/// složenost: O(v*e)
bool TezinskiGraf::BelmanFord(const int &pocetni, vector<double> &udaljenosti){

    int n = udaljenosti.size();
    for(int i=0; i<n; i++)
        udaljenosti[i] = INT_MAX;
    udaljenosti[pocetni] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first])
                    udaljenosti[it->first] = udaljenosti[i] + it->second;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                return false; // postoji ciklus negativne težine

    return true;

}

/// PROJEKAT - AISA - Edin Smajić - TKN - 5810/M

/// zad1
/*
24.1-4
Modify the Bellman-Ford algorithm so that it sets v.d to -inf for all vertices v for
which there is a negative-weight cycle on some path from the source to v.
*/
vector<double> TezinskiGraf::belmanFordModifikovan(const int &pocetni){

    int n(lista_susjedstva.size());
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[pocetni] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first])
                    udaljenosti[it->first] = udaljenosti[i] + it->second;

    vector<int> oznaceni;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                oznaceni.push_back(it->first);

    for(int i=0; i<oznaceni.size(); i++)
        DFS_oznaci(oznaceni[i], udaljenosti);

    return udaljenosti;

}

void TezinskiGraf::DFS_oznaci(const int &vrh, vector<double> &udaljenosti){
    if(udaljenosti[vrh] != INT_MIN){
        udaljenosti[vrh] = INT_MIN;
        for(auto it=lista_susjedstva[vrh].begin(); it!=lista_susjedstva[vrh].end(); it++)
            DFS_oznaci(it->first, udaljenosti);
    }
}

/// zad2
/*
24.1-5 *
Let G = (V, E) be a weighted, directed graph with weight function w: E -> R.
Give an O(VE)-time algorithm to find, for each vertex v from V, the value d*(v) =
min (u from V) {d(u,v)}.
*/
vector<double> TezinskiGraf::najmanjiUlazeciPut(const int &pocetni){

    int n(lista_susjedstva.size());
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[pocetni] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   min(udaljenosti[i] + it->second, it->second) < udaljenosti[it->first])
                    udaljenosti[it->first] = min(udaljenosti[i] + it->second, it->second);

    return udaljenosti;

}

/// zad3
/*
24.1-6 *
Suppose that a weighted, directed graph G = (V, E) has a negative-weight cycle.
Give an efficient algorithm to list the vertices of one such cycle. Prove that your
algorithm is correct.
*/
vector<int> TezinskiGraf::ciklusNegativneDuzine(){

    int n(lista_susjedstva.size());
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[0] = 0;
    vector<int> roditelj(n, -1);

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first]){
                    udaljenosti[it->first] = udaljenosti[i] + it->second;
                    roditelj[it->first] = i;
                }

    vector<int> uCiklusu(n, false);
    vector<int> ciklus;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first]){
                uCiklusu[it->first] = true;
                int trenutni(it->first);
                ciklus.push_back(it->first);
                while(!uCiklusu[roditelj[trenutni]]){
                    trenutni = roditelj[trenutni];
                    uCiklusu[trenutni] = true;
                    ciklus.push_back(trenutni);
                }
                for(int j=0; j<ciklus.size(); j++){
                    for(int k=0; k<ciklus.size(); k++){
                        if(j == k) continue;
                        if(roditelj[ciklus[j]]  == roditelj[ciklus[k]]){
                            for(int h=0; h<ciklus.size(); h++){
                                if(h == j or h == k) continue;
                                if(roditelj[ciklus[h]] == ciklus[j]){
                                    ciklus.erase(ciklus.begin() + k);
                                }
                                else if(roditelj[ciklus[h]] == ciklus[k]){
                                    ciklus.erase(ciklus.begin() + j);
                                }
                            }
                        }
                    }
                }
                reverse(ciklus.begin(), ciklus.end());
                return ciklus;
            }

    return {};

}

/// zad4/zad5/zad6
vector<double> TezinskiGraf::rijesiLinearniProgram(){

    int n = lista_susjedstva.size();
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[0] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first])
                    udaljenosti[it->first] = udaljenosti[i] + it->second;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                return {};

    return udaljenosti;

}

/// zad7 - 24.4-10
/*
24.4-10
Suppose that every row in the matrix A of a linear program Ax <= b corresponds to
a difference constraint, a single-variable constraint of the form xi <= bk, or a single-
variable constraint of the form -xi <= bk. Show how to adapt the Bellman-Ford
algorithm to solve this variety of constraint system.
*/
vector<double> TezinskiGraf::rijesiLinearniProgramSaSpecOgranicenjem(){

    int n = lista_susjedstva.size();
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[0] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first])
                    udaljenosti[it->first] = udaljenosti[i] + it->second;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                return {};

    for(int i=1; i<n-1; i++){
        udaljenosti[i] -= udaljenosti[n-1];
    }

    return udaljenosti;

}

/// zad8/zad9
/*
24.4-11
Give an efficient algorithm to solve a system Ax <= b of difference constraints
when all of the elements of b are real-valued and all of the unknowns xi must be
integers.
*/
vector<double> TezinskiGraf::rijesiLinearniProgram2(){

    int n = lista_susjedstva.size();
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[0] = 0;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            it->second = floor(it->second);

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   udaljenosti[i] + it->second < udaljenosti[it->first])
                    udaljenosti[it->first] = udaljenosti[i] + it->second;

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                return {};

    return udaljenosti;

}

/// zad10
/*
24.4-12 *
Give an efficient algorithm to solve a system Ax <= b of difference constraints
when all of the elements of b are real-valued and a specified subset of some, but
not necessarily all, of the unknowns xi must be integers.
*/
vector<double> TezinskiGraf::rijesiLinearniProgram3(){

    int n = lista_susjedstva.size();
    vector<double> udaljenosti(n, INT_MAX);
    udaljenosti[0] = 0;

    for(int brojac=0; brojac<n-1; brojac++)
        for(int i=0; i<n; i++)
            for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
                if(udaljenosti[i] != INT_MAX &&
                   floor(udaljenosti[i] + it->second) < udaljenosti[it->first])
                    udaljenosti[it->first] = floor(udaljenosti[i] + it->second);

    for(int i=0; i<n; i++)
        for(auto it=lista_susjedstva[i].begin(); it!=lista_susjedstva[i].end(); it++)
            if(udaljenosti[i] != INT_MAX &&
               udaljenosti[i] + it->second < udaljenosti[it->first])
                return {};

    return udaljenosti;

}
