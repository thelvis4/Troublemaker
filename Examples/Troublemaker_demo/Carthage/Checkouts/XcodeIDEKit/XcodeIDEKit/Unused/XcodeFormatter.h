//
//  XcodeFormatter.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XcodePrivate.h"

@class IDESourceCodeDocument;

@interface XcodeFormatter : NSObject
- (IDEWorkspaceWindowController *)getController;
- (IDESourceCodeDocument *)currentSourceCodeDocument;
- (NSString *)currentFilePath;
- (NSArray *)selectedFilePathsAtProjectNavigator;
- (NSArray *)selectedRangesAtCurrentFile;
- (void)replaceCurrentFileContentAtRange:(NSRange *)range withString:(NSString *)text;

@end
