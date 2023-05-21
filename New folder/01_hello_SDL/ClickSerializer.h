#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class Click: public Serializable
{
public:
    Click(const char * _n, int16_t _x, int16_t _y):pos_x(_x),pos_y(_y)
    {
        printf( "Click creado!\n" );
        strncpy(name, _n, MAX_NAME);
    };

    virtual ~Click(){};

    void to_bin();

    int from_bin(char * data);

    void setClickPos(int16_t newX, int16_t newY);

    void toFileAndBack(Click* deserializedClick);


private:
    const int32_t bufferSize = (sizeof(char) * MAX_NAME) + (sizeof(int16_t) * 2);
    static const size_t MAX_NAME = 20;
    char name[MAX_NAME];

    int16_t pos_x;
    int16_t pos_y;

    int fd;
};