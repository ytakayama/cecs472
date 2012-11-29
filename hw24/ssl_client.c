/* file: ssl_client.c */
/* gcc ssl_client.c -lssl */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <signal.h>

#include "connectTCP.c"

#define pass "password"

int passwd_cb(char *buf, int num,
 int rwflag,void *userdata)
{
  if (num < strlen(pass)+1)
    return 0;
  strcpy(buf, pass);
  return strlen(pass);
};
int main() {
  int s;
  int rn,wn,rslt;
  char message[80];
  struct sockaddr_in      srv_addr;
  SSL_METHOD *meth;
  SSL_CTX *ctx;
  SSL *ssl;
  signal(SIGPIPE,SIG_IGN);
  s = connectTCP("cheetah","7654");
  /* Here comes the SSL stuff */
  SSL_library_init();
  meth = SSLv23_method();
  ctx = SSL_CTX_new(meth);
  SSL_CTX_use_certificate_chain_file(ctx,"client.pem");
  SSL_CTX_set_default_passwd_cb(ctx,passwd_cb);
  SSL_CTX_use_PrivateKey_file(ctx,"client.pem",SSL_FILETYPE_PEM);
  ssl = SSL_new(ctx);
  SSL_set_fd(ssl,s);
  rslt = SSL_connect(ssl);
  strcpy(message,"Client speaks");
  /*Send a message to server*/
  wn = SSL_write(ssl, message, 80);
  /*Get server's reply*/
  rn = SSL_read(ssl, message, 80);
  printf("reply: %s\n",message);
  close(s);
  return 1;
};
