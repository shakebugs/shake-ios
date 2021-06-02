//
//  SHKFeedbackEntry.h
//  Shake
//
//  Created by David Halapir on 10.05.2021..
//  Copyright © 2021 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/**
 Object encapsulating feedback tag metadata
 */
@interface SHKFeedbackEntry : NSObject
/**
 A tag sent to Shake servers
 */
@property (nonatomic, nonnull, strong) NSString* tag;

/**
 User facing feedback title.
*/
@property (nonatomic, nonnull, strong) NSString* title;

/**
 Feedback type icon
 */
@property (nonatomic, nonnull, strong) UIImage* icon;


/**
 Returns feedback entry. Title and tag must be valid, non-empty strings.
 Returns nil if the passed in params are not valid.

 Default entries tags are : [bug , improvement, suggestion]
 Attempt to create an entry with reserved tags will fail.
 */
+ (instancetype)entryWithTitle:(nonnull NSString *)title andTag:(nonnull NSString *)tag icon:(nullable UIImage *)icon;

@end

NS_ASSUME_NONNULL_END
