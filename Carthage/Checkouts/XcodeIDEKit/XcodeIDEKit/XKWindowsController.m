//
//  XKWindowsController.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/8/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKWindowsController.h"
#import "XKWorkspaceWindowController.h"
#import "XKIDEClassNames.h"

@implementation XKWindowsController

- (nullable XKWorkspaceWindowController *)initializeWorkspaceWindowController {
    NSWindowController *workspaceWindowController = [self stealWorkspaceWindowController];
    if (!workspaceWindowController) {
        NSLog(@"XcodeIDEKit: There is no workspace window open in Xcode, and that's why XKWorkspaceWindowController cannot be initialized.");
        return nil;
    }
    
    return [[XKWorkspaceWindowController alloc] initWithNSWindowController:workspaceWindowController];
}


#pragma mark - Private methods

- (nullable NSWindowController *)stealWorkspaceWindowController {
    // Try key window
    NSWindow *keyWindow = [self workspaceWindowForWindow:NSApp.keyWindow];
    if (keyWindow) return keyWindow.windowController;
   
    // Try main window
    NSWindow *mainWindow = [self workspaceWindowForWindow:NSApp.mainWindow];
    if (mainWindow) return mainWindow.windowController;
    
    // Look up through all the windows
    for (NSWindow *window in NSApp.windows) {
        if ([self workspaceWindowForWindow:window]) {
            return window.windowController;
        }
    }
    
    return nil;
}


- (nullable NSWindow *)workspaceWindowForWindow:(NSWindow *)window {
    BOOL isWorkspaceWindow = [window isKindOfClass:NSClassFromString(IDEWorkspaceWindowClassName)];
    
    return isWorkspaceWindow ? window : nil;
}

@end
