HassOS installieren
--------------------------

Dieser Abschnitt wird Sie durch die Installation des Home Assistant Betriebssystems auf Ihrem Raspberry Pi führen.
Bitte beachten Sie, dass durch diesen Prozess alle vorhandenen Inhalte auf Ihrem Raspberry Pi System gelöscht werden. Es ist wichtig, Ihre Daten vorher zu sichern.

**Schritt 1**

Raspberry Pi hat ein grafisches SD-Karten-Schreibprogramm entwickelt, das
unter Mac OS, Ubuntu 18.04 und Windows läuft und für die meisten
Benutzer die einfachste Option ist, da es das Image automatisch herunterlädt und auf die
SD-Karte installiert.

Besuchen Sie die Download-Seite: https://www.raspberrypi.org/software/. Klicken Sie auf
den Link für den **Raspberry Pi Imager**, der zu Ihrem Betriebssystem passt.
Nachdem der Download abgeschlossen ist, klicken Sie darauf, um den Installer zu starten.

.. image:: img/image11.png
    :align: center

.. raw:: html

    <br/>

**Schritt 2**

Wenn Sie den Installer starten, kann Ihr Betriebssystem versuchen,
die Ausführung zu blockieren. Zum Beispiel erhalte ich unter Windows folgende
Meldung:

Erscheint diese Meldung, klicken Sie auf **Weitere Informationen** und dann auf **Trotzdem ausführen** und folgen Sie den Installationsanweisungen des Raspberry Pi Imagers.

.. image:: img/image12.png
    :align: center

.. raw:: html
    
    <br/>

**Schritt 3**

Stecken Sie Ihre SD-Karte in den SD-Karten-Slot Ihres Computers oder Laptops.

**Schritt 4**

Im Raspberry Pi Imager wählen Sie das Betriebssystem, das Sie installieren möchten, und
die SD-Karte, auf die es installiert werden soll.

.. image:: img/sp230627_181014.png

.. image:: img/sp230627_181052.png

.. image:: img/sp230627_181112.png

.. image:: img/sp230627_181306.png

**Schritt 5**

Wählen Sie die SD-Karte, die Sie verwenden.

.. image:: img/image14.png
    :align: center

.. raw:: html
    
    <br/>


**Schritt 6**

Klicken Sie auf den **WRITE**-Knopf.

.. image:: img/sp230627_181444.png

**Schritt 7**

Falls auf Ihrer SD-Karte aktuell Dateien gespeichert sind, sollten Sie diese eventuell zuerst sichern, um sie nicht dauerhaft zu verlieren. Wenn keine Dateien gesichert werden müssen, klicken Sie auf **Yes**.

.. image:: img/image18.png
    :align: center

.. raw:: html
    
    <br/>


**Schritt 8**

Nach einer Weile wird das folgende Fenster erscheinen, um das erfolgreiche Schreiben zu bestätigen.

.. image:: img/sp230628_161104.png
    :align: center

.. raw:: html
    
    <br/>


**Schritt 9**

Als Nächstes konfigurieren wir das WLAN für Pironman.

.. note:: Wenn Sie eine kabelgebundene Verbindung für den Netzwerkzugriff verwenden möchten, können Sie diesen Schritt überspringen.

Öffnen Sie den Datei-Explorer und greifen Sie auf die als ``Hassio-boot`` benannte SD-Karte zu.

.. image:: img/sp230628_095957.png

Erstellen Sie im Hauptverzeichnis einen neuen Ordner namens ``CONFIG``.

.. image:: img/sp230628_100453.png

Innerhalb des ``CONFIG``-Ordners erstellen Sie einen Ordner namens ``network``.

.. image:: img/sp230628_113426.png

Innerhalb des ``network``-Ordners erstellen Sie eine neue Textdatei namens ``my-network`` (ohne Dateiendung).

.. image:: img/sp230628_113506.png

In der Datei ``my-network`` schreiben Sie den folgenden Text und ersetzen dabei ``MY_SSID`` und ``MY_WLAN_SECRET_KEY`` durch den SSID und das Passwort Ihres Netzwerks:

.. code-block::

    [connection]
    id=my-network
    uuid=72111c67-4a5d-4d5c-925e-f8ee26efb3c3
    type=802-11-wireless

    [802-11-wireless]
    mode=infrastructure
    ssid=MY_SSID
    # Entfernen Sie das Kommentarzeichen unten, wenn Ihr SSID nicht gesendet wird
    #hidden=true

    [802-11-wireless-security]
    auth-alg=open
    key-mgmt=wpa-psk
    psk=MY_WLAN_SECRET_KEY

    [ipv4]
    method=auto

    [ipv6]
    addr-gen-mode=stable-privacy
    method=auto

Speichern und schließen Sie die Datei.

**Schritt 10**

Entfernen Sie die microSD-Karte aus Ihrem Computer und stecken Sie sie in den Raspberry Pi. Schließen Sie dann den Strom an (und bei Bedarf das Ethernet-Kabel).

Gehen Sie zurück zu Ihrem Computer und rufen Sie ``homeassistant.local:8123`` auf. Wenn dies nicht funktioniert, können Sie die IP-Adresse über Ihren Router herausfinden.

Beim ersten Start von Home Assistant kann es eine Weile dauern, da die Ersteinrichtung durchgeführt wird.

.. image:: img/sp230628_141749.png

**Schritt 11**

Als Nächstes werden Sie aufgefordert, das erste Konto zu erstellen.

.. image:: img/sp230627_135949.png

Das System wird Sie auffordern, einige erkannte Geräte zu installieren. Für den Moment können Sie dies jedoch überspringen und auf FERTIGSTELLEN klicken.

.. image:: img/sp230627_141016.png

Jetzt haben Sie Home Assistant eingerichtet.
