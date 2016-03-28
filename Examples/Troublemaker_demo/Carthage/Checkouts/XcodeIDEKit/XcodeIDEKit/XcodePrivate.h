//
//  XcodePrivate.h
//  XcodeIDEKit
//
//  Created by Andrei Raifura on 12/3/15.
//  Copyright © 2015 Andrei Raifura. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>

@interface DVTTextDocumentLocation : NSObject
@property (readonly) NSRange characterRange;
@property (readonly) NSRange lineRange;
@end

@interface DVTTextPreferences : NSObject
+ (id)preferences;
@property BOOL trimWhitespaceOnlyLines;
@property BOOL trimTrailingWhitespace;
@property BOOL useSyntaxAwareIndenting;
@end

@interface DVTSourceTextStorage : NSTextStorage
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)string withUndoManager:(id)undoManager;
- (NSRange)lineRangeForCharacterRange:(NSRange)range;
- (NSRange)characterRangeForLineRange:(NSRange)range;
- (void)indentCharacterRange:(NSRange)range undoManager:(id)undoManager;
@end

@interface DVTFileDataType : NSObject
@property (readonly) NSString *identifier;
@end

@interface DVTFilePath : NSObject
@property (readonly) NSURL *fileURL;
@property (readonly) DVTFileDataType *fileDataTypePresumed;
@end

@interface IDEContainerItem : NSObject
@property (readonly) DVTFilePath *resolvedFilePath;
@end

@interface IDEGroup : IDEContainerItem

@end

@interface IDEFileReference : IDEContainerItem

@end

@interface IDENavigableItem : NSObject
@property (readonly) IDENavigableItem *parentItem;
@property (readonly) NSArray *childItems;
@property (readonly) id representedObject;
@end

@interface IDEFileNavigableItem : IDENavigableItem
@property (readonly) DVTFileDataType *documentType;
@property (readonly) NSURL *fileURL;
@end

@interface IDEGroupNavigableItem : IDENavigableItem
@property (readonly) IDEGroup *group;
@end

@interface IDEStructureNavigator : NSObject
@property (retain) NSArray *selectedObjects;
@end

@interface IDENavigableItemCoordinator : NSObject
- (id)structureNavigableItemForDocumentURL:(id)arg1 inWorkspace:(id)arg2 error:(id *)arg3;
@end

@interface IDENavigatorArea : NSObject
- (id)currentNavigator;
@end

@interface IDEWorkspaceTabController : NSObject
@property (readonly) IDENavigatorArea *navigatorArea;
@end

@interface IDEDocumentController : NSDocumentController
+ (id)editorDocumentForNavigableItem:(id)arg1;
+ (id)retainedEditorDocumentForNavigableItem:(id)arg1 error:(id *)arg2;
+ (void)releaseEditorDocument:(id)arg1;
@end

@interface IDESourceCodeDocument : NSDocument
- (DVTSourceTextStorage *)textStorage;
- (NSUndoManager *)undoManager;
@end

@interface IDESourceCodeComparisonEditor : NSObject
@property (readonly) NSTextView *keyTextView;
@property (retain) NSDocument *primaryDocument;
@end

@interface IDESourceCodeEditor : NSObject
@property (retain) NSTextView *textView;
- (IDESourceCodeDocument *)sourceCodeDocument;
@end

@interface IDEEditorContext : NSObject
- (id)editor; // returns the current editor. If the editor is the code editor, the class is `IDESourceCodeEditor`
@end

@interface IDEEditorArea : NSObject
- (IDEEditorContext *)lastActiveEditorContext;
@end

@interface IDEEntityIdentifier : NSObject <NSCopying>
{
    unsigned long long _hashValue;
    int _sharedState;
    int _entityType;
    NSString *_entityName;
    NSString *_containerName;
    NSString *_entityGUID;
}

+ (id)entityIdentifierFromEntityName:(id)arg1 entityType:(int)arg2 containerName:(id)arg3;
+ (id)entityIdentifierFromEntityName:(id)arg1 entityType:(int)arg2 containerName:(id)arg3 isShared:(BOOL)arg4;
+ (id)entityIdentifierFromGUID:(id)arg1 entityName:(id)arg2 entityType:(int)arg3 containerName:(id)arg4;
+ (id)entityIdentifierFromGUID:(id)arg1 entityName:(id)arg2 entityType:(int)arg3 containerName:(id)arg4 isShared:(BOOL)arg5;
@property(readonly, copy) NSString *entityGUID; // @synthesize entityGUID=_entityGUID;
@property(readonly) int entityType; // @synthesize entityType=_entityType;
@property(readonly, copy) NSString *containerName; // @synthesize containerName=_containerName;
@property(readonly, copy) NSString *entityName; // @synthesize entityName=_entityName;
@property(readonly) int sharedState; // @synthesize sharedState=_sharedState;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (BOOL)isSimilarToEntityIdentifier:(id)arg1;
- (unsigned long long)hash;
- (id)description;
- (BOOL)isEqual:(id)arg1;
- (id)initWithGUID:(id)arg1 entityName:(id)arg2 entityType:(int)arg3 containerName:(id)arg4 shared:(int)arg5;

@end

@class IDETypeIdentifier;

@interface IDEActivityLogRecord : NSObject
{
    IDEEntityIdentifier *_entityIdentifier;
}

+ (unsigned long long)assertionBehaviorAfterEndOfEventForSelector:(SEL)arg1;
+ (id)cacheLog:(id)arg1;
+ (void)uncacheLogRecord:(id)arg1;
+ (void)cacheLogRecord:(id)arg1;
+ (id)cachedLogRecordWithURL:(id)arg1;
@property(readonly) IDEEntityIdentifier *entityIdentifier; // @synthesize entityIdentifier=_entityIdentifier;
- (id)testableSummariesForFilePath:(id)arg1 runDestinationRecord:(id *)arg2 error:(id *)arg3;
- (id)coverageReport;
- (id)coverageReportFilePath;
- (id)testableSummariesPlistFilePath;
- (id)initWithEntityIdentifier:(id)arg1;
- (long long)compareUsingTimeStartedRecording:(id)arg1;
- (id)fullLogIfInMemory;
- (id)fullLogWithError:(id *)arg1;
@property(readonly) BOOL isRemoved;
@property(readonly) BOOL isRecording;
@property(readonly) NSString *highLevelStatus;
@property(readonly) NSString *signature;
@property(readonly) DVTFileDataType *documentType;
@property(readonly, nonatomic) double timeStoppedRecording;
@property(readonly) double timeStartedRecording;
@property(readonly) NSString *title;
@property(readonly) IDETypeIdentifier *domainType;
@property(readonly) NSString *uniqueIdentifier;
@property(readonly) NSURL *logURL;

@end


