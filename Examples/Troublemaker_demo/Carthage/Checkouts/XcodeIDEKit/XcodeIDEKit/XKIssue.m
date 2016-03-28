//
//  XKIssue.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKIssue.h"

@implementation XKIssue

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath lineNumber:(NSUInteger)line severity:(XKIssueSeverity)severity {
    self = [super init];
    
    if (self) {
        _title = title;
        _filePath = filePath;
        _lineNumber = line;
        _severity = severity;
    }
    
    return self;
}

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath lineNumber:(NSUInteger)line {
    return [self initWithTitle:title filePath:filePath lineNumber:line severity:XKIssueSeverityIssue];
}


- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath severity:(XKIssueSeverity)severity {
    return [self initWithTitle:title filePath:filePath lineNumber:XKUndefinedLine severity:severity];
}

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath {
    return [self initWithTitle:title filePath:filePath severity:XKIssueSeverityIssue];
}


- (nonnull instancetype)initWithTitle:(nonnull NSString *)title {
    return [self initWithTitle:title severity:XKIssueSeverityIssue];
}


- (nonnull instancetype)initWithTitle:(nonnull NSString *)title severity:(XKIssueSeverity)severity {
    self = [super init];
    
    if (self) {
        _title = title;
        _filePath = nil;
        _lineNumber = XKUndefinedLine;
        _severity = severity;
    }
    
    return self;
}


- (nonnull instancetype)initWithIDEIssue:(nonnull IDEIssue *)IDEIssue {
    NSString *title = IDEIssue.originatingMessage.title;
    XKIssueSeverity severity = (XKIssueSeverity)IDEIssue.issueType;
    
    _IDEIssue = IDEIssue;
    
    NSString *filePath = [self filePathForIDEIssue:IDEIssue];

    if (filePath) {
        NSInteger lineNumber = IDEIssue._lineNumber ? IDEIssue._lineNumber.unsignedIntegerValue : XKUndefinedLine;
        return [self initWithTitle:title
                          filePath:filePath
                        lineNumber:lineNumber
                          severity:severity];
    }
    
    return [self initWithTitle:title severity:severity];
}


- (NSString *)filePathForIDEIssue:(IDEIssue *)issue {
    if (issue.documentLocations.count <= 0) return nil;
    
    DVTTextDocumentLocation *location = issue.documentLocations[0];
    return [self documentURLFromTextDocumentLocation:location].path;
}


- (NSURL *)documentURLFromTextDocumentLocation:(DVTTextDocumentLocation *)location {
    Ivar ivar = class_getInstanceVariable([location class], "_documentURL");
    
    return object_getIvar(location, ivar);
}


- (NSUInteger)severityForIssueSeverity:(XKIssueSeverity)severity {
    switch (severity) {
        case XKIssueSeverityIssue:
            return 1;
        case  XKIssueSeverityError:
            return 2;
        default:
            return 1;
    }
}


- (IDEIssue *)IDEIssueForIssueProvider:(nonnull IDEIssueProvider *)provider {
    IDEActivityLogMessage *message = [self activityLogMessage];
    
    return [[IDEIssue alloc] initWithIssueProvider:provider message:message wasFetchedFromCache:NO];
}


- (IDEActivityLogMessage *)activityLogMessage {
    IDETypeIdentifier *identifier = [self warningTypeIdentifier];
    if (self.lineNumber == XKUndefinedLine) {
        return [[IDEActivityLogMessage alloc] initWithType:identifier
                                                  severity:[self severityForIssueSeverity:self.severity]
                                                     title:self.title
                                                  filePath:self.filePath];
    }
    
    return [[IDEActivityLogMessage alloc] initWithType:identifier
                                              severity:[self severityForIssueSeverity:self.severity]
                                                 title:self.title
                                              filePath:self.filePath
                                            lineNumber:self.lineNumber];
}

- (IDETypeIdentifier *)warningTypeIdentifier {
    static IDETypeIdentifier *identifier = nil;
    if (!identifier) {
        identifier = [IDETypeIdentifier registerTypeIdentifierWithStringRepresentation:@"com.XcodeIDEKit.warning" basedOn:nil];
    }
    
    return identifier;
}


@end
