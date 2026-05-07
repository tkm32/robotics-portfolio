# 学習進捗

## 2026/4/19 — 環境構築
- Ubuntu 24.04 セットアップ完了
- ROS2 Jazzy インストール・動作確認
- Claude Code 導入、CLAUDE.md 作成

## 2026/4/22 — Modern C++ 速習
- C → C++17 の主要な差分を整理（auto, 範囲for, nullptr, 構造化束縛）
- vector, unordered_map, priority_queue を使った演習

## 2026/4/27 — アルゴリズム基礎
- BFS/DFS の理解と実装（Python → C++）
- A* 探索の実装

## 2026/4/29 — アルゴリズム応用 + ROS2
- KD木の構築（再帰、中央値分割）
- ROS2 通信パターン（Topic / Service / Action）の理解と実装（Python & C++）
- SO-101 をゴールにした ROS2 学習カリキュラムの策定
- ROS2 ワークスペースの正規構成で C++ パッケージをビルド・実行

## 2026/5/4-5 — ROS2 C++ 実装
- C++ Subscriber 実装（create_subscription, UniquePtr コールバック, spin の理解）
- C++ Service Server/Client 実装（create_service, create_client, 非同期コールバック方式）
- CMakeLists.txt に custom_executable 便利関数を導入
- ROS2 通信の内部構造（middleware/DDS、所有権モデル）の理解を深めた
- 知識対策テキストブック作成（C++, Python, OS, ネットワーク, データ構造）
- LeetCode 6問: #67 Add Binary (C++), #191 Number of 1 Bits (C++), #200 Number of Islands, #994 Rotting Oranges, #207 Course Schedule, #743 Network Delay Time

## 2026/5/6 — CS基礎知識の深掘り
- C++: vtable、weak_ptr（循環参照・lock()・atomicカウンタ）、テンプレート、キャスト4種、constexpr
- Python: GIL（refcount保護、解放タイミング、C++との対比）
- OS: プロセスvsスレッド、デッドロック（4条件・回避策）、仮想メモリ、TLBフラッシュ

## 2026/5/7 — LeetCode + CS基礎知識
- LeetCode 2問: #3 Longest Substring Without Repeating, #56 Merge Intervals
- テキストブック追加: デザインパターン、SOLID、マルチスレッド実践、テスト、Linuxデバッグツール
- データ構造の内部動作の理解: ハッシュマップ（O(1)の仕組み、衝突解決）、ヒープ（二分木の理由、sift up/down）
- OOP設計: Observer/Factory/Singleton、Open/Closed原則
