//
//  XcodeFormatter.m
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import "XcodeFormatter.h"
#import "XcodePrivate.h"

NSString *const WorkspaceWindowController = @"IDEWorkspaceWindowController";
NSString *const SourceCodeEditor = @"IDESourceCodeEditor";
NSString *const SourceCodeComparisonEditor = @"IDESourceCodeComparisonEditor";
NSString *const SourceCodeDocument = @"IDESourceCodeDocument";
NSString *const StructureNavigator = @"IDEStructureNavigator";
NSString *const GroupNavigableItem = @"IDEGroupNavigableItem";
NSString *const FileNavigableItem = @"IDEFileNavigableItem";

@implementation XcodeFormatter


#pragma mark - Public Methods

- (NSArray *)selectedFilePathsAtProjectNavigator {
    NSArray *fileNavigableItems = [self selectedSourceCodeFileNavigableItems];
    NSMutableArray *paths = [NSMutableArray array];
    
    for (IDEFileNavigableItem *fileNavigableItem in fileNavigableItems) {
        NSString *path = [fileNavigableItem.fileURL path];
        if (path) {
            [paths addObject:path];
        }
    }
    
    return paths.count ? paths : nil;
}


- (NSArray *)selectedRangesAtCurrentFile {
    NSTextView *textView = [self currentSourceCodeTextView];
    if (!textView) return nil;
    
    return textView.selectedRanges;
}


- (void)replaceCurrentFileContentAtRange:(NSRange *)range withString:(NSString *)string {
    IDESourceCodeDocument *document = [self currentSourceCodeDocument];
    if (!document || !range) return;
    
    [document.textStorage replaceCharactersInRange:*range  withString:string withUndoManager:document.undoManager];
}


- (id)currentEditor {
    NSWindowController *currentWindowController = [[NSApp keyWindow] windowController];
    if (![currentWindowController isKindOfClass:NSClassFromString(WorkspaceWindowController)]) return nil;
    
    IDEWorkspaceWindowController *workspaceController = (IDEWorkspaceWindowController *)currentWindowController;
    IDEWorkspace *workspace = IDEWorkspaceFromWorkspaceWindowController(workspaceController);

    IDEIssueManager *issueManager = workspace.issueManager;
//    
//    NSArray *issues = [issueManager issuesWithNoDocument];
//    NSSet *issueSet = [NSSet setWithArray:issues];
//    [issueManager _removeIssues:issueSet forProviderContext:issueManager session:nil];
    
    
    NSSet *issues = [self generateIssuesForManager:issueManager];
    IDEIssueProviderSession *session = [[IDEIssueProviderSession alloc] init];
    [issueManager _addIssues:issues forProviderContext:issueManager container:nil blueprint:nil session:session tryToCoalesce:NO];
    
    
    IDEEditorArea *editorArea = [workspaceController editorArea];
    IDEEditorContext *editorContext = [editorArea lastActiveEditorContext];
    
    return [editorContext editor];
}


- (NSSet *)generateIssuesForManager:(IDEIssueManager *)issueManager {
    IDEBuildIssueProvider *provider = [self buildIssueProviderForIssueManager:issueManager];
//    IDEActivityLogMessage *message = [[IDEActivityLogMessage alloc] initWithType:nil severity:2 title:@"Evrica"];
    IDEActivityLogMessage *message = [[IDEActivityLogMessage alloc] initWithType:nil severity:1 title:@"This warning is for Simion" filePath:@"/Users/thelvis/Developer/taylor/Taylor/Configurator.swift" lineNumber:2];
    
    IDEIssue *issue = [[IDEIssue alloc] initWithIssueProvider:provider message:message wasFetchedFromCache:NO];

    return [NSSet setWithObjects:issue, nil];
}


- (IDEBuildIssueProvider *)buildIssueProviderForIssueManager:(IDEIssueManager *)issueManager {
    for (id provider in IDEIssueProvidersFromIssueManager(issueManager)) {
        if ([provider isKindOfClass:[IDEBuildIssueProvider class]]) {
            return provider;
        }
    }
    
    return nil;
}

- (NSString *)currentFilePath {
    IDESourceCodeDocument *document = [self currentSourceCodeDocument];
    if (!document) return nil;
    
    return document.fileURL.path;
}

