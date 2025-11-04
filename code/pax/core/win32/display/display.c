#ifndef PAX_WIN32_DISPLAY_DISPLAY_C
#define PAX_WIN32_DISPLAY_DISPLAY_C

#include "./display.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#define PAX_WIN32_DISPLAY_WIDTH  800
#define PAX_WIN32_DISPLAY_HEIGHT 600

#define PAX_WIN32_WINDOW_CLASS pax_str16(L"__pax_window_class__")

struct Pax_Win32_Display
{
    Pax_Display_Message_Filter filter;
    Pax_Win32_Display_Buffer*  buffer;

    HWND      handle;
    HINSTANCE instance;

    paxiword left;
    paxiword top;
    paxiword width;
    paxiword height;
};

struct Pax_Win32_Display_Buffer
{
    BITMAPINFO bitmap;

    paxu8*   memory;
    paxiword width;
    paxiword height;
    paxiword stride;
};

static Pax_Keyboard_Button
pax_win32_map_keyboard_button(paxiword value)
{
    switch (value) {
        case PAX_ASCII_UPPER_A: return PAX_KEYBOARD_BUTTON_A;
        case PAX_ASCII_UPPER_B: return PAX_KEYBOARD_BUTTON_B;
        case PAX_ASCII_UPPER_C: return PAX_KEYBOARD_BUTTON_C;
        case PAX_ASCII_UPPER_D: return PAX_KEYBOARD_BUTTON_D;
        case PAX_ASCII_UPPER_E: return PAX_KEYBOARD_BUTTON_E;
        case PAX_ASCII_UPPER_F: return PAX_KEYBOARD_BUTTON_F;
        case PAX_ASCII_UPPER_G: return PAX_KEYBOARD_BUTTON_G;
        case PAX_ASCII_UPPER_H: return PAX_KEYBOARD_BUTTON_H;
        case PAX_ASCII_UPPER_I: return PAX_KEYBOARD_BUTTON_I;
        case PAX_ASCII_UPPER_J: return PAX_KEYBOARD_BUTTON_J;
        case PAX_ASCII_UPPER_K: return PAX_KEYBOARD_BUTTON_K;
        case PAX_ASCII_UPPER_L: return PAX_KEYBOARD_BUTTON_L;
        case PAX_ASCII_UPPER_M: return PAX_KEYBOARD_BUTTON_M;
        case PAX_ASCII_UPPER_N: return PAX_KEYBOARD_BUTTON_N;
        case PAX_ASCII_UPPER_O: return PAX_KEYBOARD_BUTTON_O;
        case PAX_ASCII_UPPER_P: return PAX_KEYBOARD_BUTTON_P;
        case PAX_ASCII_UPPER_Q: return PAX_KEYBOARD_BUTTON_Q;
        case PAX_ASCII_UPPER_R: return PAX_KEYBOARD_BUTTON_R;
        case PAX_ASCII_UPPER_S: return PAX_KEYBOARD_BUTTON_S;
        case PAX_ASCII_UPPER_T: return PAX_KEYBOARD_BUTTON_T;
        case PAX_ASCII_UPPER_U: return PAX_KEYBOARD_BUTTON_U;
        case PAX_ASCII_UPPER_V: return PAX_KEYBOARD_BUTTON_V;
        case PAX_ASCII_UPPER_W: return PAX_KEYBOARD_BUTTON_W;
        case PAX_ASCII_UPPER_X: return PAX_KEYBOARD_BUTTON_X;
        case PAX_ASCII_UPPER_Y: return PAX_KEYBOARD_BUTTON_Y;
        case PAX_ASCII_UPPER_Z: return PAX_KEYBOARD_BUTTON_Z;

        case PAX_ASCII_ZERO:  return PAX_KEYBOARD_BUTTON_ZERO;
        case PAX_ASCII_ONE:   return PAX_KEYBOARD_BUTTON_ONE;
        case PAX_ASCII_TWO:   return PAX_KEYBOARD_BUTTON_TWO;
        case PAX_ASCII_THREE: return PAX_KEYBOARD_BUTTON_THREE;
        case PAX_ASCII_FOUR:  return PAX_KEYBOARD_BUTTON_FOUR;
        case PAX_ASCII_FIVE:  return PAX_KEYBOARD_BUTTON_FIVE;
        case PAX_ASCII_SIX:   return PAX_KEYBOARD_BUTTON_SIX;
        case PAX_ASCII_SEVEN: return PAX_KEYBOARD_BUTTON_SEVEN;
        case PAX_ASCII_EIGHT: return PAX_KEYBOARD_BUTTON_EIGHT;
        case PAX_ASCII_NINE:  return PAX_KEYBOARD_BUTTON_NINE;

        case VK_F1:  return PAX_KEYBOARD_BUTTON_F1;
        case VK_F2:  return PAX_KEYBOARD_BUTTON_F2;
        case VK_F3:  return PAX_KEYBOARD_BUTTON_F3;
        case VK_F4:  return PAX_KEYBOARD_BUTTON_F4;
        case VK_F5:  return PAX_KEYBOARD_BUTTON_F5;
        case VK_F6:  return PAX_KEYBOARD_BUTTON_F6;
        case VK_F7:  return PAX_KEYBOARD_BUTTON_F7;
        case VK_F8:  return PAX_KEYBOARD_BUTTON_F8;
        case VK_F9:  return PAX_KEYBOARD_BUTTON_F9;
        case VK_F10: return PAX_KEYBOARD_BUTTON_F10;
        case VK_F11: return PAX_KEYBOARD_BUTTON_F11;
        case VK_F12: return PAX_KEYBOARD_BUTTON_F12;

        case VK_NUMPAD0: return PAX_KEYBOARD_BUTTON_NUM0;
        case VK_NUMPAD1: return PAX_KEYBOARD_BUTTON_NUM1;
        case VK_NUMPAD2: return PAX_KEYBOARD_BUTTON_NUM2;
        case VK_NUMPAD3: return PAX_KEYBOARD_BUTTON_NUM3;
        case VK_NUMPAD4: return PAX_KEYBOARD_BUTTON_NUM4;
        case VK_NUMPAD5: return PAX_KEYBOARD_BUTTON_NUM5;
        case VK_NUMPAD6: return PAX_KEYBOARD_BUTTON_NUM6;
        case VK_NUMPAD7: return PAX_KEYBOARD_BUTTON_NUM7;
        case VK_NUMPAD8: return PAX_KEYBOARD_BUTTON_NUM8;
        case VK_NUMPAD9: return PAX_KEYBOARD_BUTTON_NUM9;

        case VK_SPACE:  return PAX_KEYBOARD_BUTTON_SPACE;
        case VK_RETURN: return PAX_KEYBOARD_BUTTON_ENTER;
        case VK_TAB:    return PAX_KEYBOARD_BUTTON_TAB;
        case VK_ESCAPE: return PAX_KEYBOARD_BUTTON_ESCAPE;
        case VK_BACK:   return PAX_KEYBOARD_BUTTON_BACKSPACE;
        case VK_DELETE: return PAX_KEYBOARD_BUTTON_DELETE;
        case VK_INSERT: return PAX_KEYBOARD_BUTTON_INSERT;
        case VK_HOME:   return PAX_KEYBOARD_BUTTON_HOME;
        case VK_END:    return PAX_KEYBOARD_BUTTON_END;
        case VK_PRIOR:  return PAX_KEYBOARD_BUTTON_PAGE_UP;
        case VK_NEXT:   return PAX_KEYBOARD_BUTTON_PAGE_DOWN;

        case VK_LEFT:  return PAX_KEYBOARD_BUTTON_LEFT;
        case VK_RIGHT: return PAX_KEYBOARD_BUTTON_RIGHT;
        case VK_UP:    return PAX_KEYBOARD_BUTTON_UP;
        case VK_DOWN:  return PAX_KEYBOARD_BUTTON_DOWN;

        case VK_LSHIFT:   return PAX_KEYBOARD_BUTTON_SHIFT_LEFT;
        case VK_RSHIFT:   return PAX_KEYBOARD_BUTTON_SHIFT_RIGHT;
        case VK_LCONTROL: return PAX_KEYBOARD_BUTTON_CTRL_LEFT;
        case VK_RCONTROL: return PAX_KEYBOARD_BUTTON_CTRL_RIGHT;
        case VK_LMENU:    return PAX_KEYBOARD_BUTTON_ALT_LEFT;
        case VK_RMENU:    return PAX_KEYBOARD_BUTTON_ALT_RIGHT;

        default: break;
    }

    return PAX_KEYBOARD_BUTTON_NONE;
}

