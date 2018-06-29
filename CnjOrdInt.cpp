/* 
 * File:   CnjOrdInt.cpp
 * Author: Roberto Vargas
 * 
 * Created on 10 de agosto de 2017, 10:50 AM
 */

#include "CnjOrdInt.h" 

shared_ptr<CnjOrdInt> CnjOrdInt::cnj_nvo_ptr(nullptr);

CnjOrdInt::CnjOrdInt() : inicio(nullptr) {
}

CnjOrdInt::CnjOrdInt(const CnjOrdInt& orig) {
    shared_ptr<NdoInt> p = orig.inicio;
    if (p == nullptr) {
        inicio = nullptr;
    } else {
        inicio = shared_ptr <NdoInt> (new NdoInt(orig.inicio->dato));
        p = p->sgt;
        shared_ptr<NdoInt> ultimo = inicio;
        while (p != nullptr) { //mientras no se acabe orig
            ultimo->sgt = shared_ptr <NdoInt> (new NdoInt(p->dato));
            p = p->sgt;
            ultimo = ultimo->sgt;
        }
    }
}

CnjOrdInt::~CnjOrdInt() {
    /*shared_ptr<NdoInt> p = inicio;
    shared_ptr<NdoInt> q = nullptr;

    while (p != nullptr) {
        q = p->sgt;
        // delete p;
        p = q;
    }*/
}

bool CnjOrdInt::buscar(int x) const {

    bool rsl = false;
    shared_ptr<NdoInt> p = inicio;

    while (p != nullptr) { //mientras la lista no termine
        if (p->dato == x) { //ya se encontro x en *this
            rsl = true;
            p = nullptr;
        } else { //No se encuentra pero puede estar mas adelante
            if (p->dato < x) {
                p = p->sgt;
            } else {
                p = nullptr;
            }
        }
    }
    return rsl;
}

bool CnjOrdInt::insertarOrd(int x) {
    bool rsl = false;
    shared_ptr<NdoInt> p = inicio;
    shared_ptr<NdoInt> ant = nullptr;

    if (inicio == 0) { //Caso en que la lista este vacia,se agrega el primer elemento
        inicio = shared_ptr <NdoInt> (new NdoInt(x));
        inicio->sgt = nullptr;
        rsl = true;
    } else if (x < inicio->dato) { //Se agrega el valor x al inicio del conjunto
        p = shared_ptr <NdoInt> (new NdoInt(x)); //Se crea un nuevo Nodo
        p->sgt = inicio; //Se liga con el anterior inicio
        inicio = p; //se cambia inicio
        rsl = true;
    } else {
        p = inicio;
        while (p != nullptr) {
            if (p->dato == x) { //Se encontro x, no se agrega
                p = nullptr;
            } else { //todavia no se encuentra pero puede estar mas adelante
                if (p->dato < x) {
                    ant = p;
                    p = p->sgt;
                    if (p == nullptr) {
                        rsl = true;
                    }
                } else {// se concluye que x no esta
                    p = nullptr;
                    rsl = true;
                }
            }
        }
        if (rsl) { //sirve para agregar al medio y al final
            p = ant->sgt; // p podria ser 0 o null
            ant->sgt = shared_ptr <NdoInt> (new NdoInt(x));
            ant->sgt->sgt = p;
        }
    }
    return rsl;
}

bool CnjOrdInt::eliminar(int x) {
    bool rsl = false;
    shared_ptr<NdoInt> p = inicio;
    shared_ptr<NdoInt> ant = nullptr;

    if (inicio != nullptr && inicio->dato < x) {
        if (inicio->dato == x) {
            p = inicio->sgt;
            // delete inicio;
            inicio = p;
        } else {
            while (p != nullptr) { //Hay que buscar x
                if (p->dato == x) {
                    rsl = true;
                    p = nullptr;
                } else { //hay que seguir buscando
                    if (p->dato < x) {
                        ant = p;
                        p = p->sgt;
                    } else {
                        p = nullptr; //No esta y no hay que eliminar
                    }
                }
            }
            if (rsl) { //hay que eliminar en medio o al final
                p = ant->sgt->sgt;
                //delete ant->sgt;
                ant->sgt = p;
            }
        }
    }
    return rsl;
}

CnjOrdInt & CnjOrdInt::operator+(const CnjOrdInt & b) const {
    if (cnj_nvo_ptr != nullptr)
        cnj_nvo_ptr.reset();

    cnj_nvo_ptr = shared_ptr <CnjOrdInt> (new CnjOrdInt());
    CnjOrdInt & cnj_nvo = *cnj_nvo_ptr;
    shared_ptr <NdoInt> p, q, ultimo;
    p = inicio;
    q = b.inicio;
    ultimo = nullptr;

    //Algortimo de match
    while ((p != nullptr) && (q != nullptr)) {
        if (p->dato < q->dato) {
            if (cnj_nvo.inicio == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = cnj_nvo.inicio;
                p = p->sgt;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = ultimo->sgt;
                p = p->sgt;
            }
        } else if (p ->dato > q ->dato) {
            if (cnj_nvo.inicio == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(q->dato));
                ultimo = cnj_nvo.inicio;
                q = q->sgt;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(q->dato));
                ultimo = ultimo->sgt;
                q = q->sgt;
            }
        } else {
            if (ultimo == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = cnj_nvo.inicio;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = ultimo->sgt;
            }
            p = p->sgt;
            q = q->sgt;
        }
    }
    while (q != nullptr) {
        ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(q->dato));
        ultimo = ultimo->sgt;
        q = q->sgt;
    }
    while (p != nullptr) {
        ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
        ultimo = ultimo->sgt;
        p = p->sgt;
    }

    return cnj_nvo;
}

