# Shake iOS SDK

Bug and crash reporting SDK for iOS apps. 

## Features 

 |     Feature     | Avaliable |
|:---------------:|:---------:|
|  Bug reporting  |     ✅     |
| Crash reporting |     ✅     |
|      Users      |     ✅     |

## Requirements 

- iOS 12.0+ 

## Install Shake

### Cocoapods

[![npm version](https://img.shields.io/cocoapods/v/Shake)](https://cocoapods.org/pods/Shake)

Not using CocoaPods yet? Follow their brief [installation guide](https://guides.cocoapods.org/using/getting-started.html#installation), then run `pod init` in the root of your project.  

Next, add Shake to your `Podfile`.

#### Objective-C
```objc
pod 'Shake'
```

#### Swift
```objc
use_frameworks! 
pod 'Shake'
```

Then, run the `pod install` command in your terminal.  

Since CocoaPods might not always download the latest version of an SDK when using `pod install`, it's recommended that you also run `pod update Shake` after the installation has completed, or whenever you'd like to update Shake.

### Swift Package Manager

Select `File > Swift Packages > Add Package Dependency`

Enter the Shake repository url when prompted:

```
https://github.com/shakebugs/shake-ios
```

Choose the appropriate cloning details and optionally specify the exact Shake version or branch.

Click `Finish` to add the Shake package to your project.

Note:
Shake is distributed as a binary framework. There is a [known issue](https://bugs.swift.org/browse/SR-13343) with SPM signing the binary packages which will pop up when running your app on the real device. The issue has been fixed in the Xcode Version 12.2 beta 3.

#### Temporary workaround

Select your app target, and add a new `Copy Files phase` to the `Build Phases`. Make sure to change the destination to `Frameworks` folder.
 ​
 Add a new `Run Script` phase and paste the following script to force the deep signing of frameworks with your own identity.
 
 ```
 find "${CODESIGNING_FOLDER_PATH}" -name '*.framework' -print0 | while read -d $'\0' framework 
 do 
     codesign --force --deep --sign "${EXPANDED_CODE_SIGN_IDENTITY}" --preserve-metadata=identifier,entitlements --timestamp=none "${framework}" 
 done
 ```

### Manually

Visit Shake iOS SDK GitHub repo, click the green Clone button and then Download ZIP. Shake directory will be downloaded to your computer — drag-and-drop the Shake.framework folder into your project. Then select Embed & Sign for Shake.framework in Xcode General tab; Frameworks, Libraries, and Embedded content (Xcode 11, Xcode 12).

Note:
By not using a dependency manager like CocoaPods, you won't be able to use the simple `pod update Shake` command to always pull the latest version of Shake SDK into your app. Instead, you will have to repeat the the first step described in the above paragraph.

## Initialize Shake
Initialize Shake in the `didFinishLaunchingWithOptions` callback of your *AppDelegate*.
Replace `your-api-client-id` and `your-api-client-secret` with the actual values you have in [your workspace settings](https://app.shakebugs.com/settings/workspace#general).

#### Objective-C
In your `AppDelegate.m`:
```objc
#import "AppDelegate.h"
@import Shake;

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [SHKShake startWithClientId:@"your-api-client-id" clientSecret:@"your-api-client-secret"];
    return YES;
}
@end
```

#### Swift
```swift
import UIKit
import Shake

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
  func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        Shake.start(clientId: "your-api-client-id", clientSecret: "your-api-client-secret")
        return true
  }
}
```

Note:
Some of the Shake features use swizzling, so to avoid any kind of swizzling conflicts, we recommend calling `Shake.start()` before initializing all other frameworks.

## Build and run
Select _Product > Run_ in the menu bar. This first run will automatically add your app to your [Shake Dashboard](https://app.shakebugs.com/) based on your app bundle ID.

## Resources
- [Official docs](https://www.shakebugs.com/docs/)
