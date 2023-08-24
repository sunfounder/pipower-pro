PiPower Pro in Home Assistant hinzufügen
==============================================

**Schritt 1**

Setzen Sie die Batterie ein.

**Schritt 2**

Verbinden Sie das USB-C-Ladegerät, bis alle vier Batterieanzeigen leuchten (dies bedeutet, dass die Batterie vollständig geladen ist). Drücken Sie den Ein-/Ausschalter, um das Gerät einzuschalten.

**Schritt 3**

Konfigurieren Sie das Netzwerk für PiPower Pro. Suchen Sie mit Ihrem Handy (oder einem anderen Gerät) nach Wi-Fi und verbinden Sie sich mit dem ``PiPower Pro Fallback Hotspot``. Das Passwort lautet ``123456``.

.. image:: img/pipw_host.jpg

**Schritt 4**

Nachdem Sie verbunden sind, wird auf Ihrem Handy eine Konfigurationsseite angezeigt. Vervollständigen Sie hier die Wi-Fi-Konfiguration für PiPower.

.. image:: img/pipw_wifi.jpg

Wenn die Konfigurationsseite nicht automatisch angezeigt wird, können Sie einen Browser öffnen und ``pipower-pro.local`` besuchen.

**Schritt 5**

Öffnen Sie Ihre Home Assistant Seite, wählen Sie Konfiguration in der linken Seitenleiste und dann Geräte und Dienste.

.. image:: img/sp230803_162403.png

**Schritt 6**

Klicken Sie unten rechts auf ``+ ADD INTEGRATION``.

.. image:: img/sp230803_162631.png

**Schritt 7**

Wählen Sie ``ESPHome`` aus.

.. image:: img/sp230803_162801.png

**Schritt 8**

Geben Sie ``pipower-pro.local`` ein und bestätigen Sie.

.. image:: img/sp230803_162936.png

**Schritt 9**

Wählen Sie einen Bereich dafür aus und schließen Sie die Einrichtung ab.

.. image:: img/sp230803_165117.png

**Schritt 10**

Sie haben PiPower Pro erfolgreich hinzugefügt. Sie können die gewünschten PiPower Pro Konfigurationen im Dashboard hinzufügen.
