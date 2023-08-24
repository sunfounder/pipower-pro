

Coulomb-Zähler (Beta)
----------------------------------

Der Coulomb-Zähler-Algorithmus kann die Genauigkeit der Batteriekapazitätsberechnung verbessern, befindet sich jedoch derzeit im Beta-Stadium und kann zu erheblichen Ungenauigkeiten führen. Bitte mit Vorsicht verwenden.

**Coulomb-Zähler aktivieren**

1. Gehen Sie zur Home Assistant-Seite und klicken Sie auf "Entwicklertools" in der linken Seitenleiste.
2. Auf der Entwicklertools-Seite wählen Sie den Tab "Dienste" aus.
3. In der Liste der Dienste wählen Sie ``ESPHome: pipower_pro_enable_coulomb_count_beta``.
4. Schalten Sie den Schalter für ``enable_coulomb_count_beta`` ein.
5. Klicken Sie unten auf den Button **Dienst aufrufen**.
6. Die aktuell ausgewählte Batteriekapazitätsalgorithmus können Sie im Entity ``sensor.pipower_pro_battery_capacity_algorithm`` prüfen.

**Algorithmus**

Der Coulomb-Zähler-Algorithmus berechnet die Energie, indem er jede Sekunde die Strom- und Spannungsmessungen der Batterie integriert.

``Kapazität += Spannung * Strom``

**Abgleich**

Die durch diese Integration berechnete Kapazität entspricht nur 
der Lade-/Entladeenergie ab dem aktuellen Zeitpunkt. 
Um sie mit der tatsächlichen Kapazität der Batterie in Verbindung zu bringen, 
ist ein Abgleichprozess erforderlich.
Die hier verwendete Abgleichmethode ist einfach. 
Die Standardbatteriekapazität des PiPower Pro entspricht der Nennkapazität der Batterie, 
also 2000mAh. Die tatsächliche Batteriekapazität wird geringer sein als dieser Wert. 
Solange die Batterie geladen wird, 
wird die Kapazität auf maximal 2000mAh eingestellt 
(kann über den Dienst ``set_battery_factory_capacity`` geändert werden). 
Wenn die Batterie vollständig geladen ist, 
entspricht der Kapazitätswert der tatsächlichen Batteriekapazität von 2000mAh, 
und der Integrationsberechnungswert entspricht dem tatsächlichen Batteriekapazitätswert.

**Automatische Kalibrierung**

Integrationen können Fehler ansammeln, und die Batteriekapazität wird im Laufe der Zeit abnehmen, wenn die Batterie verwendet wird, was möglicherweise nicht die nominelle Kapazität von 2000mAh erreicht.
Deshalb müssen einige Kalibrierungsmethoden verwendet werden, um die Batteriekapazität zu kalibrieren.

Hier wird die Methode der Kompensierten Endladespannung (CEDV) verwendet.
Das Prinzip der CEDV-Kalibrierungsmethode ist, dass die Spannung am Ende der Batterieentladung relativ genau ist und die Spannungskurve zu diesem Zeitpunkt auch am steilsten ist. Die Verwendung dieser Spannung als Kalibrierungspunkt ist daher angemessener.
Deshalb setzen wir hier 3 EDV-Punkte: edv2 (7%), edv1 (3%) und edv0 (0%).

Nach dem Festlegen dieser 3 Kalibrierspannungen wird PiPower Pro die Batterie kalibrieren, wenn sie zu diesen 3 Punkten entladen wird:
``MaxKapazität = MaxKapazität - Kapazität + MaxKapazität * 7%``
Um eine unbegrenzte Kalibrierung am selben Punkt aufgrund von Spannungsschwankungen zu vermeiden, wird die Kalibrierung auf einmal vor dem Erreichen des RCV (Zurücksetzen der Kalibrierspannung, Standard 8,0V) begrenzt.
Sowohl edv2, edv1, edv0 als auch rcv können im Dienst Service konfiguriert werden, siehe :ref:`entity` für Details.

**Anzeige**

Wenn der Coulomb-Zähler-Algorithmus aktiviert ist, 
wechselt die Batterieanzeige ebenfalls in den Coulomb-Zähler-Modus.
Es besteht jedoch eine geringe Chance, dass die Batterieanzeige falsch ist oder sogar die Batterieanzeige zurückgesetzt wird.

Das Verhältnis zwischen den Batterieanzeigen und der Leistung ist wie folgt:

* 4 LEDs alle an:  75%
* 3 LEDs an:  50%
* 2 LEDs an:  25%
* 1 LED an:  10%
* 4 LEDs alle aus: 0%, Batterien müssen geladen werden.