@interface IDEIssueLogRecordsGroup : NSObject
{
    NSMutableArray *_logRecords;
}

+ (void)initialize;
- (void)removeLogsForIssues:(id)arg1;
- (void)addLogsForIssues:(id)arg1;
- (id)init;

// Remaining properties
@property(copy) NSArray<IDEActivityLogRecord *> *logRecords; // @dynamic logRecords;
@property(readonly, copy) NSMutableArray *mutableLogRecords; // @dynamic mutableLogRecords;

@end


@class IDEWorkspace;

@interface IDEIssueManager : NSObject {
    NSMutableArray *_issueProviders;
}

+ (id)issueManagerLogAspect;
+ (id)_issueProviderInfo;
+ (void)_useDebugProviderExtensionPointWithIdentifier:(id)arg1;
+ (void)initialize;
@property(readonly) IDEIssueLogRecordsGroup *issueLogRecordsGroup; // @synthesize issueLogRecordsGroup=_issueLogRecordsGroup;
@property(readonly, getter=areLiveIssuesEnabled) BOOL liveIssuesEnabled; // @synthesize liveIssuesEnabled=_liveIssuesEnabled;
@property(readonly) IDEWorkspace *workspace; // @synthesize workspace=_workspace;
- (void)_containersOrBlueprintsUpdated;
- (id)_issuesForProviderContext:(id)arg1;
- (id)_providerContextToProvisionInfoMapForIssues:(id)arg1;
- (id)_unitTestIssueProvidersAccessor;
- (void)_validateGroupIdentifiers;
- (void)_delayedValidateGroupIdentifiers;
- (void)_updateVendedIssues;
- (void)_updateContainersAndBlueprintsForActiveScheme;
- (void)_findDependencyForBuildable:(id)arg1;
- (void)_updateIssueFilterStyle;
- (void)_needsUpdateInResponseToFilterChanges;
- (void)_coalescedUpdateInResponseToFilterChanges;
- (void)_hideIssues:(id)arg1;
- (void)_setIssues:(NSSet *)issues forProviderContext:(id)arg2 container:(id)arg3 blueprint:(id)arg4 session:(id)arg5;
- (void)_removeIssues:(NSSet *)issues forProviderContext:(id)arg2 session:(id)arg3;
- (void)_addIssues:(id)arg1 forProviderContext:(id)arg2 container:(id)arg3 blueprint:(id)arg4 session:(id)arg5 tryToCoalesce:(BOOL)arg6;
- (BOOL)_vendOnlyActiveSchemeIssues;
- (void)_retractIssues:(id)arg1;
- (void)_vendIssues:(id)arg1 container:(id)arg2 blueprint:(id)arg3 issueToGroupingObjectMap:(id)arg4 session:(id)arg5;
- (id)_similarExistingIssueForIssue:(id)arg1;
- (id)_similarExistingIssueForIssue:(id)arg1 container:(id)arg2 blueprint:(id)arg3;
- (_Bool)_doesIssue:(id)arg1 fromContainer:(id)arg2 andBlueprint:(id)arg3 coalesceWithIssue:(id)arg4;
- (_Bool)_doesIssue:(id)arg1 coalesceWithIssue:(id)arg2;
- (id)_identifierForGroupWithBlueprint:(id)arg1 container:(id)arg2;
- (id)_groupingObjectsForIssue:(id)arg1;
- (void)_rescindObserverToken:(id)arg1;
- (id)newIssueObserverForDocumentURL:(id)arg1 options:(unsigned long long)arg2 withHandlerBlock:(void (^)())arg3;
- (void)_notifyAllObserversOfDocumentURL:(id)arg1 isPrior:(BOOL)arg2;
- (void)_notifyObserver:(id)arg1 forURL:(id)arg2 isPrior:(BOOL)arg3;
- (NSArray *)issuesWithNoDocument;
- (id)issuesForDocumentURL:(id)arg1;
- (unsigned long long)maxSeverityOfDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfFixableDiagnosticItemsInDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfAnalyzerResultsInDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfNoticesInDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfWarningsInDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfErrorsInDocumentAtURL:(id)arg1;
- (unsigned long long)numberOfTestFailuresInDocumentAtURL:(id)arg1;
- (id)_documentIssueSummaryForURL:(id)arg1;
@property(readonly) NSArray *documentURLsWithIssues;
@property(readonly) NSArray *issueGroups; // @synthesize issueGroups=_issueGroups;
- (void)_updateIssueProviders;
- (void)primitiveInvalidate;
- (id)initWithWorkspace:(id)arg1;
- (id)init;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) NSSet *lastSchemeActionIssues; // @dynamic lastSchemeActionIssues;
@property(readonly) NSMutableSet *mutableLastSchemeActionIssues; // @dynamic mutableLastSchemeActionIssues;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end


@interface IDEWorkspace : NSObject
@property (readonly) DVTFilePath *representingFilePath;
@property(readonly) IDEIssueManager *issueManager;

@end

@interface IDEWorkspaceWindowController : NSObject
@property (readonly) IDEWorkspaceTabController *activeWorkspaceTabController;
- (IDEEditorArea *)editorArea;

@end

@interface IDEWorkspaceDocument : NSDocument
@property (readonly) IDEWorkspace *workspace;
@end



@interface IDEIssueProviderSession : NSObject
@property(readonly) double timestamp;
- (id)init;

@end

@interface IDEIssueProvider : NSObject {
    IDEIssueProviderSession *_session;
    IDEIssueProviderSession *_currentProviderSession;
}

+ (int)providerType;
+ (unsigned long long)assertionBehaviorAfterEndOfEventForSelector:(SEL)arg1;
+ (void)initialize;
@property(retain) IDEIssueProviderSession *currentProviderSession;
- (BOOL)allowsExistingIssuesToBeCoalesced;
- (BOOL)allowsNewIssuesToBeCoalesced;
@property(readonly) BOOL _filterIssuesByActiveScheme;
- (id)logDocumentLocationForIssue:(id)arg1;
- (id)activityLogRecordForIssue:(id)arg1;
- (void)endProviderSession;
- (void)startProviderSession;
- (id)displayNameForIssueTypeIdentifier:(id)arg1;
- (void)removeIssues:(id)arg1 forProviderContext:(id)arg2 providerSession:(id)arg3;
- (void)removeIssues:(id)arg1 forProviderContext:(id)arg2;
- (void)addIssues:(id)arg1 forProviderContext:(id)arg2 providerSession:(id)arg3 container:(id)arg4 blueprint:(id)arg5;
- (void)addIssues:(id)arg1 forProviderContext:(id)arg2 container:(id)arg3 blueprint:(id)arg4;
- (void)setIssues:(id)arg1 forProviderContext:(id)arg2 providerSession:(id)arg3 container:(id)arg4 blueprint:(id)arg5;
- (void)setIssues:(id)arg1 forProviderContext:(id)arg2 container:(id)arg3 blueprint:(id)arg4;
@property(readonly, copy) NSString *description;
- (void)primitiveInvalidate;
- (id)initWithIssueManager:(id)arg1 extension:(id)arg2;
- (id)init;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end



