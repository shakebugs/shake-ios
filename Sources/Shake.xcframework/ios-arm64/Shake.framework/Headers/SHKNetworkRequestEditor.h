//
//  SHKNetworkRequestEditor.h
//  Shake
//
//  Created by Vedran Ozir on 02/11/2020.
//  Copyright © 2020 Shake Technologies, Inc. All rights reserved. 
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NetworkRequestEditor)
@interface SHKNetworkRequestEditor : NSObject

- (instancetype)initWith:(nonnull NSURLRequest *)request response:(nullable NSURLResponse *)response responseData:(nullable NSData *)data error:(nullable NSError *)error timestamp:(NSDate *)timestamp duration:(NSTimeInterval)duration;

@property (nonatomic, strong, nullable) NSString *method;
@property (nonatomic, strong, nullable) NSString *statusCode;
@property (nonatomic, strong, nonnull) NSURL *url;
@property (nonatomic, strong, nullable) NSData *requestBody;
@property (nonatomic, strong, nonnull)  NSMutableDictionary<NSString *,NSString *> *requestHeaders;
@property (nonatomic, strong, nullable) NSData *responseBody;
@property (nonatomic, strong, nullable)  NSMutableDictionary<NSString *,NSString *> *responseHeaders;
@property (nonatomic) NSTimeInterval duration;
@property (nonatomic, strong, nonnull) NSString *timestamp;
@property (nonatomic, strong, nullable) NSError *error;

@end

NS_ASSUME_NONNULL_END
