#include "ClickSerializer.h"

void Click::to_bin()
{
    alloc_data(bufferSize);

    char* tmp = _data;

    memcpy(tmp, name, sizeof(char)* MAX_NAME);

    tmp += sizeof(char)* MAX_NAME;

    memcpy(tmp, &pos_x, sizeof(int16_t));

    tmp += sizeof(int16_t);

    memcpy(tmp, &pos_y, sizeof(int16_t));

}

int Click::from_bin(char *data)
{
    memcpy(name, data, MAX_NAME);
    data += sizeof(char) * MAX_NAME;

    memcpy(&pos_x, data, sizeof(int16_t));
    data += sizeof(int16_t);

    memcpy(&pos_y, data, sizeof(int16_t));
    
    return 0;
}

void Click::setClickPos(int16_t newX, int16_t newY)
{
    pos_x = newX;
    pos_y = newY;
}

void Click::toFileAndBack(Click* deserializedClick)
{
    to_bin();
    // 2. Escribir la serialización en un fichero
    int id = open("binarios", O_RDWR | O_TRUNC, 0644);
    write(id, data(), size());
    close(id);
    // 3. Leer el fichero
    char buff[256];
    id = open("./binarios", O_RDONLY);
    read(id, buff, 256);
    close(id);
    // 4. "Deserializar" en one_r
    deserializedClick->from_bin(buff);
    // 5. Mostrar el contenido de one_r
    std::cout << deserializedClick->name << ", " << deserializedClick->pos_x << ", " << deserializedClick->pos_y << '\n';

}
