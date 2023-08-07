


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