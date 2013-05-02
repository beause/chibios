# List of all the board related files.
GENISTSRC = ${CHIBIOS}/genist_common/itmstream.c \
			${CHIBIOS}/genist_common/led.c \
			${CHIBIOS}/genist_common/ms5803.c \
			${CHIBIOS}/genist_common/rtd.c \
			${CHIBIOS}/genist_common/fake_speed.c \
			${CHIBIOS}/genist_common/hall_sensor.c \
			${CHIBIOS}/genist_common/db.c \
			${CHIBIOS}/genist_common/statemachine.c \
			${CHIBIOS}/genist_common/actions.c \
			${CHIBIOS}/genist_common/speed.c \
			${CHIBIOS}/genist_common/monitor.c

# Required include directories
GENISTINC = ${CHIBIOS}/genist_common
