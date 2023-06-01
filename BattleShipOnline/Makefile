CC = g++
CFLAGS = -w -pthread
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

# Nombre de los archivos fuente
CLIENT_SRC = Client.cpp
SERVER_SRC = Server.cpp

# Nombre de los ejecutables
CLIENT_EXE = client
SERVER_EXE = server

# Dependencias para el cliente
CLIENT_DEPS =	Texture.cpp \
				Vector2D.cpp \
				GameObjects/Barco.cpp \
				GameObjects/Button.cpp \
				GameObjects/Tablero.cpp \
				GameObjects/Hitmarker.cpp \
				GameObjects/BattleShipObject.cpp \
				Network/ClickSerializer.cpp \
				Network/ClientServer.cpp \
				Network/Socket.cc \
				Game.cpp

# Dependencias para el servidor
SERVER_DEPS = 	Texture.cpp \
				Network/Socket.cc \
				Network/ClientServer.cpp \
				Game.cpp \
				GameObjects/Tablero.cpp \
				GameObjects/Barco.cpp \
				GameObjects/Button.cpp \
				GameObjects/Hitmarker.cpp \
				GameObjects/BattleShipObject.cpp \
				Network/ClickSerializer.cpp \


all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC) $(CLIENT_DEPS)
	$(CC) $(CFLAGS) $(CLIENT_DEPS) $(LINKER_FLAGS) -o $(CLIENT_EXE) $(CLIENT_SRC)

$(SERVER_EXE): $(SERVER_SRC) $(SERVER_DEPS)
	$(CC) $(CFLAGS) $(SERVER_DEPS) $(LINKER_FLAGS) -o $(SERVER_EXE) $(SERVER_SRC)