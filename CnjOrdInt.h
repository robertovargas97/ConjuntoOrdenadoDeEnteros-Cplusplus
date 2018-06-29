/* 
 * File:   CnjOrdInt.h
 * Author: Roberto Vargas
 *
 * Created on 10 de agosto de 2017, 10:50 AM
 */

#ifndef CNJORDINT_H
#define CNJORDINT_H

#include <string.h>
#include <iostream>
#include <sstream> 
#include <memory>

using namespace std;

class CnjOrdInt {
    //Representa un conjunto ordenado de enteros

public:
    //EFE: construye un nuevo conjunto de enteros vacio.
    CnjOrdInt();

    //EFE: Construye una copia identica e independiente de orig
    CnjOrdInt(const CnjOrdInt& orig);


    ~CnjOrdInt();

    //MOD: *this
    //EFE: si x no pertenece al objeto entomces lo agrega en orden
    //retorna true,en caso contrario no tiene efecto y retorna false
    bool insertarOrd(int x);

    //MOD:*this
    //EFE: si x pertenece a *this entonces lo elimina preservando el orden
    //retorn true , en caso dcontario, no tiene efecto y retorna false
    bool eliminar(int x);

    //EFE: retorna true si x pertenece al objeto o false en caso contrario
    bool buscar(int x) const; //el const indica que el objeto que recibe la
    //accion no es modificado

    //EFE: retorna un nuevo conjunto ordenado que representa la union de *this con b
    CnjOrdInt& operator+(const CnjOrdInt& b) const;

    //EFE: retorna un nuevo conjunto ordenado que representa la interseccion de *this con b
    CnjOrdInt& operator*(const CnjOrdInt& b) const;

    //EFE: retorna un nuevo conjunto ordenado que representa la diferencia de *this con b
    CnjOrdInt& operator-(const CnjOrdInt& b) const;

    //EFE: retorna un nuevo conjunto ordenado que representa la diferencia simetrica de *this con b
    CnjOrdInt& operator/(const CnjOrdInt& b) const;

    //EFE: retorma una hilera que representa al conjunto
    //Por ejemplo "{}"`çpara el vacio y "{1,2,3}"
    string aHil();

private:

    struct NdoInt {
        int dato;
        shared_ptr<NdoInt> sgt;

        //Constructor de NdoInt

        NdoInt(int x) : dato(x), sgt(0) {
        }

        ~NdoInt() {
            // cout << "Borrando : " << dato << endl;
        };

    };

    shared_ptr<NdoInt> inicio;
    static shared_ptr<CnjOrdInt> cnj_nvo_ptr;
};

#endif /* CNJORDINT_H */

