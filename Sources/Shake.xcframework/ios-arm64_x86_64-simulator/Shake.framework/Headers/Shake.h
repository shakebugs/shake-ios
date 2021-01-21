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
@property (nullable, class, nonatomic) SHKShakeReportData *_Nonnull (^onPrepareReportData)(SHKShakeReportData * _Nonnull reportData);

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

@end
