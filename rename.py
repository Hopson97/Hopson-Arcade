from pathlib import Path
import re
import os

def convert(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

pathlist = Path('src').glob('**/*.h')
for path in pathlist:
    paths = str(path).split('/')
    new_path = ""
    for p in paths:
        n = convert(p)
        if (n.startswith('_')):
            n = n[1:]
        new_path += n
        if not (p.endswith(".cpp") or p.endswith(".h")):
            new_path += '/'

    os.rename(str(path), new_path)
