//
//  IssueManager.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKIssueManager.h"

@interface XKIssueManager ()
@property (nonnull, readwrite) IDEIssueManager *IDEIssueManager;

@end

@implementation XKIssueManager

- (nonnull instancetype)initWithIDEIssueManager:(nonnull IDEIssueManager *)IDEIssueManager {
    self = [super init];
    if (self) {
        _IDEIssueManager = IDEIssueManager;
    }
    
    return self;
}


- (NSMutableArray<IDEIssueProvider *> *)IDEIssueProviders {
    Class managerClass = NSClassFromString(@"IDEIssueManager");
    Ivar ivar = class_getInstanceVariable(managerClass, "_issueProviders");
    
    return object_getIvar(self.IDEIssueManager, ivar);
}


- (IDEIssueProvider *)IDEBuildIssueProvider {
    for (id provider in [self IDEIssueProviders]) {
        if ([provider isKindOfClass:[IDEBuildIssueProvider class]]) {
            return provider;
        }
    }
    
    return nil;
}


- (NSArray<IDEIssue *> *)IDEIssues {
    NSMutableArray *issues = [NSMutableArray array];
    
    for (NSString *documentURL in self.IDEIssueManager.documentURLsWithIssues) {
        [issues addObjectsFromArray:[self.IDEIssueManager issuesForDocumentURL:documentURL]];
    }
    
    [issues addObjectsFromArray:self.IDEIssueManager.issuesWithNoDocument];
    
    return [NSArray arrayWithArray:issues];
}


- (NSArray<XKIssue *> *)issues {
    NSMutableArray *issues = [NSMutableArray array];
    NSArray *IDEIssues = self.IDEIssues;
    for (IDEIssue *IDEIssue in IDEIssues) {
        [issues addObject:[[XKIssue alloc] initWithIDEIssue:IDEIssue]];
    }
    
    return [NSArray arrayWithArray:issues];
}


- (void)addIssue:(XKIssue *)issue {
    IDEIssueProvider *provider = self.IDEBuildIssueProvider;
    if (provider == nil) return;
    
    IDEIssue *IDEIssue = [issue IDEIssueForIssueProvider:provider];
    issue.IDEIssue = IDEIssue;
    
    NSSet *issues = [NSSet setWithObject:IDEIssue];
    
    IDEIssueProviderSession *session = [[IDEIssueProviderSession alloc] init];
    [self.IDEIssueManager _addIssues:issues forProviderContext:self.IDEIssueManager
                           container:nil
                           blueprint:nil
                             session:session
                       tryToCoalesce:NO];
}


- (void)removeIssue:(XKIssue *)issue {
    IDEIssue *IDEIssue = [self IDEIssueForXKIssue:issue];
    if (!IDEIssue) return;
    
    NSSet *issues = [NSSet setWithObject:IDEIssue];
    [self.IDEIssueManager _removeIssues:issues forProviderContext:self.IDEIssueManager session:nil];
}


- (void)clearAllIssues {
    NSSet *issuesSet = [NSSet setWithArray:[self IDEIssues]];
    [self removeIssues:issuesSet];
}


// TODO: Find a better way to identify generated issues
- (void)clearGeneratedIssues {
    NSMutableSet *generatedIssues = [NSMutableSet set];
    for (IDEIssue *issue in [self IDEIssues]) {
        if ([[issue issueTypeIdentifier] isEqualToString:@"Uncategorized"]) {
            [generatedIssues addObject:issue];
        }
    }
    [self removeIssues:generatedIssues];
}


- (void)removeIssues:(NSSet<IDEIssue *> *)issues {
    [self.IDEIssueManager _removeIssues:issues forProviderContext:self.IDEIssueManager session:nil];
}


- (IDEIssue *)IDEIssueForXKIssue:(XKIssue *)XKIssue {
    if (XKIssue.IDEIssue == nil) return XKIssue.IDEIssue;
    
    for (IDEIssue *issue in self.issues) {
        if ([issue.fullMessage isEqualToString:XKIssue.title]) {
            return issue;
        }
    }
    
    return nil;
}

@end
