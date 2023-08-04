Advanced Features
=============================

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
