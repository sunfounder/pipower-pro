Custom Development
----------------------------------

If you find that the basic functionality of PiPower Pro is not enough for your needs, you can perform custom development on PiPower Pro.


All software for PiPower Pro is open source. Below is the basic tutorial and preparation for custom development.

1. Open the developer mode of Home Assistant.
    a. Open the Home Assistant management page.
    b. Select "Configuration" in the lower-left corner.
2. Install ESPHome.
    a. Open the Home Assistant management page.
    b. Select "Configuration" in the lower-left corner.
    c. Select "Add-ons."
    d. Click "Add" button.
    e. Search for "esphome."
    f. Click "Install."
    g. After installation, click "Start."
    h. Select "Add to Sidebar."
3. Create a new device.
    a. Click "ESPhome" in the sidebar to enter the ESPHome management page.
    b. Select "New Device."
    c. Enter the device name, such as "PiPower Pro."
    d. For the first configuration, you also need to enter the Wi-Fi account and password.
    e. Select "ESP32 S2."
    f. Confirm and skip the installation.
4. Configure the new device.
    a. Select the device you just created and click "Edit" to enter the YAML editing page.
    b. At the bottom, add the PiPower Pro template:

        .. code-block::

            packages:
              remote_package: github://sunfounder/pipower-pro/pipower-pro-template.yaml@main
    
    c. Click "Install" in the upper right corner to install it on PiPower Pro.


