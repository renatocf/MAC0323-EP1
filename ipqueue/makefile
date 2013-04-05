LIB   := ipqueue
CLIBS := -I../edge -I../Point
HEADERS := ipqueue-internal.h

include ../compile.mk

ipqueue-internal.h: ipqueue.h
ipqueue.h: ipqueue-item.h
ipqueue-item.h: ../edge/edge.h
