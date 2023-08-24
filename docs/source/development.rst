
Maßgeschneiderte Entwicklung
----------------------------------

Sollten Sie feststellen, dass die Grundfunktionen von PiPower Pro nicht ausreichend für Ihre Anforderungen sind, können Sie individuelle Entwicklungen für PiPower Pro durchführen.

Die gesamte Software für PiPower Pro ist Open Source. Hier finden Sie das Grundtutorial und die Vorbereitung für die individuelle Entwicklung.

1. Aktivieren Sie den Entwicklermodus von Home Assistant.
    a. Öffnen Sie die Home Assistant Verwaltungsseite.
    b. Wählen Sie "Configuration" in der unteren linken Ecke.
2. Installieren Sie ESPHome.
    a. Öffnen Sie die Home Assistant Verwaltungsseite.
    b. Wählen Sie "Configuration" in der unteren linken Ecke.
    c. Wählen Sie "Add-ons".
    d. Klicken Sie auf den "Add"-Button.
    e. Suchen Sie nach "esphome".
    f. Klicken Sie auf "Installieren".
    g. Nach der Installation klicken Sie auf "Start".
    h. Wählen Sie "Add to Sidebar".
3. Erstellen Sie ein neues Gerät.
    a. Klicken Sie in der Seitenleiste auf "ESPhome", um die ESPHome Verwaltungsseite aufzurufen.
    b. Wählen Sie "New Device".
    c. Geben Sie den Gerätenamen ein, z.B. "PiPower Pro".
    d. Bei der ersten Konfiguration müssen Sie auch das WLAN-Konto und das Passwort eingeben.
    e. Wählen Sie "ESP32 S2".
    f. Bestätigen Sie und überspringen Sie die Installation.
4. Konfigurieren Sie das neue Gerät.
    a. Wählen Sie das gerade erstellte Gerät aus und klicken Sie auf "Edit", um die YAML-Bearbeitungsseite zu öffnen.
    b. Fügen Sie am Ende die PiPower Pro Vorlage hinzu:

       .. code-block::

           packages:
             remote_package: github://sunfounder/pipower-pro/pipower-pro-template.yaml@main
    
    c. Klicken Sie in der oberen rechten Ecke auf "Installieren", um es auf PiPower Pro zu installieren.




