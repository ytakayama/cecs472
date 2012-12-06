#include <iostream>
using namespace std;
// Note: we do not attempt to maintain a queue. We allows holes in the
//  middle.
class Repair_Service {
  public:
    struct RepairInfo {
      unsigned short time;
      float cost;
      long id;
    };
    struct SummaryInfo {
      long ids[5];
    };

    Repair_Service() {
      int i;
      for (i=0 ; i<5; i++) {
        queue[i].time = 0;   /* estimated time */
        queue[i].cost = 0.0; /* estimated cost */
        queue[i].id = 0;     /* car id */
      }
    };
    virtual ~Repair_Service() {};

    virtual void Queue_Car(unsigned short time, float cost, long id){
      int i;
      //find an empty
      for (i=0 ; i<5; i++ ) {
	if ( queue[i].id ==0 ) break;
      }
      if ( i < 5 ) {
        cout << "added at " << i << endl;
        queue[i].time = time;
        queue[i].cost = cost;
        queue[i].id = id;
      }
    };

    virtual struct RepairInfo Repair_Car(short index){
      struct RepairInfo answer;
      int i;
      cout << "repaired car at slot " << index << endl;
      // Save the answer
      answer = queue[index];
      // Remove the car from the queue
      queue[index].time = 0;
      queue[index].cost = 0.0;
      queue[index].id = 0;
      return answer;
    };
    virtual struct SummaryInfo Summarize(void){
      struct SummaryInfo answer;
      int i;
      for (i=0 ; i<5; i++) {
         answer.ids[i] = queue[i].id;
      }
      return answer;
    };
  private:
    struct RepairInfo queue[5];
};
typedef Repair_Service* Repair_ptr;
int run_repair_shop(Repair_ptr shop){
  struct Repair_Service::RepairInfo repair_stuff;
  struct Repair_Service::SummaryInfo summary;
  while (1) {
    char command;
    unsigned short time;
    float cost;
    long id;
    short index;
    cout << "a)queue, b)repair, c)summarize q)quit " ;
    cin >> command ;
    switch (command) {
      case 'a':
	cout << "estimated time? " ;
	cin >> time;
	cout << "estimated cost? " ;
	cin >> cost;
	cout << "car id? " ;
	cin >> id;
	shop->Queue_Car(time,cost,id);
	break;
      case 'b':
	cout << "index? " ;
	cin >> index;
	repair_stuff = shop->Repair_Car(index);
	cout << "Repaired-> time: " << repair_stuff.time << " cost: " ;
	cout << repair_stuff.cost << " id: " << repair_stuff.id << endl;
	break;
      case 'c':
	summary = shop->Summarize();
	{ int i;
	  cout << "car id summary: " ;
          for (i=0 ; i<5; i++) {
             cout << summary.ids[i] << "  " ;
          }
	  cout << endl;
	}
	break;
      case 'q':
	return 0;
	break;
      default: cout << "Huh?" << endl ;
	break;
    }
  }
}
int main(int argc , char *argv[])
{
  Repair_ptr repair_shop = new Repair_Service;
  return run_repair_shop(repair_shop);
}
