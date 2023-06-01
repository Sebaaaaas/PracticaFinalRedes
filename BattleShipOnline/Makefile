CC = g++
CFLAGS = -w -pthread
LINKER_FLAGS = -lSDL2 -lSDL2_image

CLIENT_SRC = Client.cpp
SERVER_SRC = Server.cpp

CLIENT_EXE = client
SERVER_EXE = server

COMMON_DEPS = Texture.cpp \
              Network/Socket.cc \
              Network/ClientServer.cpp \
              Game.cpp \
              GameObjects/Tablero.cpp \
              GameObjects/Barco.cpp \
              GameObjects/Button.cpp \
              GameObjects/Hitmarker.cpp \
              GameObjects/BattleShipObject.cpp \
              Network/ClickSerializer.cpp

CLIENT_OBJS = $(CLIENT_SRC:.cpp=.o) $(COMMON_DEPS:.cpp=.o)
SERVER_OBJS = $(SERVER_SRC:.cpp=.o) $(COMMON_DEPS:.cpp=.o)

all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LINKER_FLAGS) -o $(CLIENT_EXE)

$(SERVER_EXE): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LINKER_FLAGS) -o $(SERVER_EXE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@