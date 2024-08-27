
// Online C++ Compiler - Build, Compile and Run your C++ programs online in your favorite browser

#include <iostream>
#include <cstdint>
#include <cstdio>

using namespace std;

typedef unsigned char BYTE;
BYTE buffer_data[184] = {
0xab, 0xcd, 0x00, 0xb3, 0x4a, 0x42, 0x00, 0x19, 0x01, 0x00, 
0x01, 0x02, 0x03, 0x14, 0x0f, 0x01, 0x04, 0x1c, 0x08, 0x04, 
0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1d, 0x4d,
0x42, 0x00, 0x75, 0xe2, 0x02, 0x61, 0xff, 0xc2, 0xff, 0x04,
0x00, 0x03, 0x04, 0x3e, 0x00, 0x2a, 0xff, 0xfb, 0x46, 0xc3, 
0x00, 0xff, 0xff, 0xff, 0xc2, 0x00, 0x00, 0x02, 0x61, 0x00,
0x2d, 0xe3, 0x03, 0x85, 0xff, 0xa5, 0xfe, 0xd2, 0x00, 0x02,
0x05, 0x03, 0x00, 0x2a, 0xff, 0xf6, 0x47, 0x1a, 0x00, 0xff,
0xff, 0xff, 0xa5, 0x00, 0x00, 0x03, 0x85, 0x00, 0x2d, 0xe4,
0x05, 0xee, 0xff, 0xe0, 0xfe, 0xd3, 0x00, 0x04, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x46, 0x62, 0x00, 0xff, 0xff, 0xff,
0xe0, 0x00, 0x00, 0x05, 0xee, 0x00, 0x2d, 0xe1, 0x06, 0x6d, 
0x00, 0x82, 0x00, 0xf7, 0x00, 0x08, 0x11, 0x63, 0x00, 0xb5,
0x00, 0x0b, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00,
0x00, 0x06, 0x6d, 0x00, 0x2f, 0xea, 0x44, 0x4c, 0x00, 0x25,
0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 
0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 
0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 
0x00, 0x00, 0xd9, 0xc0};

typedef struct {
    uint16_t head;
    uint16_t size;
} header;

typedef struct {
    uint8_t targetID;                 // Номер первой цели (1-255)
    uint16_t longitudinalDistance;     // Продольное расстояние
    uint16_t horizontalDistance;       // Горизонтальное расстояние
    uint16_t speedY;                   // Скорость (Y направление)
    uint8_t targetType;                // Тип цели (0-4)
    uint8_t laneNumber;                // Номер полосы движения (1-8)
    uint16_t frontDistance;            // Переднее расстояние
    uint16_t frontTimeInterval;        // Передний временной интервал
    uint16_t speedX;                   // Скорость (X направление)
    uint16_t guidingAngle;             // Направляющий угол (0-360)
    uint8_t eventOccurred;             // Произошло событие (каждый бит представляет событие)
    uint32_t radarNetworkX;            // Координата X радиолокационной сети
    uint32_t radarNetworkY;            // Координата Y радиолокационной сети
    uint8_t blindSpotFilled;           // Заполните слепую отметку (0: Отчет главного радара, 1: Заполните отчет о слепом радаре)
    uint8_t vehicleLength;             // Длина автомобиля
    uint8_t vehicleWidth;              // Ширина автомобиля
} infoModule;

int main()
{
    header *phead = (header*)buffer_data;
    uint32_t size = __builtin_bswap16(phead->size);
    uint32_t moduleIndex = 1;
    uint32_t headIndex = 0;
    
    while (size > 0) {
        phead->head = __builtin_bswap16(phead->head);
        phead->size = __builtin_bswap16(phead->size);
        printf("Module %d    %d %d\n", moduleIndex, headIndex, phead->size);
        printf(" - frame header\t0x%04X\n", 0xFFFF & phead->head);
        printf(" - frame size\t%d bytes\n", phead->size);        
        switch (phead->head) {
            case 0xABCD: {
                break;
            }
            case 0x4A42: {
                printf(" - data\t\t");
                for (int i=0; i<phead->size; i++)
                    printf("0x%02X ", buffer_data[i + headIndex + 4]);
                printf("\n");
                break;
            }
            case 0x4D42: {
                printf(" - crc\t\t0x%02X\n", buffer_data[headIndex + phead->size]);
                uint32_t targetIndex = 1;
                uint32_t moduleSize = phead->size;
                infoModule *target;
                
                while (moduleSize > 0) {
                    target = (infoModule*)&buffer_data[headIndex + (targetIndex - 1) * sizeof(infoModule) + 4];
                    target->longitudinalDistance = __builtin_bswap16(target->longitudinalDistance);
                    target->horizontalDistance   = __builtin_bswap16(target->horizontalDistance);
                    target->speedY               = __builtin_bswap16(target->speedY);
                    target->frontDistance        = __builtin_bswap16(target->frontDistance);
                    target->frontTimeInterval    = __builtin_bswap16(target->frontTimeInterval);
                    target->speedX               = __builtin_bswap16(target->speedX);
                    target->guidingAngle         = __builtin_bswap16(target->guidingAngle);
                    target->radarNetworkX        = __builtin_bswap32(target->radarNetworkX);
                    target->radarNetworkY        = __builtin_bswap32(target->radarNetworkY);
                    
                    printf(" - Target N%d:\n", targetIndex);
                    printf("    - targetID\t\t\t%d\n",          target->targetID);
                    printf("    - longitudinalDistance\t%d\n",  target->longitudinalDistance);
                    printf("    - horizontalDistance\t%d\n",    target->horizontalDistance);
                    printf("    - speedY\t\t\t%d\n",            target->speedY);
                    printf("    - targetType\t\t%d\n",          target->targetType);
                    printf("    - laneNumber\t\t%d\n",          target->laneNumber);
                    printf("    - frontDistance\t\t%d\n",       target->frontDistance);
                    printf("    - frontTimeInterval\t\t%d\n",   target->frontTimeInterval);
                    printf("    - speedX\t\t\t%d\n",            target->speedX);
                    printf("    - guidingAngle\t\t%d\n",        target->guidingAngle);
                    printf("    - eventOccurred:\n");
                    if ((targetr->eventOccurred & (1 << 0)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 1)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 2)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 3)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 4)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 5)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 6)) != 0) printf("      - 0: Event flag\n");
                    if ((targetr->eventOccurred & (1 << 7)) != 0) printf("      - 0: Event flag\n");
                    printf("    - radarNetworkX\t\t%u\n",       target->radarNetworkX);
                    printf("    - radarNetworkY\t\t%u\n",       target->radarNetworkY);
                    printf("    - blindSpotFilled\t\t%d\n",     target->blindSpotFilled);
                    printf("    - vehicleLength\t\t%d\n",       target->vehicleLength);
                    printf("    - vehicleWidth\t\t%d\n",        target->vehicleWidth);
                    
                    targetIndex++;
                    if (moduleSize >= sizeof(infoModule)) {
                        moduleSize -= sizeof(infoModule);
                    }
                    else
                        moduleSize = 0;
                }
                break;
            }
            default: {
                size = 0;
                break;
            }
        }
        
        if (size > 0) {
            if (moduleIndex == 1) {
                headIndex += 4;
                size -= 4;
            }
            else {
                headIndex += phead->size;
                size -= phead->size;
            }
            phead = (header*)&buffer_data[headIndex];
        }

        moduleIndex++;
    }
    return 0;
}

