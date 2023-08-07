Advanced Features
=============================


Setting up Safe Shutdown
---------------------------------

PiPower Pro has two pins that are pre-configured to 
monitor the power status (referred to as sub-devices below) of connected devices, 
enabling remote power on, power off, 
and automatic safe shutdown when the battery is low.

.. note:: If the host running HassOS is set as a sub-device of PiPower Pro, it will also lose its functionality when the host shuts down, and remote power-on will not be possible.

* Pin 42 and sensor entity ``binary_sensor.pipower_pro_sub_device_power_state`` read the current state of the device.
* Pin 41 and entity ``switch.pipower_pro_sub_device_power`` control the sub-device power.

For example, let's use PiPower Pro as a UPS power source for a Raspberry Pi, 
monitoring its status and automatically shutting it 
down safely when external power is lost and the battery level is low.

**Step 1**

Configure the Raspberry Pi. 

Set the two Raspberry Pi pins 
to the **Power Status Signal Pin** 
and **Shutdown Signal Pin** respectively. 
This can be done through devicetree.

Insert the SD card with the Raspberry Pi system into your computer. 
In the root directory of the boot partition, find ``config.txt``.

.. image:: img/sp230804_143344.png

Open it and add the following two lines at the end under ``[all]``.

.. code-block::

    dtoverlay=gpio-poweroff,gpiopin=17
    dtoverlay=gpio-shutdown,gpio_pin=18

* ``gpio-poweroff`` is the Raspberry Pi's power on/off status. After successful configuration, the Raspberry Pi will set this pin high when powered on and pull it low when powered off.
* ``gpio-shutdown`` controls the signal for shutting down the Raspberry Pi. After successful configuration, pulling this pin low will trigger the Raspberry Pi to shut down.

**Step 2**


* Connect PiPower Pro's pin 42 to the Raspberry Pi's ``gpio-poweroff`` pin, here using pin 17.
* Connect PiPower Pro's pin 41 to the Raspberry Pi's ``gpio-shutdown`` pin, here using pin 18.

**Step 3**

Now test if the above two signals are working properly.

Add two entities to the Dashboard: 

* ``binary_sensor.pipower_pro_sub_device_power_state``
* ``switch.pipower_pro_sub_device_power``

If you add the **Settings** Card (see :ref:`add_card_by_editor` for instructions on adding cards), these two entities will be included, labeled as ``PiPower-Pro Sub Device Power State`` and ``PiPower-Pro Sub Device Power``.

.. image:: img/sp230804_151521.png

You can use the former to check if the Raspberry Pi is working and 
the latter to power off the Raspberry Pi.

.. note:: ``PiPower-Pro Sub Device Power`` can only power off the Raspberry Pi. To power it on, you still need to supply power to the Raspberry Pi (i.e., turn on the main switch on the **PiPower Pro** Card).

**Step 4**

Next, configure automations to enable PiPower Pro to safely shut down the Raspberry Pi:

1. Open the Home Assistant configuration page, click on "Settings" on the left sidebar, and choose "Automations."

    .. image:: img/sp230804_170032.png

2. Create a new automation.

    .. image:: img/sp230804_170118.png

    .. image:: img/sp230804_170148.png

#. Click "Edit in YAML."

    .. image:: img/sp230804_170218.png

#. Replace the existing code with the following code.

    .. code-block::

        alias: Safe shutdown RPi
        description: Turn off Raspberry Pi if no external power plug in and battery low
        trigger:
          - platform: state
            entity_id:
              - binary_sensor.pipower_pro_external_power
            from: "on"
            to: "off"
          - platform: numeric_state
            entity_id: sensor.pipower_pro_a03846_battery_level
            below: 25
        condition:
          - condition: and
            conditions:
              - condition: state
                entity_id: binary_sensor.pipower_pro_a03846_external_power
                state: "off"
          - condition: and
            conditions:
              - condition: state
                entity_id: switch.pipower_pro_sub_device_power
                state: "on"
        action:
          - type: turn_off
            device_id: a0ee4e356c85c4f69f765ed72baad129
            entity_id: switch.pipower_pro_sub_device_power
            domain: switch
        mode: single

