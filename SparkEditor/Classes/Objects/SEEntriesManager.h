/*
 *  SEEntriesManager.h
 *  Spark Editor
 *
 *  Created by Black Moon Team.
 *  Copyright (c) 2004 - 2006 Shadow Lab. All rights reserved.
 */

#import <Cocoa/Cocoa.h>

@class SparkLibrary, SparkApplication, SparkPlugIn;
@class SESparkEntrySet, SEEntryEditor;
@class SparkEntry;
@interface SEEntriesManager : NSObject {
  @private
  SEEntryEditor *se_editor;
  SparkApplication *se_app;
  SESparkEntrySet *se_globals;
  SESparkEntrySet *se_snapshot;
  SESparkEntrySet *se_overwrites;
}

/* All globals entries */
- (SESparkEntrySet *)globals;
/* Current entryset */
- (SESparkEntrySet *)snapshot;
/* Current application entries */
- (SESparkEntrySet *)overwrites;

- (SparkApplication *)application;
- (void)setApplication:(SparkApplication *)anApplication;

- (void)removeEntries:(NSArray *)entries;

- (void)createEntry:(SparkPlugIn *)aPlugin modalForWindow:(NSWindow *)aWindow;
- (void)editEntry:(SparkEntry *)anEntry modalForWindow:(NSWindow *)aWindow;

@end

SK_PRIVATE
NSString * const SEApplicationDidChangeNotification;
SK_PRIVATE
NSString * const SEEntriesManagerDidReloadNotification;
SK_PRIVATE
NSString * const SEEntriesManagerDidCreateEntryNotification;

@interface SEEntriesManager (ShadowSingleton)

+ (SEEntriesManager *)sharedManager;

@end
