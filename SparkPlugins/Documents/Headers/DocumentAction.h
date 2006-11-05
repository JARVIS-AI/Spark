/*
 *  DocumentAction.h
 *  Spark Plugins
 *
 *  Created by Black Moon Team.
 *  Copyright (c) 2004 - 2006, Shadow Lab. All rights reserved.
 */

#import <SparkKit/SparkPluginAPI.h>

enum {
  kDocumentActionOpen              = 'Open', /* 1332766062 */
  kDocumentActionOpenWith          = 'OpWi', /* 1332762473 */
  kDocumentActionOpenSelection     = 'OpSe', /* 1332761445 */
  kDocumentActionOpenSelectionWith = 'OpSW', /* 1332761431 */
  kDocumentActionOpenURL           = 'OURL', /* 1330991692 */
};

SPARK_PRIVATE
NSString * const kDocumentActionBundleIdentifier;

#define kDocumentActionBundle		[NSBundle bundleWithIdentifier:kDocumentActionBundleIdentifier]

@class SKAlias, SKAliasedApplication;
@interface DocumentAction : SparkAction <NSCoding, NSCopying> {
  int da_action;
  SKAlias *da_doc;
  NSString *da_url;
  SKAliasedApplication *da_app;
}

- (int)action;
- (void)setAction:(int)anAction;

- (void)setDocumentPath:(NSString *)path;
- (void)setApplicationPath:(NSString *)path;

- (NSString *)url;
- (void)setURL:(NSString *)url;

- (SKAlias *)document;
- (void)setDocument:(SKAlias *)aDoc;
- (SKAliasedApplication *)application;
- (void)setApplication:(SKAliasedApplication *)anApplication;

- (void)openSelection;

@end

SK_PRIVATE
NSString *DocumentActionDescription(DocumentAction *anAction);
