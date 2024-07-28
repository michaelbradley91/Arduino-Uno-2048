.PHONY: all clean mocks runners
.DEFAULT_GOAL = all

# This make file contains additional build steps run as a hook by platform IO

CMOCK=CMock/lib/cmock.rb
RUNNER_GENERATOR=Unity/auto/generate_test_runner.rb
LOCAL_RUNNER_CONFIG=test/unity_local.yml
REMOTE_RUNNER_CONFIG=test/unity_remote.yml
EXISTING_RUNNERS=$(wildcard test/**/*_Runner.cpp)
TEST_LOCAL_C_FILES=$(filter-out ${EXISTING_RUNNERS},$(wildcard test/**/test_local_*.cpp))
TEST_REMOTE_C_FILES=$(filter-out ${EXISTING_RUNNERS},$(wildcard test/**/test_remote_*.cpp))
TEST_LOCAL_RUNNER_FILES=$(patsubst %.cpp,%_Runner.cpp,${TEST_LOCAL_C_FILES})
TEST_REMOTE_RUNNER_FILES=$(patsubst %.cpp,%_Runner.cpp,${TEST_REMOTE_C_FILES})

${TEST_LOCAL_RUNNER_FILES}: %_Runner.cpp: %.cpp
	ruby ${RUNNER_GENERATOR} $^ ${LOCAL_RUNNER_CONFIG}

${TEST_REMOTE_RUNNER_FILES}: %_Runner.cpp: %.cpp
	ruby ${RUNNER_GENERATOR} $^ ${REMOTE_RUNNER_CONFIG}

runners: ${TEST_LOCAL_RUNNER_FILES} ${TEST_REMOTE_RUNNER_FILES}

mocks:
	ruby ${CMOCK} -o'test/unity_graphics.yml' lib/Graphics/src/Graphics.hpp
	ruby ${CMOCK} -o'test/unity_random.yml' include/random.h
	ruby ${CMOCK} -o'test/unity_input.yml' lib/Input/src/Input.hpp
# Rename the mocks to be C++
	python3 -c 'import os; os.replace("lib/GraphicsFake/src/GraphicsFake.c", "lib/GraphicsFake/src/GraphicsFake.cpp")'
	python3 -c 'import os; os.replace("lib/randomFake/src/randomFake.c", "lib/randomFake/src/randomFake.cpp")'
	python3 -c 'import os; os.replace("lib/InputFake/src/InputFake.c", "lib/InputFake/src/InputFake.cpp")'

all: mocks runners

clean:
	python3 -c 'import shutil; shutil.rmtree("lib/randomFake/src", ignore_errors=True)'
	python3 -c 'import shutil; shutil.rmtree("lib/GraphicsFake/src", ignore_errors=True)'
	python3 -c 'import shutil; shutil.rmtree("lib/InputFake/src", ignore_errors=True)'
	python3 -c 'from pathlib import Path; import shutil; [shutil.rmtree(p, ignore_errors=True) for p in Path("test").glob("**/*_Runner.cpp")]'