#ifndef MBIT_MORE_RADIO_H
#define MBIT_MORE_RADIO_H

#include "pxt.h"


enum MbitMoreRadioPacketState
{
    NUM = 0,
    STRING_AND_NUMBER = 1,
    STRING  = 2,
    info = 3 , //not use
    UINT64LENUMBER = 4,
    STRING_AND_UINT64LENUMBER =5

}; 

enum MbitMoreRadioControlCommand
{ SETGROUP = 0,
  SETSIGNALPOWER = 1,
  SENDSTRING = 2,
  SENDNUMBER = 3,
  GETLASTPACKET = 4,
  GETLASTPACKETSIGNAL = 5

};

#define RADIOPACKETSIZE  32 

#define PACKETSTATEINFO  0



class  MbitMoreRadio {
    private:

    uint8_t a = 1;
 

   
public:
 MbitMoreRadio(int group ,int signalpower);
  uint8_t RECEIVEDLASTPACKET[RADIOPACKETSIZE] ;

  void Radiosetgroup(int group);

  void Radiosetsignalpower(int signalpower);

  void onRadioreceived(MicroBitEvent e );

  void sendrawpacket(uint8_t buf);

  ~MbitMoreRadio();

  

 



};

#endif