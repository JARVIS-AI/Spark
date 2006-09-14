/*
 *  ITunesAction.h
 *  Spark Plugins
 *
 *  Created by Black Moon Team.
 *  Copyright (c) Shadow Lab. 2004 - 2006. All rights reserved.
 */

#import <SparkKit/SparkPluginAPI.h>

#import "ITunesInfo.h"

SPARK_PRIVATE
NSString * const kiTunesActionBundleIdentifier;
#define kiTunesActionBundle		[NSBundle bundleWithIdentifier:kiTunesActionBundleIdentifier]

typedef enum {
  kiTunesLaunch				= 'Laun', /* 1281455470 */
  kiTunesQuit				= 'Quit', /* 1366649204 */
  
  kiTunesStop				= 'Stop', /* 1400139632 */
  kiTunesPlayPause			= 'PlPs', /* 1349275763 */
  kiTunesBackTrack			= 'Back', /* 1113678699 */
  kiTunesNextTrack			= 'Next', /* 1315272820 */
  
  kiTunesRateTrack			= 'RaTr', /* 1382110322 */
  kiTunesPlayPlaylist		= 'PlPy', /* 1349275769 */
  kiTunesShowTrackInfo		= 'TrIn', /* 1416776046 */
  
  kiTunesVolumeUp			= 'VoUp', /* 1450136944 */
  kiTunesVolumeDown			= 'VoDo', /* 1450132591 */
  
  kiTunesVisual				= 'Visu', /* 1449751413 */
  kiTunesEjectCD			= 'Ejec', /* 1164600675 */
} iTunesAction;

@interface ITunesAction : SparkAction <NSCoding, NSCopying> {
  @private
    iTunesAction ia_action;
  NSString *ia_playlist;
  
  struct _ia_iaFlags {
    unsigned int rate:7; /* 0 to 100 */
    /* launch flags */
    unsigned int hide:1;
    unsigned int autoplay:1;
    unsigned int background:1;
    /* visuals settings */
    unsigned int show:1; /* visual enabled */
    unsigned int visual:2; /* visual type: default, custom */
    unsigned int reserved:19;
  } ia_iaFlags;
  
  ITunesVisual *ia_visual;
}

- (SInt32)rating;
- (void)setRating:(SInt32)aRate;

- (NSString *)playlist;
- (void)setPlaylist:(NSString *)newPlaylist;

- (iTunesAction)iTunesAction;
- (void)setITunesAction:(iTunesAction)newAction;

- (const ITunesVisual *)visual;

- (BOOL)showInfo;
- (void)setShowInfo:(BOOL)flag;

- (int)visualMode;
- (void)setVisualMode:(int)mode;

- (void)switchVisualStat;
- (void)volumeUp;
- (void)volumeDown;
- (void)ejectCD;
- (SparkAlert *)playPlaylist:(NSString *)name;

@end

SK_PRIVATE
NSString *ITunesActionDescription(ITunesAction *action);
