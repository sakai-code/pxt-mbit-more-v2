#ifndef MBIT_MORE_DEVICE_H
#define MBIT_MORE_DEVICE_H

#include "pxt.h"

#include "MicroBit.h"
#include "MicroBitConfig.h"

#include "MbitMoreCommon.h"

#if MICROBIT_CODAL
#include "MbitMoreService.h"
class MbitMoreService;
#else // MICROBIT_CODAL
#include "MbitMoreServiceDAL.h"
class MbitMoreServiceDAL;
using MbitMoreService = MbitMoreServiceDAL;
#endif // NOT MICROBIT_CODAL

#if MICROBIT_CODAL
#define LIGHT_LEVEL_SAMPLES_SIZE 11
#define ANALOG_IN_SAMPLES_SIZE 5
#else // NOT MICROBIT_CODAL
#define LIGHT_LEVEL_SAMPLES_SIZE 5
#define ANALOG_IN_SAMPLES_SIZE 5
#endif // NOT MICROBIT_CODAL

#if MICROBIT_CODAL
#define MBIT_MORE_WAITING_MESSAGE_LENGTH 16
#define MBIT_MORE_WAITING_MESSAGE_NOT_FOUND 0xff
#define MBIT_MORE_MESSAGE_LABEL_SIZE 8
#define MBIT_MORE_MESSAGE_CONTENT_SIZE 11
#endif // MICROBIT_CODAL

/**
 * @brief Button ID in MicrobitMore
 * This number is used to memory offset in state data.
 */
enum MbitMoreButtonID
{
  // GPIO array using [0..20]
  P0 = 24,
  P1 = 25,
  P2 = 26,
  A = 27,
  B = 28,
  LOGO = 29,
};

/**
 * @brief Version of this micro:bit
 * 
 */
enum MbitMoreHardwareVersion
{
  MICROBIT_V1 = 1,
  MICROBIT_V2 = 2,
};

/**
 * @brief Version of protocol to use
 * 
 */
enum MbitMoreProtocol
{
  MBIT_MORE_V2 = 2,
};

/**
 * Class definition for main logics of Micribit More Service except bluetooth connectivity.
 *
 */
class MbitMoreDevice {
private:
  /**
   * Constructor.
   * Create a representation of default extension for Scratch3.
   * @param _uBit The instance of a MicroBit runtime.
   */
  MbitMoreDevice(MicroBit &_uBit);

  /**
   * @brief Destroy the MbitMoreDevice object
   *
   */
  ~MbitMoreDevice();

public:
  // setup the class as singleton
  MbitMoreDevice(const MbitMoreDevice &) = delete;
  MbitMoreDevice &operator=(const MbitMoreDevice &) = delete;
  MbitMoreDevice(MbitMoreDevice &&) = delete;
  MbitMoreDevice &operator=(MbitMoreDevice &&) = delete;

  /**
   * @brief Get the Instance object as singleton
   * 
   * @return MbitMoreDevice& 
   */
  static MbitMoreDevice &getInstance() {
    static MbitMoreDevice instance(pxt::uBit);
    return instance;
  }

  /**
   * @brief Microbit runtime
   * 
   */
  MicroBit &uBit;

  /**
   * @brief BLE service for basic micro:bit extension.
   *
   */
  MbitMoreService *basicService;

  /**
   * @brief BLE service for Microbit More extension.
   *
   */
  MbitMoreService *moreService;

  // ---------------------

  /**
   * @brief Index of controllabel GPIO pins.
   * 
   */
  int gpioPin[9] = {0, 1, 2, 8, 12, 13, 14, 15, 16};

  /**
   * @brief Pins which is pull-up at connected.
   * 
   */
  int initialPullUp[3] = {0, 1, 2};

  /**
   * @brief Shadow screen to display on the LED.
   *
   */
  uint8_t shadowPixcels[5][5] = {{0}};

  /**
   * Samples of Light Level.
   */
  int lightLevelSamples[LIGHT_LEVEL_SAMPLES_SIZE] = {0};

  /**
   * @brief Last index of the Light Level Samples.
   *
   */
  size_t lightLevelSamplesLast = 0;

#if MICROBIT_CODAL
  /**
   * @brief Structure of messages in MbitMore.
   * 
   */
  typedef struct {
    char label[MBIT_MORE_MESSAGE_LABEL_SIZE];            /** label of the message */
    MbitMoreMessageType type;                            /** type of the content */
    uint8_t content[MBIT_MORE_MESSAGE_CONTENT_SIZE + 1]; /** content of the message */
  } MbitMoreMessage;

  /**
   * @brief Received message data store from Scratch.
   * 
   */
  MbitMoreMessage receivedMessages[MBIT_MORE_WAITING_MESSAGE_LENGTH] = {{{0}}};
#endif // MICROBIT_CODAL

  /**
   * Samples of Light Level.
   */
  int analogInSamples[3][ANALOG_IN_SAMPLES_SIZE] = {{0}};

#if MICROBIT_CODAL
  /**
   * @brief On-board microphone is in use or not.
   * 
   */
  bool micInUse = false;

  /**
   * @brief Laudness on the microphone.
   * 
   */
  float soundLevel = 0.0;
#endif // MICROBIT_CODAL

  /**
   * Protocol of microbit more.
   */
  int mbitMoreProtocol;

  /**
   * Current mode of all pins.
   */
  MbitMorePullMode pullMode[sizeof(gpioPin) / sizeof(gpioPin[0])];

  /**
   * @brief Set pin configuration for initial.
   *
   */
  void initializeConfig();

  /**
   * @brief Update version data on the charactaristic.
   * 
   */
  void updateVersionData();

