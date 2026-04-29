# ROS2 学習カリキュラム — SO-101 を動かすまで

## ゴール
SO-101 ロボットアームを ROS2 経由で制御し、簡単なピック&プレース動作を実現する。

## SO-101 のシステム構成
```
PC (Ubuntu 24.04 / ROS2 Jazzy)
  └── USB Serial
       └── Feetech STS3215 サーボモータ × 6軸
```
コミュニティパッケージ: so101_ros2, so101_hardware_interface, so101_moveit2_config

---

## Step 1: ROS2 通信の基礎（概念理解 + 最小実装）

### 1.1 ノード (Node)
- ROS2 の最小実行単位。1プロセスに1つ以上のノードが動く
- SO-101 では: カメラノード、サーボ制御ノード、動作計画ノード等が協調動作する

### 1.2 Topic (Publisher / Subscriber)
- 一方通行のデータストリーム。返事不要
- SO-101 での用途: 関節角度の指令値を publish → サーボドライバが subscribe して実行
- 実習: Float64MultiArray で6軸分の関節角度を pub/sub（Python & C++）

### 1.3 Service (Client / Server)
- 1回のリクエストに対して1回のレスポンス
- SO-101 での用途: グリッパー開閉、キャリブレーション実行
- 実習: SetBool でグリッパー開閉の Service を実装（Python & C++）

### 1.4 Action (Client / Server + Feedback)
- 時間がかかる処理 + 途中経過の通知
- SO-101 での用途: 「この姿勢まで動いて」→ 途中経過 → 「完了」（MoveIt2 が内部で使用）
- 実習: Fibonacci Action サンプルで feedback → result の流れを体験

### 1.5 メッセージ型
- トピックで流れるデータの型定義
- 重要な型: `sensor_msgs/JointState`, `geometry_msgs/Pose`, `trajectory_msgs/JointTrajectory`

## Step 2: URDF と可視化
- SO-101 の URDF（ロボットの形状・関節の定義ファイル）を読み込む
- RViz でロボットモデルを表示し、関節を動かして確認
- リンク・ジョイントの概念を理解する

## Step 3: ros2_control によるハードウェア制御
- ros2_control フレームワークの構造を理解（Controller Manager → Hardware Interface）
- so101_hardware_interface で実機のサーボと接続
- トピック経由で関節角度を指令し、実機を動かす

## Step 4: MoveIt2 による動作計画
- MoveIt2 のセットアップ（so101_moveit2_config を使用）
- RViz 上でドラッグ&ドロップで目標姿勢を設定 → Plan & Execute
- 逆運動学（IK）、衝突回避の概念を理解する

## Step 5: カメラ連携とピック&プレース
- USB カメラノードで画像を取得
- 物体検出（色・形状ベース or 学習ベース）で把持対象を認識
- MoveIt2 で把持動作を実行

---

## 通信パターン まとめ
```
Topic:   Publisher ──→ Subscriber        (センサデータ配信、関節角指令)
Service: Client ←──→ Server              (パラメータ取得、状態問い合わせ)
Action:  Client ←──→ Server + Feedback   (ナビゲーション、動作計画の実行)
```
