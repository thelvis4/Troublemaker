//
//  XKActivityReport.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/15/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKActivityReport.h"
#import "XcodePrivate.h"
#import "XKReportSegment.h"
#import "XKActivityController.h"

NS_OPTIONS(NSInteger, XKActivityReportOptions) {
    XKActivityReportOptionCancelable = 1 << 0,
    XKActivityReportOptionUserRequested = 1 << 1,
    XKActivityReportHidesProgress = 1 << 2,
    XKActivityReportSchemeBased = 1 << 3,
    XKActivityReportShouldDisplayImmediately = 1 << 4,
    XKActivityReportDisableTitleAnimation = 1 << 5,
    XKActivityReportPersistent = 1 << 6,
    XKActivityReportFileIOIntensive = 1 << 7,
    XKActivityReportInvisible = 1 << 8,
};

@interface NSArray (ReportSegmentsConverting)
@end

@implementation NSArray (ReportSegmentsConverting)

- (NSArray<IDEActivityReportStringSegment *> *)IDEActivityReportStringSegments {
    NSMutableArray *IDESegments = [NSMutableArray array];
    for (XKReportSegment *segment in self) {
        [IDESegments addObject:segment.IDEActivityReportStringSegment];
    }
    
    return [IDESegments copy];
}

@end


CGFloat const XKActivityReportProgressCompleted = 1.0f;

@interface XKActivityReport ()
@property (nonnull, nonatomic, strong, readwrite) IDEActivityReport *IDEActivityReport;

@end

@implementation XKActivityReport

- (nonnull instancetype)initWithTitle:(nonnull NSString *)title {
    self = [super init];
    if (self) {
        XKActivityController *activityController = [[XKActivityController alloc] init];
        if (!activityController) return nil;
        int options = (XKActivityReportOptionUserRequested | XKActivityReportShouldDisplayImmediately | XKActivityReportSchemeBased);
        _IDEActivityReport = [activityController.sourceCodeScanningActivityReporter newActivityReportWithTitle:title options:options];
    }
    
    return self;
}


- (nonnull instancetype)initWithTitleSegments:(nonnull NSArray<XKReportSegment *> *)segments {
    self = [self initWithTitle:@"XcodeIDEKit"];
    self.titleSegments = segments;
    
    return self;
}


#pragma mark - Custom Accessors

- (void)setTitleSegments:(NSArray<XKReportSegment *> *)titleSegments {
    _titleSegments = titleSegments;
    self.IDEActivityReport.titleSegments = [titleSegments IDEActivityReportStringSegments];
}


- (void)setProgress:(CGFloat)progress {
    self.IDEActivityReport.progress = floor(progress * 100);
}


- (void)setCompleted:(BOOL)completed {
    _completed = completed;
    
    self.IDEActivityReport.progress = XKActivityReportProgressCompleted;
    self.IDEActivityReport.completionSummaryStringSegments = self.IDEActivityReport.titleSegments;
}


- (CGFloat)progress {
    return self.IDEActivityReport.progress / 100.0;
}


- (void)setTitle:(NSString *)title {
    self.IDEActivityReport.title = title;
}


- (NSString *)title {
    return self.IDEActivityReport.title;
}

@end
