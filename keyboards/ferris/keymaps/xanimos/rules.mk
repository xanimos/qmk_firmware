CONVERT_TO=promicro_rp2040
TAP_DANCE_ENABLE = yes
OLED_ENABLE = yes
CONSOLE_ENABLE = no

ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled/oled_basic.c
endif

ifeq ($(TAP_DANCE_ENABLE),yes)
	SRC += ./tap_dance.c
endif
