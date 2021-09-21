//
// Created by Manuel Vrhovac on 25/05/2020.
// Copyright © 2020 Shake Technologies, Inc. All rights reserved.
//

/**
 Used to configure an individual report before submitting it, ex. leave out some data or display a toast on success
 */
NS_SWIFT_NAME(ShakeReportConfiguration)
@interface SHKShakeReportConfiguration : NSObject

@property (nonatomic, assign) BOOL includesBlackBoxData;
@property (nonatomic, assign) BOOL includesActivityHistoryData;
@property (nonatomic, assign) BOOL includesScreenshotImage;
@property (nonatomic, assign) BOOL showsToastMessageOnSend;

@end
