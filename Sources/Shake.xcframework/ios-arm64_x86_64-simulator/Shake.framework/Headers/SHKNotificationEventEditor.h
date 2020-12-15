//
//  SHKNotificationEventEditor.h
//  Shake
//
//  Created by Vedran Ozir on 03/11/2020.
//  Copyright © 2020 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NotificationEventEditor)
@interface SHKNotificationEventEditor : NSObject

@property (nonnull) NSString *title;
@property (nonnull) NSString *description;

-(instancetype)initWithTitle:(nonnull NSString *)title description:(nonnull NSString *)description;

@end

NS_ASSUME_NONNULL_END
