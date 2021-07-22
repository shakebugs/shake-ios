//
//  Copyright © 2020 Shake Technologies, Inc. All rights reserved.
//  https://www.shakebugs.com
//

#import <Foundation/Foundation.h>
#import "SHKShakeFile.h"
#import "SHKShakeConfiguration.h"
#import "SHKShakeReportConfiguration.h"
#import "SHKShakeReportData.h"
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

// MARK: - Properties

///Shake tracking, invoking and user interaction options
@property (nonnull, class, readonly) SHKShakeConfiguration* configuration;

///Add additional data and files to the report object provided by the block.
@property (nullable, class, nonatomic) NSArray<SHKShakeFile *> *_Nonnull (^onPrepareReportData)(void);

///Privacy - Network requests filter
@property (nullable, class) SHKNetworkRequestEditor * _Nullable (^networkRequestsFilter)(SHKNetworkRequestEditor * _Nonnull);

///Privacy - Notification event filter
@property (nullable, class) SHKNotificationEventEditor * _Nullable (^notificationEventsFilter)(SHKNotificationEventEditor * _Nonnull);

///Shake bundle
@property (nonnull, class, readonly) NSBundle *bundle;

///Use this property to check if Shake has been started
@property (class, readonly) BOOL isStarted;

///Use this property to pause or resume Shake - ex. temporarely disable invocation and BlackBox/Activity History tracking.
@property (class) BOOL isPaused;

// MARK: - Methods

/// Starts recording BlackBox and Activity History data. Enables invocation. Use '.isPaused' to pause or resume tracking.
+ (void)startWithClientId:(nonnull NSString *)clientId clientSecret:(nonnull NSString *)clientSecret
NS_SWIFT_NAME(start(clientId:clientSecret:));

/// Brings up Shake UI allowing user to send a new bug report
+ (void)show;

/// Adds a notifications log entry to Notifications
+ (void)handleNotificationWithNotificationTitle:(NSString* __nonnull)notificationTitle notificationDescription:(NSString * __nonnull)notificationDescription;

/// Brings up Shake UI with pre-populated report data (description, attachments etc.) allowing user to send a new bug report
+ (void)showWithReportData:(nonnull SHKShakeReportData *)reportData
NS_SWIFT_NAME(show(reportData:));

/// Send bug report to the server without displaying any user interface to the user. Use this to report certain state of the app.
+ (void)silentReportWithReportData:(nullable SHKShakeReportData *)reportData reportConfiguration:(nonnull SHKShakeReportConfiguration *)reportConfiguration
NS_SWIFT_NAME(silentReport(reportData:reportConfiguration:));

/// Adds a custom log entry to Activity History
+ (void)logWithLevel:(LogLevel)level message:(NSString * __nonnull)message
NS_SWIFT_NAME(log(_:_:));

/// Adds a custom log entry to Activity History with debug level
+ (void)logWithMessage:(NSString * __nonnull)message
NS_SWIFT_NAME(log(_:));

// MARK: Privacy

/// Adds private UIView/UIViewController  entry to Activity History
+ (void)addPrivateView:(nullable id)view;
+ (void)removePrivateView:(nullable id)view;

+ (void)addPrivateViewController:(nullable id)viewController;
+ (void)removePrivateViewController:(nullable id)viewController;

+ (void)clearPrivateViews;

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

+ (void)insertNetworkRequest:(nonnull SHKNetworkRequestEditor *)networkRequest
NS_SWIFT_NAME(insertNetworkRequest(_:));

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

// MARK: - Deprecated

+ (nonnull SHKShake *)sharedInstance
__attribute__((unavailable("Use 'Shake' class methods/properties instead")));

+ (void)setBlackBoxEnabled:(BOOL)isBlackBoxEnabled
__attribute__((unavailable("Use 'Shake.isBlackBoxEnabled' property instead")));

__attribute__((deprecated("Using ShakeInvocationEvent is deprecated. Use 'Shake.configuration' instead!")))
typedef NS_OPTIONS(NSUInteger, ShakeInvocationEvent) {
    ShakeInvocationEventShake = 1<<0,
    ShakeInvocationEventButton = 1<<1,
    ShakeInvocationEventScreenshot = 1<<2,
    ShakeInvocationEventManual = 1<<3
};

+ (void)startWithInvocationEvents:(ShakeInvocationEvent)invocationEvents
__attribute__((unavailable("Use 'start' method instead. Use 'Shake.configuration' to change invocation methods.")));

@property (nullable, nonatomic, copy) SHKShakeReportData *_Nonnull (^onPrepareData)(SHKShakeReportData * _Nonnull reportData)
__attribute__((unavailable("Simply use 'Shake.onPrepareReportData' instead.")));

@property (nullable, class, nonatomic, copy) SHKShakeReportData *_Nonnull (^onPrepareData)(SHKShakeReportData * _Nonnull reportData)
__attribute__((unavailable("Use 'Shake.onPrepareReportData' instead.")));

+ (void)stop
__attribute__((unavailable("Use 'Shake.isPaused = true' instead.")));

/// Starts recording BlackBox and Activity History data. Enables invocation. Use '.isPaused' to pause or resume tracking.
+ (void)start
__attribute__((deprecated("Use start(clientId:clientSecret:) instead. Providing API credentials using Info.plist is deprecated.")));

+ (void)setMetadataWithKey:(nonnull NSString *)key value:(nullable NSString *)value
NS_SWIFT_NAME(setMetadata(key:value:));

/**
 Silently reports a non fatal error. Cluster ID affects dashboard grouping.
 */
+ (void)handleError:(nonnull NSError *)error clusterID:(nonnull NSString *)clusterID;

@end
