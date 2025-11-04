// Note: As per your request, I've separated the implementations completely: first the full Win32 (Windows) implementation,
// then the full X11 (Linux) implementation. Shared structs, enums, and helpers are duplicated in each for completeness.
// You can copy-paste each section independently if needed. I've kept the function names the same for the abstraction,
// but in practice, you might wrap them with platform defines.

// I've assumed a basic Arena allocator with a function like arena_alloc_struct(arena, Type) for allocation.
// If your Arena API is different, adjust accordingly.
// String8 is assumed to be a struct like { u8* data; size_t size; }.
// For simplicity, titles are assumed to be ASCII/UTF-8 compatible; no advanced Unicode handling.
// Events/messages are handled via a polling function, focusing on the enum kinds.

// -----------------------------------------------------------------------------
// Win32 Implementation (Windows)
// -----------------------------------------------------------------------------

#include <stdint.h> // For uint8_t, etc.
typedef uint8_t u8;
typedef size_t usize;

// Assuming String8 definition (adjust if needed)
typedef struct String8 {
    u8* data;
    usize size;
} String8;

// Assuming Arena definition with allocation (stub; replace with your actual Arena API)
typedef struct Arena {
    // Your arena details...
} Arena;

void* arena_alloc(Arena* arena, usize size); // Stub: Implement or use your allocator
#define arena_alloc_struct(arena, Type) (Type*)arena_alloc((arena), sizeof(Type))

#include <windows.h>

// Internal window struct (platform-specific)
typedef struct Window_Internal {
    HWND hwnd;
    HINSTANCE hinstance;
    // Add more fields if needed, e.g., for event queue
} Window_Internal;

typedef Window_Internal* Window;

// Helper to convert String8 to null-terminated C string (allocates temp buffer if needed)
static char* string8_to_cstr(Arena* arena, String8 str) {
    char* cstr = (char*)arena_alloc(arena, str.size + 1);
    if (cstr) {
        memcpy(cstr, str.data, str.size);
        cstr[str.size] = '\0';
    }
    return cstr;
}

Window
windows_create(Arena* arena, String8 title, int width, int height) {
    Window_Internal* win = arena_alloc_struct(arena, Window_Internal);
    if (!win) {
        return NULL; // Allocation failed
    }

    HINSTANCE hinstance = GetModuleHandle(NULL);
    win->hinstance = hinstance;

    // Register window class
    WNDCLASS wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc; // Default proc for now; extend for events
    wc.hInstance = hinstance;
    wc.lpszClassName = "AbstractWindowClass";
    RegisterClass(&wc);

    // Create window
    char* title_cstr = string8_to_cstr(arena, title);
    win->hwnd = CreateWindow("AbstractWindowClass", title_cstr ? title_cstr : "Untitled",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             width, height, NULL, NULL, hinstance, NULL);
    if (!win->hwnd) {
        // Error handling: You can add logging or return NULL
        return NULL;
    }

    ShowWindow(win->hwnd, SW_SHOW);
    UpdateWindow(win->hwnd);

    return win;
}

void
windows_destroy(Window self) {
    if (!self) return;

    Window_Internal* win = (Window_Internal*)self;

    if (win->hwnd) {
        DestroyWindow(win->hwnd);
    }
    UnregisterClass("AbstractWindowClass", win->hinstance);

    // Note: Assuming arena handles deallocation; if not, free(win) here.
}

typedef enum Window_Message_Kind {
    WINDOW_MESSAGE_KIND_NONE,
    WINDOW_MESSAGE_KIND_CLOSE,
    WINDOW_MESSAGE_KIND_COORDS,
    WINDOW_MESSAGE_KIND_SIZE,
} Window_Message_Kind;

typedef struct Window_Message {
    Window_Message_Kind kind;

    union {
        struct { int x, y; } coords; // For COORDS
        struct { int width, height; } size; // For SIZE
        // Add more as needed
    };
} Window_Message;

Window_Message
windows_poll_message(Window self) {
    Window_Message msg = { WINDOW_MESSAGE_KIND_NONE };

    if (!self) return msg;

    Window_Internal* win = (Window_Internal*)self;

    MSG win_msg;
    if (PeekMessage(&win_msg, win->hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&win_msg);
        DispatchMessage(&win_msg);

        switch (win_msg.message) {
            case WM_CLOSE:
            case WM_QUIT:
            case WM_DESTROY: {
                msg.kind = WINDOW_MESSAGE_KIND_CLOSE;
            } break;
            case WM_MOVE: {
                msg.kind = WINDOW_MESSAGE_KIND_COORDS;
                msg.coords.x = (int)LOWORD(win_msg.lParam);
                msg.coords.y = (int)HIWORD(win_msg.lParam);
            } break;
            case WM_SIZE: {
                msg.kind = WINDOW_MESSAGE_KIND_SIZE;
                msg.size.width = (int)LOWORD(win_msg.lParam);
                msg.size.height = (int)HIWORD(win_msg.lParam);
            } break;
        }
    }

    return msg;
}

// -----------------------------------------------------------------------------
// X11 Implementation (Linux)
// -----------------------------------------------------------------------------

#include <stdint.h> // For uint8_t, etc.
typedef uint8_t u8;
typedef size_t usize;

// Assuming String8 definition (adjust if needed)
typedef struct String8 {
    u8* data;
    usize size;
} String8;

