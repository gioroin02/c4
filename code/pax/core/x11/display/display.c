#ifndef PAX_X11_DISPLAY_DISPLAY_C
#define PAX_X11_DISPLAY_DISPLAY_C

#include "./display.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>

#define PAX_X11_DISPLAY_WIDTH  800
#define PAX_X11_DISPLAY_HEIGHT 600

struct Pax_X11_Display
{
    Pax_Display_Message_Filter filter;
    Pax_X11_Display_Buffer*    buffer;

    Display *connection;
    Window   window;
    int      screen;

    Atom wm_delete_window;

    paxiword left;
    paxiword top;
    paxiword width;
    paxiword height;
};

struct Pax_X11_Display_Buffer
{
    XImage* image;

    paxu8*   memory;
    paxiword width;
    paxiword height;
    paxiword stride;
};

static Pax_Keyboard_Button
pax_x11_map_keyboard_button(KeySym value)
{
    switch (value) {
        case XK_a: case XK_A: return PAX_KEYBOARD_BUTTON_A;
        case XK_b: case XK_B: return PAX_KEYBOARD_BUTTON_B;
        case XK_c: case XK_C: return PAX_KEYBOARD_BUTTON_C;
        case XK_d: case XK_D: return PAX_KEYBOARD_BUTTON_D;
        case XK_e: case XK_E: return PAX_KEYBOARD_BUTTON_E;
        case XK_f: case XK_F: return PAX_KEYBOARD_BUTTON_F;
        case XK_g: case XK_G: return PAX_KEYBOARD_BUTTON_G;
        case XK_h: case XK_H: return PAX_KEYBOARD_BUTTON_H;
        case XK_i: case XK_I: return PAX_KEYBOARD_BUTTON_I;
        case XK_j: case XK_J: return PAX_KEYBOARD_BUTTON_J;
        case XK_k: case XK_K: return PAX_KEYBOARD_BUTTON_K;
        case XK_l: case XK_L: return PAX_KEYBOARD_BUTTON_L;
        case XK_m: case XK_M: return PAX_KEYBOARD_BUTTON_M;
        case XK_n: case XK_N: return PAX_KEYBOARD_BUTTON_N;
        case XK_o: case XK_O: return PAX_KEYBOARD_BUTTON_O;
        case XK_p: case XK_P: return PAX_KEYBOARD_BUTTON_P;
        case XK_q: case XK_Q: return PAX_KEYBOARD_BUTTON_Q;
        case XK_r: case XK_R: return PAX_KEYBOARD_BUTTON_R;
        case XK_s: case XK_S: return PAX_KEYBOARD_BUTTON_S;
        case XK_t: case XK_T: return PAX_KEYBOARD_BUTTON_T;
        case XK_u: case XK_U: return PAX_KEYBOARD_BUTTON_U;
        case XK_v: case XK_V: return PAX_KEYBOARD_BUTTON_V;
        case XK_w: case XK_W: return PAX_KEYBOARD_BUTTON_W;
        case XK_x: case XK_X: return PAX_KEYBOARD_BUTTON_X;
        case XK_y: case XK_Y: return PAX_KEYBOARD_BUTTON_Y;
        case XK_z: case XK_Z: return PAX_KEYBOARD_BUTTON_Z;

        case XK_0: return PAX_KEYBOARD_BUTTON_ZERO;
        case XK_1: return PAX_KEYBOARD_BUTTON_ONE;
        case XK_2: return PAX_KEYBOARD_BUTTON_TWO;
        case XK_3: return PAX_KEYBOARD_BUTTON_THREE;
        case XK_4: return PAX_KEYBOARD_BUTTON_FOUR;
        case XK_5: return PAX_KEYBOARD_BUTTON_FIVE;
        case XK_6: return PAX_KEYBOARD_BUTTON_SIX;
        case XK_7: return PAX_KEYBOARD_BUTTON_SEVEN;
        case XK_8: return PAX_KEYBOARD_BUTTON_EIGHT;
        case XK_9: return PAX_KEYBOARD_BUTTON_NINE;

        case XK_F1:  return PAX_KEYBOARD_BUTTON_F1;
        case XK_F2:  return PAX_KEYBOARD_BUTTON_F2;
        case XK_F3:  return PAX_KEYBOARD_BUTTON_F3;
        case XK_F4:  return PAX_KEYBOARD_BUTTON_F4;
        case XK_F5:  return PAX_KEYBOARD_BUTTON_F5;
        case XK_F6:  return PAX_KEYBOARD_BUTTON_F6;
        case XK_F7:  return PAX_KEYBOARD_BUTTON_F7;
        case XK_F8:  return PAX_KEYBOARD_BUTTON_F8;
        case XK_F9:  return PAX_KEYBOARD_BUTTON_F9;
        case XK_F10: return PAX_KEYBOARD_BUTTON_F10;
        case XK_F11: return PAX_KEYBOARD_BUTTON_F11;
        case XK_F12: return PAX_KEYBOARD_BUTTON_F12;

        case XK_KP_0: return PAX_KEYBOARD_BUTTON_NUM0;
        case XK_KP_1: return PAX_KEYBOARD_BUTTON_NUM1;
        case XK_KP_2: return PAX_KEYBOARD_BUTTON_NUM2;
        case XK_KP_3: return PAX_KEYBOARD_BUTTON_NUM3;
        case XK_KP_4: return PAX_KEYBOARD_BUTTON_NUM4;
        case XK_KP_5: return PAX_KEYBOARD_BUTTON_NUM5;
        case XK_KP_6: return PAX_KEYBOARD_BUTTON_NUM6;
        case XK_KP_7: return PAX_KEYBOARD_BUTTON_NUM7;
        case XK_KP_8: return PAX_KEYBOARD_BUTTON_NUM8;
        case XK_KP_9: return PAX_KEYBOARD_BUTTON_NUM9;

        case XK_space:      return PAX_KEYBOARD_BUTTON_SPACE;
        case XK_Return:     return PAX_KEYBOARD_BUTTON_ENTER;
        case XK_Tab:        return PAX_KEYBOARD_BUTTON_TAB;
        case XK_Escape:     return PAX_KEYBOARD_BUTTON_ESCAPE;
        case XK_BackSpace:  return PAX_KEYBOARD_BUTTON_BACKSPACE;
        case XK_Delete:     return PAX_KEYBOARD_BUTTON_DELETE;
        case XK_Insert:     return PAX_KEYBOARD_BUTTON_INSERT;
        case XK_Home:       return PAX_KEYBOARD_BUTTON_HOME;
        case XK_End:        return PAX_KEYBOARD_BUTTON_END;
        case XK_Page_Up:    return PAX_KEYBOARD_BUTTON_PAGE_UP;
        case XK_Page_Down:  return PAX_KEYBOARD_BUTTON_PAGE_DOWN;

        case XK_Left:  return PAX_KEYBOARD_BUTTON_LEFT;
        case XK_Right: return PAX_KEYBOARD_BUTTON_RIGHT;
        case XK_Up:    return PAX_KEYBOARD_BUTTON_UP;
        case XK_Down:  return PAX_KEYBOARD_BUTTON_DOWN;

        case XK_Shift_L:   return PAX_KEYBOARD_BUTTON_SHIFT_LEFT;
        case XK_Shift_R:   return PAX_KEYBOARD_BUTTON_SHIFT_RIGHT;
        case XK_Control_L: return PAX_KEYBOARD_BUTTON_CTRL_LEFT;
        case XK_Control_R: return PAX_KEYBOARD_BUTTON_CTRL_RIGHT;
        case XK_Alt_L:     return PAX_KEYBOARD_BUTTON_ALT_LEFT;
        case XK_Alt_R:     return PAX_KEYBOARD_BUTTON_ALT_RIGHT;

        default: break;
    }

    return PAX_KEYBOARD_BUTTON_NONE;
}

