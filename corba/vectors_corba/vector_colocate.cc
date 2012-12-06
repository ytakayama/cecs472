#include <iostream>
using namespace std;
#include "vector_handler.hh"
#include "vector_handlerSK.cc"
#include "vector_ops_i.cc"
#include "do_vectors.cc"
int main(int argc, char *argv[]) {
  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB4");
  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
  PortableServer::POA_var poa=PortableServer::POA::_narrow(obj);

  Vector_Ops_i *myobj = new Vector_Ops_i();
  PortableServer::ObjectId_var myobjid = poa->activate_object(myobj);
  Vector_Ops_var myobjRef = myobj->_this();
  myobj->_remove_ref();
  PortableServer::POAManager_var pman = poa->the_POAManager();
  pman->activate();
  Vector_Ops_ptr Vector_Obj = Vector_Ops::_narrow(myobjRef);
  if (CORBA::is_nil(Vector_Obj)) {
    cerr  << "Object request failed" << endl;
    return -1;
  }
  do_vectors(Vector_Obj);
  orb->destroy();
  return 0;
}
