#include <iostream>
int do_Echo( CORBA::Object_ptr obj ) {
  Echo_ptr Echo_Obj = Echo::_narrow(obj);
  if (CORBA::is_nil(Echo_Obj)) {
    cerr << "Object request failed" << endl ;
    return -1;
  }
  struct Echo::Line original;
  struct Echo::Line new_version;
  strcpy( original.data, "Hi there" );
  new_version = Echo_Obj->echoString( original );
  cout << new_version.data << endl;
};
