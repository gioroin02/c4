#include "../export.h"
#include "../../cpax/pax/stream/export.h"

#include <stdio.h>

pxiword
fileRead(void* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword amount = 0;

    fgets(pxCast(char*, memory), size, self);

    while (memory[amount] != 0)
        amount += 1;

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

PxReader
fileReader(void* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &fileRead,
    };
}

void
showGameBoard(C4GameBoard* self)
{
    printf("#");

    for (pxiword i = 0; i < self->width; i += 1)
        printf("-------#");

    printf("\n");

    for (pxiword r = self->height; r > 0; r -= 1) {
        printf("| ");

        for (pxiword c = 0; c < self->width; c += 1) {
            pxuword item = c4GameBoardReadOr(self, c, r - 1, 0);

            if (item != 0)
                printf(" %4llu | ", item);
            else
                printf("      | ");
        }

        printf("\n");
    }

    printf("#");

    for (pxiword i = 0; i < self->width; i += 1)
        printf("-------#");

    printf("\n");
}

pxiword
consoleReadIWord(PxString8 string, PxReader* reader, PxArena* arena, PxFormatOptions options)
{
    pxb8    state  = 0;
    pxiword result = 0;
    pxiword offset = pxArenaOffset(arena);

    do {
        printf("%.*s", pxCast(int, string.length), string.memory);

        PxString8 line =
            pxReaderLine(reader, arena, reader->buffer->length);

        state = pxIWordFromString8(&result, options, line);

        pxArenaRewind(arena, offset);
    } while (state == 0);

    return result;
}

pxuword
playerHasWon(C4GameBoard* self, pxiword x, pxiword y, pxiword length)
{
    #define DIRS 8

    pxiword xs[DIRS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    pxiword ys[DIRS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    pxuword value = 0;

    for (pxiword i = 0; i < DIRS; i += 1) {
        pxiword line =
            c4GameBoardContainsLine(self, x, y, xs[i], ys[i], &value);

        printf("");

        if (line >= length) return value;
    }

    printf("\n");

    return 0;
}

int
main(int argc, char** argv)
{
    PxArena     arena = pxMemoryReserve(16);
    C4GameBoard board = c4GameBoardReserve(&arena, 7, 5);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    PxReader  reader = fileReader(stdin, &buffer);

    PxFormatOptions options = pxFormatOptions(10,
        PX_FORMAT_FLAG_LEADING_ZERO | PX_FORMAT_FLAG_LEADING_PLUS);

    pxuword value = 0;

    while (value == 0) {
        pxiword column = board.width;
        pxiword height = board.height;
        pxb8    state  = 0;

        showGameBoard(&board);

        printf("\n");

        column = consoleReadIWord(pxs8("-> "),
            &reader, &arena, options) - 1;

        if (column < 0 || column >= board.width)
            break;

        height = c4GameBoardHeight(&board, column);

        printf("\n");

        c4GameBoardInsert(&board, column, 1);

        value  = playerHasWon(&board, column, height, 4);
    }

    showGameBoard(&board);
}
