//
//  XKActivityReport.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/15/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IDEActivityReporter;
@class IDEActivityReport;
@class XKReportSegment;

extern CGFloat const XKActivityReportProgressCompleted;

@interface XKActivityReport : NSObject
@property (nonnull, nonatomic, strong, readonly) IDEActivityReport *IDEActivityReport;

@property (nonnull, nonatomic, copy) NSString *title;
@property (null_resettable, nonatomic, copy) NSArray<XKReportSegment *> *titleSegments;
@property (nonatomic, assign) CGFloat progress;
@property (nonatomic, assign) BOOL completed;

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title;
- (nonnull instancetype)initWithTitleSegments:(nonnull NSArray<XKReportSegment *> *)segments;

@end
