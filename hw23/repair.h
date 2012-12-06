/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REPAIR_H_RPCGEN
#define _REPAIR_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct procedure1_in {
	u_long time_to_repair;
	float estimated_cost;
	u_long vin;
};
typedef struct procedure1_in procedure1_in;

struct procedure2_out {
	long time_to_repair;
	float cost_to_repair;
};
typedef struct procedure2_out procedure2_out;

struct procedure3_out {
	u_long answer[5];
};
typedef struct procedure3_out procedure3_out;

#define REPAIR_PROG 0x20004e62
#define REPAIR_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define QUEUECAR 1
extern  void * queuecar_1(procedure1_in *, CLIENT *);
extern  void * queuecar_1_svc(procedure1_in *, struct svc_req *);
#define REPAIRCAR 2
extern  procedure2_out * repaircar_1(u_long *, CLIENT *);
extern  procedure2_out * repaircar_1_svc(u_long *, struct svc_req *);
#define CARSINGARAGE 3
extern  procedure3_out * carsingarage_1(void *, CLIENT *);
extern  procedure3_out * carsingarage_1_svc(void *, struct svc_req *);
#define WORKTIMELEFT 4
extern  int * worktimeleft_1(void *, CLIENT *);
extern  int * worktimeleft_1_svc(void *, struct svc_req *);
#define CLEARGARAGE 5
extern  void * cleargarage_1(void *, CLIENT *);
extern  void * cleargarage_1_svc(void *, struct svc_req *);
#define GARAGEEMPTY 6
extern  int * garageempty_1(void *, CLIENT *);
extern  int * garageempty_1_svc(void *, struct svc_req *);
extern int repair_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define QUEUECAR 1
extern  void * queuecar_1();
extern  void * queuecar_1_svc();
#define REPAIRCAR 2
extern  procedure2_out * repaircar_1();
extern  procedure2_out * repaircar_1_svc();
#define CARSINGARAGE 3
extern  procedure3_out * carsingarage_1();
extern  procedure3_out * carsingarage_1_svc();
#define WORKTIMELEFT 4
extern  int * worktimeleft_1();
extern  int * worktimeleft_1_svc();
#define CLEARGARAGE 5
extern  void * cleargarage_1();
extern  void * cleargarage_1_svc();
#define GARAGEEMPTY 6
extern  int * garageempty_1();
extern  int * garageempty_1_svc();
extern int repair_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_procedure1_in (XDR *, procedure1_in*);
extern  bool_t xdr_procedure2_out (XDR *, procedure2_out*);
extern  bool_t xdr_procedure3_out (XDR *, procedure3_out*);

#else /* K&R C */
extern bool_t xdr_procedure1_in ();
extern bool_t xdr_procedure2_out ();
extern bool_t xdr_procedure3_out ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REPAIR_H_RPCGEN */