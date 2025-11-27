# generate levels.json with `[...document.querySelectorAll('.level_icon')].map((e) => e.level)`
import json

def load_from_extract(path):
    with open(path) as file:
        levels = json.load(file)

    level_dict = {}

    cnt = 1
    for level in levels:
        if 'title' in level:
            key = level['title']
        else:
            key = cnt
            cnt += 1

        par = level['par']
        width = level['tiles']['width']
        height = level['tiles']['height']
        level_array = map(lambda x: 'O' if x == 2 else '_', level['tiles']['array'])

        level_grid = [''.join(next(level_array) for _ in range(width)) for _ in range(height)]

        level_dict[key] = {
            'par': par,
            'width': width,
            'height': height,
            'grid': level_grid
        }

    return level_dict
