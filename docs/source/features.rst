Merkmale
===============

.. image:: img/media2.png

* **Durchladefunktion**
* **Abschaltstrom：< 0.5mA**
* **Eingang:**

    * USB Typ-C, 5V/3A
    * Batterie-Eingang
* **Ausgang:**

    * USB Typ-A, 5V/3A
    * 2x4P P2.54 Pin-Header

* **Ladeleistung: 5V/2A**
* **Integrierter Akku:**

    * Typ: 3,7V Lithium-Ionen-Akkus x 2
    * Kapazität: 2000mAh
    * Anschluss: PH2.0, 3P

* **Überentladungsschutzspannung: 6,0V**
* **Überladeschutzspannung: 8,4V**
* **Abmessungen: 90mm x 60mm x 24,9mm**
* **Bordindikatoren:**

    * 1 x Ladeanzeige (CHG)
    * 1 x Netzindikator (PWR)
    * 4 Batterieindikatoren (D4 ~ D7)

* **Bordnetzschalter**
* **On-board MCU ESP32 S2**


Detaillierte Einführung
------------------------------------

**STAT LED**

Die STAT LED ist die Statusanzeige für den ESP32 S2.

* Aus: Der ESP32 S2 ist ausgeschaltet.
* Langsames Blinken: Der ESP32 S2 ist eingeschaltet, aber das WLAN ist nicht verbunden.
* Dauerhaft eingeschaltet: Der ESP32 S2 ist eingeschaltet und das WLAN ist verbunden.

.. note:: Der sogenannte "ESP32 S2 ausgeschaltet" Zustand bezieht sich auf die Situation, wenn die USB Type C-Stromversorgung angeschlossen ist. In diesem Zustand ist der ESP32 S2 technisch "ausgeschaltet", aber nicht vollständig heruntergefahren. Die Strom-LED benötigt immer noch den ESP32 S2, um ihre Beleuchtung zu steuern, und einige Funktionen können weiterhin betriebsbereit sein. Wenn Sie jedoch die USB Type C-Stromversorgung trennen, wird der ESP32 S2 vollständig heruntergefahren.

**Umschaltung des Strompfads**

Das PiPower Pro integriert eine Strompfad-Funktion, die automatisch die Strompfade umschaltet, um maximalen Ausgangsschutz zu gewährleisten.

1. Wenn eine externe Stromversorgung angeschlossen ist, wird die 5V-Ausgabe direkt über den externen USB Typ C geliefert und kann über den Schalter ausgeschaltet werden. Die externe Stromquelle lädt den Akku mit so viel Strom wie möglich (siehe Lade-Stromstärke), während sichergestellt wird, dass die Eingangsspannung größer als 4,6V ist.
2. Im Moment der Stromtrennung schaltet das System automatisch nahtlos auf Akkustrom um und stellt sicher, dass das System bei Stromausfällen ordnungsgemäß funktionieren kann.
3. Wenn die externe Stromversorgung unter 4,6V liegt, schaltet das System automatisch auf die Akku-Backup-Stromversorgung um, um zu verhindern, dass externe Geräte den Strom verlieren.

.. list-table:: Logik der Ausgangsleistung
    :widths: 25 50 50
    :header-rows: 1

    * - Schalter 
      - Externe Stromversorgung 
      - Ausgangsstatus
    * - An 
      - Angeschlossen 
      - Externe Stromversorgung
    * - An 
      - Nicht angeschlossen oder Spannung unter 4,6V
      - Akku-Stromversorgung
    * - Aus 
      - Angeschlossen 
      - Aus
    * - Aus 
      - Nicht angeschlossen oder Spannung unter 4,6V
      - Aus

**Ladeleistung**

Im eingeschalteten Zustand wird der Ladestrom automatisch anhand der Eingangsspannung angepasst.

.. list-table:: Logik des Ladestroms
    :widths: 25 50
    :header-rows: 1

    * - Schalter 
      - Ladestrom
    * - An 
      - Anhand der Eingangsspannung angepasst
    * - Aus 
      - 2A

1. Wenn der Schalter auf "Aus" steht, liefert das PiPower Pro keinen externen Strom, und der Ladestrom erreicht ein Maximum von 2A, was ein schnelles Laden ermöglicht. Die Ladezeit von 0% auf 100% beträgt ungefähr 2 Stunden und 10 Minuten.
2. Im "An"-Zustand, da das PiPower Pro externen Strom liefern muss, muss der externe USB auch Strom für den Akku liefern. Um sicherzustellen, dass die Spannung der USB-Stromversorgung stabil bleibt, wird der Ladestrom anhand der Eingangsspannung angepasst, wodurch die Spannung über 4,6V bleibt.






