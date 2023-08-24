.. _entity:

PiPower Pro エンティティ
--------------------------

Home Assistantに詳しく、カードのカスタマイズを自分で行いたい場合、使用できるPiPower Proエンティティのリストは以下の通りです。

**基本情報**
    * ``binary_sensor.pipower_pro_battery_low`` - バッテリー低下状態 (bool)
    * ``binary_sensor.pipower_pro_is_charging`` - 充電状態 (V)

**スイッチ**
    * ``switch.pipower_pro_battery_output`` - バッテリー出力スイッチ (bool)
    * ``switch.pipower_pro_esp32_power`` - ESP32 電源スイッチ (bool)
    * ``switch.pipower_pro_external_output`` - 外部出力スイッチ (bool)

**出力**
    * ``sensor.pipower_pro_output_voltage`` - 出力電圧 (V)
    * ``sensor.pipower_pro_output_current`` - 出力電流 (A)
    * ``sensor.pipower_pro_output_power`` - 出力電力 (W)
    * ``sensor.pipower_pro_output_energy`` - 出力エネルギー (Wh) 全出力エネルギーの計算に使用される。サービス経由でリセット可能。詳細はすべてのサービスを参照

**バッテリー**
    * ``sensor.pipower_pro_battery_voltage`` - バッテリー電圧 (V)
    * ``sensor.pipower_pro_battery_current`` - バッテリー電流、充電の場合は正、放電の場合は負 (A)
    * ``sensor.pipower_pro_battery_power`` - バッテリー出力電力 (W)
    * ``sensor.pipower_pro_battery_capacity`` - バッテリー容量 (mAh)
    * ``sensor.pipower_pro_battery_level`` - バッテリーレベル (%)

**入力**
    * ``sensor.pipower_pro_input_voltage`` - 外部入力電圧 (V)

**サブデバイス制御**
    * ``switch.pipower_pro_sub_device_power`` - サブデバイス電源制御信号 (bool)
    * ``binary_sensor.pipower_pro_sub_device_power_state`` - サブデバイス電源状態 (bool)

**その他**
    * ``sensor.pipower_pro_battery_capacity_algorithm`` - バッテリー容量アルゴリズム (String)
    * ``sensor.pipower_pro_power_source`` - 現在の出力ソース: バッテリー/外部 (String)
    * ``sensor.pipower_pro_battery_factory_capacity`` - バッテリー工場名義容量 (mAh)
    * ``binary_sensor.pipower_pro_external_power`` - 外部入力状態 (bool)
    * ``button.pipower_pro_factory_reset`` - 工場設定リセットボタン (bool)
    * ``update.pipower_pro_firmware`` - ファームウェア更新
    * ``switch.pipower_pro_power_switch`` - 出力スイッチ (bool)
    * ``sensor.pipower_pro_version`` - PiPower Proバージョン (String)

**すべてのサービス**
    * ``set_battery_factory_capacity`` - バッテリー工場名義容量の変更 (capacity: int, mAh)、デフォルト2000
    * ``enable_coulomb_count_beta`` - クーロン計算アルゴリズムの有効化 (enable: bool)、デフォルトはfalse
    * ``reset_capacity`` - 現在の容量を工場名義容量にリセット
    * ``reset_output_energy`` - 出力エネルギーを0にリセット
    * ``set_edv2`` - 放電終了電圧2の設定、放電キャリブレーション2のための電圧、デフォルト6.8. クーロンカウントの詳細を参照
    * ``set_edv1`` - 放電終了電圧1の設定、放電キャリブレーション1のための電圧、デフォルト6.5. クーロンカウントの詳細を参照
    * ``set_edv0`` - 放電終了電圧0の設定、放電キャリブレーション0のための電圧、デフォルト6.2. クーロンカウントの詳細を参照
    * ``set_rcv`` - リセットキャリブレーションステータスのための電圧の設定、デフォルト8.0. クーロンカウントの詳細を参照
    * ``simulate_low_power`` - 低電力トリガーシナリオのテストのための低電力シミュレーション
