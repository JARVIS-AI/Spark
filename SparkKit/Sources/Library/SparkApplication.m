/*
 *  SparkApplication.m
 *  SparkKit
 *
 *  Created by Black Moon Team.
 *  Copyright © 2004 - 2006 Shadow Lab. All rights reserved.
 *
 */

#import <SparkKit/SparkApplication.h>

#import <ShadowKit/SKImageUtils.h>
#import <ShadowKit/SKApplication.h>

static NSString * const kSparkApplicationKey = @"SparkApplication";

#pragma mark -
@interface SKApplication (SparkSerialization)
- (BOOL)serialize:(NSMutableDictionary *)plist;
- (id)initWithSerializedValues:(NSDictionary *)plist;
@end

@implementation SparkApplication

#pragma mark -
#pragma mark NSCoding
- (void)encodeWithCoder:(NSCoder *)coder {
  [super encodeWithCoder:coder];
  [coder encodeObject:sp_application forKey:kSparkApplicationKey];
  return;
}
- (id)initWithCoder:(NSCoder *)coder {
  if (self = [super initWithCoder:coder]) {
    sp_application = [[coder decodeObjectForKey:kSparkApplicationKey] retain];
  }
  return self;
}

#pragma mark NSCopying
- (id)copyWithZone:(NSZone *)zone {
  SparkApplication* copy = [super copyWithZone:zone];
  copy->sp_application = [sp_application copy];
  return copy;
}

#pragma mark SparkSerialization
- (BOOL)serialize:(NSMutableDictionary *)plist {
  [super serialize:plist];
  if ([sp_application identifier])
    return [sp_application serialize:plist];
  return YES;
}
- (id)initWithSerializedValues:(NSDictionary *)plist {
  if (self = [super initWithSerializedValues:plist]) {
    sp_application = [[SKApplication alloc] initWithSerializedValues:plist];
  }
  return self;
}

#pragma mark -
#pragma mark Init & Dealloc Methods
- (id)init {
  if (self = [super init]) {
    sp_application = [[SKApplication alloc] init];
  }
  return self;
}

- (id)initWithPath:(NSString *)path {
  if (self = [super init]) {
    [self setPath:path];
    if (!sp_application) {
      DLog(@"Invalid app at path: %@", path);
      [self release];
      self = nil;
    }
  }
  return self;
}

- (void)dealloc {
  [sp_application release];
  [super dealloc];
}

- (BOOL)isEqual:(id)object {
  if (self == object)
    return YES;
  else if ([object isKindOfClass:[SparkApplication class]])
    return [sp_application isEqual:((SparkApplication *)object)->sp_application];
  else return NO;
}
- (unsigned)hash {
  return [sp_application hash];
}

#pragma mark -
#pragma mark Accessors
- (NSString *)path {
  return [sp_application path];
}
- (void)setPath:(NSString *)path {
  if (sp_application) {
    [sp_application release];
  }
  sp_application = [[SKApplication alloc] initWithPath:path];
  if (sp_application) {
    [self setName:[sp_application name]];
    [self setIcon:SKResizedIcon([[NSWorkspace sharedWorkspace] iconForFile:path], NSMakeSize(16, 16))];
    [sp_application setName:nil];
  }
}

//- (NSString *)identifier {
//  return [sp_application identifier];
//}

- (OSType)signature {
  return [sp_application signature];
}
//- (void)setSignature:(NSString *)signature {
//  [sp_application setIdentifier:signature type:kSKApplicationOSType];
//}
//
- (NSString *)bundleIdentifier {
  return [sp_application bundleIdentifier];
}
//- (void)setBundleIdentifier:(NSString *)identifier {
//  [sp_application setIdentifier:identifier type:kSKApplicationBundleIdentifier];
//}

@end

#pragma mark -
static NSString * const kSKApplicationName = @"Name";
static NSString * const kSKApplicationIdType = @"IDType";
static NSString * const kSKApplicationIdentifier = @"Identifier";

@implementation SKApplication (SparkSerialization)

- (id)initWithSerializedValues:(NSDictionary *)plist {
  if (self = [super init]) {
    [self setName:[plist objectForKey:kSKApplicationName]];
    /* Compatibility with Library version 1.0 */
    if ([plist objectForKey:@"SparkApplication"]) {
      plist = [plist objectForKey:@"SparkApplication"];
    } 
    [self setIdentifier:[plist objectForKey:kSKApplicationIdentifier]
                   type:[[plist objectForKey:kSKApplicationIdType] intValue]];
  }
  return self;
}

- (BOOL)serialize:(NSMutableDictionary *)plist {
  [plist setObject:SKInt([self idType]) forKey:kSKApplicationIdType];
  [plist setObject:[self identifier] forKey:kSKApplicationIdentifier];
  return YES;
}

@end