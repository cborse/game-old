#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "scenes/scene.h"
#include "helpers/frame.h"
#include "helpers/text.h"

typedef struct
{
    Scene scene;
    Frame *frame;
    Text *texts[4];
    Text *text_info[4];
} PlayerInfo;

void PlayerInfo_init(void);

#endif
