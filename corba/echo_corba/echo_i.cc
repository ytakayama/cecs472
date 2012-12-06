#include "echo.hh"
class Echo_i : public POA_Echo,
               public PortableServer::RefCountServantBase {
  public:
    // struct Line {
    //   char data[20];
    // } ;

    Echo_i() {};
    virtual ~Echo_i() {};
    struct Echo::Line echoString(const struct Echo::Line & mesg){
      return mesg;
    };
};
