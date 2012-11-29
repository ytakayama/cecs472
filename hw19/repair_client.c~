//Yohei Takayma  //csa472q1
//cecs472 Homework19 11/13/2012
//repair_client.c

#include <rpc/rpc.h>
#include <stdlib.h>
#include <stdio.h>
#include "repair.h"

void QueueCar(unsigned long timeToRepair, float estimatedCost, unsigned long VIN );
void RepairCar(unsigned long VIN, long *timeToRepair, float *costToRepair);
void CarsInGarage(unsigned long answer[]);
int WorkTimeLeft();
void ClearGarage();
int GarageEmpty();

CLIENT *handle;

int main (int argc, char* argv[])
{
  char user_input[20];
  unsigned long VIN;
  unsigned long repairTime;
  float repairCost;
  unsigned long VINs[5];

 char *host = "localhost";

    switch(argc)
    {
        case 1:
            break;
        case 2:
            host = argv[1];
            break;
        default:
            fprintf(stderr, "error in repair_client swtich");
            exit(1);
     }

     if((handle = clnt_create(host, REPAIR_PROG, REPAIR_VER, "tcp")) == NULL)
     {
	  clnt_pcreateerror("conver client");
	  exit(-1);
     }

  while (1)
  {
    printf( "a)queue, b)repair, c)cars in d)time left, e)clear f)is empty q)quit \n");
    fgets(user_input,sizeof(user_input)-1, stdin);
    switch (user_input[0]) {
      case 'a':
        printf("VIN? ");
        fgets(user_input,sizeof(user_input)-1, stdin);
        VIN = atoi( user_input );
        printf( "time to repair? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        repairTime = atoi( user_input );
        printf( "estimated cost? " );
        fgets(user_input,sizeof(user_input)-1, stdin);
        repairCost = (float) atof( user_input );
        QueueCar(repairTime,repairCost,VIN);
        break;
      case 'b':
        printf( "id? " );
      fgets(user_input,sizeof(user_input)-1, stdin);
        VIN = atoi( user_input );
        RepairCar(VIN, &repairTime, &repairCost);
        printf( "Repaired %d Time: %d, Cost: %f\n", VIN,  repairTime, 
          repairCost);
        break;
      case 'c':
        CarsInGarage(VINs);
        { int i;
          printf("Cars in Garage: " );
          for (i=0 ; i<5; i++) {
            printf(" %d ", VINs[i] );
          }
          printf("\n");
        }
        break;
      case 'd':
        printf("Amount of Work left %d \n", WorkTimeLeft() ) ;
        break;
      case 'e':
        ClearGarage();
        break;
      case 'f':
        if ( GarageEmpty() ) {
          printf("Garage is empty\n" );
        } else {
          printf("Garage is not empty\n" );
        };
        break;
      case 'q':
        exit(1);
      default: 
        printf( "Unrecognized option\n" );
    }
  }
  return 0;
}
