# Robotics Learning Portfolio

ロボティクスエンジニアへのキャリアチェンジを目指して学習中のポートフォリオです。

## Background

- **中学2年**: 独学でC言語を学び始め、以来プログラミングに親しむ
- **学部**: 電子情報系（アンテナ設計・信号処理）
- **大学院**: ロボット（ロボット用油圧アクチュエータの設計開発、国際学会含む論文発表・受賞）
- **学生時代**: アルバイトでフルスタック開発に従事（モバイルアプリ、3D処理、機械学習向けデータ変換アルゴリズム開発等）
- **現職**: クラウドベンダーのソリューションアーキテクト（5年目）
  - メイン業務の傍ら、IoTデバイスの回路設計・組み込み開発からクラウド・AI連携まで一気通貫で実装し、イベントでデモ展
  示・講演などの経験
- **2024年末**: SO-101 ロボットアームを自宅3Dプリンターで製作、LeRobotで模倣学習を体験
- ものづくりへの情熱を持ち続け、ロボティクス領域への転身を決意

## 学習の現在地

- C++17・ROS2 の理解を深めるため学習中
- アルゴリズム（探索、空間データ構造）をロボティクス応用の観点でリハビリ中

## 学習環境

- Ubuntu 24.04 / ROS2 Jazzy
- Python 3.12 / C++17（g++）
- Claude Code（AI支援による効率的な学習）
- SO-101 ロボットアーム（自宅3Dプリンター製作）

## リポジトリ構成

```
robotics-portfolio/
├── CLAUDE.md                # Claude Code 設定（AI支援学習の指示書）
├── PROGRESS.md              # 学習進捗記録
├── README.md                # ← このファイル
├── ros2_curriculum.md       # ROS2 学習カリキュラム（SO-101を動かすまで）
├── cpp_basics/              # Modern C++ 基礎
├── algorithms/              # ロボティクス向けアルゴリズム
│   ├── bfs_dfs/             #   幅優先・深さ優先探索
│   ├── a_star/              #   A*経路探索
│   └── kd_tree/             #   KD木（構築・最近傍探索）
├── ros2_notes_py/           # ROS2 学習用 Python スクリプト
└── ros2_workspace/          # ROS2 ワークスペース（正規構成）
    └── src/
        ├── ros2_notes_cpp/  #   C++ による ROS2 ノード実装
        └── so101_tools/     #   SO-101 キャリブレーション・デモツール（C++）
```

## 学習ロードマップ

### Phase 0: 環境構築（2024/12〜2025/4前半）
- [x] SO-101 ロボットアームを自宅3Dプリンターで製作（年末年始）
- [x] LeRobotフレームワークでテレオペレーション・模倣学習を体験
- [x] Ubuntu 24.04 + ROS2 Jazzy セットアップ
- [x] Claude Code 導入、AI支援学習ワークフロー構築

### Phase 1: アルゴリズム・C++・CS基礎（2025/4〜5月前半）
- [x] Modern C++ 独習（C→C++17 の差分、STLコンテナ、スマートポインタ）
- [x] 探索アルゴリズム（BFS/DFS、A*）を Python & C++ で実装
- [x] KD木の構築と最近傍探索を Python で実装（SLAMでのICP応用を理解）
- [x] LeetCode でアルゴリズム実装力強化（ヒープ、ハッシュ、スタック、連結リスト、区間マージ等）
- [x] C++ 深掘り（RAII、ムーブセマンティクス、vtable、テンプレート、キャスト4種）
- [x] OS・並行処理（プロセス/スレッド、mutex/セマフォ/condvar、デッドロック、RTOS）
- [x] ネットワーク（TCP/UDP、シリアル通信、TLS、gRPC）
- [x] 設計（Observer/Factory/Singleton、SOLID、Producer-Consumer、Thread Pool）
- [x] ROS2 通信パターン（Topic / Service / Action）の自力実装（Python & C++）

### Phase 2: ROS2 × SO-101 実機（2025/5）
- [x] feetech_ros2_driver でサーボ認識・通信確認
- [x] キャリブレーションツール自作（C++、全6軸のhome_raw + 可動域測定）
- [x] ros2_control 設定作成（so101_ros2_control_real.xacro）
- [x] デモモーション実行（全軸フルスイープ + 波打ち動作）
- [ ] SO-101 の URDF を読み込み、RViz で可視化
- [ ] MoveIt2 での動作計画

### Phase 3: 自律移動ロボットの基礎（今後）
- [ ] SLAM の基礎理解（Gazebo + TurtleBot3 シミュレーションで体験）
- [ ] Nav2 による自律ナビゲーション（シミュレーション上で経路計画・障害物回避）

### Phase 4: MoveIt2 と応用（今後）
- [ ] SO-101 + カメラでの物体認識・ピック&プレース
- [ ] LeRobot による模倣学習パイプライン（テレオペ教示→方策学習→実機デプロイ）

