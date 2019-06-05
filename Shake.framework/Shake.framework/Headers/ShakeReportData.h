//
//  ShakeReportData.h
//  Shake
//
//  Created by Ante Baus on 19/11/2018.
//  Copyright © 2018 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ShakeFile.h"

NS_ASSUME_NONNULL_BEGIN
NS_SWIFT_NAME(ShakeReportData)
@interface SHKShakeReportData : NSObject <NSCoding, NSSecureCoding>
/**
 Additional data to be attached to the report.
 */
@property (nonatomic, strong, nullable) NSString *quickFacts;
/**
 Files to be uploaded with the report.
 */
@property (nonatomic, strong, nullable) NSArray <SHKShakeFile *> *attachedFiles;

@end

NS_ASSUME_NONNULL_END
