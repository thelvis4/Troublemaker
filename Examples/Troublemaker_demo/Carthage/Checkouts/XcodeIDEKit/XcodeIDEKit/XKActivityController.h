//
//  XKActivityController.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/11/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XcodePrivate.h"
#import "XKReportSegment.h"
#import "XKActivityReport.h"

@interface XKActivityController : NSObject
@property (nonnull, nonatomic, strong, readonly) IDEActivityView *IDEActivityView;
@property (nullable, nonatomic, strong, readonly) IDEActivityReporter *sourceCodeScanningActivityReporter;

- (nullable instancetype)init;
- (nullable NSArray<IDEActivityReporter *> *)activityReporters;

- (void)addReport:(nonnull XKActivityReport *)report;
- (void)removeReport:(nonnull XKActivityReport *)report;

@end
