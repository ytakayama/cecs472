// Yohei Takayama
// cecs472  homework23  11/26/2012
// repair_shop_i
/* Repair operations ineterface */
#include "repair_services.hh"
class Repair_Shop_i : public POA_Repair_Shop,
		     public PortableServer::RefCountServantBase {

 public: 

//**Note to use these struct, do Repair_Shop::repairInfo and Repair_Shop::garageInfo 
//    struct repairInfo{
//      unsigned long timeToRepair;
//      float costToRepair;
//    };
  
//    struct garageInfo {
//      long VINs[5];
//    };
  
    Repair_Shop_i(){
      for (int i=0 ; i<5; i++) {
        garage[i].timeToRepair = 0;
        garage[i].costToRepair = 0.0;
        garage[i].VIN = 0;
      };
    };
  
    virtual ~Repair_Shop_i() {};
  
    void QueueCar(const unsigned long &timeToRepair, const float  &estimatedCost, const  unsigned long &VIN ) {
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
  
    virtual struct Repair_Shop::repairInfo RepairCar(unsigned long &VIN){
      /* remove a car from the repair queue */
      struct Repair_Shop::repairInfo answer;
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
  
    struct Repair_Shop::garageInfo CarsInGarage( ){
        struct Repair_Shop::garageInfo answer;
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