#. Click "Save."

    .. image:: img/sp230804_170504.png

#. Click "rename."

    .. image:: img/sp230804_170527.png

#. Go back one level. Now you should see the newly set automation.

    .. image:: img/sp230804_170710.png

.. note:: We need to create a few more automations. Refer to the previous steps to complete them all.

**Save Power**

.. code-block::

    alias: Save Power
    description: Turn off if raspberry pi power off
    trigger:
      - platform: state
        entity_id:
          - binary_sensor.pipower_pro_sub_device_power_state
        from: "on"
        to: "off"
    condition:
      - condition: state
        entity_id: switch.pipower_pro_sub_device_power
        state: "off"
    action:
      - delay:
        hours: 0
        minutes: 0
        seconds: 2
        milliseconds: 0
      - type: turn_off
        device_id: a0ee4e356c85c4f69f765ed72baad129
        entity_id: switch.pipower_pro_a03846_power_switch
        domain: switch
      - type: turn_off
        device_id: a0ee4e356c85c4f69f765ed72baad129
        entity_id: switch.pipower_pro_a03846_esp32_power
        domain: switch
    mode: single

**Sync Power Off RPi**


.. code-block::

    alias: Sync Power Off RPi
    description: Power Off Raspberry Pi is Switch Off
    trigger:
      - platform: state
        entity_id:
          - switch.pipower_pro_a03846_power_switch
        from: "on"
        to: "off"
    condition: []
    action:
      - type: turn_off
        device_id: a0ee4e356c85c4f69f765ed72baad129
        entity_id: switch.pipower_pro_sub_device_power
        domain: switch
    mode: single

**Sync Power On RPi**

.. code-block::

    alias: Sync Power On RPi
    description: Power On Raspberry Pi is Switch On
    trigger:
      - platform: state
        entity_id:
          - switch.pipower_pro_a03846_power_switch
        from: "off"
        to: "on"
    condition: []
    action:
      - type: turn_on
        device_id: a0ee4e356c85c4f69f765ed72baad129
        entity_id: switch.pipower_pro_sub_device_power
        domain: switch
    mode: single

**Step 5**

We use a simulated low-power state to trigger the test:

1. Open the SERVICES interface in Developer Tools.

    .. image:: img/sp230804_171500.png

2. Find ``ESPHome: pipower_pro_simulate_low_power``, enable it, and click the "Call Service" button.

    .. image:: img/sp230804_171721.png

You will see the PiPower battery light go off, 
and the battery level drop to 10% in the overview.

The Raspberry Pi will then shut down, 
and 2 seconds after it completes the shutdown, 
the PiPower Pro will power off, and the PWR light will go off.



Coulomb Counter (Beta)
----------------------------------

The Coulomb Counter algorithm can improve the accuracy of battery capacity 
calculation, but it is currently in the beta stage and may result in serious 
inaccuracies. Please use it with caution.

**Enable the Coulomb Counter**

1. Go to the Home Assistant page and click on "Developer Tools" on the left sidebar.
2. In the Developer Tools page, select the "Services" tab.
3. In the list of services, choose ``ESPHome: pipower_pro_enable_coulomb_count_beta``.
4. Turn on the switch for ``enable_coulomb_count_beta``.
5. Click the **Call Service** button below.
6. You can check the currently selected battery capacity algorithm in the entity ``sensor.pipower_pro_battery_capacity_algorithm``.

**Algorithm**

The Coulomb Counter algorithm calculates the energy by integrating the current and voltage measurements of the battery every second.

``Capacity += Voltage * Current``

**Matching**

The capacity calculated by this integration is only 
the charge/discharge energy from the current moment. 
To associate it with the actual capacity of the battery, 
a matching process is needed.
The matching method here is simple. 
PiPower Pro's default battery capacity is the nominal capacity of the battery, 
which is 2000mAh. The actual battery capacity will be less than this value. 
As long as the battery is charged, 
the capacity will be set to the maximum of 2000mAh 
(can be changed using the service ``set_battery_factory_capacity``), 
so when the battery is fully charged, 
the capacity value matches the actual battery capacity of 2000mAh, 
and the integration calculation value matches the actual battery capacity value.

