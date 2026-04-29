from heapq import heappush, heappop

# グリッドマップ: 0=通行可, 1=壁
grid = [
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 1, 0, 1, 0, 1, 1, 1, 0, 0],
    [0, 1, 0, 0, 0, 0, 0, 1, 0, 1],
    [0, 1, 1, 1, 1, 1, 1, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 1, 1, 0],
    [1, 0, 0, 0, 1, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 1, 1, 0],
    [0, 1, 1, 1, 1, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0, 1, 0, 0, 0],
    [1, 1, 1, 0, 0, 0, 0, 0, 1, 0],
]

start = (0, 0)
goal = (9, 9)

directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]


def heuristic(pos, goal):
    """マンハッタン距離"""
    return abs(pos[0] - goal[0]) + abs(pos[1] - goal[1])


def a_star(grid, start, goal):
    """A*でstartからgoalへの最短経路を返す"""
    # heapqの使い方: heapq.heappush(リスト, (優先度, データ))
    #                heapq.heappop(リスト) → 優先度が最小の要素を取り出す
    q = []
    heappush(q, (heuristic(start, goal), start))

    visited = set()
    visited.add(start)
    came_from = {}
    cost = {}
    cost[start] = 0
    path_ = []

    while q:
        x, y = heappop(q)[1]
        if goal == (x, y):
            break
        for dx, dy in directions:
            x_ = x+dx
            y_ = y+dy
            if x_ < 0 or x_ >= len(grid[0]) or y_ < 0 or y_ >= len(grid):
                continue
            
            if grid[y_][x_] == 0 and (x_, y_) not in visited:
                visited.add((x_, y_))
                came_from[(x_, y_)] = (x, y)
                cost[(x_, y_)] = cost[(x, y)]+1
                heappush(q, (cost[(x_, y_)] + heuristic((x_, y_), goal), (x_, y_)))
    else:
        return None

    pos = goal
    while pos != start:
        path_.append(pos)
        pos = came_from[pos]

    path_.append(start)
    path_.reverse()
    return path_


path = a_star(grid, start, goal)
if path:
    print("経路:", path)
    print("ステップ数:", len(path) - 1)

    display = [["." if c == 0 else "#" for c in row] for row in grid]
    for r, c in path:
        display[c][r] = "*"
    display[0][0] = "S"
    display[9][9] = "G"
    for row in display:
        print(" ".join(row))
else:
    print("経路が見つかりませんでした")
