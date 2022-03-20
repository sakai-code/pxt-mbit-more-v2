#include "pxt.h"

#include "MbitMoreRadio.h"



MbitMoreRadio::MbitMoreRadio(MbitMoreDevice &_mbitMore) : mbitMore(_mbitMore) {
   

uBit.radio.enable();

 Radiosetgroup(0);
 Radiosetsignalpower(7);



}

void MbitMoreRadio::Radiosetsignalpower(int signalpower){

 uBit.radio.setTransmitPower(signalpower);


 



}


void MbitMoreRadio::Radiosetgroup(int group){

    uBit.radio.setGroup(group);
    


}

void MbitMoreRadio::sendrawpacket( uint8_t buf[],int len){
PacketBuffer b(buf,len);


uBit.radio.datagram.send(b);



}





MbitMoreRadio::~MbitMoreRadio(){

}