  /**
   * @brief Invoked when BLE connected.
   * 
   * @param _e event which has connection data
   */
  void onBLEConnected(MicroBitEvent _e);

  /**
   * @brief Invoked when BLE disconnected.
   * 
   * @param _e event which has disconnection data
   */
  void onBLEDisconnected(MicroBitEvent _e);

  /**
   * @brief Call when a command was received.
   *
   * @param data
   * @param length
   */
  void onCommandReceived(uint8_t *data, size_t length);

  /**
   * @brief Set the pattern on the line of the shadow pixels.
   *
   * @param line Index of the lines to set.
   * @param pattern Array of brightness(0..255) according columns.
   */
  void setPixelsShadowLine(int line, uint8_t *pattern);

  /**
   * @brief Display the shadow pixels on the LED.
   *
   */
  void displayShadowPixels();

  /**
   * @brief Display text on LED.
   *
   * @param text Contents to display with null termination.
   * @param delay The time to delay between characters, in milliseconds.
   */
  void displayText(char *text, int delay);

  /**
   * @brief Update GPIO and sensors state.
   *
   * @param data Buffer for BLE characteristics.
   */
  void updateState(uint8_t *data);

  /**
   * @brief Update data of motion.
   *
   * @param data Buffer for BLE characteristics.
   */
  void updateMotion(uint8_t *data);

  /**
   * @brief Get data of analog input of the pin.
   *
   * @param data Buffer for BLE characteristics.
   * @param pinIndex Index of the pin [0, 1, 2].
   */
  void updateAnalogIn(uint8_t *data, size_t pinIndex);

  /**
   * @brief Sample current light level and return filtered value.
   *
   * @return int Filtered light level.
   */
  int sampleLigthLevel();

  /**
   * @brief Set PMW signal to the speaker pin for play tone.
   * 
   * @param period  PWM period (1000000 / frequency)[us]
   * @param volume laudness of the sound [0..255]
   */
  void playTone(int period, int volume);

  /**
   * @brief Stop playing tone.
   * 
   */
  void stopTone();

#if MICROBIT_CODAL
  /**
   * @brief Return message ID for the label
   * 
   * @param messageLabelChar message label
   * @param messageType
   * @return int 
   */
  int findWaitingMessageIndex(const char *messageLabel, MbitMoreMessageType messageType);

  /**
   * @brief Register message label and retrun message ID.
   *
   * @param messageLabel
   * @param messageType
   * @return int ID for the message label
   */
  int registerWaitingMessage(ManagedString messageLabel, MbitMoreMessageType messageType);

  /**
   * @brief Get type of content for the message ID
   *
   * @param messageID
   * @return content type
   */
  MbitMoreMessageType messageType(int messageID);

  /**
   * @brief Return content of the message as number
   *
   * @param messageID
   * @return content of the message
   */
  float messageContentAsNumber(int messageID);

  /**
   * @brief Return content of the message as string
   *
   * @param messageID
   * @return content of the message
   */
  ManagedString messageContentAsText(int messageID);

  /**
   * @brief Send a labeled message with content in float.
   * 
   * @param messageLabel 
   * @param messageContent 
   */
  void sendMessageWithNumber(ManagedString messageLabel, float messageContent);

  /**
   * @brief Send a labeled message with content in string.
   * 
   * @param messageLabel 
   * @param messageContent 
   */
  void sendMessageWithText(ManagedString messageLabel, ManagedString messageContent);

#endif // MICROBIT_CODAL

  /**
   * Callback. Invoked when a pin event sent.
   */
  void onPinEvent(MicroBitEvent evt);

  /**
   * @brief Display friendly name of the micro:bit.
   * 
   */
  void displayFriendlyName();

private:
  /**
   * @brief Listen pin events on the pin.
   * Make it listen events of the event type on the pin.
   * Remove listener if the event type is MICROBIT_PIN_EVENT_NONE.
   * 
   * @param pinIndex index in edge pins
   * @param eventType type of events
   */
  void listenPinEventOn(int pinIndex, int eventType);

  /**
   * @brief Set pull-mode.
   * 
   * @param pinIndex index to set
   * @param pull pull-mode to set
   */
  void setPullMode(int pinIndex, MbitMorePullMode pull);

  /**
   * @brief Set the value on the pin as digital output.
   * 
   * @param pinIndex index in edge pins
   * @param value digital value [0 | 1]
   */
  void setDigitalValue(int pinIndex, int value);

  /**
   * @brief Set the value on the pin as analog output (PWM).
   * 
   * @param pinIndex index in edge pins
   * @param value analog value (0..1024)
   */
  void setAnalogValue(int pinIndex, int value);

  /**
   * @brief Set the value on the pin as servo driver.
   * 
   * @param pinIndex index in edge pins
   * @param angle the level to set on the output pin, in the range 0 - 180.
   * @param range which gives the span of possible values the i.e. the lower and upper bounds (center +/- range/2). Defaults to DEVICE_PIN_DEFAULT_SERVO_RANGE.
   * @param center the center point from which to calculate the lower and upper bounds. Defaults to DEVICE_PIN_DEFAULT_SERVO_CENTER
   */
  void setServoValue(int pinIndex, int angle, int range, int center);

  /**
   * @brief Invoked when button state changed.
   * 
   * @param evt event which has button states
   */
  void onButtonChanged(MicroBitEvent evt);

  /**
   * @brief Invoked when gesture state changed.
   * 
   * @param evt event which has gesture states.
   */
  void onGestureChanged(MicroBitEvent evt);

  /**
   * @brief Normalize angle when upside down.
   * 
   * @param heading value of the compass heading
   * @return normalizes angle relative to north [degree]
   */
  int normalizeCompassHeading(int heading);
};

#endif // MBIT_MORE_DEVICE_H
