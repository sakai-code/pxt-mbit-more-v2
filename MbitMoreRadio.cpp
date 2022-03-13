#include "pxt.h"

#include "MbitMoreRadio.h"



MbitMoreRadio::MbitMoreRadio(int group,int signalpower){
   
uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this,&MbitMoreRadio::onRadioreceived);
uBit.radio.enable();
 Radiosetgroup(group);
 Radiosetsignalpower(signalpower);


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


void MbitMoreRadio::onRadioreceived( MicroBitEvent e){


    


}

MbitMoreRadio::~MbitMoreRadio(){

}

