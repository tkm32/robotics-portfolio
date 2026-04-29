import math

# テスト用の2次元点群
points = [(2, 3), (5, 4), (9, 6), (4, 7), (8, 1), (7, 2), (1, 1), (3, 6), (6, 1), (8, 7)]


class Node:
    def __init__(self, point, left=None, right=None, axis=0):
        self.point = point
        self.left = left
        self.right = right
        self.axis = axis  # 0=x, 1=y


def build_kd_tree(points, depth=0):
    """点群からKD木を構築する"""
    # ヒント:
    #   1. 点が空ならNoneを返す
    #   2. axis = depth % 2 (2次元の場合)
    #   3. axisの座標でソートし、中央値の点をrootにする
    #   4. 中央値より左の点でleft、右の点でrightを再帰的に構築
    if len(points) < 1:
        return None

    axis = depth % 2
    points = sorted(points, key=lambda p: p[axis])
    pivot = len(points) // 2

    depth += 1

    return Node(points[pivot], build_kd_tree(points[:pivot], depth), build_kd_tree(points[pivot+1:], depth), axis)

def print_tree(node, indent=0):
    """KD木を可視化"""
    if node is None:
        return
    print(" " * indent + f"{node.point} (axis={node.axis})")
    print_tree(node.left, indent + 2)
    print_tree(node.right, indent + 2)


# 構築
root = build_kd_tree(points)
print("=== KD Tree ===")
print_tree(root)
