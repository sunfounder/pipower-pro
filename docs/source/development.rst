进阶功能
=============================

库仑计(Beta)
-------------------

库仑计算法可以提高电池电量计算的精准度,但目前仍在Beta阶段,可能会出现严重计算不精准的问题,请谨慎选择使用。

**使用库仑计的方法：**

1. 在Home Assistant页面,点击左侧栏的开发者工具
2. 在开发者工具页面选择服务选项卡
3. 在服务列表中选择服务：ESPHome: pipower_pro_enable_coulomb_count_beta
4. 把enable_coulomb_count_beta开关打开
5. 点击下方的调用服务即可。
6. 可以通过实体sensor.pipower_pro_battery_capacity_algorithm看到当前选择的电量计的算法。

**算法**

库仑计算法是对电池每一秒的电流监测和电压监测计算出能量再进行积分。
Capacity += Voltage * Current

**匹配**

而这个积分算出的容量只是从当前开始充放电的电量。和电池实际的容量关联上的话,还需要做一次匹配。
这里的匹配方法很简单。PiPower 出厂设定的电量值是电池的标称电量2000mAh,电池当前实际的电量值一定会比这个值少。只要对电池进行充电,电量值又被设定上限为标称值2000mAh(可以通过这个服务进行更改set_battery_factory_capacity),那么电池充满点的时候,电量值和电池的实际容量就都是满电的2000mAh,这样积分计算的电量值就和实际电池电量值匹配上了。

**自动校准**

积分容易产生累计误差,电池也会随着使用时长,寿命降低,容量也会减少,而达不到标称的2000mAh。
所以需要使用一些校准手段来对电池容量进行校准。

这里使用的是(Compensated End of Discharge Voltage)CEDV校准法。
CEDV校准法原理是在电池End of Discharge的时候的电压是相对准确的,
而且在这个时候的电压曲线也是最陡峭的,以这个电压值作为一个校准点会比较合适。
所以这里我们设置了3个EDV点。
分别是 edv2(7%), edv1(3%) 和 edv0(0%)。

PiPower Pro设定这3个校准电压后,在电池放电至这3个点时,都会对电池做一次校准:
``MaxCapacity = MaxCapacity - Capacity + MaxCapacity * 7%``
为了防止电压波动导致无限次同一地方校准, 
限定每次在充电达到 RCV(Reset Calibration Voltage,默认8.0V) 之前只校准一次。
edv2,edv1,edv0和rcv都可以在服务Service中配置,详见 :ref:`entity`


**Indicator**

库仑计算法启用后，电量指示灯也会切换成库仑计。
但是它有小概率出现电量读取错误，甚至电量会无故清零的情况。

The relationship between the battery indicators and power is as follows:

* 4 LEDs all on:  75%
* 3 LEDs on:  50%
* 2 LEDs on:  25%
* 1 LED on:  10%
* 4 LEDs all off: 0% ，at this time，batteries need to be charged.


二次开发
----------------

如果觉得PiPower Pro的基础功能满足不了你, 你可以对PiPower Pro进行二次开发。


PiPower Pro 的所有软件开源。以下是基础教程,和二次开发的准备。

1. 打开Home assistant 的开发者模式
    a. 打开Homeassistant 管理页面
    b. 选择左下角的配置
2. 安装ESPhome
    a. 打开Homeassistant 管理页面
    b. 选择左下角的配置
    c. 选择加载项
    d. 点击添加
    e. 搜索esphome
    f. 点击安装
    g. 安装完成后点击开启
    h. 选择添加到侧边栏
3. 新建一个设备
    a. 点击侧边栏的ESPhome,进入ESPhome管理页面
    b. 选择新设备
    c. 输入设备名称,如PiPower Pro
    d. 第一次配置还需要填写Wi-Fi账号密码
    e. 选择ESP32 S2
    f. 确认,并跳过安装。
4. 配置新设备
    a. 选择刚刚创建的设备,点击Edit,进入yaml编辑页面
    b. 在最下面添加PiPower Pro template:

        .. code-block::

            packages:
              remote_package: github://sunfounder/pipower-pro/pipower-pro-template.yaml@main
    
    c. 点击右上角的Install,安装到PiPower Pro即可。



多台PiPower Pro
-------------------------

如果有多台多台PiPower Pro需要在同一Home Assistant 环境下使用,
你需要修改yaml设置。在esphome下添加 ``name_add_mac_suffix: true``。

.. code-block::

    esphome:
      name: pipower-pro
      friendly_name: PiPower-Pro
      name_add_mac_suffix: true





IO拓展
-----------------

J4排针是用于扩展的。IO来自ESP32 S2

.. list-table:: IO扩展
    :widths: 50 25 25 50
    :header-rows: 1

    * - Functions
      - Pin
      - Pin
      - Functions
    * - 5V
      - 5V
      - 3V3
      - 3V3
    * - ADC,Touch,GPIO8
      - 8
      - GND
      - Ground
    * - ADC,Touch,GPIO9
      - 9
      - 10
      - GPIO10,Touch,ADC
    * - ADC,DAC,GPIO18
      - 18
      - 36
      - GPIO36
    * - GPIO37
      - 37
      - 38
      - GPIO38
    * - GPIO39
      - 39
      - 40
      - GPIO40
    * - GPIO41
      - 41
      - 42
      - GPIO42