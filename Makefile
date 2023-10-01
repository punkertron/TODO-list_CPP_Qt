NAME		=	TODO-list
BUILD_DIR	=	build

all: ${NAME}

${NAME}:
	@ cmake -DDEBUG_MODE=OFF -S . -B ${BUILD_DIR}
	@ cmake --build ${BUILD_DIR}
	@ cp -f ${BUILD_DIR}/${NAME} .

debug:
	@ cmake -DDEBUG_MODE=ON -S . -B ${BUILD_DIR}
	@ cmake --build ${BUILD_DIR}
	@ cp -f ${BUILD_DIR}/${NAME} .

.PHONY: all ${NAME} debug