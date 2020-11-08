#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

char *key_name[] = {
    "first",
    "second (or middle)",
    "third",
    "fourth",  // :D
    "fifth"    // :|
};

int main(int argc, char **argv)
{
    Display *display;
    XEvent xevent;
    Window window;

    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;
    
    int screen = DefaultScreen(display);
    
    XVisualInfo vinfo;

    XMatchVisualInfo(display, screen, 32, TrueColor, &vinfo);

    XSetWindowAttributes attr;
    attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
    attr.border_pixel = 0;
    attr.background_pixel = 0x0a000000;

    //window = DefaultRootWindow(display);
    window = XCreateWindow(display, RootWindow(display, screen), 100, 100, 400, 400, 4, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);
    //window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100, 400, 400, 4, 4, 4);
    //window = XCreateSimpleWindow(display, parent, x, y, width, height, border_width, border, background);
    XAllowEvents(display, ReplayPointer, CurrentTime);
    
    XGrabPointer(display, 
                 window,
                 1, 
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask , 
                 GrabModeAsync,
                 GrabModeAsync, 
                 None,
                 None,
                 CurrentTime);

    /* select kind of events we are interested in */
    XSelectInput(display, window, ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
    
    /* display the window */
    XMapWindow(display, window); 
    
    while (1) {
        XNextEvent(display, &xevent);

        switch (xevent.type) {
            case MotionNotify:
                printf("Mouse move      : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
                break;
            case ButtonPress:
                printf("Button pressed  : %s\n", key_name[xevent.xbutton.button - 1]);
                break;
            case ButtonRelease:
                printf("Button released : %s\n", key_name[xevent.xbutton.button - 1]);
                //if (xevent.xbutton.button == 1) {
                //    system("xdotool key ctrl && xdotool click 1");
                //}
                system("xdotool key ctrl");
                break;
        }
    }
}
