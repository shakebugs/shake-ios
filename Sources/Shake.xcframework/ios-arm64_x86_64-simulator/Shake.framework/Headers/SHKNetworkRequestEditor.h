//
//  SHKNetworkRequestEditor.h
//  Shake
//
//  Created by Vedran Ozir on 02/11/2020.
//  Copyright © 2020 DECODE HQ Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(NetworkRequestEditor)
@interface SHKNetworkRequestEditor : NSObject

@property (nonnull) NSString* method;
@property (nonnull) NSString* statusCode;
@property (nonnull) NSString* url;
@property (nullable) NSString* requestBody;
@property (nonnull) NSData* requestBodyAsDats;
@property (nullable) NSMutableDictionary<NSString*, NSString*>* requestHeaders;
@property (nullable) NSString* responseBody;
@property (nullable) NSData* responseBodyAsData;
@property (nullable) NSMutableDictionary<NSString*, NSString*>* responseHeaders;
@property (nonnull) NSString* timestamp;
@property (nullable) NSDate* date;
@property float duration;

- (instancetype)initWithUrl:(nonnull NSURL *)url request:(nullable NSURLRequest*)request response:(nullable NSURLResponse *)response;

@end

NS_ASSUME_NONNULL_END
