# SO-101 ROS2 Control 作業ログ

## ゴール

ROS2（ros2_control）経由でSO-101のFeetechサーボに角度指令を送り、実機を動かす。

## ディレクトリ構成

```
ros2_workspace/
├── src/
│   ├── ros2_notes_cpp/          # ROS2学習用（Topic/Service）
│   ├── feetech_ros2_driver/     # Feetech STS3215用 ros2_control hardware interface
│   │                            # https://github.com/JafarAbdi/feetech_ros2_driver
│   └── lerobot_ws/src/
│       ├── lerobot_controller/  # SO-101の ros2_control launch・設定
│       ├── lerobot_description/ # SO-101の URDF
│       └── lerobot_moveit/      # MoveIt2設定（今回は不使用）
├── build/
├── install/
└── log/
```

## アーキテクチャ

```
ROS2 topic (角度指令)
  → ros2_control (controller_manager)
    → feetech_ros2_driver (hardware_interface)
      → シリアル通信 (/dev/ttyACM0)
        → Feetech STS3215 サーボ × 6軸
```

## セットアップ手順

### 1. パッケージclone

```bash
cd ros2_workspace/src/
git clone https://github.com/JafarAbdi/feetech_ros2_driver.git
git clone https://github.com/Pavankv92/lerobot_ws.git
```

### 2. 依存インストール

```bash
sudo apt install -y \
  ros-jazzy-xacro \
  ros-jazzy-controller-manager \
  ros-jazzy-joint-state-publisher-gui \
  ros-jazzy-hardware-interface \
  ros-jazzy-tl-expected \
  librange-v3-dev \
  libserial-dev
```

### 3. ビルド

```bash
colcon build --packages-select feetech_ros2_driver lerobot_description lerobot_controller
source install/setup.bash
```

### 4. キャリブレーション

自作ツール（so101_tools/calibration）を使用。詳細は下記「自作ツール」セクション参照。

### 5. コントローラ起動（実機接続）— 未実装

so101_ros2_control_real.xacroの統合とlaunchファイルの切り替えが必要。「次のステップ」参照。

## キャリブレーション結果（2026-05-16）

サーボのEEPROMオフセットは以前のMac環境で設定済み（ゼロまたぎなし）。

| Joint | home_raw | min_cum | max_cum | min_rad | max_rad |
|-------|----------|---------|---------|---------|---------|
| 1 | 2091 | -310 | 719 | -0.475534 | 1.102932 |
| 2 | 2069 | -1638 | 730 | -2.512661 | 1.119806 |
| 3 | 2023 | -1200 | 1002 | -1.840777 | 1.537049 |
| 4 | 2080 | -1173 | 1175 | -1.799359 | 1.802427 |
| 5 | 1940 | -1830 | 1932 | -2.807185 | 2.963651 |
| 6 | 1582 | 0 | 1474 | 0.000000 | 2.261088 |

- home_raw: ホームポジションでのサーボ生値
- min_cum/max_cum: ホームからの相対変位（生値）
- min_rad/max_rad: ラジアン変換（2π/4096）

## 自作ツール（so101_tools/）

### ビルド

```bash
cd ros2_workspace
cmake -S src/so101_tools -B build/so101_tools
cmake --build build/so101_tools
```

### キャリブレーション測定

```bash
LD_LIBRARY_PATH=build/so101_tools/feetech_driver:$LD_LIBRARY_PATH \
  ./build/so101_tools/calibration /dev/ttyACM0 ./calibration.json
```

Phase 1: 全関節をホームに合わせてEnter → home_raw記録
Phase 2: 各関節を限界まで動かしてEnter → 累積変位でmin/max記録（ゼロまたぎ検知付き）

### デモモーション

```bash
LD_LIBRARY_PATH=build/so101_tools/feetech_driver:$LD_LIBRARY_PATH \
  ./build/so101_tools/demo_motion /dev/ttyACM0
```

全関節を順にフルスイープ → 波打ち動作 → ホーム復帰。

## 実機用 ros2_control 設定

`src/lerobot_ws/src/lerobot_description/urdf/so101_ros2_control_real.xacro` にキャリブ結果を反映済み。

## 次のステップ

- so101.urdf.xacroでsim/realを切り替えられるようにする
- ros2_control経由でcontroller_managerから実機を動かす

## メモ

- SO-101のサーボ: Feetech STS3215（半二重UART、/dev/ttyACM0で認識）
- シリアルポートの権限: `sudo usermod -aG dialout tak`（要再ログイン）、または `sudo chmod 666 /dev/ttyACM0`
- ros-gz系パッケージはGazeboシミュレーション用。実機のみなら不要