@interface IDELogStore : NSObject
{
    NSMutableArray *_logRecords;
}

+ (id)onDiskOrInMemoryLogStoreInWorkspaceArena:(id)arg1 prefix:(id)arg2;
+ (void)initialize;
- (id)coverageReportFilePathForActivityLogSection:(id)arg1;
- (id)testableSummariesPlistFilePathForActivityLogSection:(id)arg1;
- (id)logRecordWithURL:(id)arg1;
- (id)addLog:(id)arg1 entityIdentifier:(id)arg2 completionBlock:(void(^)())arg3;
- (id)init;
- (void)primitiveInvalidate;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) NSArray *logRecords; // @dynamic logRecords;
@property(readonly) NSMutableArray *mutableLogRecords; // @dynamic mutableLogRecords;
@property BOOL preserveOldLogs; // @dynamic preserveOldLogs;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end


@interface IDEBuildIssueProvider : IDEIssueProvider
{
    NSMapTable *_blueprintToLatestLogSectionObserverMap;
    NSMapTable *_buildLogToLogNotificationObserverMap;
    NSMapTable *_blueprintToLatestBuildLogSectionMap;
    NSMapTable *_blueprintToLogRecordsMap;
    NSMapTable *_blueprintToIssuesForFileMap;
    NSMapTable *_blueprintToAuxiliaryFilesForFileMap;
    NSMapTable *_haveRemovedIssuesForFileInBlueprintMap;
    NSMutableSet *_pendingLogSections;
    IDELogStore *_logStore;
}

+ (int)providerType;
+ (id)_backgroundScanningQueue;
+ (id)_backgroundLoadingQueue;
- (id)ideModelObjectTypeIdentifier;
- (id)displayNameForIssueTypeIdentifier:(id)arg1;
- (void)_buildLogDidUpdateItems:(id)arg1 blueprint:(id)arg2;
- (void)_scanIssuesInLog:(id)arg1 forBlueprint:(id)arg2 intoArray:(id)arg3 usingSeenMessages:(id)arg4 withFileToIssuesMap:(id)arg5 fileToAuxFilesMap:(id)arg6;
- (void)_addIssueForMessage:(id)arg1 blueprint:(id)arg2 intoArray:(id)arg3 usingSeenMessages:(id)arg4 withFileToIssuesMap:(id)arg5 fileToAuxFilesMap:(id)arg6 wasFetchedFromCache:(BOOL)arg7;
- (void)startProviderSession;
- (void)_postBuildIssueChange:(id)arg1;
- (void)_asyncPostBuildIssueChanges:(void (^)())changesBlock;
- (void)_observeLogSection:(id)arg1 forBlueprint:(id)arg2 loadedFromLogStore:(BOOL)arg3;
- (void)_currentBuildOperationDidChange;
- (void)_blueprintsDidChange;
- (void)_reactToCleanBuildFolder;
- (void)_forgetBlueprint:(id)arg1;
- (void)_latestBuildLogDidChange;
- (void)_workspaceFinishedLoading;
- (void)primitiveInvalidate;
- (id)initWithIssueManager:(id)arg1 extension:(id)arg2;
- (BOOL)allowsExistingIssuesToBeCoalesced;
- (void)removeBlueprintFromIssuesCache:(id)arg1;
- (BOOL)shouldRemoveIssuesFromCacheForFile:(id)arg1 inBlueprint:(id)arg2;
- (id)removeIssuesFromCacheForFile:(id)arg1 inBlueprint:(id)arg2;
- (void)addAuxiliaryFiles:(id)arg1 toCacheForFile:(id)arg2 inBlueprint:(id)arg3;
- (void)addIssues:(id)arg1 toCacheForFile:(id)arg2 inBlueprint:(id)arg3;
- (id)latestLogRecordForBlueprint:(id)arg1;
- (void)removeAllLogRecordsForBlueprint:(id)arg1;
- (void)addLogRecord:(id)arg1 forBlueprint:(id)arg2;
- (id)logRecordsForBlueprint:(id)arg1;

@end

@interface IDETypeIdentifier : NSObject
{
    NSString *_stringRepresentation;
    NSArray *_subTypes;
    IDETypeIdentifier *_parentType;
}

+ (id)typeIdentifierForStringRepresentation:(id)arg1;
+ (id)registerTypeIdentifierWithStringRepresentation:(id)arg1 basedOn:(id)arg2;
+ (id)_registerTypeIdentifierWithStringRepresentation:(id)arg1 basedOn:(id)arg2;
+ (id)_rootType;
+ (void)_registerBasicTypeIdentifiers;
@property(retain) IDETypeIdentifier *parentType; // @synthesize parentType=_parentType;
@property(retain) NSArray *subTypes; // @synthesize subTypes=_subTypes;
@property(copy) NSString *stringRepresentation; // @synthesize stringRepresentation=_stringRepresentation;
- (id)typeIdentifierLineage;
- (BOOL)isEqual:(id)arg1;
- (BOOL)isKindOfType:(id)arg1;
- (void)addSubType:(id)arg1;
- (id)description;
- (id)initWithStringRepresentation:(id)arg1;

@end



@class IDEActivityLogSection;

@interface IDEActivityLogSectionRecorder : NSObject
{
    NSPointerArray *_parentRecorders;
    NSMutableArray *_childRecorders;
    IDEActivityLogSection *_section;
    NSMutableArray *_observations;
    NSMutableArray *_changesToPost;
    BOOL _hasScheduledChangePosting;
    NSMapTable *_rememberedMessagesByKey;
    struct _NSRange _mostRecentTextRange;
    NSMutableDictionary *_severityToLimitTable;
    NSMutableDictionary *_severityToCountTable;
    int _lock;
    BOOL _hasAddedAnyErrorMessages;
    int _hasRequestedStop;
}

