.. _entity:

PiPower Pro Entity
--------------------------

If you are familiar with Home Assistant and want to customize the Card yourself, 
here is a list of PiPower Pro entities you can use.

**Basic Information**
    * binary_sensor.pipower_pro_battery_low - Battery low status (bool)
    * binary_sensor.pipower_pro_is_charging - Charging status (V)

**Switches**
    * switch.pipower_pro_battery_output - Battery output switch (bool)
    * switch.pipower_pro_esp32_power - ESP32 power switch (bool)
    * switch.pipower_pro_external_output - External output switch (bool)

**Output**
    * sensor.pipower_pro_output_voltage - Output voltage (V)
    * sensor.pipower_pro_output_current - Output current (A)
    * sensor.pipower_pro_output_power - Output power (W)
    * sensor.pipower_pro_output_energy - Output energy (Wh) used for calculating total output energy, can be reset via services, see all services for details

**Battery**
    * sensor.pipower_pro_battery_voltage - Battery voltage (V)
    * sensor.pipower_pro_battery_current - Battery current, positive for charging, negative for discharging (A)
    * sensor.pipower_pro_battery_power - Battery output power (W)
    * sensor.pipower_pro_battery_capacity - Battery capacity (mAh)
    * sensor.pipower_pro_battery_level - Battery level (%)

**Input**
    * sensor.pipower_pro_input_voltage - External input voltage (V)

**Sub-device Control**
    * switch.pipower_pro_sub_device_power - Sub-device power control signal (bool)
    * binary_sensor.pipower_pro_sub_device_power_state - Sub-device power state (bool)

**Others**
    * sensor.pipower_pro_battery_capacity_algorithm - Battery capacity algorithm (String)
    * sensor.pipower_pro_power_source - Current output source: Battery/External (String)
    * sensor.pipower_pro_battery_factory_capacity - Battery factory nominal capacity (mAh)
    * binary_sensor.pipower_pro_external_power - External input status (bool)
    * button.pipower_pro_factory_reset - Factory reset button (bool)
    * update.pipower_pro_firmware - Update firmware
    * switch.pipower_pro_power_switch - Output switch (bool)
    * sensor.pipower_pro_version - PiPower Pro version (String)

**All Services**
    * set_battery_factory_capacity - Modify battery factory nominal capacity (capacity: int, mAh), default 2000
    * enable_coulomb_count_beta - Enable Coulomb counting algorithm (enable: bool), default false
    * reset_capacity - Reset current capacity to factory nominal capacity
    * reset_output_energy - Reset output energy to 0
    * set_edv2 - Set End of Discharge Voltage 2, voltage for end-of-discharge calibration 2, default 6.8. See Coulomb count for details
    * set_edv1 - Set End of Discharge Voltage 1, voltage for end-of-discharge calibration 1, default 6.5. See Coulomb count for details
    * set_edv0 - Set End of Discharge Voltage 0, voltage for end-of-discharge calibration 0, default 6.2. See Coulomb count for details
    * set_rcv - Set Reset Calibrate Voltage, voltage for reset calibration status, default 8.0. See Coulomb count for details
    * simulate_low_power - Simulate low power for testing low power trigger scenarios
