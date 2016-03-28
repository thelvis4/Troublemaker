//
//  WorkspaceWindowController.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/2/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XcodePrivate.h"

@class XKIssueManager;

@interface XKWorkspaceWindowController : NSObject

@property (nonnull, readonly) IDEWorkspaceWindowController *IDEWorkspaceWindowController;
@property (nonnull, readonly) IDEWorkspace *IDEWorkspace;

@property (nonnull, nonatomic, readonly) XKIssueManager *issueManger;

- (nullable instancetype)initWithNSWindowController:(nonnull NSWindowController *)windowController;

@end
