// The original, non-networked version, in three parts
#include <iostream>
using namespace std;
// The server class
class Vector_Ops {

  public: 
    struct Vector { 
      long x,y;
    };

    Vector_Ops() {};
    virtual ~Vector_Ops() {};

    virtual Vector Add(struct Vector a, struct Vector b) {
      struct Vector Answer;
      Answer.x = a.x + b.x;
      Answer.y = a.y + b.y;
      return Answer;
    };
};

// The user interface part
typedef Vector_Ops* Vector_ptr;
int do_vectors(Vector_ptr Vector_Obj) {
  struct Vector_Ops::Vector p;
  struct Vector_Ops::Vector q;
  struct Vector_Ops::Vector r;
  p.x = 1;
  p.y = 4;
  q.x = 2;
  q.y = 5;
  r = Vector_Obj->Add(p, q);
  cout << "answer (should be (3, 9)) " <<  r.x << "  " <<  r.y << endl;
}

// The main program part
int main() {
  Vector_ptr Vector_Instance = new Vector_Ops;
  return do_vectors(Vector_Instance);
}
