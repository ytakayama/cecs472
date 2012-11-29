//Yohei Takayama  //csa472q1
//cecs472 Homework19 11/13/2012
//repair_sif.c

#include <rpc/rpc.h>
#include "repair.h"

void QueueCar(long timeToRepair, float estimatedCost, unsigned VIN);
void Repaircar(unsigned long VIN, long *timeToRepair, float *costToRepair);
void CarsInGarage(unsigned long answer[]);
int WorkTimeLeft();
void ClearGarage();
int GarageEmpty();


// call the remote function
void * queuecar_1_svc(struct procedure1_in * param1, struct svc_req *dummy)
{
   QueueCar(param1->time_to_repair, param1->estimated_cost, param1->vin);
}

//static struct procedure_2_out param2;
// call the remote function
procedure2_out * repaircar_1_svc(unsigned long * vin, struct svc_req *dummy)
{
    static struct procedure2_out param2;
    RepairCar(*vin, &param2.time_to_repair, &param2.cost_to_repair);
    return &param2;
}

// call the remote function
procedure3_out * carsingarage_1_svc(void *p, struct svc_req *dummy)
{
    static struct procedure3_out param3;
	
    CarsInGarage(param3.answer);
    return &param3;
}

// call the remote function
int * worktimeleft_1_svc(void *p, struct svc_req *dummy)
{
    static int time;
    time = WorkTimeLeft();
    return &time; 
}

// call the remote function
void * cleargarage_1_svc(void *p, struct svc_req *dummy)
{
    static int nothing;
    ClearGarage();
    return &nothing;
}

// call the remote function
int * garageempty_1_svc(void  *p, struct svc_req *dummy)
{
   static int num;
   num = GarageEmpty();
   return &num;
}

