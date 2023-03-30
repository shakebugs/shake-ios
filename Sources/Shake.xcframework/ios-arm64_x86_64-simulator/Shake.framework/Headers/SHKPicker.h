//
//  SHKPicker.h
//  Shake
//
//  Created by David Halapir on 01.03.2023..
//  Copyright © 2023 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHKPickerItem.h"
#import "SHKFormItemProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface SHKPicker : NSObject<SHKFormItemProtocol>

@property (readonly, strong) NSString * label;
@property (readonly, strong) NSArray<SHKPickerItem *> * items;
@property (readonly, strong, nullable) NSString * labelRes;

- (instancetype)initWithLabel:(NSString *)label items:(NSArray<SHKPickerItem *> *)items labelRes:(nullable NSString *)labelRes;

- (instancetype)init
__attribute__((unavailable("Use provided initializer")));

@end

NS_ASSUME_NONNULL_END
