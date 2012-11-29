//Yohei Takayama  //csa472q1
//cecs472  Homework15  11/07/2012
//sender.c 

//#include <rpc/types.h>
#include <rpc/xdr.h>
#include "connectUDP.c"
#include "get_port.c"

/* load up two integers and a string using xdr, then ship them */
int main(int argc, char* argv[])
{
    int sock;
    int test_number_a = 6;
    int test_number_b = 47;
    float test_number_c = -34.5;
    char *test_string = "Hi There!!";
    char buffer[80];
    char *host = "localhost";
    char *service = get_port();
    
    switch(argc)
    {
        case 1:
            break;
        case 3:
            service = argv[2];
        case 2:
            host = argv[1];
            break;
        default:
            fprintf(stderr, "usage: UDPtime [host [port]]\n");
            exit(1);
    }

	    
    XDR xdrobject;
    XDR *xdrstream = &xdrobject;
    /* XDR a message */
    xdrmem_create(xdrstream, buffer, 80, XDR_ENCODE);
    xdr_int(xdrstream, &test_number_a);
    xdr_int(xdrstream, &test_number_b);
    xdr_float(xdrstream, &test_number_c);
    xdr_wrapstring(xdrstream, &test_string);
    /* Get a socket (UDP) */ 
    sock = connectUDP(host, service);
    /* send the message */
    write(sock, buffer, 80);
    xdr_destroy(xdrstream);
    close(sock);
    return 0;
}
