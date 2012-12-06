#include <iostream>
using namespace std;
class Repair_Shop
{
  public: 

    struct repairInfo{
      unsigned long timeToRepair;
      float costToRepair;
    };
  
    struct garageInfo {
      long VINs[5];
    };
  
    Repair_Shop(){
      for (int i=0 ; i<5; i++) {
        garage[i].timeToRepair = 0;
        garage[i].costToRepair = 0.0;
        garage[i].VIN = 0;
      };
    };
  
    virtual ~Repair_Shop() {};
  
    void QueueCar(unsigned long timeToRepair, float estimatedCost,
        unsigned long VIN ){
      /* Accept a car for repair */
      int i;
      /* find an empty slot */
      for (i=0 ; i<5; i++ ) {
        if ( garage[i].VIN == 0 ) break;
      };
      if (i==5) return; /* Queue full, discard the car*/
      garage[i].VIN = VIN;
      garage[i].timeToRepair = timeToRepair;
      garage[i].costToRepair = estimatedCost;
    };
  
    virtual struct repairInfo RepairCar(unsigned long VIN){
      /* remove a car from the repair queue */
      struct repairInfo answer;
      int i;
      for (i=0 ; i<5; i++ ) {
        if ( garage[i].VIN == VIN ) break;
      }
      if (5 == i) {
        /* didn't find the car */
        answer.timeToRepair = 0;
        answer.costToRepair = 0.0;
      } else {
        answer.timeToRepair = garage[i].timeToRepair;
        answer.costToRepair = garage[i].costToRepair;
        /* We've fixed it, clean out the garage slot */
        garage[i].VIN = 0;
        garage[i].timeToRepair = 0;
        garage[i].costToRepair = 0.0;
      }
      return answer;
    };
  
    struct garageInfo CarsInGarage(void ){
        struct garageInfo answer;
      /* Give the VIN of each of the cars in the garage */
      /* We receive no parameter, we values in an array parameter. */
      int i;
      for (i=0 ; i<5; i++) {
         answer.VINs[i] = garage[i].VIN;
      }
      return answer;
    };
  private:
  
    struct CarEntry {
      unsigned long timeToRepair; /* Minutes */
      float costToRepair;
      unsigned long VIN; /* Vehicle Identification Number */
    };
  
    struct CarEntry garage[5];

};

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
