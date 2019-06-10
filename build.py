import os
import time

from colorama import Fore, Style

if not os.path.isdir("build"):
    os.mkdir("build")

os.chdir("build")

before = time.time()

if not os.system("cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++") == 0:
    exit()

if not os.system("make") == 0:
    exit()

print(f"{Fore.GREEN}Total compilation time: {round(time.time() - before, 2)} seconds{Style.RESET_ALL}")