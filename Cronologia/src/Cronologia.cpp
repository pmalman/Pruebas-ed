#include <iostream>
#include "Cronologia.h"
#include "Fecha_Historica.h"

using namespace std;

//Resize
  void Cronologia::resize(int r){
     if(r>reservados){
     Fecha_Historica *aux = new Fecha_Historica[r];   
     for (int i=0; i<neventos; i++)
        aux[i]=event[i]; 
     delete[] event;
     event = aux;
     reservados=r;
     }
  }
  
//Ordena
  void Cronologia::ordenar(){
     for (int i=neventos-1; i>0; --i) 
      for (int j=0; j<i; ++j)
         if (event[j].getAnio() > event[j+1].getAnio()) {
            Fecha_Historica aux;
            aux = event[j];
            event[j] = event[j+1];
            event[j+1]= aux;
         }
}

//Constructor vacío
  Cronologia::Cronologia():reservados(0),neventos(0),event(0){}
     

//Constructor con parámetro cadena de Fecha_Historica y número de objetos
  Cronologia::Cronologia(Fecha_Historica *eh, int n):reservados(n),neventos(n){
     Fecha_Historica *event = new Fecha_Historica[n];   
     for (int i=0; i<n; i++)
        event[i]=eh[i];
  }

//Constructor de copias
   Cronologia::Cronologia(const Cronologia& c){
      event = new Fecha_Historica[c.reservados];
      neventos = c.neventos;
      reservados = c.neventos;
      for(int i=0; i<neventos; ++i)
         event[i] = c.event[i];
   }

//Añade objeto de Fecha_Historica
  void Cronologia::aniadirEvento(Fecha_Historica& eh){
     //cout << "aniadirEvento " << endl;
     if (neventos == reservados){
        if (neventos==0)
           resize(1);
        else
           resize(2*reservados);
     }
     event[neventos]=eh; //operador asignacion de fecha historica hace falta aqui??
     neventos++;
     //cout << "neventos: " << neventos << endl;
     ordenar();
  }

Cronologia Cronologia::operator=(const Cronologia &crono){
   
     if (this != &crono)
     {

        delete[] event;
        event = new Fecha_Historica[crono.reservados];
        neventos = crono.neventos;
        reservados = crono.neventos;
        for (int i = 0; i < neventos; ++i)
           event[i] = crono.event[i];
     }
     return *this;
  
   
}
Cronologia Cronologia::operator+(const Cronologia &crono){
   Cronologia suma;
   for (int i = 0; i < crono.neventos; i++)
     {
         //cout << "aniadir evento: " << crono.event[i] << endl;
        suma.aniadirEvento(crono.event[i]);
     }
   for (int i = 0; i < neventos; i++)
     {
         //cout << "aniadir evento: " << crono.event[i] << endl;
        suma.aniadirEvento(event[i]);
     }
   return suma;
   
}
void Cronologia::operator+=(const Cronologia &crono)
  {
     //cout <<"numero eventos cronologia 2: " << crono.neventos << endl;
     for (size_t i = 0; i < crono.neventos; i++)
     {
         //cout << "aniadir evento: " << crono.event[i] << endl;
        aniadirEvento(crono.event[i]);
     }
     ordenar();
     
  }

//Busca un evento en la Cronología y devuelve su posición en el vector
  int Cronologia::buscarAnio(int f){
     int i=0;
     bool valido=false;
     while(i<neventos && !valido){
        if(event[i].getAnio()==f)
           valido = true;
        else
           ++i;
     }
     if(!valido)
        i=-1;
     return i;
  }


//Busca un evento en la Cronología y devuelve su posición en el vector
  Cronologia Cronologia::buscarEventos(string s){
     Cronologia nuevo;
     for (int i=0; i < neventos; ++i){
        Fecha_Historica aux;
        if(event[i].buscarEventos(s,aux)){
           nuevo.aniadirEvento(aux);
        }
     }
     nuevo.ordenar();
     return nuevo;
   }

//Operador <<
  ostream& operator<< (ostream& os, const Cronologia& c){
     //cout << "Cronologia << " << c.neventos << endl;
     for(int i=0; i<c.neventos; i++)
        os << c.event[i];
     return os;     
  }

//Operador >>
  istream& operator>> (istream& is, Cronologia& c){
     Fecha_Historica b;
   //   cout << "Cronologia >> ";
     while(is >> b ){
        //cout << "cronologia >> ";
        c.aniadirEvento(b);
     }
     return is;
  } 