long long CALLBACK
pax_win32_display_proc(HWND handle, UINT kind, WPARAM wparam, LPARAM lparam)
{
    long long data = GetWindowLongPtr(handle, GWLP_USERDATA);

    if (data == 0)
        return DefWindowProcW(handle, kind, wparam, lparam);

    Pax_Win32_Display* self = pax_as(Pax_Win32_Display*, data);

    switch (kind) {
        case WM_CLOSE:
        case WM_DESTROY: {
            PostQuitMessage(0);

            return 0;
        } break;

        case WM_SIZE: {
            self->width  = LOWORD(lparam);
            self->height = HIWORD(lparam);

            if (wparam == SIZE_MAXIMIZED)
                pax_win32_display_clear(self);

            return 0;
        } break;

        case WM_MOVE: {
            self->left = LOWORD(lparam);
            self->top  = HIWORD(lparam);

            return 0;
        } break;

        case WM_ERASEBKGND: {
            pax_win32_display_clear(self);

            return 1;
        } break;

        case WM_PAINT: {
            Pax_Win32_Display_Buffer* buffer = self->buffer;

            PAINTSTRUCT paint   = {0};
            HDC         context = BeginPaint(handle, &paint);

            if (buffer != 0) {
                paxiword left = (self->width  / 2) - (buffer->width  / 2);
                paxiword top  = (self->height / 2) - (buffer->height / 2);

                paxiword width  = pax_between(buffer->width,  0, self->width  - left);
                paxiword height = pax_between(buffer->height, 0, self->height - top);

                StretchDIBits(context, left, top, width, height, 0, 0, width, height,
                    buffer->memory, &buffer->bitmap, DIB_RGB_COLORS, SRCCOPY);
            }

            EndPaint(handle, &paint);

            return 0;
        } break;

        default: break;
    }

    return DefWindowProcW(handle, kind, wparam, lparam);
}

