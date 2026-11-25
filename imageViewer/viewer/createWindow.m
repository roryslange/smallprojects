#import <Cocoa/Cocoa.h>

int main(void) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        
        NSRect frame = NSMakeRect(0, 0, 800, 600);
        
        NSWindow *window = [[NSWindow alloc]
            initWithContentRect:frame
            styleMask:
                NSWindowStyleMaskTitled |
                NSWindowStyleMaskClosable |
                NSWindowStyleMaskMiniaturizable |
                NSWindowStyleMaskResizable
            backing:NSBackingStoreBuffered
            defer:NO];

        [window setTitle:@"My C Application"];

        [window center];
        [window makeKeyAndOrderFront:nil];

        [window setTitle:@"My C Application"];

        [window center];
        [window makeKeyAndOrderFront:nil];

        [app activateIgnoringOtherApps:YES];
        [app run];
    }

    return 0;
}
