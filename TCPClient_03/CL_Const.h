#ifndef ___CL_Const_H___
#define ___CL_Const_H___


#define MAKE_ATTESTATION_NO (work.Msg.Body0.rndNo * 13 / 15 % 20)	

typedef enum SOCKETTYPE{ TCP, UDP };				// ソケットのタイプを表す
typedef enum clOperatingNormally{ clFalse = 0, clTrue };


const int SVRPORTNO = 20250;
const char* MULTICAST_ADDR = "239.1.2.37";

#endif