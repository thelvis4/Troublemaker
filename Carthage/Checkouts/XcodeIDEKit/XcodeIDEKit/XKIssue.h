//
//  XKIssue.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XcodePrivate.h"


typedef NS_ENUM(NSInteger, XKIssueSeverity) {
    XKIssueSeverityIssue = 1, // default
    XKIssueSeverityError = 2
};

static const NSUInteger XKUndefinedLine = NSUIntegerMax;


@interface XKIssue : NSObject

@property (nonnull, readonly) NSString *title;
@property (nullable ,readonly) NSString *filePath;
@property (readonly) NSUInteger lineNumber;
@property (readonly) XKIssueSeverity severity;

@property (nullable) IDEIssue *IDEIssue;

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath lineNumber:(NSUInteger)line severity:(XKIssueSeverity)severity;
- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath lineNumber:(NSUInteger)line;
- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath severity:(XKIssueSeverity)severity;
- (nonnull instancetype)initWithTitle:(nonnull NSString *)title filePath:(nonnull NSString *)filePath;

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title;
- (nonnull instancetype)initWithTitle:(nonnull NSString *)title severity:(XKIssueSeverity)severity;

- (nonnull instancetype)initWithIDEIssue:(nonnull IDEIssue *)IDEIssue;

- (nonnull IDEIssue *)IDEIssueForIssueProvider:(nonnull IDEIssueProvider *)provider;

@end
