複数のPiPower Proユニット
------------------------------------------

もし同じHome Assistant環境内で複数のPiPower Proユニットを使用する場合、YAMLの設定を変更する必要があります。
"esphome"の下に ``name_add_mac_suffix: true`` を追加してください。

.. code-block::

    esphome:
      name: pipower-pro
      friendly_name: PiPower-Pro
      name_add_mac_suffix: true
