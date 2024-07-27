.PHONY: all clean mocks
.DEFAULT_GOAL = all

# This make file contains additional build steps run as a hook by platform IO

CMOCK=CMock/lib/cmock.rb

mocks:
	ruby ${CMOCK} -o'test/unity_graphics.yml' lib/Graphics/src/Graphics.hpp
	ruby ${CMOCK} -o'test/unity_random.yml' include/random.h
	ruby ${CMOCK} -o'test/unity_input.yml' lib/Input/src/Input.hpp
# Rename the mocks to be C++
	python3 -c 'import os; os.replace("lib/GraphicsFake/src/GraphicsFake.c", "lib/GraphicsFake/src/GraphicsFake.cpp")'
	python3 -c 'import os; os.replace("lib/randomFake/src/randomFake.c", "lib/randomFake/src/randomFake.cpp")'
	python3 -c 'import os; os.replace("lib/InputFake/src/InputFake.c", "lib/InputFake/src/InputFake.cpp")'

all: mocks

clean:
	python3 -c 'import shutil; shutil.rmtree("lib/randomFake/src", ignore_errors=True)'
	python3 -c 'import shutil; shutil.rmtree("lib/GraphicsFake/src", ignore_errors=True)'
	python3 -c 'import shutil; shutil.rmtree("lib/InputFake/src", ignore_errors=True)'