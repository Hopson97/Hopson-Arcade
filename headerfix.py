from pathlib import Path
import re
import os

pathlist = Path('src/arcade').glob('**/*.cpp')
for path in pathlist:
    with open(path) as file:
        print ("__--------------------------________")
        fileContent = ""
        found = False
        for line in file:
            if not line.startswith('#include') and not line.startswith('#pragma') and not "*" in line and not line.isspace() and not found:
                fileContent += 'namespace arcade {\n'
                found = True

            fileContent += line
        fileContent += '}'
        print (fileContent)
        with open(path, 'w') as out:
            out.write(fileContent)