- (IDEWorkspaceWindowController *)getController {
    return nil;
}

- (IDESourceCodeDocument *)currentSourceCodeDocument {
    id currentEditor = [self currentEditor];
    if ([currentEditor isKindOfClass:NSClassFromString(SourceCodeEditor)]) {
        IDESourceCodeEditor *editor = currentEditor;
        return editor.sourceCodeDocument;
    }
    
    if ([currentEditor isKindOfClass:NSClassFromString(SourceCodeComparisonEditor)]) {
        IDESourceCodeComparisonEditor *editor = currentEditor;
        if ([[editor primaryDocument] isKindOfClass:NSClassFromString(SourceCodeDocument)]) {
            IDESourceCodeDocument *document = (IDESourceCodeDocument *)editor.primaryDocument;
            return document;
        }
    }
    
    return nil;
}


- (NSTextView *)currentSourceCodeTextView {
    if ([[self currentEditor] isKindOfClass:NSClassFromString(SourceCodeEditor)]) {
        IDESourceCodeEditor *editor = [self currentEditor];
        return editor.textView;
    }
    if ([[self currentEditor] isKindOfClass:NSClassFromString(SourceCodeComparisonEditor)]) {
        IDESourceCodeComparisonEditor *editor = [self currentEditor];
        return editor.keyTextView;
    }
    
    return nil;
}


#pragma mark - Helpers

- (NSArray *)selectedSourceCodeFileNavigableItems {
    id windowController = [[NSApp keyWindow] windowController];
    if (![windowController isKindOfClass:NSClassFromString(WorkspaceWindowController)]) return nil;
    
    id currentNavigator = [self currentNavigatorFromWorkspaceWindowController:windowController];
    if (![currentNavigator isKindOfClass:NSClassFromString(StructureNavigator)]) return nil;
    
    return [self sourceCodeFileNavigableItems:currentNavigator];
}


- (NSArray *)sourceCodeFileNavigableItems:(IDEStructureNavigator *)structureNavigator {
    NSMutableArray *mutableArray = [NSMutableArray array];
    for (id selectedObject in structureNavigator.selectedObjects) {
        NSArray *arrayOfFiles = [self recursivlyCollectFileNavigableItemsFrom:selectedObject];
        [mutableArray addObjectsFromArray:arrayOfFiles];
    }
    
    return mutableArray;
}


- (id)currentNavigatorFromWorkspaceWindowController:(IDEWorkspaceWindowController *)workspaceController {
    IDEWorkspaceTabController *workspaceTabController = workspaceController.activeWorkspaceTabController;
    IDENavigatorArea *navigatorArea = workspaceTabController.navigatorArea;
    
    return [navigatorArea currentNavigator];
}


- (NSArray *)recursivlyCollectFileNavigableItemsFrom:(IDENavigableItem *)selectedObject {
    if ([selectedObject isKindOfClass:NSClassFromString(GroupNavigableItem)]) {
        return [self fileNavigableItemsFromGroupNavigableItem:(IDEGroupNavigableItem *)selectedObject];
    } else if ([selectedObject isKindOfClass:NSClassFromString(FileNavigableItem)]) {
        return [self fileNavigableItemsFromFileNavigableItem:(IDEFileNavigableItem *)selectedObject];
    }
    
    return nil;
}


- (NSArray *)fileNavigableItemsFromGroupNavigableItem:(IDEGroupNavigableItem *)groupNavigableItem {
    NSMutableArray *mItems = [NSMutableArray array];
    
    for (IDENavigableItem *child in groupNavigableItem.childItems) {
        NSArray *childItems = [self recursivlyCollectFileNavigableItemsFrom:child];
        if (childItems.count > 0) {
            [mItems addObjectsFromArray:childItems];
        }
    }
    
    return mItems;
}


- (NSArray *)fileNavigableItemsFromFileNavigableItem:(IDEFileNavigableItem *)navigableItem {
    NSString *identifier = navigableItem.documentType.identifier;
    
    return [[NSWorkspace sharedWorkspace] type:identifier conformsToType:(NSString *)kUTTypeSourceCode] ? @[navigableItem] : nil;
}

@end
