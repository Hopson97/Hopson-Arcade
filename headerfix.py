from pathlib import Path
import re
import os

pathlist = Path('src').glob('**/*.h')
for path in pathlist:
    with open(path) as file:
        for line in file:
            if line.startswith('#include') and "arcade" in line:
                i = line.find('arcade')
                line = "#include <" + line[i:-2] + ">"
                print(line)
