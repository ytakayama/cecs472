// The main part split out
#include "vector_services.cc"
#include "do_vectors.cc"
int main(int argc, char *argv[]) {
  Vector_ptr Vector_Instance = new Vector_Ops;
  return do_vectors(Vector_Instance);
}
