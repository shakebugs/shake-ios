//
//  Shake.h
//  ShakeFramework
//
//  Created by David Halapir on 19/11/2018.
//  Copyright © 2018 Shake Technologies, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ShakeReportData.h"
#import "ShakeEnums.h"

//! Project version number for Shake.
FOUNDATION_EXPORT double ShakeVersionNumber;

//! Project version string for Shake.
FOUNDATION_EXPORT const unsigned char ShakeVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <Shake/PublicHeader.h>

NS_ASSUME_NONNULL_BEGIN
NS_SWIFT_NAME(Shake)
@interface SHKShake : NSObject

/**
 Add additional data and files to the report object provided by the block.
 */
@property (nonatomic, copy) SHKShakeReportData *(^onPrepareData)(SHKShakeReportData *reportData);

+ (void)start;
+ (void)startWithInvocationEvents:(ShakeInvocationEvent)invocationEvents;
+ (void)manualStart;
+ (SHKShake *)sharedInstance;
+ (NSBundle*) bundle;
+ (void)setBlackBoxEnabled:(BOOL)isBlackBoxEnabled;
+ (void)autoReportWithAttachScreenshot:(BOOL)screenshot description:(NSString *)description;
+ (void)autoReportWithAttachScreenshot:(BOOL)screenshot;
+ (void)autoReportWithDescription:(NSString *)description;
+ (void)autoReport;
+ (void)stop;
@end

NS_ASSUME_NONNULL_END
