#include "esphome.h"
//#include "esphome/core/component.h"
//#include "esphome/components/remote_base/remote_base.h"

#define LIVOLO_PREAMBLE_DURATION 525
#define LIVOLO_ZERO_DURATION 120
#define LIVOLO_ONE_DURATION 315
#define LIVOLO_NUM_REPEATS 150

class LivoloSwitch : public Component, public Switch {
 public:

  uint8_t  touchID;
  uint16_t  remoteID;
  uint8_t  mTxPin;
  bool mIsHigh;

  LivoloSwitch(uint8_t  TxPin, uint16_t premoteID, uint8_t ptouchID){
        mTxPin = TxPin;
        mIsHigh = false;
        touchID = ptouchID;
        remoteID = premoteID;
  }


  void setup() override {
    pinMode(mTxPin, OUTPUT);
  }

  void write_state(bool state) override {

      SendButton(remoteID,touchID);

      publish_state(state);
  }

  void SendButton(uint16_t remoteId, uint8_t keyId){
    // 7 bit Key Id and 16 bit Remote Id
    uint32_t command = ((uint32_t)keyId & 0x7F) | (remoteId << 7);
    noInterrupts();
    sendCommand(command, 23);
    interrupts();
  }

  void sendCommand(uint32_t command, uint8_t numBits){
    for (uint8_t repeat = 0; repeat < LIVOLO_NUM_REPEATS; ++repeat)
    {
      uint32_t mask = (1 << (numBits - 1));
      sendPreamble();
      for (uint8_t i = numBits; i > 0; --i)
      {
        if ((command & mask) > 0)
        {
          sendOne();
        }
        else
        {
          sendZero();
        }
        mask >>= 1;
      }
    }
    tx(false);
  }

  void sendOne(){
    delayMicroseconds(LIVOLO_ONE_DURATION);
    mIsHigh = !mIsHigh;
    tx(mIsHigh);
  }

  void sendZero(){
    delayMicroseconds(LIVOLO_ZERO_DURATION);
    tx(!mIsHigh);
    delayMicroseconds(LIVOLO_ZERO_DURATION);
    tx(mIsHigh);
  }

  void sendPreamble(){
    tx(true);
    delayMicroseconds(LIVOLO_PREAMBLE_DURATION);
    tx(false);
    mIsHigh = false;
  }

  void tx(bool value){
    digitalWrite(mTxPin, value ? HIGH : LOW);
  }

};
