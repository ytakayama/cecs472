#include "vector_handler.hh" 
#include "vector_handlerSK.cc"
#include "do_vectors.cc"
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
 // Get the sior string from the file
 char siorbuf[2048];
 ifstream F("mysior.txt");
 F >> siorbuf ;
 F.close();
 // The object request broker is initialized.
 CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB4");

 // The stringified reference is used to contact the server
 CORBA::Object_var obj = orb->string_to_object(siorbuf);
 Vector_Ops_var Vector_Obj = Vector_Ops::_narrow(obj);
 if (CORBA::is_nil(Vector_Obj)) {
   cerr  << "Object request failed" << endl;
   return -1;
 }

 //Call the procedure that uses the object.
 do_vectors(Vector_Obj);

 orb->destroy(); //cleanup

 return 0; 
}