**Auto Calibration**

Integration can accumulate errors, and the battery capacity will decrease as the battery is used over time, which may not reach the nominal 2000mAh capacity.
Therefore, some calibration methods need to be used to calibrate the battery capacity.

Here, the Compensated End of Discharge Voltage (CEDV) calibration method is used.
The principle of the CEDV calibration method is that the voltage at the end of the battery discharge is relatively accurate, and the voltage curve at this time is also the steepest. Using this voltage as a calibration point is more appropriate.
So here we set 3 EDV points: edv2 (7%), edv1 (3%), and edv0 (0%).

After setting these 3 calibration voltages, when the battery is discharged to these 3 points, PiPower Pro will calibrate the battery:
``MaxCapacity = MaxCapacity - Capacity + MaxCapacity * 7%``
To avoid unlimited calibration at the same point due to voltage fluctuations, calibration is limited to once before charging reaches RCV (Reset Calibration Voltage, default 8.0V).
Both edv2, edv1, edv0, and rcv can be configured in the service Service, see :ref:`entity` for details.


**Indicator**

When the Coulomb Counter algorithm is enabled, 
the battery indicator will also switch to the Coulomb Counter mode.
However, there is a small chance of incorrect battery level readings or even the battery level resetting.

The relationship between the battery indicators and power is as follows:

* 4 LEDs all on:  75%
* 3 LEDs on:  50%
* 2 LEDs on:  25%
* 1 LED on:  10%
* 4 LEDs all off: 0%, batteries need to be charged.


Custom Development
----------------------------------

If you find that the basic functionality of PiPower Pro is not enough for your needs, you can perform custom development on PiPower Pro.


All software for PiPower Pro is open source. Below is the basic tutorial and preparation for custom development.

1. Open the developer mode of Home Assistant.
    a. Open the Home Assistant management page.
    b. Select "Configuration" in the lower-left corner.
2. Install ESPHome.
    a. Open the Home Assistant management page.
    b. Select "Configuration" in the lower-left corner.
    c. Select "Add-ons."
    d. Click "Add" button.
    e. Search for "esphome."
    f. Click "Install."
    g. After installation, click "Start."
    h. Select "Add to Sidebar."
3. Create a new device.
    a. Click "ESPhome" in the sidebar to enter the ESPHome management page.
    b. Select "New Device."
    c. Enter the device name, such as "PiPower Pro."
    d. For the first configuration, you also need to enter the Wi-Fi account and password.
    e. Select "ESP32 S2."
    f. Confirm and skip the installation.
4. Configure the new device.
    a. Select the device you just created and click "Edit" to enter the YAML editing page.
    b. At the bottom, add the PiPower Pro template:

        .. code-block::

            packages:
              remote_package: github://sunfounder/pipower-pro/pipower-pro-template.yaml@main
    
    c. Click "Install" in the upper right corner to install it on PiPower Pro.

Multiple PiPower Pro Units
------------------------------------------

If you have multiple PiPower Pro units to use in the same Home Assistant 
environment, you need to modify the YAML settings. 
Add ``name_add_mac_suffix: true`` under "esphome."

.. code-block::

    esphome:
      name: pipower-pro
      friendly_name: PiPower-Pro
      name_add_mac_suffix: true


IO Expansion
-----------------

J4 is used for expansion. The IO comes from ESP32 S2.

.. list-table:: IO Expansion
    :widths: 50 25 25 50
    :header-rows: 1

    * - Functions
      - Pin
      - Pin
      - Functions
    * - 5V
      - 5V
      - 3V3
      - 3V3
    * - ADC,Touch,GPIO8
      - 8
      - GND
      - Ground
    * - ADC,Touch,GPIO9
      - 9
      - 10
      - GPIO10,Touch,ADC
    * - ADC,DAC,GPIO18
      - 18
      - 36
      - GPIO36
    * - GPIO37
      - 37
      - 38
      - GPIO38
    * - GPIO39
      - 39
      - 40
      - GPIO40
    * - GPIO41
      - 41
      - 42
      - GPIO42
