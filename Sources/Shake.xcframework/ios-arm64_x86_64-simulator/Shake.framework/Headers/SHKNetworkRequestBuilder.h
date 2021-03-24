//
//  SHKNetworkRequestBuilder.h
//  Shake
//
//  Created by Domagoj Kolaric on 11.02.2021..
//  Copyright © 2021 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NetworkRequestBuilder)
@interface SHKNetworkRequestBuilder : NSObject

@property (nonnull) NSString* method;
@property (nonnull) NSString* statusCode;
@property (nonnull) NSString* url;
@property (nullable) NSString* requestBody;
@property (nullable) NSMutableDictionary<NSString*, NSString*>* requestHeaders;
@property (nullable) NSString* responseBody;
@property (nullable) NSMutableDictionary<NSString*, NSString*>* responseHeaders;
@property (nonnull) NSDate* timestamp;
@property float duration;

-(instancetype)initWithUrl:(nonnull NSString*)url method:(nonnull NSString*)method statusCode:(nonnull NSString*)statusCode responseBody:(nullable NSString*)responseBody requestBody:(nullable NSString*)requestBody requestHeaders:(nullable NSMutableDictionary<NSString*, NSString*>*)requestHeaders responseHeaders:(nullable NSMutableDictionary<NSString*, NSString*>*)responseHeaders timestamp:(nonnull NSDate*)timestamp duration:(float)duration;
@end

NS_ASSUME_NONNULL_END
