安全シャットダウンの設定
---------------------------------

PiPower Proには、接続デバイスの電源ステータス（以下、サブデバイスと称します）を監視するための2つのピンが標準で設定されています。これにより、遠隔での電源オン、オフ、そしてバッテリーが低くなった際の自動安全シャットダウンが可能となります。

.. note:: HassOSを実行しているホストがPiPower Proのサブデバイスとして設定されている場合、そのホストがシャットダウンすると機能が失われ、遠隔電源オンは不可能となります。

* ピン42およびセンサーエンティティ ``binary_sensor.pipower_pro_sub_device_power_state`` はデバイスの現在の状態を検知します。
* ピン41およびエンティティ ``switch.pipower_pro_sub_device_power`` はサブデバイスの電源を制御します。

例として、PiPower ProをRaspberry PiのUPS電源として利用し、その状態を監視し、外部電源が途絶え、バッテリー残量が低下した場合に安全にシャットダウンさせる方法を見ていきましょう。

**ステップ1**

Raspberry Piの設定を行います。

Raspberry Piの2つのピンをそれぞれ **Power Status Signal Pin** と **Shutdown Signal Pin** に設定します。これはdevicetreeを通じて行います。

Raspberry PiシステムのSDカードをPCに挿入し、bootパーティションのルートディレクトリで ``config.txt`` を探します。

.. image:: img/sp230804_143344.png

このファイルを開き、 ``[all]`` の下に次の2行を追加します。

.. code-block::

    dtoverlay=gpio-poweroff,gpiopin=17
    dtoverlay=gpio-shutdown,gpio_pin=18

* ``gpio-poweroff`` はRaspberry Piの電源のオン/オフ状態を示します。正しく設定すると、Raspberry Piは電源がオンの際にこのピンをハイにし、オフの際にはローにします。
* ``gpio-shutdown`` はRaspberry Piのシャットダウンを制御する信号です。正しく設定すると、このピンをローにすることでRaspberry Piがシャットダウンを開始します。

**ステップ2**

* PiPower Proのピン42をRaspberry Piの ``gpio-poweroff`` ピン（こちらではピン17）に接続します。
* PiPower Proのピン41をRaspberry Piの ``gpio-shutdown`` ピン（こちらではピン18）に接続します。

**ステップ3**

上記の2つの信号が正常に動作するか確認します。

ダッシュボードに以下の2つのエンティティを追加します:

* ``binary_sensor.pipower_pro_sub_device_power_state``
* ``switch.pipower_pro_sub_device_power``

**Settings** カードを追加する際（カードの追加方法は :ref:`add_card_by_editor` を参照）、これらの2つのエンティティがそれぞれ ``PiPower-Pro Sub Device Power State`` および ``PiPower-Pro Sub Device Power`` として表示されます。

.. image:: img/sp230804_151521.png

前者を使用してRaspberry Piの動作状態を確認し、後者を使用してRaspberry Piの電源をオフにすることができます。

.. note:: ``PiPower-Pro サブデバイス電源`` はRaspberry Piをオフにするだけです。再度オンにするためには、Raspberry Piに電源を供給する必要があります（例: **PiPower Pro** カードのメインスイッチをオンにする）。



**ステップ 4**

次に、PiPower Pro が Raspberry Pi を安全にシャットダウンできるように自動化を設定します：

1. Home Assistant の設定ページを開き、左側のサイドバーの「Settings」をクリックし、「Automations」を選択します。

    .. image:: img/sp230804_170032.png

2. 新しい自動化を作成します。

    .. image:: img/sp230804_170118.png

    .. image:: img/sp230804_170148.png

#. 「Edit in YAML」をクリックします。

    .. image:: img/sp230804_170218.png

#. 既存のコードを以下のコードに置き換えます。

    .. code-block::

        alias: Safe shutdown RPi
        description: Turn off Raspberry Pi if no external power plug in and battery low
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

#. 「Save」をクリックします。

    .. image:: img/sp230804_170504.png

#. 「rename」をクリックします。

    .. image:: img/sp230804_170527.png

#. 1つ前のレベルに戻ります。新しく設定された自動化が表示されるはずです。

    .. image:: img/sp230804_170710.png

.. note:: さらにいくつかの自動化を作成する必要があります。それらを完了するために前のステップを参照してください。

**電力を節約**

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

**RPi 電源オフ同期**

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

**RPi 電源オン同期**

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

**ステップ 5**

低電力状態のシミュレーションを使用してテストをトリガーします：

1. Developer Tools の SERVICES インターフェースを開きます。

    .. image:: img/sp230804_171500.png

2. ``ESPHome: pipower_pro_simulate_low_power`` を見つけて有効にし、「Call Service」ボタンをクリックします。

    .. image:: img/sp230804_171721.png

PiPower のバッテリーライトが消え、概要でバッテリーレベルが 10% に低下するのを確認できます。

Raspberry Pi はシャットダウンし、シャットダウンが完了すると 2 秒後に PiPower Pro の電源が切れ、PWR ライトが消えます。

