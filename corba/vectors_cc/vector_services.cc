// The services class split out
class Vector_Ops {

  public: 
    struct Vector { 
      int x,y;
    };

    Vector_Ops() {};
    virtual ~Vector_Ops() {};

    virtual struct Vector Add(struct Vector a, struct Vector b) {
      struct Vector Answer;
      Answer.x = a.x + b.x;
      Answer.y = a.y + b.y;
      return Answer;
    };
};
