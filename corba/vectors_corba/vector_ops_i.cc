/* Vector operations interface */
#include "vector_handler.hh"
class Vector_Ops_i : public POA_Vector_Ops, 
                     public PortableServer::RefCountServantBase {

  public: 
//    struct Vector { 
//      int x,y;
//    };

    Vector_Ops_i() {};
    virtual ~Vector_Ops_i() {};

    virtual struct Vector_Ops::Vector Add(const struct Vector_Ops::Vector &a, const struct Vector_Ops::Vector &b) {
      struct Vector_Ops::Vector Answer;
      Answer.x = a.x + b.x;
      Answer.y = a.y + b.y;
      return Answer;
    };
};

