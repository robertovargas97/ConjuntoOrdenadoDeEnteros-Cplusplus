/* 
 * File:   main.cpp
 * Author: Roberto Vargas
 *
 * Created on 10 de agosto de 2017, 10:48 AM
 */


//Encabezados del sistema
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

//Mis encabezados
#include "CnjOrdInt.h"

int main(int argc, char** argv) {

     CnjOrdInt a, b;

     a.insertarOrd(1);
     a.insertarOrd(2);
     a.insertarOrd(3);
     cout << a.aHil() << endl;

     b.insertarOrd(10);
     b.insertarOrd(11);
     b.insertarOrd(12);
     cout << b.aHil() << endl;

     shared_ptr<CnjOrdInt> e (new CnjOrdInt());
     e->insertarOrd(12);
     e->insertarOrd(9);
     e->insertarOrd(6);
     cout << e->aHil() << endl;
     //delete e;

     // CnjOrdInt c = a + b; //une a con b
     // CnjOrdInt d = a / b; // representa la diferencia simetrica entre a y b 

     //c.insertarOrd(5);
    
             
    /*CnjOrdInt a, b;

    a.insertarOrd(6);
    //a.insertarOrd(7);
    //a.insertarOrd(9);
    //a.insertarOrd(13);
    // a.insertarOrd(22);

    cout << "A: " << a.aHil() << endl;

   // b.insertarOrd(1);
   // b.insertarOrd(2);
   // b.insertarOrd(3);
   // b.insertarOrd(4);
   // b.insertarOrd(5);
    b.insertarOrd(6);
    // b.insertarOrd(17);

    cout << "B: " << b.aHil() << endl;

    CnjOrdInt c = a - b;

    cout << "C: " << c.aHil() << endl;
*/

    return 0;
}

