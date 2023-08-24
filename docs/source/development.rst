カスタム開発
----------------------------------

PiPower Proの基本機能がご自身のニーズに十分でない場合、PiPower Pro上でカスタム開発を行うことができます。

PiPower Proのすべてのソフトウェアはオープンソースです。以下は、カスタム開発のための基本的なチュートリアルと準備です。

1. Home Assistantの開発者モードを開く。
    a. Home Assistantの管理ページを開きます。
    b. 左下の「Configuration」を選択します。
2. ESPHomeをインストール。
    a. Home Assistantの管理ページを開きます。
    b. 左下の「Configuration」を選択します。
    c. 「Add-ons」を選択します。
    d. 「Add」ボタンをクリックします。
    e. "esphome"を検索します。
    f. 「Install」をクリックします。
    g. インストール後、「Start」をクリックします。
    h. 「Add to Sidebar」を選択します。
3. 新しいデバイスを作成。
    a. サイドバーの「ESPhome」をクリックし、ESPHome管理ページに入ります。
    b. 「New Device」を選択します。
    c. デバイス名を入力します、例："PiPower Pro"。
    d. 初回設定では、Wi-Fiのアカウントとパスワードも入力する必要があります。
    e. 「ESP32 S2」を選択します。
    f. 確認してインストールをスキップします。
4. 新しいデバイスを設定。
    a. 作成したばかりのデバイスを選択し、「Edit」をクリックしてYAML編集ページに入ります。
    b. 下部にPiPower Proのテンプレートを追加します：

       .. code-block::

           packages:
             remote_package: github://sunfounder/pipower-pro/pipower-pro-template.yaml@main
    
    c. 右上の「Install」をクリックして、PiPower Proにインストールします。

