NAME		= TODO-list
BUILD_DIR	= build
TESTS_NAME	= TODO-tests
TESTS_DIR	= tests
RM			= rm -rf

all: ${NAME}

${NAME}:
	@ cmake -DDEBUG_MODE=OFF -S . -B ${BUILD_DIR}
	@ cmake --build ${BUILD_DIR}
	@ cp -f ${BUILD_DIR}/${NAME} .

debug:
	@ cmake -DDEBUG_MODE=ON -S . -B ${BUILD_DIR}
	@ cmake --build ${BUILD_DIR}
	@ cp -f ${BUILD_DIR}/${NAME} .

tests:
	@ cmake -S ${TESTS_DIR} -B ${TESTS_DIR}/${BUILD_DIR}
	@ cmake --build ${TESTS_DIR}/${BUILD_DIR}
	@ cp -f ${TESTS_DIR}/${BUILD_DIR}/${TESTS_NAME} .

clean:
	${RM} ${BUILD_DIR} ${TESTS_DIR}/${BUILD_DIR}

fclean: clean
	${RM} ${NAME} ${TESTS_NAME}

.PHONY: all ${NAME} debug tests clean fclean