/*
 *  SparkEntry.h
 *  SparkKit
 *
 *  Created by Black Moon Team.
 *  Copyright (c) 2004 - 2006 Shadow Lab. All rights reserved.
 */

#import <Cocoa/Cocoa.h>

typedef enum {
  kSparkEntryTypeDefault = 0, /* Inherits or global */
  kSparkEntryTypeSpecific = 1, /* Defined in custom application only */
  kSparkEntryTypeOverWrite = 2, /* OverWrite a default action and status */
  kSparkEntryTypeWeakOverWrite = 3, /* Overwrite default status but same action */
} SparkEntryType;

@class SparkAction, SparkTrigger, SparkApplication;

@interface SparkEntry : NSObject <NSCopying> {
  @private
  SparkAction *sp_action;
  SparkTrigger *sp_trigger;
  SparkApplication *sp_application;
  
  struct _sp_seFlags {
    unsigned int type:8;
    unsigned int enabled:1;
    unsigned int reserved:23;
  } sp_seFlags;
}

+ (id)entryWithAction:(SparkAction *)anAction trigger:(SparkTrigger *)aTrigger application:(SparkApplication *)anApplication;

- (id)initWithAction:(SparkAction *)anAction trigger:(SparkTrigger *)aTrigger application:(SparkApplication *)anApplication;

- (BOOL)isEqualToEntry:(SparkEntry *)anEntry;

- (SparkAction *)action;
- (void)setAction:(SparkAction *)action;

- (id)trigger;
- (void)setTrigger:(SparkTrigger *)trigger;

- (SparkApplication *)application;
- (void)setApplication:(SparkApplication *)anApplication;

- (SparkEntryType)type;
- (void)setType:(SparkEntryType)type;

- (NSImage *)icon;
- (void)setIcon:(NSImage *)anIcon;

- (NSString *)name;
- (void)setName:(NSString *)aName;

- (NSString *)categorie;
- (NSString *)actionDescription;
- (NSString *)triggerDescription;

@end