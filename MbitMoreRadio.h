#ifndef MBIT_MORE_RADIO_H
#define MBIT_MORE_RADIO_H

#include "pxt.h"


enum MbitMoreRadioPacketState
{
    NUM = 0x00,
    STRING_AND_NUMBER = 0x01,
    STRING  = 0x02,
    info = 0x03 , //not use
   

}; 

enum MbitMoreRadioControlCommand
{ SETGROUP = 0x00,
  SETSIGNALPOWER = 0x01,
  SENDSTRING = 0x02,
  SENDNUMBER = 0x03,
  SENDVALUE = 0x04,
  GETLASTPACKET = 0x05,
  GETLASTPACKETSIGNAL = 0x06

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

  void sendrawpacket(uint8_t buf[],int len);

  ~MbitMoreRadio();

  

 



};

#endif