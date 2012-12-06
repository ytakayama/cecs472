#include "echo.hh"
#include "echoSK.cc"
#include "echo_i.cc"
#include "do_echo.cc"
int main(int argc, char *argv[] ) {
 CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB4");
 CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
 PortableServer::POA_var poa=PortableServer::POA::_narrow(obj);

 Echo_i *myobj = new Echo_i();
 PortableServer::ObjectId_var myobjid = poa->activate_object(myobj);
 Echo_var myobjRef = myobj->_this();
 myobj->_remove_ref();
 PortableServer::POAManager_var pman = poa->the_POAManager();
 pman->activate();
 do_Echo(myobjRef);
 orb->destroy();
 return 0;
}
