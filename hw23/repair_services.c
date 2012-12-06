struct CarEntry {
  unsigned long timeToRepair; /* Minutes */
  float costToRepair;
  unsigned long VIN; /* Vehicle Identification Number */
};
struct CarEntry garage[5] = { {0, 0.0, 0},  {0, 0.0, 0},  {0, 0.0, 0},  
                           {0, 0.0, 0},  {0, 0.0, 0} } ;

/* garage rule: if the VIN is 0, then the slot is empty */

void QueueCar(unsigned long timeToRepair, float estimatedCost, unsigned long VIN ){
  /* Accept a car for repair */
  int i;
  /* find an empty slot */
  for (i=0 ; i<5; i++ ) {
    if ( garage[i].VIN == 0 ) break;
  };
  garage[i].VIN = VIN;
  garage[i].timeToRepair = timeToRepair;
  garage[i].costToRepair = estimatedCost;
};

void RepairCar(unsigned long VIN, long *timeToRepair, float *costToRepair){
  /* remove a car from the repair queue */
  /* We receive one parameter, we return values in two.*/
  int i;
  for (i=0 ; i<5; i++ ) {
    if ( garage[i].VIN == VIN ) break;
  }
  if (5 == i) {
    /* didn't find the car */
    *timeToRepair = 0;
    *costToRepair = 0.0;
  } else {
    *timeToRepair = garage[i].timeToRepair;
    *costToRepair = garage[i].costToRepair;
    /* We've fixed it, clean out the garage slot */
    garage[i].VIN = 0;
    garage[i].timeToRepair = 0;
    garage[i].costToRepair = 0.0;
  }
};

void CarsInGarage(unsigned long answer[]){
  /* Give the VIN of each of the cars in the garage */
  /* We receive no parameter, we return 5 values in an array parameter. */
  int i;
  for (i=0 ; i<5; i++) {
     answer[i] = garage[i].VIN;
  }
};

int WorkTimeLeft() {
  /* Total waiting time till repairs are done */
  /* We receive no parameter, we return an integer.*/
  int i, total = 0;
  for (i=0 ; i<5; i++) {
     if (garage[i].VIN != 0)
       total = total + garage[i].timeToRepair;
  }
  return total;
};
  
void ClearGarage() {
  /* Clear out the list of cars to repair (so we can conduct more tests) */
  int i;
  for (i=0 ; i<5; i++) {
     garage[i].VIN = 0;
     garage[i].timeToRepair = 0;
     garage[i].costToRepair = 0.0;
  }
};

int GarageEmpty() {
  /* Return 1 if the garage is full, 0 if it is not */
  int i;
  for (i=0 ; i<5; i++) {
    if ( 0 != garage[i].VIN ) {
      /* found a car, we are not empty */
      return 0;
    }
  }
  /* Searched but didn't find any cars, we're empty */
  return 1;

};