**Tiefentladeschutz**

Wenn die Spannung einer einzelnen Batterie unter 3V fällt, wird der Batterieschutz aktiviert und die Batterie nicht weiter entladen.

Wenn die Batterie ausgesteckt wird, aktiviert der an Bord befindliche Tiefentladeschutzschaltkreis aufgrund seiner Mechanik den Schutz, da die Spannung als zu niedrig betrachtet wird. Wenn Sie die Batterie wieder an das PiPower anschließen, funktioniert die Batterie nicht ordnungsgemäß. In diesem Fall müssen Sie das Type C-Kabel in den Ladeanschluss stecken, um den Schutzschaltkreis auszuschalten, und die Batterie kann dann normal verwendet werden.

**Überladeschutz**

Das Laden endet, wenn die Gesamtspannung der Batterie 8,4V erreicht.

**Ladeausgleich**

Wenn die Spannungen der beiden Batterien nicht gleich sind, wird der Ladestrom der beiden Batterien automatisch angepasst, um die beiden Batterien auszugleichen.

Wenn eine einzelne Batterie 4,2V übersteigt, leitet der Spannungsteiler-Widerstandskanal und der Ladestrom der Batterie wird verringert oder sogar entladen.

**Batterie**

Das Produkt wird mit zwei in Reihe geschalteten 3,7V 18650 Lithium-Ionen-Batterien geliefert, die über einen XH2.54 3P-Anschluss verfügen und eine Nennkapazität von 2000mAh haben.

* Zusammensetzung: Li-ion (Lithium-Ion)
* Kapazität: 2000mAh, 14,8Wh
* Gewicht: 90,8g
* Zellen: 2
* Anschluss: XH2.54 3P
* Überladeschutzspannung: 4,2V pro Zelle
* Tiefentladeschutz: 3V

**Externe Batterie**

.. image:: img/ex_btr0.png

Sie können Ihre eigene Batterie über den Schraubanschluss anschließen. Das Gerät unterstützt nur zwei 3,7V Lithium-Ionen- oder Lithium-Polymer-Batterien. Es ist vorzuziehen, dass die Batterien über eine Schutzplatine verfügen und eine Ausgabe von mehr als 15W sicherstellen.

.. warning:: Schließen Sie nicht gleichzeitig die externe Batterie und die im Lieferumfang enthaltene Batterie an!

.. image:: img/ex_btr.png

**Temperatur**

Wenn die Ausgangsleistung den maximalen Nennwert von 5V/3A erreicht, steigt die Temperatur des DC-DC-Abwärtswandlers U1 auf etwa 70-80 Grad Celsius. Seien Sie also vorsichtig und berühren Sie ihn nicht, um Verbrennungen zu vermeiden und für Belüftung zu sorgen. Wenn die Temperatur die DC-DC-Schutztemperatur von 75 Grad Celsius erreicht, schaltet sich der DC-DC ab, um Überhitzungsschäden zu vermeiden.

.. image:: img/temp_c.png

**D8 LED**

Die D8 LED ist eine Ladezustandsanzeige, die vom IP2326-Ladechip bereitgestellt wird. Ursprünglich wurde diese Leuchte entwickelt, um sowohl den Ladezustand als auch eventuelle Anomalien der Batterie anzuzeigen. Sie kann jedoch nur erkennen, ob im Ladeausgang ein Stromfluss vorhanden ist. Dieser Ausgangsstrom kann über einen DC-DC-Wandler umgeleitet werden, um 5V auszugeben. Einfach ausgedrückt: Wenn nicht genügend Eingangsleistung vorhanden ist, ergänzt die Batterie die Stromversorgung, und währenddessen bleibt die LED ständig eingeschaltet, was irreführend sein kann. Die LED wurde jedoch beibehalten, da sie anzeigen kann, ob die Batterie normal funktioniert (die LED blinkt, wenn die Batterie nicht eingesetzt ist).

Batterieanzeigen
--------------------------

Das Verhältnis zwischen den Batterieanzeigen und der Spannung ist wie folgt:

* 4 LEDs alle eingeschaltet: Spannung > 7,7V
* 3 LEDs eingeschaltet: Spannung > 7,2V
* 2 LEDs eingeschaltet: Spannung > 6,7V
* 1 LED eingeschaltet: Spannung > 6,4V
* 4 LEDs alle ausgeschaltet: Spannung <6V, zu diesem Zeitpunkt müssen die Batterien geladen werden.

