#include "esphome.h"
using namespace esphome;

class CurrentControl : public Component, public FloatOutput {
  public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  
  void setup() override {
    pinMode(17, OUTPUT);
  }

  protected:
  void write_state(float state) override {
    float maxVoltage = 1.5;
    state = 1 - state;
    float voltage = state * 1.5;
    int value = voltage * 255 / 3.12;
    dacWrite(17, value);
  }
};
