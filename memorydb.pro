CONFIG -= release
CONFIG -= debug
TARGET = memorydb.exe

SOURCES = src/memorydb.C


CONFIG += debug
CONFIG += console
CONFIG -= qt

contains( CONFIG, release ) {
	QMAKE_LFLAGS_RELEASE += -flto
	QMAKE_CXXFLAGS_RELEASE += -flto
}

