Einrichten des sicheren Herunterfahrens
---------------------------------

PiPower Pro verfügt über zwei vorab konfigurierte Pins, 
um den Energiezustand (im Folgenden als Untergeräte bezeichnet) von angeschlossenen Geräten zu überwachen. 
Dies ermöglicht das Fern-Einschalten, das Fern-Ausschalten 
sowie ein automatisches sicheres Herunterfahren, wenn der Akku schwach ist.

.. note:: Wenn der mit HassOS betriebene Host als Untergerät von PiPower Pro eingerichtet ist, verliert er ebenfalls seine Funktion, wenn der Host heruntergefahren wird, und ein Fernstart ist nicht möglich.

* Pin 42 und Sensor-Entität ``binary_sensor.pipower_pro_sub_device_power_state`` lesen den aktuellen Zustand des Geräts.
* Pin 41 und Entität ``switch.pipower_pro_sub_device_power`` steuern die Energieversorgung des Untergeräts.

Zum Beispiel verwenden wir PiPower Pro als eine USV-Stromquelle für einen Raspberry Pi, 
überwachen dessen Status und schalten ihn 
automatisch sicher ab, wenn die externe Stromversorgung unterbrochen wird und der Akkuladestand niedrig ist.

**Schritt 1**

Konfigurieren Sie den Raspberry Pi.

Legen Sie die beiden Raspberry Pi-Pins 
für den **Power Status Signal Pin** 
und den **Shutdown Signal Pin** fest.
Dies kann über devicetree gemacht werden.

Stecken Sie die SD-Karte mit dem Raspberry Pi-System in Ihren Computer.
Im Stammverzeichnis der Boot-Partition finden Sie ``config.txt``.

.. image:: img/sp230804_143344.png

Öffnen Sie diese und fügen Sie die folgenden zwei Zeilen am Ende unter ``[all]`` hinzu.

.. code-block::

    dtoverlay=gpio-poweroff,gpiopin=17
    dtoverlay=gpio-shutdown,gpio_pin=18

* ``gpio-poweroff`` ist der Ein-/Ausschaltzustand des Raspberry Pi. Nach erfolgreicher Konfiguration setzt der Raspberry Pi diesen Pin beim Einschalten auf hoch und zieht ihn beim Ausschalten auf niedrig.
* ``gpio-shutdown`` steuert das Signal zum Herunterfahren des Raspberry Pi. Nach erfolgreicher Konfiguration bewirkt das Ziehen dieses Pins auf niedrig, dass der Raspberry Pi heruntergefahren wird.

**Schritt 2**

* Verbinden Sie den Pin 42 von PiPower Pro mit dem ``gpio-poweroff``-Pin des Raspberry Pi, hier mit Pin 17.
* Verbinden Sie den Pin 41 von PiPower Pro mit dem ``gpio-shutdown``-Pin des Raspberry Pi, hier mit Pin 18.

**Schritt 3**

Testen Sie nun, ob die beiden oben genannten Signale ordnungsgemäß funktionieren.

Fügen Sie dem Dashboard zwei Entitäten hinzu:

* ``binary_sensor.pipower_pro_sub_device_power_state``
* ``switch.pipower_pro_sub_device_power``

Wenn Sie die **Settings**-Karte hinzufügen (siehe :ref:`add_card_by_editor` für Anweisungen zum Hinzufügen von Karten), werden diese beiden Entitäten enthalten sein und als ``PiPower-Pro Sub Device Power State`` und ``PiPower-Pro Sub Device Power`` bezeichnet.

.. image:: img/sp230804_151521.png

Mit Ersterem können Sie überprüfen, ob der Raspberry Pi funktioniert, 
und mit Letzterem können Sie den Raspberry Pi ausschalten.

.. note:: ``PiPower-Pro Untergeräte-Strom`` kann den Raspberry Pi nur ausschalten. Um ihn einzuschalten, müssen Sie ihm weiterhin Strom zuführen (d.h., den Hauptschalter auf der **PiPower Pro**-Karte einschalten).


**Schritt 4**

Konfigurieren Sie nun Automatisierungen, um PiPower Pro einen sicheren Herunterfahren des Raspberry Pi zu ermöglichen:

1. Öffnen Sie die Home Assistant Konfigurationsseite, klicken Sie in der linken Seitenleiste auf "Einstellungen" und wählen Sie "Automatisierungen."

    .. image:: img/sp230804_170032.png

2. Erstellen Sie eine neue Automatisierung.

    .. image:: img/sp230804_170118.png

    .. image:: img/sp230804_170148.png

3. Klicken Sie auf "In YAML bearbeiten."

    .. image:: img/sp230804_170218.png

4. Ersetzen Sie den vorhandenen Code durch den folgenden Code.

    .. code-block::

        alias: Sicherer Shutdown RPi
        description: Raspberry Pi ausschalten, wenn keine externe Stromversorgung angeschlossen ist und der Akku schwach ist
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

5. Klicken Sie auf "Speichern."

    .. image:: img/sp230804_170504.png

6. Klicken Sie auf "Umbenennen."

    .. image:: img/sp230804_170527.png

7. Gehen Sie einen Schritt zurück. Nun sollten Sie die neu eingerichtete Automatisierung sehen.

    .. image:: img/sp230804_170710.png

.. note:: Weitere Automatisierungen müssen erstellt werden. Befolgen Sie dazu die vorherigen Schritte.

**Strom sparen**

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

**Sync Ausschalten RPi**

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

**Sync Einschalten RPi**

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

**Schritt 5**

Um den Test auszulösen, simulieren wir einen Zustand niedriger Leistung:

1. Öffnen Sie die SERVICES-Oberfläche in den Entwicklertools.

    .. image:: img/sp230804_171500.png

2. Finden Sie ``ESPHome: pipower_pro_simulate_low_power``, aktivieren Sie es und klicken Sie auf die Schaltfläche "Call Service".

    .. image:: img/sp230804_171721.png

Sie werden sehen, dass das PiPower-Batterielicht erlischt 
und der Batteriestand im Überblick auf 10% sinkt.

Der Raspberry Pi wird dann heruntergefahren,
und 2 Sekunden nachdem er das Herunterfahren abgeschlossen hat,
wird der PiPower Pro ausgeschaltet und die PWR-Leuchte erlischt.