// Assuming Arena definition with allocation (stub; replace with your actual Arena API)
typedef struct Arena {
    // Your arena details...
} Arena;

void* arena_alloc(Arena* arena, usize size); // Stub: Implement or use your allocator
#define arena_alloc_struct(arena, Type) (Type*)arena_alloc((arena), sizeof(Type))

#include <X11/Xlib.h>
#include <stdlib.h> // For exit on error
#include <string.h> // For memcpy

// Internal window struct (platform-specific)
typedef struct Window_Internal {
    Display* display;
    Window xwindow;
    // Add more fields if needed, e.g., for event queue
} Window_Internal;

typedef Window_Internal* Window;

// Helper to convert String8 to null-terminated C string (allocates temp buffer if needed)
static char* string8_to_cstr(Arena* arena, String8 str) {
    char* cstr = (char*)arena_alloc(arena, str.size + 1);
    if (cstr) {
        memcpy(cstr, str.data, str.size);
        cstr[str.size] = '\0';
    }
    return cstr;
}

Window
windows_create(Arena* arena, String8 title, int width, int height) {
    Window_Internal* win = arena_alloc_struct(arena, Window_Internal);
    if (!win) {
        return NULL; // Allocation failed
    }

    win->display = XOpenDisplay(NULL);
    if (!win->display) {
        // Error: No display
        return NULL;
    }

    Screen* screen = DefaultScreenOfDisplay(win->display);
    int screen_num = DefaultScreen(win->display);

    char* title_cstr = string8_to_cstr(arena, title);

    // Create window
    win->xwindow = XCreateSimpleWindow(win->display, RootWindow(win->display, screen_num),
                                       0, 0, width, height, 1,
                                       BlackPixel(win->display, screen_num),
                                       WhitePixel(win->display, screen_num));
    if (!win->xwindow) {
        XCloseDisplay(win->display);
        return NULL;
    }

    // Set title
    if (title_cstr) {
        XStoreName(win->display, win->xwindow, title_cstr);
    }

    // Select events (focus on the kinds in your enum: close, move/coords, resize/size)
    XSelectInput(win->display, win->xwindow,
                 StructureNotifyMask | // For ConfigureNotify (resize/move)
                 ClientMessage);       // For WM_DELETE_WINDOW (close)

    // Handle close event protocol
    Atom wm_delete = XInternAtom(win->display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(win->display, win->xwindow, &wm_delete, 1);

    // Map/show window
    XMapWindow(win->display, win->xwindow);
    XFlush(win->display);

    return win;
}

void
windows_destroy(Window self) {
    if (!self) return;

    Window_Internal* win = (Window_Internal*)self;

    if (win->display && win->xwindow) {
        XDestroyWindow(win->display, win->xwindow);
        XCloseDisplay(win->display);
    }

    // Note: Assuming arena handles deallocation; if not, free(win) here.
}

typedef enum Window_Message_Kind {
    WINDOW_MESSAGE_KIND_NONE,
    WINDOW_MESSAGE_KIND_CLOSE,
    WINDOW_MESSAGE_KIND_COORDS,
    WINDOW_MESSAGE_KIND_SIZE,
} Window_Message_Kind;

typedef struct Window_Message {
    Window_Message_Kind kind;

    union {
        struct { int x, y; } coords; // For COORDS
        struct { int width, height; } size; // For SIZE
        // Add more as needed
    };
} Window_Message;

Window_Message
windows_poll_message(Window self) {
    Window_Message msg = { WINDOW_MESSAGE_KIND_NONE };

    if (!self) return msg;

    Window_Internal* win = (Window_Internal*)self;

    if (win->display) {
        XEvent event;
        if (XPending(win->display)) {
            XNextEvent(win->display, &event);

            switch (event.type) {
                case ClientMessage: {
                    // Close event
                    Atom wm_delete = XInternAtom(win->display, "WM_DELETE_WINDOW", True);
                    if (event.xclient.data.l[0] == wm_delete) {
                        msg.kind = WINDOW_MESSAGE_KIND_CLOSE;
                    }
                } break;
                case ConfigureNotify: {
                    // Handles both move and resize; you can emit two messages if needed
                    msg.kind = WINDOW_MESSAGE_KIND_SIZE; // Example: prioritize size
                    msg.size.width = event.xconfigure.width;
                    msg.size.height = event.xconfigure.height;
                    // Alternatively for coords:
                    // msg.kind = WINDOW_MESSAGE_KIND_COORDS;
                    // msg.coords.x = event.xconfigure.x;
                    // msg.coords.y = event.xconfigure.y;
                } break;
            }
        }
    }

    return msg;
}

// Usage example (applies to both, but platform-specific):
/*
int main() {
    Arena arena = {0}; // Init your arena
    String8 title = { (u8*)"My Window", 9 };
    Window win = windows_create(&arena, title, 800, 600);
    if (!win) {
        // Error
        return 1;
    }

    bool running = true;
    while (running) {
        Window_Message msg = windows_poll_message(win);
        switch (msg.kind) {
            case WINDOW_MESSAGE_KIND_CLOSE: running = false; break;
            case WINDOW_MESSAGE_KIND_COORDS: // Handle coords
                break;
            case WINDOW_MESSAGE_KIND_SIZE: // Handle size
                break;
            default: break;
        }
        // Your app logic...
    }

    windows_destroy(win);
    return 0;
}
*/
