from collections import deque

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

# 上下左右の移動方向
directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

def bfs(grid, start, goal):
    """BFSでstartからgoalへの最短経路を返す"""
    q = deque()
    q.append(start)

    visited = set()
    visited.add(start)
    came_from = {}
    path_ = []

    while q:
        x, y = q.popleft()
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
                q.append((x_, y_))
    else:
        return None

    pos = goal
    while pos != start:
        path_.append(pos)
        pos = came_from[pos]

    path_.append(start)
    path_.reverse()
    return path_

path = bfs(grid, start, goal)
if path:
    print("経路:", path)
    print("ステップ数:", len(path) - 1)

    # グリッドに経路を表示
    display = [["." if c == 0 else "#" for c in row] for row in grid]
    for r, c in path:
        display[r][c] = "*"
    display[start[0]][start[1]] = "S"
    display[goal[0]][goal[1]] = "G"
    for row in display:
        print(" ".join(row))
else:
    print("経路が見つかりませんでした")