@property BOOL hasAddedAnyErrorMessages; // @synthesize hasAddedAnyErrorMessages=_hasAddedAnyErrorMessages;
- (void)setCommandDetailDescription:(id)arg1;
- (void)addContextInfoMessageWithTitle:(id)arg1;
- (void)addAnalyzerResultStepMessageWithTitle:(id)arg1;
- (void)addAnalyzerResultMessageWithTitle:(id)arg1;
- (void)addNoticeMessageWithTitle:(id)arg1;
- (void)addBuildSetupWarningString:(id)arg1;
- (void)addErrorMessageWithTitle:(id)arg1;
- (void)addTestFailureMessageWithTitle:(id)arg1;
- (void)stopRecordingWithInfo:(id)arg1;
- (void)stopRecordingWithInfo:(id)arg1 completionBlock:(void(^)())arg2;
- (void)_stopRecordingWithInfo:(id)arg1 completionBlock:(void(^)())arg2;
- (void)childRecorderDidStopRecording:(id)arg1;
- (void)addSubmessage:(id)arg1 toMessage:(id)arg2;
- (void)addMessage:(id)arg1 ignoreMessageLimit:(BOOL)arg2;
- (void)addMessage:(id)arg1;
- (struct _NSRange)mostRecentlyAppendedTextRange;
- (struct _NSRange)appendTextUTF8Bytes:(const char *)arg1 length:(unsigned long long)arg2;
- (struct _NSRange)appendTextFormat:(id)arg1;
- (struct _NSRange)appendText:(id)arg1;
- (void)addSubsection:(id)arg1;
- (BOOL)_attachToParentRecorderIfStillRecording:(id)arg1;
- (BOOL)hasReachedAllMessageLimits;
- (BOOL)hasReachedMessageLimitForSeverity:(unsigned long long)arg1;
- (void)setMessageLimit:(unsigned long long)arg1 forSeverity:(unsigned long long)arg2;
- (unsigned long long)messageLimitForSeverity:(unsigned long long)arg1;
- (void)setLocalizedResultString:(id)arg1;
- (void)setWasFetchedFromCache:(BOOL)arg1;
- (void)setIsQuiet:(BOOL)arg1;
- (id)addUnitTestSectionWithTitle:(id)arg1 location:(id)arg2;
- (id)addCommandSectionWithTitle:(id)arg1 detailDescription:(id)arg2;
- (id)addCommandSectionWithDomainType:(id)arg1 title:(id)arg2 detailDescription:(id)arg3;
- (void)noteDescendantLogSectionDidClose:(id)arg1 inSupersection:(id)arg2;
- (void)noteDescendantLogSection:(id)arg1 didAppendText:(id)arg2;
- (void)noteDescendantLogSection:(id)arg1 didAddSubsection:(id)arg2;
- (void)handleChangeEvent:(id)arg1;
- (void)setRememberedMessage:(id)arg1 forKey:(id)arg2;
- (id)rememberedMessageForKey:(id)arg1;
- (void)addCompletionBlock:(void(^)())arg1;
- (IDEActivityLogSection *)section;
- (void)_performOrderedAsyncBlock:(void(^)())arg1;
- (id)initWithLogSection:(id)arg1;

@end


@interface IDEActivityLogSection : NSObject <NSCopying>
{
    IDETypeIdentifier *_domainType;
    NSString *_title;
    double _timeStartedRecording;
    double _timeStoppedRecording;
    NSMutableArray *_subsections;
    NSMutableString *_text;
    NSMutableArray *_messages;
    id _representedObject;
    NSString *_subtitle;
    NSString *_signature;
    NSString *_commandDetailDesc;
    unsigned short _totalTestFailureCount;
    unsigned short _totalErrorCount;
    unsigned short _totalWarningCount;
    unsigned short _totalAnalyzerWarningCount;
    unsigned short _totalAnalyzerResultCount;
    unsigned short _sectionType;
    unsigned short _sectionAuthority;
    unsigned short _resultCode;
    BOOL _wasCancelled;
    BOOL _isQuiet;
    BOOL _wasFetchedFromCache;
    BOOL _hasAddedIssueMessage;
    NSString *_uniqueIdentifier;
    NSString *_localizedResultString;
    int _lock;
}

+ (id)sectionWithContentsOfFile:(id)arg1 error:(id *)arg2;
+ (id)sectionByDeserializingData:(id)arg1 error:(id *)arg2;
+ (unsigned long long)serializationFormatVersion;
+ (id)UUIDWithURL:(id)arg1;
+ (id)URLWithUUID:(id)arg1;
+ (id)defaultMainLogDomainType;
+ (id)defaultLogSectionDomainType;
+ (Class)logRecorderClass;
+ (void)initialize;
@property(readonly) NSString *uniqueIdentifier; // @synthesize uniqueIdentifier=_uniqueIdentifier;
@property(copy) NSString *localizedResultString; // @synthesize localizedResultString=_localizedResultString;
@property BOOL hasAddedIssueMessage; // @synthesize hasAddedIssueMessage=_hasAddedIssueMessage;
@property BOOL wasFetchedFromCache; // @synthesize wasFetchedFromCache=_wasFetchedFromCache;
@property(readonly) IDETypeIdentifier *domainType; // @synthesize domainType=_domainType;
@property unsigned short sectionAuthority; // @synthesize sectionAuthority=_sectionAuthority;
- (id)indexPathForMessageOrSection:(id)arg1;
- (id)messageOrSectionAtIndexPath:(id)arg1;
- (BOOL)writeToFile:(id)arg1 error:(id *)arg2;
- (id)serializedData;
- (void)dvt_writeToSerializer:(id)arg1;
- (id)dvt_initFromDeserializer:(id)arg1;
- (void)removeObserver:(id)arg1;
- (id)addObserverUsingBlock:(void (^)())arg1;
@property(readonly) NSURL *logSectionURL;
- (id)emittedOutputText;
- (void)logRecorder:(id)arg1 setCommandDetailDescription:(id)arg2;
@property(readonly) NSString *commandDetailDescription;
- (void)logRecorder:(id)arg1 setWasFetchedFromCache:(BOOL)arg2;
- (void)logRecorder:(id)arg1 setIsQuiet:(BOOL)arg2;
@property(readonly) BOOL isQuiet;
- (void)logRecorder:(id)arg1 adjustMessageCountsWithTestFailureDelta:(long long)arg2 errorCountDelta:(long long)arg3 warningCountDelta:(long long)arg4 analyzerWarningDelta:(long long)arg5 analyzerResultDelta:(long long)arg6;
@property(readonly) unsigned long long totalNumberOfAnalyzerResults;
@property(readonly) unsigned long long totalNumberOfAnalyzerWarnings;
@property(readonly) unsigned long long totalNumberOfWarnings;
@property(readonly) unsigned long long totalNumberOfErrors;
@property(readonly) unsigned long long totalNumberOfTestFailures;
- (id)description;
- (void)logRecorder:(id)arg1 didStopRecordingWithInfo:(id)arg2;
- (void)checkMessageCounts;
@property(readonly) IDEActivityLogSectionRecorder *recorder;
@property(readonly) BOOL isRecording;
- (void)logRecorder:(id)arg1 setWasCancelled:(BOOL)arg2;
@property(readonly) long long resultCode;
@property(readonly) BOOL wasCancelled;
- (void)logRecorder:(id)arg1 addMessage:(id)arg2;
@property(readonly) NSArray *messages;
- (void)logRecorder:(id)arg1 appendText:(id)arg2;
- (void)setAdditionalDescription:(id)arg1;
@property(readonly) NSString *subtitle;
@property(readonly) NSString *text;
- (void)logRecorder:(id)arg1 addSubsection:(id)arg2;
@property(readonly) NSArray *subsections;
@property(readonly) double timeStoppedRecording;
@property(readonly) double timeStartedRecording;
@property(copy) NSString *signature;
@property(readonly) NSString *title;
@property(readonly) id representedObject;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)dealloc;
@property(readonly) unsigned long long sectionType;
- (id)initWithTitle:(id)arg1;
- (id)init;
- (id)initWithSectionType:(unsigned long long)arg1 domainType:(id)arg2 title:(id)arg3;
- (id)initCommandInvocationWithDomainType:(id)arg1 title:(id)arg2 detailDescription:(id)arg3 filePath:(id)arg4;
- (id)initCommandInvocationWithDomainType:(id)arg1 title:(id)arg2 detailDescription:(id)arg3 location:(id)arg4;
- (id)initMajorGroupWithDomainType:(id)arg1 title:(id)arg2 representedObject:(id)arg3 subtitle:(id)arg4;
- (id)initMainLogWithDomainType:(id)arg1 title:(id)arg2;
- (id)initWithSectionType:(unsigned long long)arg1 domainType:(id)arg2 title:(id)arg3 location:(id)arg4;

