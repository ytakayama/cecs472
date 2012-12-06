class Echo {
  public:
    struct Line {
      char data[20];
    } ;
    Echo() {};
    virtual ~Echo() {};
    struct Line echoString(const struct Line mesg){
      return mesg;
    };
};
