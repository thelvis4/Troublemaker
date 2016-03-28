//
//  XKActivityController.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/11/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XKActivityController.h"
#import "XKWindowsController.h"
#import "XKWorkspaceWindowController.h"
#import "XKRuntimeUtils.h"
#import "XKActivityReport.h"

@interface XKActivityController ()
@property (nonnull, nonatomic, strong) XKWorkspaceWindowController *workspaceWindowController;

@property (nonnull, nonatomic, strong, readwrite) IDEActivityView *IDEActivityView;
@property (nullable, nonatomic, strong, readwrite) IDEActivityReporter *sourceCodeScanningActivityReporter;

@end

@implementation XKActivityController

- (nullable instancetype)init {
    self = [super init];
    if (self) {
        XKWindowsController *windowsController = [[XKWindowsController alloc] init];
        _workspaceWindowController = [windowsController initializeWorkspaceWindowController];
        if (!_workspaceWindowController) return nil;
    }
    
    return self;
}


- (IDEActivityView *)IDEActivityView {
    if (_IDEActivityView) return _IDEActivityView;
    
    id toolbarDelegate = getPropertyWithNameFromObject("_toolbarDelegate", self.workspaceWindowController.IDEWorkspaceWindowController);
    if (!toolbarDelegate) {
        NSLog(@"XKActivityController: Cannot reach to activity view. '_toolbarDelegate' not found.");
        return nil;
    }
    
    NSArray *toolbarControllers = getPropertyWithNameFromObject("_allToolbarControllers", toolbarDelegate);
    if (!toolbarControllers) {
        NSLog(@"XKActivityController: Cannot reach to activity view. '_allToolbarControllers' not found.");
        return nil;
    }
    
    id activityToolbarController = [self IDEActivityViewToolbarViewControllerFromControllers:toolbarControllers];
    if (!activityToolbarController) {
        NSLog(@"XKActivityController: Cannot reach to activity view. '_IDEActivityViewToolbarViewController' not found.");
        return nil;
    }
    
    _IDEActivityView = getPropertyWithNameFromObject("_activityView", activityToolbarController);
    
    return _IDEActivityView;
}


- (nullable NSArray<IDEActivityReporter *> *)activityReporters {
    return getPropertyWithNameFromObject("_activityReporters", [self activityReportManager]);
}


- (nullable IDEActivityReporter *)sourceCodeScanningActivityReporter {
    if (_sourceCodeScanningActivityReporter) return _sourceCodeScanningActivityReporter;
    
    Class codeScanningReporterClass = NSClassFromString(@"IBSourceCodeScanningActivityReporter");
    for (IDEActivityReporter *reporter in [self activityReporters]) {
        if ([reporter isKindOfClass:codeScanningReporterClass]) {
            _sourceCodeScanningActivityReporter = reporter;
            return _sourceCodeScanningActivityReporter;
        }
    }
    
    return nil;
}


- (void)addReport:(nonnull XKActivityReport *)report {
    IDEActivityReporter *reporter = self.sourceCodeScanningActivityReporter;
    if (!reporter) return;
    
    [reporter.mutableActivityReports addObject:report.IDEActivityReport];
    [[self activityReportManager] startObservingReportForCompletion:report.IDEActivityReport];
}


- (void)removeReport:(nonnull XKActivityReport *)report {
    IDEActivityReporter *reporter = self.sourceCodeScanningActivityReporter;
    if (!reporter) return;
    
    report.completed = YES;
    [[self activityReportManager] reportDidComplete:report.IDEActivityReport];
    [reporter.mutableActivityReports removeObject:report.IDEActivityReport];
    
}


- (nullable IDEActivityViewDataSource *)activityViewDataSource {
    IDEActivityView *activityView = self.IDEActivityView;
    if (!activityView) return nil;
    
    return getPropertyWithNameFromObject("_dataSource", activityView);
}


- (nullable IDEActivityReportManager *)activityReportManager {
    IDEActivityViewDataSource *dataSource = [self activityViewDataSource];
    if (!dataSource) return nil;
    
    return [dataSource activityReportManager];
}


- (nullable id)IDEActivityViewToolbarViewControllerFromControllers:(NSArray *)controllers {
    Class class = NSClassFromString(@"_IDEActivityViewToolbarViewController");
    for (id controller in controllers) {
        if ([controller isKindOfClass:class]) {
            return controller;
        }
    }
    
    return nil;
}

@end
