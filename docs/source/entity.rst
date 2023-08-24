.. _entity:

PiPower Pro Entität
--------------------------

Wenn Sie mit Home Assistant vertraut sind und die Karte selbst anpassen möchten, 
finden Sie hier eine Liste der PiPower Pro Entitäten, die Sie verwenden können.

**Grundinformationen**
    * ``binary_sensor.pipower_pro_battery_low`` - Batteriestatus niedrig (bool)
    * ``binary_sensor.pipower_pro_is_charging`` - Ladezustand (V)

**Schalter**
    * ``switch.pipower_pro_battery_output`` - Batterieausgangsschalter (bool)
    * ``switch.pipower_pro_esp32_power`` - ESP32 Energieversorgungsschalter (bool)
    * ``switch.pipower_pro_external_output`` - Externer Ausgangsschalter (bool)

**Ausgabe**
    * ``sensor.pipower_pro_output_voltage`` - Ausgangsspannung (V)
    * ``sensor.pipower_pro_output_current`` - Ausgangsstrom (A)
    * ``sensor.pipower_pro_output_power`` - Ausgangsleistung (W)
    * ``sensor.pipower_pro_output_energy`` - Verbrauchte Ausgangsenergie (Wh), wird zur Berechnung der gesamten Ausgangsenergie verwendet, kann über Dienste zurückgesetzt werden, siehe alle Dienste für Details

**Batterie**
    * ``sensor.pipower_pro_battery_voltage`` - Batteriespannung (V)
    * ``sensor.pipower_pro_battery_current`` - Batteriestrom, positiv beim Laden, negativ beim Entladen (A)
    * ``sensor.pipower_pro_battery_power`` - Batterieausgangsleistung (W)
    * ``sensor.pipower_pro_battery_capacity`` - Batteriekapazität (mAh)
    * ``sensor.pipower_pro_battery_level`` - Batterieladestand (%)

**Eingang**
    * ``sensor.pipower_pro_input_voltage`` - Externe Eingangsspannung (V)

**Steuerung von Untergeräten**
    * ``switch.pipower_pro_sub_device_power`` - Stromsteuersignal des Untergeräts (bool)
    * ``binary_sensor.pipower_pro_sub_device_power_state`` - Betriebszustand des Untergeräts (bool)

**Sonstiges**
    * ``sensor.pipower_pro_battery_capacity_algorithm`` - Batteriekapazitätsalgorithmus (String)
    * ``sensor.pipower_pro_power_source`` - Aktuelle Energiequelle: Batterie/Extern (String)
    * ``sensor.pipower_pro_battery_factory_capacity`` - Nominale Kapazität der Batterie ab Werk (mAh)
    * ``binary_sensor.pipower_pro_external_power`` - Externer Eingangszustand (bool)
    * ``button.pipower_pro_factory_reset`` - Taster für Werksreset (bool)
    * ``update.pipower_pro_firmware`` - Firmware aktualisieren
    * ``switch.pipower_pro_power_switch`` - Ausgangsschalter (bool)
    * ``sensor.pipower_pro_version`` - PiPower Pro Version (String)

**Alle Dienste**
    * ``set_battery_factory_capacity`` - Ändern Sie die nominale Kapazität der Batterie ab Werk (capacity: int, mAh), Standardwert 2000
    * ``enable_coulomb_count_beta`` - Coulomb-Zählalgorithmus aktivieren (enable: bool), Standardwert false
    * ``reset_capacity`` - Aktuelle Kapazität auf nominale Werkkapazität zurücksetzen
    * ``reset_output_energy`` - Ausgangsenergie auf 0 zurücksetzen
    * ``set_edv2`` - Festlegen der Spannung für das Ende der Entladungskalibrierung 2, Standard 6.8. Siehe Coulomb-Zählung für Details
    * ``set_edv1`` - Festlegen der Spannung für das Ende der Entladungskalibrierung 1, Standard 6.5. Siehe Coulomb-Zählung für Details
    * ``set_edv0`` - Festlegen der Spannung für das Ende der Entladungskalibrierung 0, Standard 6.2. Siehe Coulomb-Zählung für Details
    * ``set_rcv`` - Festlegen der Spannung zum Zurücksetzen des Kalibrierungsstatus, Standard 8.0. Siehe Coulomb-Zählung für Details
    * ``simulate_low_power`` - Simulieren eines niedrigen Energiezustands zum Testen von Szenarien mit niedrigem Energieauslöser
