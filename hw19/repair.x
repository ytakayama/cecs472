/* Yohei Takayama  csa472q1 */
/* cecs472  Homework19  11/13/2012 */
/* repair.x  this is rpcgen file */

/* this is for QUEUECAR: takes unsigned long/float/unsigned long */
struct procedure1_in
{
    unsigned long time_to_repair;
    float estimated_cost;
    unsigned long vin;
};

/* this is for REPAIRCAR: returns long/float */
struct procedure2_out
{
    long time_to_repair;
    float cost_to_repair;
};

/* this is for CARSINGARAGE: returns ansigned long array */
struct procedure3_out
{
    unsigned long answer[5];
};

program REPAIR_PROG
{
    version REPAIR_VER
    {
        void QUEUECAR(procedure1_in) = 1; /* procedure1 */
        procedure2_out REPAIRCAR(unsigned long) = 2; /* procedure 2 */
        procedure3_out CARSINGARAGE(void) = 3; /* procedure 3 */
        int WORKTIMELEFT(void) = 4; /* procedure 4 */
        void CLEARGARAGE(void) = 5; /* procedure 5 */
        int GARAGEEMPTY(void) = 6; /* procedure 6 */
    } = 1;
} = 0x20004e62;
        
