/*
 *  SEApplicationSource.h
 *  Spark Editor
 *
 *  Created by Black Moon Team.
 *  Copyright (c) 2004 - 2007 Shadow Lab. All rights reserved.
 */

#import <ShadowKit/SKTableDataSource.h>

@class SKTableView;
@class SELibraryWindow, SparkLibrary;
@interface SEApplicationSource : SKTableDataSource {
  IBOutlet SKTableView *uiTable;
  IBOutlet SELibraryWindow *ibWindow;
  @private
    BOOL se_locked;
  NSMutableSet *se_path;
  SparkLibrary *se_library;
}

- (IBAction)newApplication:(id)sender;
- (IBAction)deleteSelection:(id)sender;

- (void)setLibrary:(SparkLibrary *)aLibrary;

@end