@end


@interface IDEActivityLogMessage : NSObject <NSCopying>
{
    NSString *_title;
    NSString *_shortTitle;
    double _timeEmitted;
    struct _NSRange _rangeInSectionText;
    IDEActivityLogMessage *_supermessage;
    NSMutableArray *_submessages;
    unsigned long long _severity;
    IDETypeIdentifier *_type;
    NSString *_categoryIdent;
    NSArray *_secondaryLocations;
    NSString *_additionalDescription;
    int _lock;
}

+ (id)messageWithType:(id)arg1 severity:(unsigned long long)arg2 title:(id)arg3 filePath:(id)arg4 lineNumber:(unsigned long long)arg5;
+ (id)messageWithType:(id)arg1 severity:(unsigned long long)arg2 title:(id)arg3 location:(id)arg4;
@property(readonly) IDETypeIdentifier *type; // @synthesize type=_type;
@property(readonly) unsigned long long severity; // @synthesize severity=_severity;
- (void)dvt_writeToSerializer:(id)arg1;
- (id)dvt_initFromDeserializer:(id)arg1;
@property(readonly) unsigned long long totalNumberOfAnalyzerResults;
@property(readonly) unsigned long long totalNumberOfAnalyzerWarnings;
@property(readonly) unsigned long long totalNumberOfWarnings;
@property(readonly) unsigned long long totalNumberOfErrors;
@property(readonly) unsigned long long totalNumberOfTestFailures;
- (void)setSecondaryLocations:(id)arg1;
//@property(readonly) NSArray *secondaryLocations;
@property(readonly) NSString *additionalDescription;
- (void)setCategoryIdentifier:(id)arg1;
//@property(readonly) NSString *categoryIdentifier;
- (void)setShortTitle:(id)arg1;
//@property(readonly) NSString *shortTitle;
- (void)logRecorder:(id)arg1 addSectionTextRange:(struct _NSRange)arg2;
- (void)logRecorder:(id)arg1 setSectionTextRange:(struct _NSRange)arg2;
@property(readonly) NSString *logMessageString;
- (void)logRecorder:(id)arg1 addSubmessage:(id)arg2;
- (void)addSubmessage:(id)arg1;
@property(readonly) NSArray *submessages;
- (void)_setSupermessage:(id)arg1;
@property(readonly) __weak IDEActivityLogMessage *supermessage;
- (void)setSectionTextRange:(struct _NSRange)arg1;
@property(readonly) struct _NSRange rangeInSectionText;
- (void)_setSupersection:(id)arg1;
@property(readonly) __weak IDEActivityLogSection *supersection;
- (id)description;
@property(readonly) double timeEmitted;
@property(readonly) NSString *title;
- (BOOL)_hasEqualTitleLocationsSubmessages:(id)arg1 disregardingTimestamp:(BOOL)arg2;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (id)initWithType:(id)arg1 severity:(unsigned long long)arg2 title:(NSString *)title filePath:(NSString *)filePath;
- (id)initWithType:(id)arg1 severity:(unsigned long long)arg2 title:(NSString *)title filePath:(NSString *)filePath lineNumber:(unsigned long long)lineNumber;
- (id)initWithType:(id)arg1 severity:(unsigned long long)arg2 title:(NSString *)title location:(id)arg4;
- (id)initWithTitle:(NSString *)title;
- (id)init;
- (id)initWithType:(id)arg1 severity:(unsigned long long)arg2 title:(NSString *)title;

@end



@interface IDEIssue : NSObject
{
    IDEIssueProvider *_issueProvider;
    NSArray *_documentLocations;
    NSObject *_issueTypeIdentifier;
    NSString *_fullMessage;
    unsigned long long _severity;
    unsigned long long _sequenceNumber;
    NSArray *_subissues;
    IDEActivityLogMessage *_representedMessage;
    IDEActivityLogMessage *_originatingMessage;
    IDEIssue *_parentIssue;
    int _issueType;
    NSNumber *_lineNumber;
    BOOL _frozen;
    BOOL _valid;
    BOOL _coalesced;
    BOOL _wasFetchedFromCache;
    BOOL _vended;
    NSArray *_filteredSubissues;
}

