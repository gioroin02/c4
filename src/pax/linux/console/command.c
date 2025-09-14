#ifndef PX_LINUX_CONSOLE_COMMAND_C
#define PX_LINUX_CONSOLE_COMMAND_C

#include "command.h"

#define PX_LINUX_CONSOLE_CMD_LENGTH PX_MEMORY_KIB

void
pxLinuxConsoleWriteCommand(PxWriter* self, PxConsoleCmd value)
{
    pxu8 memory[PX_LINUX_CONSOLE_CMD_LENGTH] = {0};

    PxBuilder builder = pxBuilderMake(
        memory, PX_LINUX_CONSOLE_CMD_LENGTH);

    pxuword radix  = 10;
    pxiword length = 0;

    PxFormatOption options = PX_FORMAT_OPTION_NONE;

    switch (value.type) {
        case PX_CONSOLE_CMD_STYLE_8_FRONT: {
            length = pxBuilderBuild(&builder, "\x1b[3${0}m",
                pxFormatCmdUnsigned8(radix, options, value.style_8));
        } break;

        case PX_CONSOLE_CMD_STYLE_8_BACK: {
            length = pxBuilderBuild(&builder, "\x1b[4${0}m",
                pxFormatCmdUnsigned8(radix, options, value.style_8));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_FRONT: {
            length = pxBuilderBuild(&builder, "\x1b[38;5;${0}m",
                pxFormatCmdUnsigned8(radix, options, value.style_256));
        } break;

        case PX_CONSOLE_CMD_STYLE_256_BACK: {
            length = pxBuilderBuild(&builder, "\x1b[48;5;${0}m",
                pxFormatCmdUnsigned8(radix, options, value.style_256));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_FRONT: {
            length = pxBuilderBuild(&builder, "\x1b[38;2;${0};${1};${2}m",
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.r),
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.g),
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.b));
        } break;

        case PX_CONSOLE_CMD_STYLE_RGB_BACK: {
            length = pxBuilderBuild(&builder, "\x1b[48;2;${0};${1};${2}m",
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.r),
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.g),
                pxFormatCmdUnsigned8(radix, options, value.style_rgb.b));
        } break;

        case PX_CONSOLE_CMD_STYLE_CLEAR:
            length = pxBuilderBuild(&builder, "\x1b[0m", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_SHOW:
            length = pxBuilderBuild(&builder, "\x1b[?25h", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_HIDE:
            length = pxBuilderBuild(&builder, "\x1b[?25l", {0});
        break;

        case PX_CONSOLE_CMD_CURSOR_UP: {
            length = pxBuilderBuild(&builder, "\x1b[${0}A",
                pxFormatCmdUnsigned8(radix, options, value.cursor_move));
        } break;

        case PX_CONSOLE_CMD_CURSOR_DOWN: {
            length = pxBuilderBuild(&builder, "\x1b[${0}B",
                pxFormatCmdUnsigned8(radix, options, value.cursor_move));
        } break;

        case PX_CONSOLE_CMD_CURSOR_RIGHT: {
            length = pxBuilderBuild(&builder, "\x1b[${0}C",
                pxFormatCmdUnsigned8(radix, options, value.cursor_move));
        } break;

        case PX_CONSOLE_CMD_CURSOR_LEFT: {
            length = pxBuilderBuild(&builder, "\x1b[${0}D",
                pxFormatCmdUnsigned8(radix, options, value.cursor_move));
        } break;

        case PX_CONSOLE_CMD_CURSOR_PLACE: {
            length = pxBuilderBuild(&builder, "\x1b[${0};${1}H",
                pxFormatCmdUnsigned8(radix, options, value.cursor_place.y + 1),
                pxFormatCmdUnsigned8(radix, options, value.cursor_place.x + 1));
        } break;

        case PX_CONSOLE_CMD_UNICODE: {
            length = pxBuilderBuild(&builder, "${0}",
                pxFormatCmdUnicode(value.unicode));
        } break;

        case PX_CONSOLE_CMD_STRING_8: {
            length = pxBuilderBuild(&builder, "${0}",
                pxFormatCmdString8(value.string_8));
        } break;

        case PX_CONSOLE_CMD_STRING_16: {
            length = pxBuilderBuild(&builder, "${0}",
                pxFormatCmdString16(value.string_16));
        } break;

        case PX_CONSOLE_CMD_STRING_32: {
            length = pxBuilderBuild(&builder, "${0}",
                pxFormatCmdString32(value.string_32));
        } break;

        case PX_CONSOLE_CMD_RESET:
            length = pxBuilderBuild(&builder, "\x1b\x63", {0});
        break;

        default: break;
    }

    pxWriterString8(self, pxString8Make(memory, length));
}

#endif // PX_LINUX_CONSOLE_COMMAND_C
