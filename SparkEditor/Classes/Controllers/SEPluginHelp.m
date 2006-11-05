/*
 *  SEPluginHelp.m
 *  Spark Editor
 *
 *  Created by Black Moon Team.
 *  Copyright (c) 2004 - 2006, Shadow Lab. All rights reserved.
 */

#import "SEPluginHelp.h"

#import <WebKit/WebKit.h>

#import <SparkKit/SparkPlugIn.h>
#import <SparkKit/SparkActionLoader.h>

#import <ShadowKit/SKHeaderView.h>

@implementation SEPluginHelp

+ (id)sharedPluginHelp {
  static SEPluginHelp *shared = nil;
  if (shared)
    return shared;
  @synchronized(self) {
    if (!shared) {
      shared = [[SEPluginHelp alloc] init];
      /* Load nib */
      [shared window];
    }
  }
  return shared;
}

- (id)init {
  if (self = [super init]) {
  }
  return self;
}

- (void)dealloc {
  
  [super dealloc];
}

- (void)awakeFromNib {
  if (!se_previous) {
    se_previous = [ibHead addButton:[NSImage imageNamed:@"SEBack"] position:kSKHeaderLeft];
    [se_previous setTarget:ibWeb];
    [se_previous setAction:@selector(goBack:)];
    [se_previous bind:@"enabled" toObject:ibWeb withKeyPath:@"canGoBack" options:nil];
    
    se_next = [ibHead addButton:[NSImage imageNamed:@"SEForward"] position:kSKHeaderLeft];
    [se_next setTarget:ibWeb];
    [se_next setAction:@selector(goForward:)];
    [se_next bind:@"enabled" toObject:ibWeb withKeyPath:@"canGoForward" options:nil];
    
    NSMenu *aMenu = [[NSMenu alloc] initWithTitle:@"Plugins"];
    NSSortDescriptor *desc = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES selector:@selector(caseInsensitiveCompare:)];
    NSEnumerator *plugins = [[[[SparkActionLoader sharedLoader] plugins] sortedArrayUsingDescriptors:[NSArray arrayWithObject:desc]] objectEnumerator];
    [desc release];
    
    SparkPlugIn *plugin;
    while (plugin = [plugins nextObject]) {
      NSURL *help = [plugin helpURL];
      if (help) {
        NSMenuItem *item = [[NSMenuItem alloc] initWithTitle:[plugin name] action:nil keyEquivalent:@""];
        [item setImage:[plugin icon]];
        [item setRepresentedObject:[help absoluteString]];
        [aMenu addItem:item];
        [item release];
      }
    }
    
    se_plugins = [ibHead addMenu:aMenu position:kSKHeaderLeft];
    [se_plugins setTarget:self];
    [se_plugins setAction:@selector(selectPlugin:)];
    
    if ([aMenu numberOfItems])
      [self selectPlugin:[aMenu itemAtIndex:0]];
    
    [aMenu release];
  }
}

#pragma mark -
- (void)setPage:(NSString *)aPage {
  
}

- (void)setPlugin:(SparkPlugIn *)aPlugin {
  [se_plugins selectItemWithTitle:[aPlugin name]];
  [self selectPlugin:nil];
}

- (IBAction)selectPlugin:(id)sender {
  NSString *path = [[se_plugins selectedItem] representedObject];
  if (path) {
    [[ibWeb backForwardList] setCapacity:0];
    [ibWeb setValue:path forKey:@"mainFrameURL"];
    [[ibWeb backForwardList] setCapacity:10];
  }
}

@end
