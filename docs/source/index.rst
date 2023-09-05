PiPower - Raspberry Pi USV mit Batterie
=============================================

.. image:: img/media1.jpg
    :width: 100%

**Was macht eine USV?**

Wenn Ihr Raspberry Pi Projekt eine konstante Stromversorgung benötigt, ist es nicht ratsam, sich nur auf das Hauptstromsystem zu verlassen. Je nach Standort können Stromausfälle und -spitzen häufig auftreten und oft stundenlang andauern. Jegliche Stromschwankungen können Ihren Raspberry Pi beschädigen, und ein Stromausfall wird ihn sofort ausschalten. Infolgedessen wird er nicht sicher herunterfahren, was dazu führen kann, dass alle Daten auf der SD-Karte verloren gehen und die Wahrscheinlichkeit erhöht, dass sie zerstört wird.

Deshalb wird die Verwendung einer unterbrechungsfreien Stromversorgung (USV) empfohlen.

Mit einer USV übernimmt bei einem Stromausfall vom Hauptnetz die Batterie oder eine andere Energiequelle und versorgt das Gerät weiterhin ohne es auszuschalten. Eine USV wird oft als Notstromquelle betrachtet. Nachdem die Hauptstromquelle wiederhergestellt ist, wird die USV wieder aufgeladen und ist bereit für den nächsten Notfall.

**Über PiPower**

Genau aus diesem Grund haben wir PiPower entwickelt. PiPower kann als zweite Energiequelle für den Raspberry Pi verwendet werden. Ein USB-C Netzteil, das an den PiPower angeschlossen ist, versorgt den Raspberry Pi direkt mit Strom und lädt gleichzeitig die Batterie mit geringem Strom auf. PiPower kann einen Raspberry Pi bei einem Stromausfall oder bei Unterbrechung der USB-C Hauptversorgung nahtlos mit Energie versorgen.

PiPower liefert eine 5V/3A Stromversorgung, um verschiedene Nutzungsszenarien des Raspberry Pi zu decken. 
Es verfügt über 4 Energieindikatoren; jeder Indikator repräsentiert 25% der Energie und ist mit einem Schalter ausgestattet, um den Raspberry Pi ein-/auszuschalten, ohne das Netzkabel ein- oder auszustecken.

.. warning::
    Wenn Sie den Akku zum ersten Mal einlegen oder wenn er entfernt und erneut eingesetzt wird, funktioniert der Akku nicht ordnungsgemäß. In diesem Fall müssen Sie das Typ-C-Kabel in den Ladeanschluss stecken, um den Schutzschaltkreis auszuschalten, und der Akku kann dann normal verwendet werden.

**Über PiPower Pro** 

PiPower Pro baut auf PiPower auf und integriert ein ESP32 S2 Modul, das eine Echtzeitüberwachung der Batteriespannung und des aktuellen Zustands des Moduls, Eingangs-/Ausgangsspannung und -strom ermöglicht. Es verfügt zudem über eine intelligente Ladestromanpassung und einen nahtlosen Wechsel zwischen Eingangs- und Batteriestrom, um eine kontinuierliche Stromversorgung zu gewährleisten.

In Verbindung mit Home Assistant können Benutzer problemlos auf alle Parameterdaten zugreifen und diese überprüfen sowie Automatisierungen für intelligente Geräteszenarien konfigurieren.

Darüber hinaus bietet PiPower Pro externe IO-Schnittstellen zur Steuerung des Ein-/Aus-Zustands von Untergeräten. Mit seiner Open-Source-ESPHome-Konfiguration können Benutzer IO-Funktionalitäten anpassen und das System mit weiteren Sensoren erweitern.

Sollten Sie Fragen bei der Nutzung unseres Produkts haben, senden Sie bitte eine E-Mail an service@sunfounder.com. Wir werden so schnell wie möglich antworten.

.. toctree::
    Über PiPower Pro<self>
    components
    assemble
    features
    start
    faq

