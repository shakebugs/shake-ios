//
//  ShakeReportData.h
//  Shake
//
//  Created by Ante Baus on 19/11/2018.
//  Copyright © 2018 Shake Technologies, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHKShakeFile.h"

NS_ASSUME_NONNULL_BEGIN

/// ShakeReportData is an object that you use to enrich the bug report with data like description and attached files.
NS_SWIFT_NAME(ShakeReportData)
@interface SHKShakeReportData : NSObject <NSCoding, NSSecureCoding>

-(instancetype)initWithBugDescription:(nullable NSString *)bugDescription attachedFiles:(nullable NSArray<SHKShakeFile *> *)attachedFiles;

@end

NS_ASSUME_NONNULL_END