Pax_X11_Display*
pax_x11_display_create(Pax_Arena* arena, Pax_String8 name)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_X11_Display* result = pax_arena_reserve(arena, Pax_X11_Display, 1);

    if (result != 0 && name.length > 0) {
        result->connection = XOpenDisplay(NULL);
        result->screen     = DefaultScreen(result->connection);
        result->width      = PAX_X11_DISPLAY_WIDTH;
        result->height     = PAX_X11_DISPLAY_HEIGHT;

        Window parent = DefaultRootWindow(result->connection);

        result->window = XCreateSimpleWindow(result->connection,
            parent, 0, 0, result->width, result->height, 0, 0, 0);

        if (result->window != 0) {
            pax_x11_display_set_message_filter(result, PAX_DISPLAY_MESSAGE_FILTER_NONE);

            XStoreName(result->connection, result->window, name.memory);

            result->wm_delete_window =
                XInternAtom(result->connection, "WM_DELETE_WINDOW", False);

            XSetWMProtocols(result->connection,
                result->window, &result->wm_delete_window, 1);

            // XSetWindowAttributes attrib;

            // attrib.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
            //     ButtonPressMask | ButtonReleaseMask | StructureNotifyMask;

            // XChangeWindowAttributes(result->connection, result->window,
            //     CWEventMask, &attrib);

            return result;
        }

        XCloseDisplay(result->connection);
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_x11_display_destroy(Pax_X11_Display* self)
{
    if (self == 0) return;

    XDestroyWindow(self->connection,
        self->window);

    XCloseDisplay(self->connection);

    self->connection = 0;
    self->window     = 0;
}

void
pax_x11_display_clear(Pax_X11_Display* self)
{
    // Empty...
}

void
pax_x11_display_flush(Pax_X11_Display* self, Pax_X11_Display_Buffer* buffer)
{
    if (buffer != 0) {
        GC context = DefaultGC(self->connection, self->screen);

        XPutImage(self->connection, self->window, context,
            buffer->image, 0, 0, 0, 0, self->width, self->height);

        XFlush(self->connection);

        self->buffer = buffer;
    }
}

paxb8
pax_x11_display_poll_message(Pax_X11_Display* self, Pax_Display_Message* value)
{
    Pax_Display_Message message = {0};
    XEvent              event   = {0};

    while (XPending(self->connection) > 0) {
        XNextEvent(self->connection, &event);

        switch (event.type) {
            case Expose: pax_x11_display_clear(self); break;

            case ClientMessage: {
                long item = event.xclient.data.l[0];

                if (item == pax_as(long, self->wm_delete_window))
                    message = pax_display_message_display_destroy();
            } break;

            case ConfigureNotify: {
                self->width  = event.xconfigure.width;
                self->height = event.xconfigure.height;
            } break;

            case KeyPress:
            case KeyRelease: {
                KeySym keysym = XLookupKeysym(&event.xkey, 0);

                Pax_Keyboard_Button button = pax_x11_map_keyboard_button(keysym);
                paxb8               active = (event.type == KeyPress) ? 1 : 0;
                paxiword            code   = event.xkey.keycode;

                message = pax_display_message_keyboard_button(button, active, code);
            } break;

            case ButtonPress:
            case ButtonRelease: {
                Pax_Mouse_Button button = PAX_MOUSE_BUTTON_NONE;
                paxb8            active = (event.type == ButtonPress) ? 1 : 0;

                switch (event.xbutton.button) {
                    case Button1: button = PAX_MOUSE_BUTTON_LEFT;   break;
                    case Button2: button = PAX_MOUSE_BUTTON_MIDDLE; break;
                    case Button3: button = PAX_MOUSE_BUTTON_RIGHT;  break;

                    default: break;
                }

                if (button != PAX_MOUSE_BUTTON_NONE)
                    message = pax_display_message_mouse_button(button, active);
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
pax_x11_display_set_message_filter(Pax_X11_Display* self, Pax_Display_Message_Filter filter)
{
    long mask = 0;

    if ((filter & PAX_DISPLAY_MESSAGE_FILTER_KEYBOARD_BUTTON) == 0)
        mask |= KeyPressMask | KeyReleaseMask;

    if ((filter & PAX_DISPLAY_MESSAGE_FILTER_MOUSE_BUTTON) == 0)
        mask |= ButtonPressMask | ButtonReleaseMask;

    XSelectInput(self->connection, self->window, mask);

    self.filter = filter;
}

paxb8
pax_x11_display_set_visibility(Pax_X11_Display *self, Pax_Display_Visibility visibility)
{
    switch (visibility) {
        case PAX_DISPLAY_VISIBILITY_SHOW:
            XMapWindow(self->connection, self->window);
        break;

        case PAX_DISPLAY_VISIBILITY_HIDE:
            XUnmapWindow(self->connection, self->window);
        break;

        case PAX_DISPLAY_VISIBILITY_EXPAND: {
            XEvent event = {0};

            event.type                 = ClientMessage;
            event.xclient.window       = self->window;
            event.xclient.message_type = XInternAtom(self->connection, "_NET_WM_STATE", False);
            event.xclient.format       = 32;
            event.xclient.data.l[0]    = 1;
            event.xclient.data.l[1]    = XInternAtom(self->connection, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            event.xclient.data.l[2]    = XInternAtom(self->connection, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            event.xclient.data.l[3]    = 0;
            event.xclient.data.l[4]    = 0;

            XSendEvent(self->connection, DefaultRootWindow(self->connection),
                False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        } break;

        case PAX_DISPLAY_VISIBILITY_REDUCE:
            XIconifyWindow(self->connection, self->window, self->screen);
        break;

        case PAX_DISPLAY_VISIBILITY_CLEAR: {
            XEvent event = {0};

            event.type                 = ClientMessage;
            event.xclient.window       = self->window;
            event.xclient.message_type = XInternAtom(self->connection, "_NET_WM_STATE", False);
            event.xclient.format       = 32;
            event.xclient.data.l[0]    = 0;
            event.xclient.data.l[1]    = XInternAtom(self->connection, "_NET_WM_STATE_MAXIMIZED_VERT", False);
            event.xclient.data.l[2]    = XInternAtom(self->connection, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            event.xclient.data.l[3]    = 0;
            event.xclient.data.l[4]    = 0;

            XSendEvent(self->connection, DefaultRootWindow(self->connection),
                False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        } break;

        default: return 0;
    }

    XFlush(self->connection);

    return 1;
}

Pax_X11_Display_Buffer*
pax_x11_display_buffer_create(Pax_X11_Display* self, Pax_Arena* arena, paxiword width, paxiword height)
{
    if (width <= 0 || height <= 0) return 0;

    paxiword mark   = pax_arena_tell(arena);
    paxiword length = width * height;
    paxiword stride = 4;

    Pax_X11_Display_Buffer* result =
        pax_arena_reserve(arena, Pax_X11_Display_Buffer, 1);

    if (result != 0) {
        Visual* visual = DefaultVisual(self->connection, self->screen);
        int     depth  = DefaultDepth(self->connection, self->screen);

        result->memory = pax_arena_reserve_memory(arena, length, stride);

        result->image = XCreateImage(self->connection, visual, depth, ZPixmap, 0,
            pax_as(char*, result->memory), width, height, 32, width * stride);

        if (result->memory != 0 && result->image != 0) {
            result->width  = width;
            result->height = height;
            result->stride = stride;

            Pax_Slice slice = pax_slice_make(
                result->memory, length, stride);

            pax_slice_zero(slice);

            return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_x11_display_buffer_destroy(Pax_X11_Display_Buffer* self)
{
    if (self == 0) return;

    if (self->image != 0)
        XDestroyImage(self->image);

    self->memory = 0;
    self->image  = 0;
}

paxiword
pax_x11_display_buffer_length(Pax_X11_Display_Buffer* self)
{
    return self->width * self->height;
}

paxiword
pax_x11_display_buffer_width(Pax_X11_Display_Buffer* self)
{
    return self->width;
}

paxiword
pax_x11_display_buffer_height(Pax_X11_Display_Buffer* self)
{
    return self->height;
}

paxiword
pax_x11_display_buffer_stride(Pax_X11_Display_Buffer* self)
{
    return self->stride;
}

paxb8
pax_x11_display_buffer_write(Pax_X11_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    self->memory[self->stride * index + 0] = r;
    self->memory[self->stride * index + 1] = g;
    self->memory[self->stride * index + 2] = b;

    return 1;
}

paxb8
pax_x11_display_buffer_read(Pax_X11_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    if (r != 0) *r = self->memory[self->stride * index + 0];
    if (g != 0) *g = self->memory[self->stride * index + 1];
    if (b != 0) *b = self->memory[self->stride * index + 2];

    return 1;
}

#endif // PAX_X11_DISPLAY_DISPLAY_C
