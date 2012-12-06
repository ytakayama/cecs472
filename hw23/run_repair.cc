// Yohei Takayama
// cecs274  Homework23  11/26/2012
// run_repair.cc

#include <iostream>
#include "vector_handler.hh"
using namespace std;

typedef Repair_Shop *Repair_Shop_ptr;

int run_shop(Repair_Shop_ptr shop){
  struct Repair_Shop::repairInfo repair_stuff;
  struct Repair_Shop::garageInfo garage_contents;
  while (1) {
    char command;
    unsigned long VIN;
    unsigned long repairTime;
    float repairCost;
    cout <<  "a)queue, b)repair, c)cars in q)quit \n" ;
    cin >> command ;
    switch (command) {
      case 'a':
        cout << "VIN? " ;
        cin >> VIN ;
        cout << "time to repair? " ;
        cin >> repairTime ;
        cout <<  "estimated cost? " ;
        cin >> repairCost ;
        shop->QueueCar(repairTime,repairCost,VIN);
        break;
      case 'b':
        cout <<  "id? " ;
        cin >> VIN ;
        repair_stuff = shop->RepairCar(VIN);
        cout << " Repaired, time: " << repair_stuff.timeToRepair ;
        cout << " cost: " << repair_stuff.costToRepair << endl ;
        break;
      case 'c':
        garage_contents = shop->CarsInGarage();
      	for (int i=0 ; i<5; i++) {
      	  cout << garage_contents.VINs[i] << "  " ;
      	};
      	cout << endl;
        break;
      case 'q':
        return 0;
      default: 
        cout << "Unrecognized option\n" ;
    }
  }
}

int main(int argc, char *argv[]){
  Repair_Shop *ourShop = new Repair_Shop;
  return run_shop(ourShop);
};
