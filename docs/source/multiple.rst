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