Pax_Win32_Display*
pax_win32_display_create(Pax_Arena* arena, Pax_String8 name)
{
    wchar_t* class_name = pax_as(wchar_t*, PAX_WIN32_WINDOW_CLASS.memory);

    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_Display* result =
        pax_arena_reserve(arena, Pax_Win32_Display, 1);

    if (result != 0) {
        paxiword     offset = pax_arena_tell(arena) - mark;
        Pax_String16 string = pax_string16_copy_string8(arena, name);

        if (string.length > 0) {
            wchar_t* memory = pax_as(wchar_t*, string.memory);

            result->instance = GetModuleHandle(0);
            result->width    = PAX_WIN32_DISPLAY_WIDTH;
            result->height   = PAX_WIN32_DISPLAY_HEIGHT;

            WNDCLASSW temp = {
                .style         = CS_HREDRAW | CS_VREDRAW,
                .lpfnWndProc   = &pax_win32_display_proc,
                .hInstance     = result->instance,
                .lpszClassName = class_name,
            };

            if (RegisterClassW(&temp) != 0) {
                RECT surface = {0, 0, result->width, result->height};

                AdjustWindowRect(&surface, 0, 0);

                result->handle = CreateWindowExW(0, class_name, memory,
                    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                    surface.right, surface.bottom, 0, 0, result->instance, 0);

                pax_arena_rewind(arena, mark, offset);

                if (result->handle != 0) {
                    SetWindowLongPtr(result->handle,
                        GWLP_USERDATA, pax_as(LONG_PTR, result));

                    pax_win32_display_clear(result);

                    return result;
                }

                UnregisterClassW(class_name, result->instance);
            }
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_win32_display_destroy(Pax_Win32_Display* self)
{
    wchar_t* class_name =
        pax_as(wchar_t*, PAX_WIN32_WINDOW_CLASS.memory);

    if (self == 0) return;

    DestroyWindow(self->handle);

    UnregisterClassW(class_name, self->instance);

    self->handle   = 0;
    self->instance = 0;
}

void
pax_win32_display_clear(Pax_Win32_Display* self)
{
    paxiword left   = 0;
    paxiword top    = 0;
    paxiword width  = self->width;
    paxiword height = self->height;

    HDC context = GetDC(self->handle);

    PatBlt(context, left, top, width, height, BLACKNESS);

    ReleaseDC(self->handle, context);
}

void
pax_win32_display_flush(Pax_Win32_Display* self, Pax_Win32_Display_Buffer* buffer)
{
    if (buffer == 0) return;

    HDC context = GetDC(self->handle);

    paxiword left = (self->width  / 2) - (buffer->width  / 2);
    paxiword top  = (self->height / 2) - (buffer->height / 2);

    paxiword width  = pax_between(buffer->width,  0, self->width  - left);
    paxiword height = pax_between(buffer->height, 0, self->height - top);

    StretchDIBits(context, left, top, width, height, 0, 0, width, height,
        buffer->memory, &buffer->bitmap, DIB_RGB_COLORS, SRCCOPY);

    ReleaseDC(self->handle, context);

    self->buffer = buffer;
}

paxb8
pax_win32_display_poll_message(Pax_Win32_Display* self, Pax_Display_Message* value)
{
    Pax_Display_Message message = {0};
    MSG                 event   = {0};

    while (PeekMessageW(&event, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&event);
        DispatchMessageW(&event);

        switch (event.message) {
            case WM_QUIT: {
                message = pax_display_message_display_destroy();
            } break;

            case WM_KEYUP:
            case WM_KEYDOWN: {
                if ((self->filter & PAX_DISPLAY_MESSAGE_FILTER_KEYBOARD) != 0)
                    break;

                Pax_Keyboard_Button button = pax_win32_map_keyboard_button(event.wParam);
                paxb8               active = event.message == WM_KEYDOWN ? 1 : 0;
                paxiword            code   = pax_as(paxiword, (event.lParam >> 16) & 0xff);

                message = pax_display_message_keyboard_button(button, active, code);
            } break;

            case WM_LBUTTONUP:
            case WM_LBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_RBUTTONDOWN: {
                if ((self->filter & PAX_DISPLAY_MESSAGE_FILTER_MOUSE) != 0)
                    break;

                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_NONE;
                paxb8            active = 0;

                switch (event.message) {
                    case WM_LBUTTONUP:
                    case WM_LBUTTONDOWN: {
                        button = PAX_MOUSE_BUTTON_LEFT;
                        active = event.message == WM_LBUTTONDOWN ? 1 : 0;
                    } break;

                    case WM_MBUTTONUP:
                    case WM_MBUTTONDOWN: {
                        button = PAX_MOUSE_BUTTON_MIDDLE;
                        active = event.message == WM_MBUTTONDOWN ? 1 : 0;
                    } break;

                    case WM_RBUTTONUP:
                    case WM_RBUTTONDOWN: {
                        button = PAX_MOUSE_BUTTON_RIGHT;
                        active = event.message == WM_RBUTTONDOWN ? 1 : 0;
                    } break;

                    default: break;
                }

                message = pax_display_message_mouse_button(button, active);
            } break;

            case WM_EXITSIZEMOVE: {
                if ((self->filter & PAX_DISPLAY_MESSAGE_FILTER_DISPLAY) != 0)
                    break;

                message = pax_display_message_display_rect(
                    self->left, self->top, self->width, self->height);
            } break;

            default: break;
        }

        if (message.kind != PAX_DISPLAY_MESSAGE_KIND_NONE) {
            if (value != 0)
                *value = message;

            return 1;
        }
    }

    return 0;
}

void
pax_win32_display_set_message_filter(Pax_Win32_Display* self, Pax_Display_Message_Filter filter)
{
    self->filter = filter;
}

paxb8
pax_win32_display_set_visibility(Pax_Win32_Display *self, Pax_Display_Visibility visibility)
{
    int command = 0;

    switch (visibility) {
        case PAX_DISPLAY_VISIBILITY_SHOW:   command = SW_SHOW;     break;
        case PAX_DISPLAY_VISIBILITY_HIDE:   command = SW_HIDE;     break;
        case PAX_DISPLAY_VISIBILITY_EXPAND: command = SW_MAXIMIZE; break;
        case PAX_DISPLAY_VISIBILITY_REDUCE: command = SW_MINIMIZE; break;
        case PAX_DISPLAY_VISIBILITY_CLEAR:  command = SW_RESTORE;  break;

        default: break;
    }

    if (command == 0) return 0;

    ShowWindow(self->handle, command);

    return 1;
}

Pax_Win32_Display_Buffer*
pax_win32_display_buffer_create(Pax_Win32_Display* self, Pax_Arena* arena, paxiword width, paxiword height)
{
    if (self == 0 || width <= 0 || height <= 0) return 0;

    paxiword mark   = pax_arena_tell(arena);
    paxiword length = width * height;
    paxiword stride = 4;

    Pax_Win32_Display_Buffer* result =
        pax_arena_reserve(arena, Pax_Win32_Display_Buffer, 1);

    if (result != 0) {
        result->bitmap.bmiHeader.biSize        = pax_size(BITMAPINFOHEADER);
        result->bitmap.bmiHeader.biWidth       = width;
        result->bitmap.bmiHeader.biHeight      = -height;
        result->bitmap.bmiHeader.biPlanes      = 1;
        result->bitmap.bmiHeader.biBitCount    = 32;
        result->bitmap.bmiHeader.biCompression = BI_RGB;

        result->memory = pax_arena_reserve_memory(arena, length, stride);

        result->width  = width;
        result->height = height;
        result->stride = stride;

        if (result->memory != 0) return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_win32_display_buffer_destroy(Pax_Win32_Display_Buffer* self)
{
    // Empty...
}

paxiword
pax_win32_display_buffer_length(Pax_Win32_Display_Buffer* self)
{
    return self->width * self->height;
}

paxiword
pax_win32_display_buffer_width(Pax_Win32_Display_Buffer* self)
{
    return self->width;
}

paxiword
pax_win32_display_buffer_height(Pax_Win32_Display_Buffer* self)
{
    return self->height;
}

paxiword
pax_win32_display_buffer_stride(Pax_Win32_Display_Buffer* self)
{
    return self->stride;
}

paxb8
pax_win32_display_buffer_write(Pax_Win32_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    self->memory[self->stride * index + 0] = b;
    self->memory[self->stride * index + 1] = g;
    self->memory[self->stride * index + 2] = r;

    return 1;
}

paxb8
pax_win32_display_buffer_read(Pax_Win32_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    if (b != 0) *b = self->memory[self->stride * index + 0];
    if (g != 0) *g = self->memory[self->stride * index + 1];
    if (r != 0) *r = self->memory[self->stride * index + 2];

    return 1;
}

#endif // PAX_WIN32_DISPLAY_DISPLAY_C
