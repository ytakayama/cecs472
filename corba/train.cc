// We do not attempt to organize the train, we just fill in empty spaces
#include <iostream>
using namespace std;
class Train_Service {
  public:
    struct Unloadinfo {
      unsigned short boxes;
      float weight;
    };
    struct WeightInfo {
      float weights[5];
    };

    Train_Service() {
      int i;
      for (i=0 ; i<5; i++) {
        train[i].id = 0;
        train[i].boxes = 0;
        train[i].weight = 0.0;
      }
    };
    virtual ~Train_Service() {};

    void Load_Train(long id, unsigned short boxes, float weight ){
      int i;
      //find an empty
      for (i=0 ; i<5; i++ ) {
	if ( train[i].id ==0 ) break;
      }
      cout << "added at " << i << endl;
      train[i].id = id;
      train[i].boxes = boxes;
      train[i].weight = weight;
    };

    virtual struct Unloadinfo Unload_Train(long id){
      struct Unloadinfo answer;
      int i;
      for (i=0 ; i<5; i++ ) {
	if ( train[i].id == id ) break;
      }
      cout << "unload at " << i << endl;
      if (5 == i) {
        answer.boxes = 0;
        answer.weight = 0.0;
      } else {
        answer.boxes = train[i].boxes;
        answer.weight = train[i].weight;
        train[i].id = 0;
        train[i].boxes = 0;
        train[i].weight = 0.0;
      }
      return answer;
    };
    virtual struct WeightInfo GetWeights(void){
      struct WeightInfo answer;
      int i;
      for (i=0 ; i<5; i++) {
         answer.weights[i] = train[i].weight;
      }
      return answer;
    };
  private:
    struct Shipment {
      long id;
      unsigned short boxes;
      float weight;
    };
    struct Shipment train[5];
};

typedef Train_Service *Train_ptr;
int run_train(Train_ptr freight){
  struct Train_Service::Unloadinfo unloaded_stuff;
  struct Train_Service::WeightInfo summary;
  while (1) {
    char command;
    long id;
    unsigned short boxes;
    float weight;
    cout << "a)load, b)unload, c)summarize q)quit " ;
    cin >> command ;
    switch (command) {
      case 'a':
        cout << "id? " ;
        cin >> id;
        cout << "boxes? " ;
        cin >> boxes;
        cout << "weight? " ;
        cin >> weight;
        freight->Load_Train(id,boxes,weight);
        break;
      case 'b':
        cout << "id? " ;
        cin >> id;
        unloaded_stuff = freight->Unload_Train(id);
        cout << "Unloaded " << unloaded_stuff.boxes << " boxes; " ;
        cout << unloaded_stuff.weight << " weight" << endl;
        break;
      case 'c':
        summary = freight->GetWeights();
        { int i;
          cout << "weight summary: " ;
          for (i=0 ; i<5; i++) {
             cout << summary.weights[i] << "  " ;
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

int main(int argc, char *argv[]) {
  Train_Service *myTrain = new Train_Service();
  return run_train(myTrain);
}