@property(readonly) NSNumber *_lineNumber; // @synthesize _lineNumber;
@property(getter=_isVended) BOOL _vended; // @synthesize _vended;
@property(getter=_isCoalesced) BOOL _coalesced; // @synthesize _coalesced;
@property BOOL valid; // @synthesize valid=_valid;
@property(readonly) int issueType; // @synthesize issueType=_issueType;
@property BOOL wasFetchedFromCache; // @synthesize wasFetchedFromCache=_wasFetchedFromCache;
@property(readonly) __weak IDEIssue *parentIssue; // @synthesize parentIssue=_parentIssue;
@property(readonly) IDEActivityLogMessage *originatingMessage; // @synthesize originatingMessage=_originatingMessage;
@property(retain, nonatomic) IDEActivityLogMessage *representedMessage; // @synthesize representedMessage=_representedMessage;
@property(copy, nonatomic) NSArray *subissues; // @synthesize subissues=_subissues;
@property(readonly) unsigned long long sequenceNumber; // @synthesize sequenceNumber=_sequenceNumber;
@property(readonly) unsigned long long severity; // @synthesize severity=_severity;
@property(readonly) NSString *fullMessage; // @synthesize fullMessage=_fullMessage;
@property(retain) NSString *issueTypeIdentifier; // @synthesize issueTypeIdentifier=_issueTypeIdentifier;
@property(readonly) NSArray *documentLocations; // @synthesize documentLocations=_documentLocations;
@property(retain, nonatomic) IDEIssueProvider *issueProvider; // @synthesize issueProvider=_issueProvider;
@property(readonly, nonatomic) IDEIssue *representativeSubIssue;
- (BOOL)isEqualDisregardingLocationTimestamps:(id)arg1;
- (id)_firstCommonLocationFromArray:(id)arg1 andArray:(id)arg2;
- (void)diagnosticItemWasFixed:(id)arg1;
- (long long)compareByLineNumber:(id)arg1;
- (long long)compare:(id)arg1;
@property(readonly) BOOL isLiveIssue;
@property(retain) IDEIssue *_parentIssue;
@property(readonly) NSString *formattedStringRepresentation;
@property(readonly, copy) NSString *description;
- (id)_severityString;
- (void)_freeze;
@property(readonly) NSArray *fixableDiagnosticItems;
- (void)_setRepresentedMessage:(id)arg1 force:(BOOL)arg2;
@property(readonly) NSArray *filteredSubissues; // @synthesize filteredSubissues=_filteredSubissues;
- (void)_setSubissues:(id)arg1 force:(BOOL)arg2;
- (void)_setSequenceNumber:(unsigned long long)arg1;
- (id)initWithIssueProvider:(IDEIssueProvider *)provider message:(IDEActivityLogMessage *)message wasFetchedFromCache:(BOOL)arg3;
- (id)initWithIssueProvider:(id)arg1 message:(id)arg2 originatingLogRecord:(id)arg3 wasFetchedFromCache:(BOOL)arg4;
- (id)initWithIssueProvider:(id)arg1 documentLocations:(id)arg2 issueTypeIdentifier:(id)arg3 fullMessage:(id)arg4 severity:(unsigned long long)arg5 representedMessage:(id)arg6;
- (id)init;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;

@end

@class IDEActivityReport;
@class IDEActivityViewDataSource;
@class IDEActivityReportManager;

@interface IDEActivityView : NSView
{
    NSView *_layerView;
    CALayer *_reportLayerContainerLayer;
    CALayer *_backgroundLayer;
    CALayer *_reportLayerTree;
    IDEWorkspaceWindowController *_workspaceWindowController;
    NSMapTable *_strongReportsToStrongReportLayers;
    IDEActivityViewDataSource *_dataSource;
    struct {
        unsigned int setup:1;
        unsigned int displayedReportIsCompleted:1;
        unsigned int forcedDisplayedReportUpdateIsScheduled:1;
        unsigned int _reserved:5;
    } _flags;
}

+ (struct CGSize)scaledSizeWithMaximumWidth:(double)arg1 forToolbarDisplayMode:(unsigned long long)arg2 sizeMode:(unsigned long long)arg3;
+ (struct CGSize)defaultSizeForToolbarDisplayMode:(unsigned long long)arg1 sizeMode:(unsigned long long)arg2;
+ (void)initialize;
@property(retain, nonatomic) IDEWorkspaceWindowController *workspaceWindowController; // @synthesize workspaceWindowController=_workspaceWindowController;
- (id)accessibilityHitTest:(struct CGPoint)arg1;
- (BOOL)accessibilityIsAttributeSettable:(id)arg1;
- (id)accessibilityAttributeValue:(id)arg1;
- (id)accessibilityAttributeNames;
- (BOOL)accessibilityIsIgnored;
- (void)openLogNavigator;
- (void)openActivityPopUp;
- (void)cancelDisplayedReport:(id)arg1;
- (void)stopObservingActivityReports;
- (void)activityReportManagerDidInvalidateForActivityViewDataSource:(id)arg1;
- (void)activityViewDataSource:(id)arg1 activityReportDidComplete:(id)arg2;
- (void)activityReportListDidChangeForActivityViewDataSource:(id)arg1;
- (void)updateActionIndicators;
- (void)window:(id)arg1 didChangeActivationState:(long long)arg2;
- (void)makeSureIssuesLayerIsVisible;
- (void)viewDidMoveToSuperview;
- (void)viewDidMoveToWindow;
- (void)setupOrTearDown;
- (void)tearDown;
- (void)setup;
- (id)_botCompositeCategory;
- (void)teardownLayers;
- (void)setupLayers;
- (id)_buildMultiActionIndicatorLayer;
- (id)_buildAllStatusLayer;
- (id)_buildReportLayerTree;
- (id)_backgroundLayer;
- (void)_updateCurrentActivityReportForWindowActivationState;
- (id)clickableLayerAtPoint:(struct CGPoint)arg1;
- (struct CGRect)insetReportLayerBounds;
- (struct CGRect)insetRootLayerBounds;
@property struct CGSize contentSize;
- (void)sizeToFitToolbarDisplayMode:(unsigned long long)arg1 sizeMode:(unsigned long long)arg2;
- (void)activityViewDataSource:(IDEActivityViewDataSource *)arg1 countDidChangeForBotStatusCategory:(id)arg2;
- (void)activityViewDataSource:(IDEActivityViewDataSource *)arg1 workspaceRepresentingTypeStringDidChangeTo:(id)arg2;
- (void)activityViewDataSource:(IDEActivityViewDataSource *)arg1 issueCountDidChangeForIssueCategory:(id)arg2;
- (void)unschedulePendingForcedDisplayedReportUpdate;
- (void)scheduleForcedDisplayedReportUpdate;
- (void)chooseAndDisplayNextActivityReportAfterIdlePreDelay;
- (void)chooseAndDisplayNextActivityReportAfterReportCompleted;
- (void)chooseAndDisplayNextActivityReportAfterMinimumTimeExpiredOrDelayExpired;
- (void)chooseAndDisplayNextActivityReportAfterChangeInReports;
- (id)nextActivityReportToDisplay;
- (void)delayedSetDisplayedReport:(IDEActivityReport *)arg1;
- (void)activityViewDataSource:(id)arg1 displayDelayTimeWasMetForActivityReport:(id)arg2;
- (void)tryToDisplayReport:(IDEActivityReport *)arg1;
- (void)setDisplayedReport:(IDEActivityReport *)arg1;
- (id)activityReportLayerForReport:(IDEActivityReport *)arg1;
- (void)setActivityReportLayer:(id)arg1 forReport:(id)arg2;
- (void)activityViewDataSource:(id)arg1 minimumDisplayTimeWasMetForActivityReport:(id)arg2;
@property(readonly) IDEActivityReport *displayedReport;
- (id)activityReports;
- (id)orderedActivityReports;
- (IDEActivityReportManager *)activityReportManager;
- (id)workspaceTabController;
- (id)workspace;
- (id)workspaceDocument;
- (void)primitiveInvalidate;
- (id)initWithFrame:(struct CGRect)arg1;
- (id)initWithCoder:(id)arg1;
- (void)activityViewCommonInit;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end