CnjOrdInt & CnjOrdInt::operator*(const CnjOrdInt & b) const {
    if (cnj_nvo_ptr != nullptr)
        cnj_nvo_ptr.reset();
    cnj_nvo_ptr = shared_ptr <CnjOrdInt> (new CnjOrdInt());
    CnjOrdInt & cnj_nvo = *cnj_nvo_ptr;

    shared_ptr <NdoInt> p, q, ultimo;
    p = inicio;
    q = b.inicio;
    ultimo = nullptr;

    //Algortimo de match
    while ((p != nullptr) &&(q != nullptr)) {
        if (p->dato < q->dato) {
            p = p->sgt;
        } else if (p->dato > q->dato) {
            q = q->sgt;
        } else {
            if (ultimo == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = cnj_nvo.inicio;

            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = ultimo->sgt;
            }
            p = p->sgt;
            q = q->sgt;
        }
    }
    return cnj_nvo;
}

CnjOrdInt & CnjOrdInt::operator-(const CnjOrdInt & b) const {
    if (cnj_nvo_ptr != nullptr)
        cnj_nvo_ptr.reset();

    cnj_nvo_ptr = shared_ptr <CnjOrdInt> (new CnjOrdInt());
    CnjOrdInt & cnj_nvo = *cnj_nvo_ptr;
    shared_ptr <NdoInt> p, q, ultimo;
    p = inicio;
    q = b.inicio;
    ultimo = nullptr;

    //Algortimo de match
    while ((p != nullptr) && (q != nullptr)) {
        if (p->dato < q->dato) {
            if (cnj_nvo.inicio == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = cnj_nvo.inicio;
                p = p->sgt;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = ultimo->sgt;
                p = p->sgt;
            }
        } else if (p ->dato > q ->dato) {
            q = q->sgt;
        } else {
            p = p->sgt;
            q = q->sgt;
        }
    }
    while (p != nullptr) {
        if (cnj_nvo.inicio == nullptr) {
            cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
            ultimo = cnj_nvo.inicio;
            p = p->sgt;
        } else {
            ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
            ultimo = ultimo->sgt;
            p = p->sgt;
        }
    }
    return cnj_nvo;
}

CnjOrdInt & CnjOrdInt::operator/(const CnjOrdInt & b) const {
    if (cnj_nvo_ptr != nullptr)
        cnj_nvo_ptr.reset();

    cnj_nvo_ptr = shared_ptr <CnjOrdInt> (new CnjOrdInt());
    CnjOrdInt & cnj_nvo = *cnj_nvo_ptr;
    shared_ptr <NdoInt> p, q, ultimo;
    p = inicio;
    q = b.inicio;
    ultimo = nullptr;

    //Algortimo de match
    while ((p != nullptr) && (q != nullptr)) {
        if (p->dato < q->dato) {
            if (cnj_nvo.inicio == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = cnj_nvo.inicio;
                p = p->sgt;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
                ultimo = ultimo->sgt;
                p = p->sgt;
            }
        } else if (p ->dato > q ->dato) {
            if (cnj_nvo.inicio == nullptr) {
                cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(q->dato));
                ultimo = cnj_nvo.inicio;
                q = q->sgt;
            } else {
                ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(q->dato));
                ultimo = ultimo->sgt;
                q = q->sgt;
            }
        } else {
            p = p->sgt;
            q = q->sgt;
        }
    }
    while (q != nullptr) {
        if (cnj_nvo.inicio == nullptr) {
            cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(q->dato));
            ultimo = cnj_nvo.inicio;
            q = q->sgt;
        } else {
            ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(q->dato));
            ultimo = ultimo->sgt;
            q = q->sgt;
        }
    }
    while (p != nullptr) {
        if (cnj_nvo.inicio == nullptr) {
            cnj_nvo.inicio = shared_ptr <NdoInt>(new NdoInt(p->dato));
            ultimo = cnj_nvo.inicio;
            p = p->sgt;
        } else {
            ultimo -> sgt = shared_ptr <NdoInt>(new NdoInt(p->dato));
            ultimo = ultimo->sgt;
            p = p->sgt;
        }
    }


    return cnj_nvo;
}

string CnjOrdInt::aHil() {
    stringstream fs; //construye una instancia de flujo de salida
    shared_ptr<NdoInt>p = inicio;
    fs << '{';
    while (p != nullptr) {
        fs << p->dato;
        if (p->sgt != nullptr) {
            fs << ',';
        }
        p = p->sgt;
    }
    fs << '}' << endl;
    return fs.str();
}