import os

# Getting the current work directory (cwd)
os.chdir("Source/")
thisdir = os.getcwd()


blah = len("/home/matt/Documents/programming/c-and-cpp/sfml/hopson-arcade/")

# r=root, d=directories, f = files
for r, d, f in os.walk(thisdir):
    for file in f:
        if ".cpp" in file:
            print(os.path.join(r, file)[blah:])