typedef void (^CDUnknownBlockType)(void);

@interface IDEActivityViewDataSource : NSObject
{
    IDEWorkspaceDocument *_workspaceDocument;
    NSMutableSet *_registeredConsumers;
    BOOL _haveRegisteredFirstConsumer;
    NSString *_debugName;
    NSMapTable *_strongReportToStrongMinimumTimeTimerMap;
    NSMutableSet *_activityReportsUnderMinimumDisplayTime;
    NSMutableArray *_backgroundActivitiesLongerThanDelay;
    NSMapTable *_strongDelayedInvocationsByStrongReport;
    NSMapTable *_strongIssueCategoryToIssueCountByURLTable;
    NSArray *_issueCategories;
    NSArray *_botStatusCategories;
}

+ (void)initialize;
@property(copy) NSString *debugName; // @synthesize debugName=_debugName;
@property(readonly, copy) NSArray *botStatusCategories; // @synthesize botStatusCategories=_botStatusCategories;
@property(copy) NSArray *issueCategories; // @synthesize issueCategories=_issueCategories;
@property(readonly) IDEWorkspaceDocument *workspaceDocument; // @synthesize workspaceDocument=_workspaceDocument;
- (void)openIssuesNavigator;
- (void)openTestNavigator;
- (void)stopObservingActivityReports;
- (void)startObservingActivityReports;
- (void)tearDown;
- (void)stopObservingIssues;
- (void)startObservingIssues;
- (void)updateIssuesForAllURLsWithIssues;
- (void)updateNumberOfIssuesForURL:(id)arg1;
- (void)_updateCategory:(id)arg1 withCurrent:(unsigned long long)arg2 andNew:(unsigned long long)arg3;
- (id)issuesForDocumentURLOrSharedPlaceholderURL:(id)arg1;
- (id)activityViewLocalURLForIssueManagerURL:(id)arg1;
- (id)sharedPlaceholderURLForIssuesWithNoDocument;
- (void)setNumberOfIssues:(long long)arg1 forURL:(id)arg2 inCategory:(id)arg3;
- (long long)numberOfIssuesForURL:(id)arg1 inCategory:(id)arg2;
- (id)oldestKnownBackgroundActivityReportThatHasMetDisplayDelayTime;
- (BOOL)haveReachedDisplayDelayTimeForActivityReport:(id)arg1;
- (void)startTrackingDisplayDelayTimeIfNeededForReport:(id)arg1;
- (void)startPreDisplayDelayValidatorForReport:(id)arg1;
- (void)startTrackingMinimumDisplayTimeForActivityReport:(id)arg1;
- (void)stopTrackingMinimumDisplayTimeForActivityReport:(id)arg1;
- (void)startMinimumDisplayTimeTimerForActivityReport:(id)arg1;
- (id)minimumDisplayTimeTimerForActivityReport:(id)arg1;
- (void)minimumTimeTimerForActivityReportDidExpire:(id)arg1;
- (void)minimumTimeForActivityReportDidExpire:(id)arg1;
- (void)setHaveReachedMinimumDisplayTime:(BOOL)arg1 forActivityReport:(id)arg2;
- (BOOL)haveReachedMinimumDisplayTimeForActivityReport:(id)arg1;
- (void)enumerateConsumersUsingBlock:(CDUnknownBlockType)arg1;
- (void)unregisterConsumer:(id)arg1;
- (void)registerConsumer:(id)arg1;
@property(readonly) NSArray *orderedActivityReportsForListStylePresentation;
- (id)effectiveDebugName;
- (id)activityReports;
@property(readonly) NSArray *orderedActivityReports;
- (id)activityReportManager;
- (id)workspace;
- (id)dataSourceByCloningReportTimingData;
- (void)primitiveInvalidate;
- (id)initWithWorkspaceDocument:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end


@class IDEActivityReport;
@interface IDEActivityReportManager : NSObject
{
    IDEActivityReport *_lastCompletedUserVisiblePersistentSchemeBasedReport;
    IDEActivityReport *_lastCompletedUserVisibleSchemeBasedReport;
    IDEActivityReport *_lastCompletedUserVisibleReport;
    IDEWorkspaceDocument *_workspaceDocument;
    NSSet *_activityReporterObservingTokens;
    NSSet *_activityReporters;
    NSMutableSet *_observers;
    NSArray *_orderedActivityReports;
    NSSet *_activityReports;
    BOOL _lastCompletedUserVisiblePersistentSchemeBasedReportShouldBeInvalidated;
}

+ (void)initialize;
+ (unsigned long long)assertionBehaviorForKeyValueObservationsAtEndOfEvent;
@property(nonatomic) BOOL lastCompletedUserVisiblePersistentSchemeBasedReportShouldBeInvalidated; // @synthesize lastCompletedUserVisiblePersistentSchemeBasedReportShouldBeInvalidated=_lastCompletedUserVisiblePersistentSchemeBasedReportShouldBeInvalidated;
@property(retain, nonatomic) IDEActivityReport *lastCompletedUserVisiblePersistentSchemeBasedReport; // @synthesize lastCompletedUserVisiblePersistentSchemeBasedReport=_lastCompletedUserVisiblePersistentSchemeBasedReport;
@property(copy, nonatomic) NSArray *orderedActivityReports; // @synthesize orderedActivityReports=_orderedActivityReports;
@property(copy, nonatomic) NSSet *activityReports; // @synthesize activityReports=_activityReports;
@property(readonly) IDEWorkspaceDocument *workspaceDocument; // @synthesize workspaceDocument=_workspaceDocument;
- (void)reportDidComplete:(id)arg1;
- (void)stopObservingReportForCompletion:(id)arg1;
- (void)startObservingReportForCompletion:(id)arg1;
- (id)addObserver:(CDUnknownBlockType)arg1;
- (void)removeObserverBlock:(CDUnknownBlockType)arg1;
- (void)restoreLastCompletedUserVisiblePersistentSchemeBasedReportFrom:(id)arg1;
@property(retain) IDEActivityReport *lastCompletedUserVisibleSchemeBasedReport; // @synthesize lastCompletedUserVisibleSchemeBasedReport=_lastCompletedUserVisibleSchemeBasedReport;
- (void)setLastCompletedUserVisibleReport:(IDEActivityReport *)arg1;
@property(readonly) IDEActivityReport *lastCompletedUserVisibleReport; // @synthesize lastCompletedUserVisibleReport=_lastCompletedUserVisibleReport;
- (void)rebuildActivityReportCaches;
- (void)handleUpdateFromActivityReporter:(id)arg1;
@property(readonly) NSSet *activityReporters;
- (void)loadActivityReporters;
- (void)primitiveInvalidate;
- (id)initWithWorkspaceDocument:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end


