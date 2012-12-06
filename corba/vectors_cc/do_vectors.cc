// The user interface part split out
#include <iostream>
using namespace std;
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
  cout << "answer (should be (3, 9)) " <<  r.x ;
  cout << "  " <<  r.y << endl ;
  return 0;
};
