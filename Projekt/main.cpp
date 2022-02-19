#include "graf.h"

/// PROJEKAT - AISA - Edin Smajić - TKN - 5810/M

int main(){

    TezinskiGraf G(5, true);
    G.dodajGranu(0,2,6);
    G.dodajGranu(0,1,7);
    G.dodajGranu(0,4,2);
    G.dodajGranu(2,1,8); /// stavi 4 da se dobije negativan ciklus
    G.dodajGranu(1,4,9); /// stavi -14 da se dobije negativan ciklus
    G.dodajGranu(2,4,-4);
    G.dodajGranu(4,3,7); /// stavi 5 da se dobije negativan ciklus
    G.dodajGranu(2,3,5); /// stavi 1 da se dobije negativan ciklus
    G.dodajGranu(3,2,-2);
    G.dodajGranu(1,3,-3);

    /// zad1
    vector<double> udaljenosti(G.belmanFordModifikovan(0));
    for(int i=0; i<udaljenosti.size(); i++)
        cout << udaljenosti[i]<< " ";
    cout << endl;

    /// zad2
    vector<double> najmanjiPutevi(G.najmanjiUlazeciPut(0));
    for(int i=0; i<najmanjiPutevi.size(); i++)
        cout << najmanjiPutevi[i] << " ";
    cout << endl;

    /// zad3
    vector<int> ciklus(G.ciklusNegativneDuzine());
    if(ciklus.size() > 0){
        for(int i=0; i<ciklus.size(); i++)
            cout << ciklus[i] << " ";
        cout << endl;
    }
    else cout << "Ne postoji ciklus negativne tezine!" << endl;

    /// lp - zad4
/*
24.4-1
Find a feasible solution or determine that no feasible solution exists for the follow-
ing system of difference constraints:
x1 - x2 <= 1 ,
x1 - x4 <= -4 ,
x2 - x3 <= 2 ,
x2 - x5 <= 7 ,
x2 - x6 <= 5 ,
x3 - x6 <= 10 ,
x4 - x2 <= 2 ,
x5 - x1 <= -1 ,
x5 - x4 <= 3 ,
x6 - x3 <= -8 .
*/
    TezinskiGraf G1(7, true);
    G1.dodajGranu(0,1,0);
    G1.dodajGranu(0,2,0);
    G1.dodajGranu(0,3,0);
    G1.dodajGranu(0,4,0);
    G1.dodajGranu(0,5,0);
    G1.dodajGranu(0,6,0);

    G1.dodajGranu(2,1,1);
    G1.dodajGranu(4,1,-4);
    G1.dodajGranu(3,2,2);
    G1.dodajGranu(5,2,7);
    G1.dodajGranu(6,2,5);
    G1.dodajGranu(6,3,10);
    G1.dodajGranu(2,4,2);
    G1.dodajGranu(1,5,-1);
    G1.dodajGranu(4,5,3);
    G1.dodajGranu(3,6,-8);

    vector<double> rjesenje(G1.rijesiLinearniProgram());
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size(); i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

    /// lp - zad5
/*
24.4-2
Find a feasible solution or determine that no feasible solution exists for the follow-
ing system of difference constraints:
x1 - x2 <= 4 ,
x1 - x5 <= 5 ,
x2 - x4 <= -6 ,
x3 - x2 <= 1 ,
x4 - x1 <= 3 ,
x4 - x3 <= 5 ,
x4 - x5 <= 10 ,
x5 - x3 <= -4 ,
x5 - x4 <= -8 .
*/
    TezinskiGraf G2(6, true);
    G2.dodajGranu(0,1,0);
    G2.dodajGranu(0,2,0);
    G2.dodajGranu(0,3,0);
    G2.dodajGranu(0,4,0);
    G2.dodajGranu(0,5,0);

    G2.dodajGranu(2,1,4);
    G2.dodajGranu(5,1,5);
    G2.dodajGranu(4,2,-6);
    G2.dodajGranu(2,3,1);
    G2.dodajGranu(1,4,3);
    G2.dodajGranu(3,4,5);
    G2.dodajGranu(5,4,10);
    G2.dodajGranu(3,5,-4);
    G2.dodajGranu(4,5,-8);

    rjesenje = G2.rijesiLinearniProgram();
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size(); i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

    /// lp - zad6
/*
24.4-6
Suppose that in addition to a system of difference constraints, we want to handle
equality constraints of the form xi = xj + bk. Show how to adapt the Bellman-
Ford algorithm to solve this variety of constraint system.
*/
/// rješenje je da se dato ograničenje xi = xj + bk izrazi preko dvije nejednakosti
/// kako je xi = xj + bk <=> xi - xj = bk
/// xi - xj >= bk <=> xj - xi <= -bk
/// xi - xj <= bk
/// tj. dodaju se ta dva ograničenja u Graf (tj. te dvije grane)

    /// lp - zad7 - 24.4-10
/*
24.4-10
Suppose that every row in the matrix A of a linear program Ax <= b corresponds to
a difference constraint, a single-variable constraint of the form xi <= bk, or a single-
variable constraint of the form -xi <= bk. Show how to adapt the Bellman-Ford
algorithm to solve this variety of constraint system.
*/
/// Rješenje:
/// Podsjetimo se da iz teorije koja se nalazi u knjizi u uvodu u problem linearnog programiranja
/// možemo dodati svakoj varijabli rješenja konstantu, a ono će i dalje ostati rješenje.
/// Upravo iz toga razloga dodat ćemo novu varijablu xn+1 u naš graf, te kakvu god vrijednost
/// ona imala nakon rješavanja linearnog problema koji uključuje i nju, tu vrijednost ćemo
/// oduzeti od svih ostalih xi-ova rješenja tog linearnog problema.
/// Dakle ako je rješenje našeg linearnog problema x1,x2,...,xn,xn+1, konačno rješenje će biti
/// x1-xn+1, x2-xn+1,...,xn-xn+1. - ovo je implementirano u fji rijesiLinearniProgramSaSpecOgranicenjem()
/// Prepostavimo ne umanjujući opštost da se to single ograničenje odnosi na varijablu xn,
/// tj. imamo xn <= bn ili -xn <=bn. Tada:
/// Dodamo novu varijablu xn+1 u naš problem Ax <= b na način da za ograničenje
/// xn <= bn dodamo granu (xn+1, xn) sa težinom bn, jer xn - xn+1 <= bn,
/// a za ograničenje drugog oblika tj. -xn <= bn <=> xn >= -bn dodamo granu (xn, xn+1) sa
/// težinom bn, jer vrijedi xn - xn+1 >= -bn <=> xn+1 - xn <= bn
    TezinskiGraf S(8, true);
    S.dodajGranu(0,1,0);
    S.dodajGranu(0,2,0);
    S.dodajGranu(0,3,0);
    S.dodajGranu(0,4,0);
    S.dodajGranu(0,5,0);
    S.dodajGranu(0,6,0);

    S.dodajGranu(0,7,0); // (x0,xn):0, ovdje je n to n+1

    S.dodajGranu(2,1,1);
    S.dodajGranu(4,1,-4);
    S.dodajGranu(3,2,2);
    S.dodajGranu(5,2,7);
    S.dodajGranu(6,2,5);
    S.dodajGranu(6,3,10);
    S.dodajGranu(2,4,2);
    S.dodajGranu(1,5,-1);
    S.dodajGranu(4,5,3);
    S.dodajGranu(3,6,-8);

    S.dodajGranu(7,3,-1); /// (xn,x3):-1  <=>  x3 <= -1

    rjesenje = S.rijesiLinearniProgramSaSpecOgranicenjem();
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size()-1; i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

    /// lp2 - zad8
/*
24.4-1 - modifikovan
Find a feasible solution or determine that no feasible solution exists for the follow-
ing system of difference constraints:
x1 - x2 <= 1.5 ,
x1 - x4 <= -4.6 ,
x2 - x3 <= 2.4 ,
x2 - x5 <= 7.7 ,
x2 - x6 <= 5.3 ,
x3 - x6 <= 10.8 ,
x4 - x2 <= 2.2 ,
x5 - x1 <= -1.9 ,
x5 - x4 <= 3.1 ,
x6 - x3 <= -8.0 .
*/
    TezinskiGraf G3(7, true);
    G3.dodajGranu(0,1,0);
    G3.dodajGranu(0,2,0);
    G3.dodajGranu(0,3,0);
    G3.dodajGranu(0,4,0);
    G3.dodajGranu(0,5,0);
    G3.dodajGranu(0,6,0);

    G3.dodajGranu(2,1,1.5);
    G3.dodajGranu(4,1,-4.6);
    G3.dodajGranu(3,2,2.4);
    G3.dodajGranu(5,2,7.7);
    G3.dodajGranu(6,2,5.3);
    G3.dodajGranu(6,3,10.8);
    G3.dodajGranu(2,4,2.2);
    G3.dodajGranu(1,5,-1.9);
    G3.dodajGranu(4,5,3.1);
    G3.dodajGranu(3,6,-8.0);

    rjesenje = G3.rijesiLinearniProgram2();
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size(); i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

    /// lp2 - zad9
/*
24.4-2 - modifikovan
Find a feasible solution or determine that no feasible solution exists for the follow-
ing system of difference constraints:
x1 - x2 <= 4.5 ,
x1 - x5 <= 5.6 ,
x2 - x4 <= -6.4 ,
x3 - x2 <= 1.7 ,
x4 - x1 <= 3.3 ,
x4 - x3 <= 5.8 ,
x4 - x5 <= 10.2 ,
x5 - x3 <= -4.9 ,
x5 - x4 <= -8.1 .
*/
    TezinskiGraf G4(6, true);
    G4.dodajGranu(0,1,0);
    G4.dodajGranu(0,2,0);
    G4.dodajGranu(0,3,0);
    G4.dodajGranu(0,4,0);
    G4.dodajGranu(0,5,0);

    G4.dodajGranu(1,2,4.5);
    G4.dodajGranu(1,5,5.6);
    G4.dodajGranu(2,4,-6.4);
    G4.dodajGranu(3,2,1.7);
    G4.dodajGranu(4,1,3.3);
    G4.dodajGranu(4,3,5.8);
    G4.dodajGranu(4,5,10.2);
    G4.dodajGranu(5,3,-4.9);
    G4.dodajGranu(5,4,-8.1);

    rjesenje = G4.rijesiLinearniProgram2();
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size(); i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

    /// lp3 - zad10
/*
24.4-1 - modifikovan
Find a feasible solution or determine that no feasible solution exists for the following
system of difference constraints:
x1 - x2 <= 1.5 ,
x1 - x4 <= -4.6 ,
x2 - x3 <= 2.4 ,
x2 - x5 <= 7.7 ,
x2 - x6 <= 5.3 ,
x3 - x6 <= 10.8 ,
x4 - x2 <= 2.2 ,
x5 - x1 <= -1.9 ,
x5 - x4 <= 3.1 ,
x6 - x3 <= -8.0 .
*/
    TezinskiGraf G5(7, true);
    G5.dodajGranu(0,1,0);
    G5.dodajGranu(0,2,0);
    G5.dodajGranu(0,3,0);
    G5.dodajGranu(0,4,0);
    G5.dodajGranu(0,5,0);
    G5.dodajGranu(0,6,0);

    G5.dodajGranu(2,1,1.5);
    G5.dodajGranu(4,1,-4.6);
    G5.dodajGranu(3,2,2.4);
    G5.dodajGranu(5,2,7.7);
    G5.dodajGranu(6,2,5.3);
    G5.dodajGranu(6,3,10.8);
    G5.dodajGranu(2,4,2.2);
    G5.dodajGranu(1,5,-1.9);
    G5.dodajGranu(4,5,3.1);
    G5.dodajGranu(3,6,-8.0);

    rjesenje = G5.rijesiLinearniProgram3();
    if(rjesenje.size() > 0){
        cout << "Rjesenje je: ";
        for(int i=1; i<rjesenje.size(); i++)
            cout << rjesenje[i] << " ";
        cout << endl;
    }
    else cout << "Nema rjesenja!" << endl;

return 0;
}
