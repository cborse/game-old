#ifndef MESSAGE_H
#define MESSAGE_H

void Message_start(void);

void Message_line(const char *string);

void Message_next(const char *string);

void Message_continue(const char *string);

_Bool Message_yesno(_Bool right_side);

void Message_prompt(_Bool visual);

void Message_end(void);

#endif
