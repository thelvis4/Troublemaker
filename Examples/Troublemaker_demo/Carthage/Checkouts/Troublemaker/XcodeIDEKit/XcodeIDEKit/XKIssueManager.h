//
//  IssueManager.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XcodePrivate.h"
#import "XKIssue.h"

@interface XKIssueManager : NSObject
@property (nonnull, readonly) IDEIssueManager *IDEIssueManager;
@property (nullable, readonly) IDEIssueProvider *IDEBuildIssueProvider;

@property (nonnull, readonly) NSArray<XKIssue *> *issues;

- (nonnull instancetype)initWithIDEIssueManager:(nonnull IDEIssueManager *)IDEIssueManager;

- (void)addIssue:(nonnull XKIssue *)issue;
- (void)removeIssue:(nonnull XKIssue *)issue;

- (void)clearAllIssues;
- (void)clearGeneratedIssues;

@end
