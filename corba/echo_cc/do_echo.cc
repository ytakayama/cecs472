typedef Echo* Echo_ptr;
int do_Echo( Echo_ptr Echo_Obj ) {
  struct Echo::Line original;
  struct Echo::Line new_version;
  strcpy( original.data, "Hi there" );
  new_version = Echo_Obj->echoString( original );
  cout << new_version.data << endl;
};
