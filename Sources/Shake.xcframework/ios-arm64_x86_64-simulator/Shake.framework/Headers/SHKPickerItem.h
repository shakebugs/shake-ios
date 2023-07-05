//
//  SHKPickerItem.h
//  Shake
//
//  Created by David Halapir on 01.03.2023..
//  Copyright © 2023 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SHKPickerItem : NSObject

@property (readonly, strong, nullable) NSString * iconName;
@property (readonly, strong) NSString * text;

@property (readonly, strong, nullable) NSString * textRes;
@property (readonly, strong, nullable) NSString * tag;

- (instancetype)initWithIconName:(nullable NSString *)iconName text:(NSString *)text textRes:(NSString* _Nullable)textRes tag:(nullable NSString *)tag;

- (instancetype)init
__attribute__((unavailable("Use provided initializer")));

@end

NS_ASSUME_NONNULL_END
