from subprocess import Popen, DEVNULL
import datetime
import os

# Modify this variable to specify a version
VERSION = "1.2.1"

# ------------------------------------

def executeCommand(command):
    Popen(command.split(" "), shell=False, stdout=DEVNULL, stderr=DEVNULL)


if not os.path.exists("build"):
    os.mkdir("build")

print("Building man pages ...")

for man_file in os.listdir("manpages"):
    with open(f"manpages/{man_file}", "r") as fd:
        initial_content = fd.read()

    initial_content = initial_content.replace("<version>", VERSION)
    initial_content = initial_content.replace("<date>", str(datetime.datetime.now()))

    with open(f"build/{man_file}", "w") as fd:
        fd.write(initial_content)

    executeCommand(f"gzip build/{man_file}")

    print(f" -> {man_file}.gz OK.")

print("Done.")
