//Yohei Takayama  //csa472q1
//cecs472 Homework19 11/13/2012
//repair_cif.c

#include <rpc/rpc.h>
#include "repair.h"

extern CLIENT *handle;

void QueueCar(long timeToRepair, float estimatedCost, unsigned long VIN)
{
   // packup
   struct procedure1_in param1;
   param1.time_to_repair = timeToRepair;
   param1.estimated_cost = estimatedCost;
   param1.vin = VIN;

   // call the remote function
   queuecar_1(&param1, handle);
}

void RepairCar(unsigned long VIN, long *timeToRepair, float *costToRepair)
{
   struct procedure2_out *param2; 
   
   // call the remote function
   param2 = repaircar_1(&VIN, handle);

   // pack back
   timeToRepair =  &param2->time_to_repair;
   costToRepair =  &param2->cost_to_repair;
}

void CarsInGarage(unsigned long answer[])
{
    struct procedure3_out * param3;
   
    // call the remote function
    param3 = carsingarage_1(NULL, handle);

    // pack back
    answer[0] = param3->answer[0];
    answer[1] = param3->answer[1];
    answer[2] = param3->answer[2];
    answer[3] = param3->answer[3];
    answer[4] = param3->answer[4];
}

int WorkTimeLeft()
{
    // call the remote function
    int time = *worktimeleft_1(NULL, handle);
    return time;
}

void ClearGarage()
{
    // call the remote function
    cleargarage_1(NULL, handle);
}

int GarageEmpty()
{	
    // call the remote function
    int num = *garageempty_1(NULL, handle);
    return num;
}



