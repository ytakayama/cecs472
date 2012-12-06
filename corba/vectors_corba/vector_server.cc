#include <fstream>
using namespace std;
#include "vector_handler.hh"    
#include "vector_handlerSK.cc"
#include "vector_ops_i.cc"
int main(int argc, char *argv[]) {
 CORBA::ORB_var orb = CORBA::ORB_init(argc,argv,"omniORB4");
 CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
 PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
 Vector_Ops_i *myobj = new Vector_Ops_i();
 PortableServer::ObjectId_var myobjid = poa->activate_object(myobj);
 obj = myobj->_this();
 // Stringify the reference and put it into a file
 CORBA::String_var sior(orb->object_to_string(obj));
 ofstream F("mysior.txt");
 F << (char*)sior << endl;
 F.close();
 myobj->_remove_ref();
 PortableServer::POAManager_var pman = poa->the_POAManager();
 // start the server
 pman->activate(); 
 orb->run(); 
 orb->destroy();
 return 0;
}

