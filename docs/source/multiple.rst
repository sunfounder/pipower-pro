
Mehrere PiPower Pro Einheiten
------------------------------------------

Wenn Sie mehrere PiPower Pro Einheiten im gleichen Home Assistant 
Umgebung verwenden möchten, müssen Sie die YAML-Einstellungen ändern.
Fügen Sie ``name_add_mac_suffix: true`` unter "esphome" hinzu.

.. code-block::

    esphome:
      name: pipower-pro
      friendly_name: PiPower-Pro
      name_add_mac_suffix: true