@class IDEActivityReportStringSegment;
@interface IDEActivityReport : NSObject
{
    int _options;
    NSString *_title;
    NSArray *_titleSegments;
    NSString *_completionSummaryString;
    NSArray *_completionSummaryStringSegments;
    long long _progress;
    double _timestamp;
    double _displayPriority;
    unsigned long long _fileIOPriority;
    double _fileIOThrottleFactor;
}

+ (id)keyPathsForValuesAffectingPaused;
+ (BOOL)automaticallyNotifiesObserversOfFileIOThrottleFactor;
+ (id)keyPathsForValuesAffectingCompleted;
+ (unsigned long long)assertionBehaviorForKeyValueObservationsAtEndOfEvent;
+ (unsigned long long)assertionBehaviorAfterEndOfEventForSelector:(SEL)arg1;
+ (void)initialize;
@property(readonly) double fileIOThrottleFactor; // @synthesize fileIOThrottleFactor=_fileIOThrottleFactor;
@property unsigned long long fileIOPriority; // @synthesize fileIOPriority=_fileIOPriority;
@property double displayPriority; // @synthesize displayPriority=_displayPriority;
@property(readonly) double timestamp; // @synthesize timestamp=_timestamp;
@property long long progress; // @synthesize progress=_progress;
@property(copy) NSArray *completionSummaryStringSegments; // @synthesize completionSummaryStringSegments=_completionSummaryStringSegments;
@property(copy) NSString *completionSummaryString; // @synthesize completionSummaryString=_completionSummaryString;
@property(copy, nonatomic) NSArray<IDEActivityReportStringSegment *> *titleSegments; // @synthesize titleSegments=_titleSegments;
@property(copy, nonatomic) NSString *title; // @synthesize title=_title;
@property(readonly) int options; // @synthesize options=_options;
@property(readonly) NSString *stringValue;
@property(readonly) BOOL paused;
- (void)_setFileIOThrottleFactor:(double)arg1;
@property(readonly, getter=isUserVisible) BOOL userVisible;
@property(readonly, getter=isFileIOIntensive) BOOL fileIOIntensive;
@property(readonly, getter=isPersistent) BOOL persistent;
@property(readonly) BOOL disableTitleAnimation;
@property(readonly) BOOL shouldDisplayImmediately;
@property(readonly) BOOL hidesProgress;
@property(readonly, getter=isSchemeBased) BOOL schemeBased;
@property(readonly, getter=isUserRequested) BOOL userRequested;
@property(readonly, getter=isCancelable) BOOL cancelable;
@property(readonly, getter=isCompleted) BOOL completed;
@property(readonly) NSDictionary *dictionaryRepresentation;
@property(readonly, copy) NSString *description;
- (void)primitiveInvalidate;
- (id)init;
- (id)initWithDictionaryRepresentation:(id)arg1;
- (id)initWithTitle:(id)arg1 titleSegments:(id)arg2 options:(int)arg3 fileIOPriority:(unsigned long long)arg4 fileIOCoordinatorBlock:(CDUnknownBlockType)arg5;
- (id)_initWithTitle:(id)arg1 titleSegments:(id)arg2 options:(int)arg3 fileIOPriority:(unsigned long long)arg4 fileIOCoordinatorBlock:(CDUnknownBlockType)arg5 unarchived:(BOOL)arg6;
- (void)setProgressAsNSNumber:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *debugDescription;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end

@interface IDEActivityReporter : NSObject
{
    IDEWorkspace *_workspace;
    NSArray *_activityReports;
    NSImage *_image;
}

+ (void)initialize;
+ (id)activityReporterWithExtension:(id)arg1 workspace:(id)arg2;
@property(readonly) IDEWorkspace *workspace; // @synthesize workspace=_workspace;
- (void)primitiveInvalidate;
@property(readonly) NSImage *image;
- (IDEActivityReport *)newActivityReportWithTitle:(NSString *)arg1 options:(int)arg2;
- (IDEActivityReport *)newActivityReportWithTitle:(NSString *)arg1 options:(int)arg2 image:(id)arg3;
- (IDEActivityReport *)newActivityReportWithTitle:(NSString *)arg1 options:(int)arg2 isUserVisible:(BOOL)arg3 fileIOPriority:(unsigned long long)arg4 fileIOCoordinatorBlock:(CDUnknownBlockType)arg5;
- (IDEActivityReport *)newActivityReportWithTitle:(id)arg1 options:(int)arg2 isUserVisible:(BOOL)arg3 image:(id)arg4 fileIOPriority:(unsigned long long)arg5 fileIOCoordinatorBlock:(CDUnknownBlockType)arg6;
- (id)initWithWorkspace:(id)arg1;

// Remaining properties
@property(readonly) NSArray *activityReports; // @dynamic activityReports;
@property(readonly, copy) NSString *debugDescription;
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) NSMutableArray *mutableActivityReports; // @dynamic mutableActivityReports;
@property(readonly) Class superclass;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end


@interface IDEActivityReportStringSegment : NSObject

+ (id)activityReportStringSegmentWithDictionaryRepresentation:(id)arg1;
@property(readonly) NSString *frontSeparator;
@property(readonly) NSString *backSeparator;
@property(readonly) double priority;
@property(readonly) NSString *stringValue;
@property(readonly) NSDictionary *dictionaryRepresentation;
@property(readonly) long long segmentType;
- (id)description;
- (id)attributedStringValueWithDefaultAttributes:(id)arg1 hasFrontSeparator:(BOOL)arg2 hasBackSeparator:(BOOL)arg3;
- (id)initWithDictionaryRepresentation:(NSDictionary *)arg1;
- (id)initWithString:(NSString *)arg1 priority:(double)arg2;
- (id)initWithString:(id)arg1 priority:(double)arg2 frontSeparator:(NSString *)arg3 backSeparator:(NSString *)arg4;

@end

@interface IDEActivityReportDateStringSegment : IDEActivityReportStringSegment

@property(readonly) NSDateFormatterStyle timeStyle;
@property(readonly) NSDateFormatterStyle dateStyle;
@property(readonly) NSDate *date;
- (id)dictionaryRepresentation;
- (long long)segmentType;
- (id)stringValue;
- (id)initWithDictionaryRepresentation:(NSDictionary *)arg1;
- (id)initWithDate:(NSDate *)arg1 priority:(double)arg2 dateStyle:(NSDateFormatterStyle)arg3 timeStyle:(NSDateFormatterStyle)arg4;
- (id)initWithDate:(NSDate *)arg1 priority:(double)arg2 frontSeparator:(NSString *)arg3 backSeparator:(NSString *)arg4 dateStyle:(NSDateFormatterStyle)arg5 timeStyle:(NSDateFormatterStyle)arg6;

@end
