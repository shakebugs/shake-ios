//
//  Copyright © 2020 Shake Technologies, Inc. All rights reserved.
//  https://www.shakebugs.com
//

#import <Foundation/Foundation.h>
#import "SHKShakeFile.h"
#import "SHKShakeConfiguration.h"
#import "SHKShakeReportConfiguration.h"
#import "SHKNetworkRequestEditor.h"
#import "SHKNotificationEventEditor.h"
#import "SHKNetworkRequestEditor.h"
#import "SHKSessionAuthenticationProtocol.h"
#import "SHKFeedbackEntry.h"

//! Project version number for Shake.
FOUNDATION_EXPORT double ShakeVersionNumber;

//! Project version string for Shake.
FOUNDATION_EXPORT const unsigned char ShakeVersionString[];

NS_SWIFT_NAME(Shake)
@interface SHKShake : NSObject

typedef NS_ENUM(NSUInteger, LogLevel) {
    LogLevelVerbose,
    LogLevelDebug,
    LogLevelInfo,
    LogLevelWarn,
    LogLevelError
};

///Shake bundle
@property (nonnull, class, readonly) NSBundle *bundle;

///Use this property to check if Shake has been started
@property (class, readonly) BOOL isStarted;

///Use this property to pause or resume Shake - ex. temporarely disable invocation and BlackBox/Activity History tracking.
@property (class) BOOL isPaused;


// MARK: - Configuration

/**
 Shake configuration object.
 */
@property (nonnull, class, readonly) SHKShakeConfiguration* configuration;

/**
 Starts the Shake with the provided client and secret. Also start the tracking and Shake features specified in the "configuration" object.
 */
+ (void)startWithClientId:(nonnull NSString *)clientId clientSecret:(nonnull NSString *)clientSecret
NS_SWIFT_NAME(start(clientId:clientSecret:));


/**
 Assign a callback function to this property to lazily attach additional files to each Shake report. This enables you to construct various
 files at the time of the report, keeping the data most relevant.
 */
@property (nullable, class, nonatomic) NSArray<SHKShakeFile *> *_Nonnull (^onPrepareReportData)(void);

// MARK: - Manual invocation

typedef NS_ENUM(NSUInteger, SHKShowOption) {
    SHKShowOptionHome = 1,
    SHKShowOptionNew
};

/**
 Triggers the display of Shake UI.
 */
+ (void)show;

/**
 Triggers the display of Shake UI with the provided option.
 Default option is SHKShowOptionNew.
 */
+ (void)show:(SHKShowOption)option;

// MARK: Silent Report

/**
 Constructs a silent report  and sends it silently without presenting any kind of UI to the user of your app.
 */
+ (void)silentReportWithDescription:(nullable NSString *)description fileAttachBlock:(NSArray<SHKShakeFile *> *_Nonnull (^ __nonnull)(void))fileAttachBlock reportConfiguration:(nonnull SHKShakeReportConfiguration *)reportConfiguration
NS_SWIFT_NAME(silentReport(description:fileAttachBlock:reportConfiguration:));


// MARK: Notifications

/**
 Assign a filter function to this property and Shake will call the function prior to inserting the notification record in database. This gives you a chance to remove or edit some specific
 notifications.
 */
@property (nullable, class) SHKNotificationEventEditor * _Nullable (^notificationEventsFilter)(SHKNotificationEventEditor * _Nonnull);

/**
 Manually register the received notification with Shake.
 */
+ (void)handleNotificationWithNotificationTitle:(NSString* __nonnull)notificationTitle notificationDescription:(NSString * __nonnull)notificationDescription;

// MARK: Logging

/**
 Adds a custom log entry to Activity History
 */
+ (void)logWithLevel:(LogLevel)level message:(NSString * __nonnull)message
NS_SWIFT_NAME(log(_:_:));

/** Adds a custom log entry to Activity History with debug level
 */
+ (void)logWithMessage:(NSString * __nonnull)message
NS_SWIFT_NAME(log(_:));

// MARK: Privacy

/// Adds private UIView/UIViewController  entry to Activity History
+ (void)addPrivateView:(nullable id)view;
+ (void)removePrivateView:(nullable id)view;

+ (void)addPrivateViewController:(nullable id)viewController;
+ (void)removePrivateViewController:(nullable id)viewController;

+ (void)clearPrivateViews;

// MARK: - Feedback type

+ (nonnull NSArray<SHKFeedbackEntry *> *)getFeedbackTypes;

+ (void)setFeedbackTypes:(nonnull NSArray<SHKFeedbackEntry *> *)types;

// MARK: - User

/**
 Registers the user of your application with Shake.
 Ideally, passed in userId should uniquely identify the user of your application in your database or system.
 */
+ (void)registerUserWithUserId:(nonnull NSString *)userId NS_SWIFT_NAME(registerUser(userId:));

/**
 Update the metadata of previously registered user. Metadata updates are merged (updated key values will overwrite the existing ones) so this method can safely
 be called with new key value pairs in separate contexts of your application.
 This method does nothing if there is no registered user.
 */
+ (void)updateUserMetadata:(nonnull NSDictionary<NSString *, id> *)metadata NS_SWIFT_NAME(updateUserMetadata(_:));

/**
 This method updates the previously registered user with the new userId. In most cases, this is never used but can be usefull if for example your
 internal user identifiers are user emails, which can be changed from the settings screen of your application.
 */
+ (void)updateUserId:(nonnull NSString *)userId NS_SWIFT_NAME(updateUserId(_:));

/**
 Unregisters the previously registered user from this device.
 */
+ (void)unregisterUser;


//MARK: - Network Request Reporting

/**
 Pass your NSURLSessionConfiguration to this method before  initializing your NSURLSession with the configuration.
 Later, use the same configuration to initialize the NSURLSession.
 */
+ (void)registerSessionConfiguration:(nonnull NSURLSessionConfiguration *)configuration
NS_SWIFT_NAME(registerSessionConfiguration(_:));

/**
 Shake assumes your  NSURLSession is already initialized with the configuration returned by calling registerSessionConfiguration method.
 Use this method if your app using any kind of authentication challenges with the server.
 Shake will pass down authentication challenges to this delegate.
 Auth delegate is not retained.
 */
+ (void)registerAuthDelegate:(nonnull id<SHKSessionAuthenticationProtocol>)authDelegate
NS_SWIFT_NAME(registerAuthDelegate(_:));

/**
 A network request filter that is called prior to registering request with Shake. Use this this to target and  remove/edit specific requests.
 */
@property (nullable, class) SHKNetworkRequestEditor * _Nullable (^networkRequestsFilter)(SHKNetworkRequestEditor * _Nonnull);

/**
 Manually register the network request with Shake. Use this when the standard setup is not suitable, or when using the
 custom NSURLProtocol in you application.
 */
+ (void)insertNetworkRequest:(nonnull SHKNetworkRequestEditor *)networkRequest
NS_SWIFT_NAME(insertNetworkRequest(_:));

// MARK: - Metadata

+ (void)setMetadataWithKey:(nonnull NSString *)key value:(nullable NSString *)value
NS_SWIFT_NAME(setMetadata(key:value:));


// MARK: - Caught Errors

/**
 Silently reports a non fatal error. Cluster ID affects dashboard grouping.
 */
+ (void)handleError:(nonnull NSError *)error clusterID:(nonnull NSString *)clusterID;

@end
