//
//  WorkspaceWindowController.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/2/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKWorkspaceWindowController.h"
#import "XKIssueManager.h"

@interface XKWorkspaceWindowController ()
@property (readwrite) IDEWorkspaceWindowController *IDEWorkspaceWindowController;
@property (nonnull, nonatomic, readwrite) XKIssueManager *issueManger;

@end

@implementation XKWorkspaceWindowController

- (instancetype)initWithNSWindowController:(NSWindowController *)windowController {
    if (![windowController isKindOfClass:NSClassFromString(@"IDEWorkspaceWindowController")]) return nil;
    self = [super init];
    if (self) {
        _IDEWorkspaceWindowController = (IDEWorkspaceWindowController *)windowController;
    }
    
    return self;
}


- (nonnull IDEWorkspace *)IDEWorkspace {
    Class controllerClass = NSClassFromString(@"IDEWorkspaceWindowController");
    Ivar ivar = class_getInstanceVariable(controllerClass, "_workspace");
    IDEWorkspace *workspace = object_getIvar(self.IDEWorkspaceWindowController, ivar);
    
    return workspace;
}


- (nonnull XKIssueManager *)issueManger {
    if (_issueManger) return _issueManger;
    _issueManger = [[XKIssueManager alloc] initWithIDEIssueManager:self.IDEWorkspace.issueManager];
    
    return _issueManger;
}

@end
