import os
root_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../src/extern/")
files = []
dirs = [("", root_dir)]
for i in range(4):
    for (p, d) in dirs:
        files = files + [os.path.join(p, item) for item in os.listdir(d) if os.path.isfile(os.path.join(d, item))]
        dirs = [(os.path.join(p, sd), os.path.join(d, sd)) for sd in os.listdir(d) if os.path.isdir(os.path.join(d, sd))]
recartyar_header  = open(os.path.join(root_dir, "recartyar/recartyar.h"), "w")
for f in [f for f in files if "recartyar" not in f]:
    recartyar_header.write("#include \"" + f + "\"\n")
recartyar_header.close()
